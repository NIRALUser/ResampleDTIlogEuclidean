find_package( ITK )
if( ITK_FOUND )
  include(${ITK_USE_FILE})
else( ITK_FOUND )
  message( FATAL_ERROR "Cannot build without ITK" )
endif( ITK_FOUND )

find_package(GenerateCLP NO_MODULE REQUIRED)
if(GenerateCLP_FOUND)
  include(${GenerateCLP_USE_FILE})
endif(GenerateCLP_FOUND)

set( CLPEXAMPLE1_SOURCE CLPExample1.cxx )
GENERATECLP(CLPEXAMPLE1_SOURCE CLPExample1.xml)
add_executable( CLPExample1 ${CLPEXAMPLE1_SOURCE})
target_link_libraries( CLPExample1 ITKEXPAT)

set( POINTEXAMPLE1_SOURCE PointExample1.cxx )
GENERATECLP(POINTEXAMPLE1_SOURCE PointExample1.xml)
add_executable( PointExample1 ${POINTEXAMPLE1_SOURCE})
target_link_libraries( PointExample1 ITKEXPAT)

set( SLICER3EXAMPLE_SOURCE Slicer3Example.cxx )
GENERATECLP(SLICER3EXAMPLE_SOURCE Slicer3Example.xml)
add_executable( Slicer3Example ${SLICER3EXAMPLE_SOURCE})
target_link_libraries( Slicer3Example)

add_test(Slicer3CLPExample1 ${EXECUTABLE_OUTPUT_PATH}/Slicer3Example --help)
add_test(Slicer3CLPExample2 ${EXECUTABLE_OUTPUT_PATH}/Slicer3Example --echo --load_freesurfer_volume FSV --stereo)
add_test(Slicer3CLPExample3 ${EXECUTABLE_OUTPUT_PATH}/Slicer3Example)


