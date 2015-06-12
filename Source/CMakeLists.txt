project(ResampleDTIlogEuclidean)

cmake_minimum_required(VERSION 2.8.12)

find_package(SlicerExecutionModel REQUIRED)
include(${SlicerExecutionModel_USE_FILE})

set( ALL_IO
ITKIOBMP
ITKIOBioRad
ITKIOCSV
ITKIODCMTK
ITKIOGDCM
ITKIOGE
ITKIOGIPL
ITKIOHDF5
ITKIOIPL
ITKIOJPEG
ITKIOLSM
ITKIOMRC
ITKIOMesh
ITKIOMeta
ITKIONIFTI
ITKIOPNG
ITKIORAW
ITKIOSiemens
ITKIOSpatialObjects
ITKIOStimulate
ITKIOTIFF
ITKIOTransformHDF5
ITKIOTransformMatlab
ITKIOVTK
ITKIOXML
ITKIOMINC
MGHIO
)


find_package(ITK REQUIRED )
include(${ITK_USE_FILE})
list(APPEND LIST_ITK_IO_USED ITKIONRRD ITKIOTransformInsightLegacy)
foreach( io ${ALL_IO} )
  list( FIND ITK_MODULES_ENABLED ${io} position )
  if( ${position} GREATER -1 ) #not found: ${position}==-1
    list( APPEND LIST_ITK_IO_USED ${io} )
  endif()
endforeach()

set(ITKComponents
  ITKCommon
  ITKImageFunction
  ITKImageGrid
  ITKTransform
  ITKIOImageBase
  ITKIOTransformBase
  ${LIST_ITK_IO_USED}
  )

find_package(ITK COMPONENTS ${ITKComponents} REQUIRED )
if( ${ITK_VERSION_MAJOR} VERSION_LESS 4)
  message(FATAL_ERROR "ITKv4 is necessary to compile this tool")
endif()
set (MODULE_NAME ResampleDTIlogEuclidean)

Set( dtiProcessFiles
  dtiprocessFiles/deformationfieldio.h
  dtiprocessFiles/deformationfieldio.cxx
  dtiprocessFiles/itkHFieldToDeformationFieldImageFilter.h
  dtiprocessFiles/itkHFieldToDeformationFieldImageFilter.txx
  dtiprocessFiles/itkDeformationFieldToHFieldImageFilter.h
  dtiprocessFiles/itkDeformationFieldToHFieldImageFilter.txx
  )

option(STATIC_RESAMPLEDTI "Build static ResampleDTIlogEuclidean" ON)


if( ${STATIC_RESAMPLEDTI} )
  set( STATIC "EXECUTABLE_ONLY" )
endif()

SEMMacroBuildCLI(
  NAME ${MODULE_NAME}
  ${STATIC}
  ADDITIONAL_SRCS ${dtiProcessFiles}
  TARGET_LIBRARIES ${ITK_LIBRARIES}
  )
option(BUILD_TESTING "Build Testing" ON)
if(BUILD_TESTING)
  add_subdirectory(Testing)
endif(BUILD_TESTING)

