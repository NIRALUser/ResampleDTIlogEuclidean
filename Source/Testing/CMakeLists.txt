#
# Test executable
#


include( CTest )




# ResampleDTI tests
set(SOURCE_DIRECTORY ${ResampleDTIIJ_SOURCE_DIR}/Source/Testing/TestData )
set(TEMP_DIR ${ResampleDTIIJ_BINARY_DIR}/Testing/Temporary )

#set(ResampleTest ${ResampleDTIIJ_BINARY_DIR}/bin/${CLP}logEuclideanTest )
set(TransformedImage ${TEMP_DIR}/dt-helix-transformed.nrrd )
set(OriginalImage ${SOURCE_DIRECTORY}/dt-helix.nrrd )

add_executable(${CLP}logEuclideanTest ${CLP}Test.cxx)
target_link_libraries(${CLP}logEuclideanTest ${CLP}logEuclideanLib)

set(TransformFile ${SOURCE_DIRECTORY}/rotation.tfm )
set(TransformedImage1 ${TEMP_DIR}/dt-helix-transformed1.nrrd )
set(ReferenceImageRotationNN ${SOURCE_DIRECTORY}/dt-helix-ref-Rotated.nrrd)
add_test(NAME ${CLP}logEuclideanRotationNNTest COMMAND $<TARGET_FILE:${CLP}logEuclideanTest>
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

set(TransformedImage2 ${TEMP_DIR}/dt-helix-transformed2.nrrd )
set(ReferenceImageRotationAndAffine ${SOURCE_DIRECTORY}/dt-helix-ref-RotationAndAffine.nrrd)
set(RotationAndAffineFile ${SOURCE_DIRECTORY}/rotationAndAffine.tfm )
add_test( NAME ${CLP}logEuclidean2RigidTransformsLinearTest COMMAND $<TARGET_FILE:${CLP}logEuclideanTest>
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

set(TransformedImage3 ${TEMP_DIR}/dt-helix-transformed3.nrrd )
set(ReferenceImageBSplineWS ${SOURCE_DIRECTORY}/dt-helix-ref-BS.nrrd)
set(BSplineFile ${SOURCE_DIRECTORY}/FastNonrigidBSplineregistrationTransform.tfm)
add_test( NAME ${CLP}logEuclideanBSplineWSInterpolationTest COMMAND $<TARGET_FILE:${CLP}logEuclideanTest>
  --compare
    ${ReferenceImageBSplineWS}
    ${TransformedImage3}
  --compareIntensityTolerance 0
  ModuleEntryPoint
    -f ${BSplineFile}
    --interpolation ws
    ${OriginalImage}
    ${TransformedImage3}
    --correction nearest
    -n 8
    --nolog
  )

set(TransformedImage4 ${TEMP_DIR}/dt-helix-transformed4.nrrd )
set(ReferenceImageBSplineInterpolation ${SOURCE_DIRECTORY}/dt-helix-ref-BSInterpolation.nrrd)
set(AffineFile ${SOURCE_DIRECTORY}/affine.tfm)
add_test( NAME ${CLP}logEuclideanBSplineInterpolationTest COMMAND $<TARGET_FILE:${CLP}logEuclideanTest>
  --compare
    ${ReferenceImageBSplineInterpolation}
    ${TransformedImage4}
  --compareIntensityTolerance 0
  ModuleEntryPoint
    -f ${AffineFile}
    --interpolation bs
    ${OriginalImage}
    ${TransformedImage4}
    --correction none
    -o 3
    --nolog
  )

set(TransformedImage5 ${TEMP_DIR}/dt-helix-transformed5.nrrd )
set(ReferenceImageHField ${SOURCE_DIRECTORY}/dt-helix-ref-HField.nrrd)
set(HFieldFile ${SOURCE_DIRECTORY}/deformationField.nrrd)
add_test( NAME ${CLP}logEuclideanHFieldTest COMMAND $<TARGET_FILE:${CLP}logEuclideanTest>
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

set(TransformedImage7 ${TEMP_DIR}/dt-helix-transformed7.nrrd )
set(ReferenceImageLog ${SOURCE_DIRECTORY}/dt-helix-ref-Log.nrrd)
set(AffineFile ${SOURCE_DIRECTORY}/affine.tfm)
add_test(NAME ${CLP}logEuclideanLogTest COMMAND $<TARGET_FILE:${CLP}logEuclideanTest>
  --compare
    ${ReferenceImageLog}
    ${TransformedImage7}
  --compareIntensityTolerance 0
  ModuleEntryPoint
    -f ${AffineFile}
    ${OriginalImage}
    ${TransformedImage7}
  )



#Test itkTestMainExtended.h
#copy scalar file to binary directory
set(SourceScalarFile ${SOURCE_DIRECTORY}/AddTest_DOUBLE.mha )
file( COPY ${SourceScalarFile} DESTINATION ${TEMP_DIR} )
set( BinaryScalarFile ${TEMP_DIR}/AddTest_DOUBLE.mha )

add_test( NAME itkTestMainExtendedScalarTest COMMAND $<TARGET_FILE:${CLP}logEuclideanTest>
 --compare
   ${BinaryScalarFile}
   ${BinaryScalarFile}
  ModuleEntryPoint
    --interpolation nn
    ${OriginalImage}
    ${TransformedImage}
  )

set(TransformedImage6 ${TEMP_DIR}/dt-helix-transformed6.nrrd )
add_test( NAME itkTestMainExtendedFailedTest COMMAND $<TARGET_FILE:${CLP}logEuclideanTest>
  --compare
    ${ReferenceImageHField}
    ${TransformedImage6}
  --compareIntensityTolerance 0
  ModuleEntryPoint
    --interpolation nn
    ${OriginalImage}
    ${TransformedImage6}
  )
set_tests_properties( itkTestMainExtendedFailedTest PROPERTIES WILL_FAIL true)




set(ReferenceConcatenatedDisplacementField ${SOURCE_DIRECTORY}/ReferenceConcatenatedDisplacementField.nrrd)
set(ConcatDisplacementField ${TEMP_DIR}/ConcatenatedDisplacementField.nrrd )
set(DummyTransformedImage ${TEMP_DIR}/dt-helix-transformed8-dummy.nrrd )
set(HFieldFile ${SOURCE_DIRECTORY}/deformationField.nrrd)
set(ScalarInput ${SOURCE_DIRECTORY}/dt-helix-fa.nrrd)
add_test( NAME ${CLP}logEuclideanHFieldConcatOnlyTest COMMAND $<TARGET_FILE:${CLP}logEuclideanTest>
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

add_test(NAME ${CLP}logEuclideanHFieldConcatFailedNoConcatenationOnlyTest COMMAND $<TARGET_FILE:${CLP}logEuclidean>
    -H ${HFieldFile}
    ${ScalarInput}
    ${DummyTransformedImage}
    -n 8
    --hfieldtype h-Field
    -R ${OriginalImage}
    --outputDisplacementField ${ConcatDisplacementField}
  )
set_tests_properties(${CLP}logEuclideanHFieldConcatFailedNoConcatenationOnlyTest PROPERTIES WILL_FAIL true)

add_test(NAME ${CLP}logEuclideanHFieldConcatFailedNoReferenceImageTest COMMAND ${CLP}logEuclidean
    -H ${HFieldFile}
    ${ScalarInput}
    ${DummyTransformedImage}
    -n 8
    --concatenationOnly
    --hfieldtype h-Field
    --outputDisplacementField ${ConcatDisplacementField}
  )
set_tests_properties(${CLP}logEuclideanHFieldConcatFailedNoReferenceImageTest PROPERTIES WILL_FAIL true)








