#
# Test executable
#


include( CTest )




# ResampleDTI tests
set(SOURCE_DIRECTORY ${ResampleDTIIJ_SOURCE_DIR}/Source/Testing/TestData )
set(TEMP_DIR ${ResampleDTIIJ_BINARY_DIR}/Testing/Temporary )

set(ResampleTest ${ResampleDTIIJ_BINARY_DIR}/bin/${CLP}logEuclideanTest )
set(TransformedImage ${TEMP_DIR}/dt-helix-transformed.nrrd )
set(OriginalImage ${SOURCE_DIRECTORY}/dt-helix.nrrd )

add_executable(${CLP}logEuclideanTest ${CLP}Test.cxx)
target_link_libraries(${CLP}logEuclideanTest ${CLP}logEuclideanLib)

set(TransformFile ${SOURCE_DIRECTORY}/rotation.tfm )
set(TransformedImage1 ${TEMP_DIR}/dt-helix-transformed1.nrrd )
set(ReferenceImageRotationNN ${SOURCE_DIRECTORY}/dt-helix-ref-Rotated.nrrd)
add_test(${CLP}logEuclideanRotationNNTest ${ResampleTest}
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
add_test(${CLP}logEuclidean2RigidTransformsLinearTest ${ResampleTest}
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
add_test(${CLP}logEuclideanBSplineWSInterpolationTest ${ResampleTest}
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
add_test(${CLP}logEuclideanBSplineInterpolationTest ${ResampleTest}
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
add_test(${CLP}logEuclideanHFieldTest ${ResampleTest}
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
add_test(${CLP}logEuclideanLogTest ${ResampleTest}
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

add_test( itkTestMainExtendedScalarTest ${ResampleTest}
 --compare
   ${BinaryScalarFile}
   ${BinaryScalarFile}
  ModuleEntryPoint
    --interpolation nn
    ${OriginalImage}
    ${TransformedImage}
  )

set(TransformedImage6 ${TEMP_DIR}/dt-helix-transformed6.nrrd )
add_test(itkTestMainExtendedFailedTest ${ResampleTest}
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
