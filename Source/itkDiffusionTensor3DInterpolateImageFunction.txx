/*=========================================================================

  Program:   Diffusion Applications
  Module:    $HeadURL: http://svn.slicer.org/Slicer4/trunk/Modules/CLI/ResampleDTIVolume/itkDiffusionTensor3DInterpolateImageFunction.txx $
  Language:  C++
  Date:      $Date: 2012-02-02 01:52:52 -0500 (Thu, 02 Feb 2012) $
  Version:   $Revision: 19197 $

  Copyright (c) Brigham and Women's Hospital (BWH) All Rights Reserved.

  See License.txt or http://www.slicer.org/copyright/copyright.txt for details.

==========================================================================*/
#ifndef __itkDiffusionTensor3DInterpolateImageFunction_txx
#define __itkDiffusionTensor3DInterpolateImageFunction_txx

#include "itkDiffusionTensor3DInterpolateImageFunction.h"

namespace itk
{

template <class TData, class TCoordRep>
DiffusionTensor3DInterpolateImageFunction<TData, TCoordRep>
::DiffusionTensor3DInterpolateImageFunction()
{
//  m_InputImage = 0 ;
  latestTime = 0;
//  SetDefaultPixelValue( ITK_DIFFUSION_TENSOR_3D_ZERO ) ;
}

/*
template< class TData >
void
DiffusionTensor3DInterpolateImageFunction< TData >
::SetDefaultPixelValue( TensorRealType defaultPixelValue )
{
  m_DefaultPixelValue = defaultPixelValue ;
  m_DefaultPixel.SetIdentity() ;
  for( unsigned int i = 0 ; i < 3 ; i++ )
    {
    m_DefaultPixel( i , i ) *= static_cast< TData >( this->m_DefaultPixelValue ) ;
    }
}
*/

} // end namespace itk

#endif
