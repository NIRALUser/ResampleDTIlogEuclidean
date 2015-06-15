cmake_minimum_required(VERSION 2.8.9)

project(ResampleDTIlogEuclidean)

include( CTest )
include(ExternalData)

# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'Release' as none was specified.")
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

if( ResampleDTIlogEuclidean_BUILD_SLICER_EXTENSION )
  #-----------------------------------------------------------------------------
  # Extension meta-information
  set(EXTENSION_HOMEPAGE "http://www.slicer.org/slicerWiki/index.php/Documentation/Nightly/Extensions/ResampleDTIlogEuclidean")
  set(EXTENSION_CATEGORY "Diffusion")
  set(EXTENSION_CONTRIBUTORS "Francois Budin (UNC), Sylvain Bouix (PNL)")
  set(EXTENSION_DESCRIPTION "ResampleDTIlogEuclidean resamples Diffusion Tensor Images (DTI) in the log-euclidean framework. More information is available in the Insight Journal: http://www.insight-journal.org/browse/publication/742")
  set(EXTENSION_ICONURL "http://www.slicer.org/slicerWiki/images/1/13/ResampleDTIlogEuclidean-128x128-icon.png")
  set(EXTENSION_SCREENSHOTURLS "http://www.slicer.org/slicerWiki/images/4/41/ResampleDTI-Slice_extracted_from_a_real_Diffusion_Tensor_Image_-_No_transformation.png" "http://www.slicer.org/slicerWiki/images/8/87/ResampleDTI-Real_DTI_transformed_with_a_45deg_rotation_-_Linear_interpolation.png" "http://www.slicer.org/slicerWiki/images/1/14/ResampleDTI-Real_DTI_upscaled_with_a_factor_2_-_Linear_interpolation.png")

  #-----------------------------------------------------------------------------
  # Extension dependencies
  find_package(Slicer REQUIRED)
  include(${Slicer_USE_FILE})
  set(STATIC_RESAMPLEDTI OFF CACHE BOOL "Build static ResampleDTIlogEuclidean" FORCE )
endif()

#-----------------------------------------------------------------------------
# Extension modules
add_subdirectory(Source)

#-----------------------------------------------------------------------------
if( ResampleDTIlogEuclidean_BUILD_SLICER_EXTENSION )
  include(${Slicer_EXTENSION_CPACK})
endif()
