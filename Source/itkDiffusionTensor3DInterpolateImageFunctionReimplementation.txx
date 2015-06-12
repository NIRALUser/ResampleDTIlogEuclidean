/*=========================================================================

  Program:   Diffusion Applications
  Module:    $HeadURL: http://svn.slicer.org/Slicer4/trunk/Modules/CLI/ResampleDTIVolume/itkDiffusionTensor3DInterpolateImageFunctionReimplementation.txx $
  Language:  C++
  Date:      $Date: 2012-02-02 01:52:52 -0500 (Thu, 02 Feb 2012) $
  Version:   $Revision: 19197 $

  Copyright (c) Brigham and Women's Hospital (BWH) All Rights Reserved.

  See License.txt or http://www.slicer.org/copyright/copyright.txt for details.

==========================================================================*/
#ifndef __DiffusionTensor3DInterpolateImageFunctionReimplementation_txx
#define __DiffusionTensor3DInterpolateImageFunctionReimplementation_txx

#include "itkDiffusionTensor3DInterpolateImageFunctionReimplementation.h"

namespace itk
{

template <class TData, class TCoordRep>
DiffusionTensor3DInterpolateImageFunctionReimplementation<TData, TCoordRep>
::DiffusionTensor3DInterpolateImageFunctionReimplementation()
{
  m_NumberOfThreads = 0;
}

template <class TData, class TCoordRep>
void
DiffusionTensor3DInterpolateImageFunctionReimplementation<TData, TCoordRep>
::SetInputImage( const DiffusionImageType *inputImage )
{
  DiffusionTensor3DInterpolateImageFunction<DataType>::SetInputImage( inputImage );   // separateFilter->GetOutput( 0 )
                                                                                      // ) ;
  if( !inputImage )
    {
    return;
    }
  typedef SeparateComponentsOfADiffusionTensorImage<TData, TData> SeparateType;
  typename SeparateType::Pointer separateFilter = SeparateType::New();
  separateFilter->SetInput( inputImage );
  separateFilter->SetNumberOfThreads( this->m_NumberOfThreads );
  separateFilter->Update();
  AllocateInterpolator();
  for( int i = 0; i < 6; i++ )
    {
    m_Interpol[i]->SetInputImage( separateFilter->GetOutput( i ) );
    }

  // this->m_Image = separateFilter->GetOutput( 0 ) ;
}

template <class TData, class TCoordRep>
typename DiffusionTensor3DInterpolateImageFunctionReimplementation<TData, TCoordRep>
::TensorDataType
DiffusionTensor3DInterpolateImageFunctionReimplementation<TData, TCoordRep>
::EvaluateAtContinuousIndex( const ContinuousIndexType & index ) const
// ::Evaluate( const PointType &point )
{
  if( this->m_Image.IsNotNull() ) // If input image has been set
    {
    TensorDataType pixelValue;
    for( int i = 0; i < 6; i++ )
      {
      pixelValue[i] = ( DataType ) m_Interpol[i]->EvaluateAtContinuousIndex( index );
      }
    return pixelValue;
    }
  else
    {
    itkExceptionMacro( << "No InputImage Set" );
    }
}

} // end itk namespace

#endif
