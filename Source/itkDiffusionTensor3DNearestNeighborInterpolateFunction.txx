/*=========================================================================

  Program:   Diffusion Applications
  Module:    $HeadURL: http://svn.slicer.org/Slicer4/trunk/Modules/CLI/ResampleDTIVolume/itkDiffusionTensor3DNearestNeighborInterpolateFunction.txx $
  Language:  C++
  Date:      $Date: 2012-02-02 01:52:52 -0500 (Thu, 02 Feb 2012) $
  Version:   $Revision: 19197 $

  Copyright (c) Brigham and Women's Hospital (BWH) All Rights Reserved.

  See License.txt or http://www.slicer.org/copyright/copyright.txt for details.

==========================================================================*/
#ifndef __itkDiffusionTensor3DNearestNeighborInterpolateFunction_txx
#define __itkDiffusionTensor3DNearestNeighborInterpolateFunction_txx

#include "itkDiffusionTensor3DNearestNeighborInterpolateFunction.h"

namespace itk
{

template <class TData, class TCoordRep>
typename DiffusionTensor3DNearestNeighborInterpolateFunction<TData, TCoordRep>
::TensorDataType
DiffusionTensor3DNearestNeighborInterpolateFunction<TData, TCoordRep>
::EvaluateAtContinuousIndex( const ContinuousIndexType & index ) const
// ::Evaluate( const PointType &point )
{
  if( this->m_Image.IsNotNull() )
    {
    typename DiffusionImageType::IndexType pixelIndex;
    this->ConvertContinuousIndexToNearestIndex( index, pixelIndex );
    return this->m_Image->GetPixel( pixelIndex );
    }
  else
    {
    itkExceptionMacro( << " No InputImage set" );
    }
}

} // end namespace itk

#endif
