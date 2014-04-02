project(ResampleDTIlogEuclidean)

cmake_minimum_required(VERSION 2.8.7)

find_package(GenerateCLP REQUIRED)
if(GenerateCLP_FOUND)
  include(${GenerateCLP_USE_FILE})
endif(GenerateCLP_FOUND)

find_package(ITK REQUIRED )
include(${ITK_USE_FILE})


if( ${ITK_VERSION_MAJOR} VERSION_LESS 4)
  message(FATAL_ERROR "ITKv4 is necessary to compile this tool")
endif()

set (CLP ResampleDTI)
if (Slicer3_SOURCE_DIR)
   set(LOGOFILE ${Slicer3_SOURCE_DIR}/Resources/NAMICLogo.h)
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
  if( NOT ${ITKV3_COMPATIBILITY} )
    message(FATAL_ERROR "ITKV3_COMPATIBILITY set to ON is necessary to compile the tests")
  endif()
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
