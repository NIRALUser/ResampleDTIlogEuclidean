project(ResampleDTIlogEuclidean)

cmake_policy(SET CMP0012 NEW)

find_package(GenerateCLP REQUIRED)
if(GenerateCLP_FOUND)
  include(${GenerateCLP_USE_FILE})
endif(GenerateCLP_FOUND)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


set (CLP ResampleDTI)
if (Slicer3_SOURCE_DIR)
   SET(LOGOFILE ${Slicer3_SOURCE_DIR}/Resources/NAMICLogo.h)
endif (Slicer3_SOURCE_DIR)

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

add_library(${CLP}logEuclideanLib SHARED ${${CLP}_SOURCE} ${dtiProcessFiles} )
if(Slicer3_SOURCE_DIR)
  slicer3_set_plugins_output_path(${CLP}logEuclideanLib)
endif(Slicer3_SOURCE_DIR)
set_target_properties (${CLP}logEuclideanLib PROPERTIES COMPILE_FLAGS "-Dmain=ModuleEntryPoint")
target_link_libraries (${CLP}logEuclideanLib
  ModuleDescriptionParser
  ITKIO
  ITKAlgorithms
  ITKBasicFilters
)

if( NOT ${ITK_USE_OPTIMIZED_REGISTRATION_METHODS} )
  message(WARNING "ITK has been compiled with ITK_USE_OPTIMIZED_REGISTRATION_METHODS set to OFF. The test  'ResampleDTIBSplineInterpolationTest' will fail if this option is OFF. Please recompile ITK with this option set to ON to pass successfully all the tests.")
endif( NOT ${ITK_USE_OPTIMIZED_REGISTRATION_METHODS} )


option(STATIC_RESAMPLEDTI "Build static ResampleDTIlogEuclidean" ON)

IF( ${STATIC_RESAMPLEDTI} )
  add_executable(${CLP}logEuclidean ${${CLP}_SOURCE} ${dtiProcessFiles} )
  target_link_libraries (${CLP}logEuclidean 
    ModuleDescriptionParser
    ITKIO
    ITKAlgorithms
    ITKBasicFilters
    )
ELSE( ${STATIC_RESAMPLEDTI} )
  add_executable(${CLP}logEuclidean ResampleDTIApp.cxx)
  target_link_libraries (${CLP}logEuclidean ${CLP}logEuclideanLib)
ENDIF( ${STATIC_RESAMPLEDTI} )
if(Slicer3_SOURCE_DIR)
  slicer3_set_plugins_output_path(${CLP}logEuclidean)
endif(Slicer3_SOURCE_DIR)


if (Slicer3_SOURCE_DIR)
  # install each target in the production area (where it would appear in an
  # installation) and install each target in the developer area (for running
  # from a build)
  set(TARGETS
    ${CLP}logEuclidean
    ${CLP}logEuclideanLib
    )
  slicer3_install_plugins(${TARGETS})

endif (Slicer3_SOURCE_DIR)

if(BUILD_TESTING)
  ADD_SUBDIRECTORY(Testing)
endif(BUILD_TESTING)
