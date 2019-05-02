cmake_minimum_required(VERSION 3.10.2)

project(ResampleDTIlogEuclidean)

include(CTest)
include(ExternalData)

#-----------------------------------------------------------------------------
# Set a default build type if none was specified
#-----------------------------------------------------------------------------
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'Release' as none was specified.")
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

#-----------------------------------------------------------------------------
# Extension meta-information
#-----------------------------------------------------------------------------
set(EXTENSION_HOMEPAGE "http://www.slicer.org/slicerWiki/index.php/Documentation/Nightly/Extensions/ResampleDTIlogEuclidean")
set(EXTENSION_CATEGORY "Diffusion")
set(EXTENSION_CONTRIBUTORS "Francois Budin (UNC), Sylvain Bouix (PNL)")
set(EXTENSION_DESCRIPTION "ResampleDTIlogEuclidean resamples Diffusion Tensor Images (DTI) in the log-euclidean framework. More information is available in the Insight Journal: http://www.insight-journal.org/browse/publication/742")
set(EXTENSION_ICONURL "http://www.slicer.org/slicerWiki/images/1/13/ResampleDTIlogEuclidean-128x128-icon.png")
set(EXTENSION_SCREENSHOTURLS "http://www.slicer.org/slicerWiki/images/4/41/ResampleDTI-Slice_extracted_from_a_real_Diffusion_Tensor_Image_-_No_transformation.png" "http://www.slicer.org/slicerWiki/images/8/87/ResampleDTI-Real_DTI_transformed_with_a_45deg_rotation_-_Linear_interpolation.png" "http://www.slicer.org/slicerWiki/images/1/14/ResampleDTI-Real_DTI_upscaled_with_a_factor_2_-_Linear_interpolation.png")

#-----------------------------------------------------------------------------
# Standalone vs Slicer extension option
#-----------------------------------------------------------------------------

# This option should be named after the project name, it corresponds to the
# option set to ON when the project is build by the Slicer Extension build
# system.

set(_default OFF)
set(_reason "${PROJECT_NAME}_BUILD_SLICER_EXTENSION is ON")
if(NOT DEFINED ${PROJECT_NAME}_BUILD_SLICER_EXTENSION AND DEFINED Slicer_DIR)
  set(_default ON)
  set(_reason "Slicer_DIR is SET")
endif()

option(${PROJECT_NAME}_BUILD_SLICER_EXTENSION "Build as a Slicer Extension" ${_default})

set(_msg "Checking if building as a Slicer extension")
message(STATUS ${_msg})
if(${PROJECT_NAME}_BUILD_SLICER_EXTENSION)
  message(STATUS "${_msg} - yes (${_reason})")
else()
  message(STATUS "${_msg} - no (${PROJECT_NAME}_BUILD_SLICER_EXTENSION is OFF)")
endif()

#-----------------------------------------------------------------------------
# Extension dependencies
#-----------------------------------------------------------------------------
if(ResampleDTIlogEuclidean_BUILD_SLICER_EXTENSION)
  find_package(Slicer REQUIRED)
  include(${Slicer_USE_FILE})
endif()

#-----------------------------------------------------------------------------
# Build option(s)
#-----------------------------------------------------------------------------
set(_default ON)
if(ResampleDTIlogEuclidean_BUILD_SLICER_EXTENSION)
  set(_default OFF)
endif()
option(ResampleDTIlogEuclidean_STATIC_RESAMPLEDTI "Build static ResampleDTIlogEuclidean" ${_default})

#-----------------------------------------------------------------------------
# Extension modules
add_subdirectory(Source)

#-----------------------------------------------------------------------------
if(ResampleDTIlogEuclidean_BUILD_SLICER_EXTENSION)
  include(${Slicer_EXTENSION_CPACK})
endif()
