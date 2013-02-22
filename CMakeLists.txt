cmake_minimum_required(VERSION 2.8)
cmake_policy(VERSION 2.8)

include(${CMAKE_SOURCE_DIR}/IJMacros.txt)

#Change PROJECT_NAME to the name of your project
project(ResampleDTIIJ)

#The following lines are required to use Dart
enable_testing()
include(Dart)


set( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${ResampleDTIIJ_BINARY_DIR}/bin" )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY "${ResampleDTIIJ_BINARY_DIR}/bin" )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${ResampleDTIIJ_BINARY_DIR}/bin" )


#Declare any external dependencies that your project may have here.
#examples include: ITK, VTK, JPEG, PNG, OpenGL, ZLIB, Perl, Java
#If you're not sure what name to use, look in the Modules directory of your
#cmake install and check that a file named Find(Package).cmake exists
#
# The packages can be specified with a version number, for example:
#
# ITK 2.8.1
# ITK 3.2.0
#
# If no version is specified, the most recent release of the package
# will be used.
#We have to first load ITK
set(Required_Packages
ITK
)

#this foreach loads all of the packages that you specified as required.
#It shouldn't need to be modified.
foreach(Package ${Required_Packages})
  LOADPACKAGE(${Package})
endforeach(Package)

option(BUILD_GENERATECLP "Build GenerateCLP" ON)
if( ${BUILD_GENERATECLP} )
  #Then we compile GenerateCLP et al
  set( GENERATECLPDIR_DIR ${CMAKE_SOURCE_DIR}/GenerateCLPDirectory )
  set( GENERATECLPBIN_DIR ${CMAKE_BINARY_DIR}/GenerateCLPDirectory )
  try_compile(RESULT_VAR ${GENERATECLPBIN_DIR}/tclap ${GENERATECLPDIR_DIR}/tclap
    tclap)
  if(WIN32)
    try_compile(RESULT_VAR ${GENERATECLPBIN_DIR}/ModuleDescriptionParser ${GENERATECLPDIR_DIR}/ModuleDescriptionParser
      ModuleDescriptionParser CMAKE_FLAGS -DITK_DIR=${ITK_DIR} -DBUILD_SHARED_LIBS:BOOL=OFF )
    try_compile(RESULT_VAR ${GENERATECLPBIN_DIR}/GenerateCLP ${GENERATECLPDIR_DIR}/GenerateCLP
      GenerateCLP CMAKE_FLAGS -DModuleDescriptionParser_DIR=${GENERATECLPBIN_DIR}/ModuleDescriptionParser
      -DTCLAP_DIR=${GENERATECLPBIN_DIR}/tclap -DBUILD_SHARED_LIBS:BOOL=OFF )
  else(WIN32)
    try_compile(RESULT_VAR ${GENERATECLPBIN_DIR}/ModuleDescriptionParser ${GENERATECLPDIR_DIR}/ModuleDescriptionParser
      ModuleDescriptionParser CMAKE_FLAGS -DITK_DIR=${ITK_DIR} )
    try_compile(RESULT_VAR ${GENERATECLPBIN_DIR}/GenerateCLP ${GENERATECLPDIR_DIR}/GenerateCLP
      GenerateCLP CMAKE_FLAGS -DModuleDescriptionParser_DIR=${GENERATECLPBIN_DIR}/ModuleDescriptionParser
      -DTCLAP_DIR=${GENERATECLPBIN_DIR}/tclap )
  endif(WIN32)
  #And finally we load GenerateCLP
  set(GenerateCLP_DIR ${GENERATECLPBIN_DIR}/GenerateCLP)
  LOADPACKAGE( GenerateCLP )
endif()




#Set any libraries that your project depends on.
#examples: ITKCommon, VTKRendering, etc
set(Libraries
  ModuleDescriptionParser
  ITKIO
  ITKAlgorithms
  ITKBasicFilters
)

#the following block of code is an example of how to build an executable in
#cmake.  Unmodified, it will add an executable called "MyExe" to the project.
#MyExe will be built using the files MyClass.h and MyClass.cxx, and it will
#be linked to all the libraries you specified above.
#You can build more than one executable per project
#set(CurrentExe "ImageCompare")
#add_executable(${CurrentExe} ImageCompare.cxx)
#target_link_libraries(${CurrentExe} ${Libraries})
#set(CurrentExe "ImageCopy")
#add_executable(${CurrentExe} ImageCopy.cxx)
#target_link_libraries(${CurrentExe} ${Libraries})

set (CLP ResampleDTI)
add_subdirectory(Source)


#the following line is an example of how to add a test to your project.
#Testname is the title for this particular test.  ExecutableToRun is the
#program which will be running this test.  It can either be a part of this
#project or an external executable.  After that list any args that are needed
#for this test.  Include as many tests as you like.  If your project doesn't have
#any tests you can comment out or delete the following line.
#add_test(CreateImage ImageCopy ${CMAKE_SOURCE_DIR}/img1.png)
#add_test(CompareImage ImageCompare ${CMAKE_SOURCE_DIR}/img1.png ${CMAKE_SOURCE_DIR}/img1.png.base.png)

#Once you're done modifying this template, you should rename it to "CMakeLists.txt"

