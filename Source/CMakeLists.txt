
#-----------------------------------------------------------------------------
set(MODULE_NAME ResampleDTIlogEuclidean)

#-----------------------------------------------------------------------------

#
# SlicerExecutionModel
#
find_package(SlicerExecutionModel REQUIRED)
include(${SlicerExecutionModel_USE_FILE})

#
# ITK
#
set(ALL_IO
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
  MGHIO
  )

find_package(ITK REQUIRED )
list(APPEND LIST_ITK_IO_USED ITKIONRRD ITKIOTransformInsightLegacy)
foreach(io ${ALL_IO})
  list(FIND ITK_MODULES_ENABLED ${io} position)
  if(${position} GREATER -1) #not found: ${position}==-1
    list(APPEND LIST_ITK_IO_USED ${io})
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
if(${ITK_VERSION_MAJOR} VERSION_LESS 4)
  message(FATAL_ERROR "ITKv4 is required to compile this tool")
endif()

#-----------------------------------------------------------------------------
set(MODULE_SRCS
  dtiprocessFiles/deformationfieldio.h
  dtiprocessFiles/deformationfieldio.cxx
  dtiprocessFiles/itkHFieldToDeformationFieldImageFilter.h
  dtiprocessFiles/itkHFieldToDeformationFieldImageFilter.txx
  dtiprocessFiles/itkDeformationFieldToHFieldImageFilter.h
  dtiprocessFiles/itkDeformationFieldToHFieldImageFilter.txx
  )

set(MODULE_TARGET_LIBRARIES
  ${ITK_LIBRARIES}
  )

#-----------------------------------------------------------------------------
set(executable_only_option)
if(${ResampleDTIlogEuclidean_STATIC_RESAMPLEDTI})
  set(executable_only_option "EXECUTABLE_ONLY")
endif()

#-----------------------------------------------------------------------------
SEMMacroBuildCLI(
  NAME ${MODULE_NAME}
  ${executable_only_option}
  ADDITIONAL_SRCS ${MODULE_SRCS}
  TARGET_LIBRARIES ${MODULE_TARGET_LIBRARIES}
  )

export(TARGETS ${MODULE_NAME} FILE ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}-exports.cmake)

#-----------------------------------------------------------------------------
option(BUILD_TESTING "Build Testing" ON)
if(BUILD_TESTING)
  add_subdirectory(Testing)
endif()

