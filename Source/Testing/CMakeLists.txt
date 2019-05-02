

# Add standard remote object stores to user's
# configuration.
list(APPEND ExternalData_URL_TEMPLATES
  "http://slicer.kitware.com/midas3/api/rest?method=midas.bitstream.download&checksum=%(hash)"
  )

#-----------------------------------------------------------------------------
set(ExternalData_DIRECTORY TestData)
set(SOURCE_DIRECTORY ${ResampleDTIlogEuclidean_SOURCE_DIR}/Source/Testing/TestData)
set(TEMP_DIR ${ResampleDTIlogEuclidean_BINARY_DIR}/Testing/Temporary )
set(TransformedImage ${TEMP_DIR}/dt-helix-transformed.nrrd)
set(OriginalImage DATA{${ExternalData_DIRECTORY}/dt-helix.nrrd})

#-----------------------------------------------------------------------------
configure_file(
  itkTestMainExtendedConfigure.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/itkTestMainExtendedConfigure.h
  )
add_executable(${CLP}Test ${CLP}Test.cxx)
target_link_libraries(${CLP}Test ${CLP}Lib ${SlicerExecutionModel_EXTRA_EXECUTABLE_TARGET_LIBRARIES})
set_target_properties(${CLP}Test PROPERTIES LABELS ${CLP})
#set_target_properties(${CLP}Test PROPERTIES FOLDER ${${CLP}_TARGETS_FOLDER})

#-----------------------------------------------------------------------------
set(TransformFile ${SOURCE_DIRECTORY}/rotation.tfm)
set(TransformedImage1 ${TEMP_DIR}/dt-helix-transformed1.nrrd)
set(ReferenceImageRotationNN DATA{${ExternalData_DIRECTORY}/dt-helix-ref-Rotated.nrrd})
ExternalData_add_test(${CLP}Data NAME ${CLP}RotationNNTest COMMAND ${SEM_LAUNCH_COMMAND} $<TARGET_FILE:${CLP}Test>
  --compare
    ${ReferenceImageRotationNN}
    ${TransformedImage1}
  --compareIntensityTolerance 0
  ModuleEntryPoint
    -f ${TransformFile}
    --interpolation nn
    -c
    ${OriginalImage}
    ${TransformedImage1}
    -n 8
    --correction zero
    --nolog
  )

#-----------------------------------------------------------------------------
set(TransformedImage2 ${TEMP_DIR}/dt-helix-transformed2.nrrd)
set(ReferenceImageRotationAndAffine DATA{${ExternalData_DIRECTORY}/dt-helix-ref-RotationAndAffine.nrrd})
set(RotationAndAffineFile ${SOURCE_DIRECTORY}/rotationAndAffine.tfm)
ExternalData_add_test(${CLP}Data NAME ${CLP}2RigidTransformsLinearTest COMMAND ${SEM_LAUNCH_COMMAND} $<TARGET_FILE:${CLP}Test>
  --compare
    ${ReferenceImageRotationAndAffine}
    ${TransformedImage2}
  --compareIntensityTolerance 0
  ModuleEntryPoint
    -f ${RotationAndAffineFile}
    -T FS
    --interpolation linear
    -c
    ${OriginalImage}
    ${TransformedImage2}
    --correction abs
    -n 8
    --nolog
  )

#-----------------------------------------------------------------------------
set(TransformedImage3 ${TEMP_DIR}/dt-helix-transformed3.nrrd)
set(ReferenceImageBSplineWS DATA{${ExternalData_DIRECTORY}/dt-helix-ref-BS.nrrd})
set(BSplineFile ${SOURCE_DIRECTORY}/FastNonrigidBSplineregistrationTransform.tfm)
ExternalData_add_test(${CLP}Data NAME ${CLP}BSplineWSInterpolationTest COMMAND ${SEM_LAUNCH_COMMAND} $<TARGET_FILE:${CLP}Test>
  --compare
    ${ReferenceImageBSplineWS}
    ${TransformedImage3}
  --compareIntensityTolerance 0
  --compareNumberOfPixelsTolerance 1
  ModuleEntryPoint
    -f ${BSplineFile}
    --interpolation ws
    ${OriginalImage}
    ${TransformedImage3}
    --correction nearest
    -n 8
    --nolog
  )

#-----------------------------------------------------------------------------
set(TransformedImage4 ${TEMP_DIR}/dt-helix-transformed4.nrrd)
set(ReferenceImageBSplineInterpolation DATA{${ExternalData_DIRECTORY}/dt-helix-ref-BSInterpolation.nrrd})
set(AffineFile ${SOURCE_DIRECTORY}/affine.tfm)
ExternalData_add_test(${CLP}Data NAME ${CLP}BSplineInterpolationTest COMMAND ${SEM_LAUNCH_COMMAND} $<TARGET_FILE:${CLP}Test>
  --compare
    ${ReferenceImageBSplineInterpolation}
    ${TransformedImage4}
  --compareIntensityTolerance 0
  --compareNumberOfPixelsTolerance 1
  ModuleEntryPoint
    -f ${AffineFile}
    --interpolation bs
    ${OriginalImage}
    ${TransformedImage4}
    --correction none
    -o 3
    --nolog
  )

#-----------------------------------------------------------------------------
set(TransformedImage5 ${TEMP_DIR}/dt-helix-transformed5.nrrd)
set(ReferenceImageHField DATA{${ExternalData_DIRECTORY}/dt-helix-ref-HField.nrrd})
set(HFieldFile DATA{${ExternalData_DIRECTORY}/deformationField.nrrd})
ExternalData_add_test(${CLP}Data NAME ${CLP}HFieldTest COMMAND ${SEM_LAUNCH_COMMAND} $<TARGET_FILE:${CLP}Test>
  --compare
    ${ReferenceImageHField}
    ${TransformedImage5}
  --compareIntensityTolerance 0
  ModuleEntryPoint
    -H ${HFieldFile}
    ${OriginalImage}
    ${TransformedImage5}
    -n 8
    --correction zero
    --nolog
  )

#-----------------------------------------------------------------------------
set(TransformedImage7 ${TEMP_DIR}/dt-helix-transformed7.nrrd)
set(ReferenceImageLog DATA{${ExternalData_DIRECTORY}/dt-helix-ref-Log.nrrd})
set(AffineFile ${SOURCE_DIRECTORY}/affine.tfm)
ExternalData_add_test(${CLP}Data NAME ${CLP}LogTest COMMAND ${SEM_LAUNCH_COMMAND} $<TARGET_FILE:${CLP}Test>
  --compare
    ${ReferenceImageLog}
    ${TransformedImage7}
  --compareIntensityTolerance 0
  --compareNumberOfPixelsTolerance 1
  ModuleEntryPoint
    -f ${AffineFile}
    ${OriginalImage}
    ${TransformedImage7}
  )

#-----------------------------------------------------------------------------
#Test itkTestMainExtended.h
#copy scalar file to binary directory
set(SourceScalarFile DATA{${ExternalData_DIRECTORY}/AddTest_DOUBLE.mha})

ExternalData_add_test(${CLP}Data NAME itkTestMainExtendedScalarTest COMMAND ${SEM_LAUNCH_COMMAND} $<TARGET_FILE:${CLP}Test>
 --compare
   ${SourceScalarFile}
   ${SourceScalarFile}
  ModuleEntryPoint
    --interpolation nn
    ${OriginalImage}
    ${TransformedImage}
  )

#-----------------------------------------------------------------------------
set(TransformedImage6 ${TEMP_DIR}/dt-helix-transformed6.nrrd)
ExternalData_add_test(${CLP}Data NAME itkTestMainExtendedFailedTest COMMAND ${SEM_LAUNCH_COMMAND} $<TARGET_FILE:${CLP}Test>
  --compare
    ${ReferenceImageHField}
    ${TransformedImage6}
  --compareIntensityTolerance 0
  ModuleEntryPoint
    --interpolation nn
    ${OriginalImage}
    ${TransformedImage6}
  )
set_tests_properties(itkTestMainExtendedFailedTest PROPERTIES WILL_FAIL true)

#-----------------------------------------------------------------------------
set(ReferenceConcatenatedDisplacementField DATA{${ExternalData_DIRECTORY}/ReferenceConcatenatedDisplacementField.nrrd})
set(ConcatDisplacementField ${TEMP_DIR}/ConcatenatedDisplacementField.nrrd)
set(DummyTransformedImage ${TEMP_DIR}/dt-helix-transformed8-dummy.nrrd)
set(HFieldFile DATA{${ExternalData_DIRECTORY}/deformationField.nrrd})
set(ScalarInput DATA{${ExternalData_DIRECTORY}/dt-helix-fa.nrrd})
ExternalData_add_test(${CLP}Data NAME ${CLP}HFieldConcatOnlyTest COMMAND ${SEM_LAUNCH_COMMAND} $<TARGET_FILE:${CLP}Test>
  --compare
    ${ConcatDisplacementField}
    ${ReferenceConcatenatedDisplacementField}
  --compareIntensityTolerance 0
  ModuleEntryPoint
    -H ${HFieldFile}
    ${ScalarInput}
    ${DummyTransformedImage}
    -n 8
    --concatenationOnly
    --hfieldtype h-Field
    -R ${OriginalImage}
    --outputDisplacementField ${ConcatDisplacementField}
  )

#-----------------------------------------------------------------------------
ExternalData_add_test(${CLP}Data NAME ${CLP}HFieldConcatFailedNoConcatenationOnlyTest COMMAND ${SEM_LAUNCH_COMMAND} $<TARGET_FILE:${CLP}>
    -H ${HFieldFile}
    ${ScalarInput}
    ${DummyTransformedImage}
    -n 8
    --hfieldtype h-Field
    -R ${OriginalImage}
    --outputDisplacementField ${ConcatDisplacementField}
  )
set_tests_properties(${CLP}HFieldConcatFailedNoConcatenationOnlyTest PROPERTIES WILL_FAIL true)

#-----------------------------------------------------------------------------
ExternalData_add_test(${CLP}Data NAME ${CLP}HFieldConcatFailedNoReferenceImageTest COMMAND ${SEM_LAUNCH_COMMAND} $<TARGET_FILE:${CLP}>
    -H ${HFieldFile}
    ${ScalarInput}
    ${DummyTransformedImage}
    -n 8
    --concatenationOnly
    --hfieldtype h-Field
    --outputDisplacementField ${ConcatDisplacementField}
  )
set_tests_properties(${CLP}HFieldConcatFailedNoReferenceImageTest PROPERTIES WILL_FAIL true)

ExternalData_add_target(${CLP}Data)

