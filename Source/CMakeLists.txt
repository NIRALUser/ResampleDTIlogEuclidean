project(ResampleDTIlogEuclidean)

cmake_minimum_required(VERSION 2.8.7)

find_package(GenerateCLP REQUIRED)
if(GenerateCLP_FOUND)
  include(${GenerateCLP_USE_FILE})
endif(GenerateCLP_FOUND)

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
)

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
include(${ITK_USE_FILE})
if( ${ITK_VERSION_MAJOR} VERSION_LESS 4)
  message(FATAL_ERROR "ITKv4 is necessary to compile this tool")
endif()
set (CLP ResampleDTI)

set ( ${CLP}_SOURCE ${CLP}.cxx )
generateclp(${CLP}_SOURCE ${CLP}.xml ${LOGOFILE})

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
  add_library(${CLP}logEuclideanLib STATIC ${${CLP}_SOURCE} ${dtiProcessFiles} )
else( ${STATIC_RESAMPLEDTI} )
  add_library(${CLP}logEuclideanLib SHARED ${${CLP}_SOURCE} ${dtiProcessFiles} )
endif()
if(Slicer3_SOURCE_DIR)
  slicer3_set_plugins_output_path(${CLP}logEuclideanLib)
endif(Slicer3_SOURCE_DIR)
set_target_properties (${CLP}logEuclideanLib PROPERTIES COMPILE_FLAGS "-Dmain=ModuleEntryPoint")
target_link_libraries (${CLP}logEuclideanLib
  ModuleDescriptionParser
  ${ITK_LIBRARIES}
)


add_executable(${CLP}logEuclidean ResampleDTIApp.cxx)
target_link_libraries (${CLP}logEuclidean ${CLP}logEuclideanLib)
if( NOT ${STATIC_RESAMPLEDTI} )
  set_target_properties(${CLP}logEuclidean PROPERTIES COMPILE_FLAGS "-DBUILD_SHARED_LIBS") # definition of the variable for c++ preprocessor
endif()

if(BUILD_TESTING)
  add_subdirectory(Testing)
endif(BUILD_TESTING)

if( NOT DEFINED RUNTIME_DESTINATION )
  set( RUNTIME_DESTINATION bin)
endif()
if( NOT DEFINED LIBRARY_DESTINATION )
  set( LIBRARY_DESTINATION lib)
endif()
install( TARGETS ${CLP}logEuclidean RUNTIME DESTINATION ${RUNTIME_DESTINATION} )
if( NOT ${STATIC_RESAMPLEDTI} )
  install( TARGETS ${CLP}logEuclideanLib LIBRARY DESTINATION ${LIBRARY_DESTINATION} )
endif()
