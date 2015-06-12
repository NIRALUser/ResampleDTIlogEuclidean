/*=========================================================================

  Program:   Diffusion Applications
  Module:    $HeadURL: http://svn.slicer.org/Slicer4/trunk/Modules/CLI/ResampleDTIVolume/itkDiffusionTensor3DLinearInterpolateFunction.txx $
  Language:  C++
  Date:      $Date: 2012-02-02 01:52:52 -0500 (Thu, 02 Feb 2012) $
  Version:   $Revision: 19197 $

  Copyright (c) Brigham and Women's Hospital (BWH) All Rights Reserved.

  See License.txt or http://www.slicer.org/copyright/copyright.txt for details.

==========================================================================*/
#ifndef __itkDiffusionTensor3DLinearInterpolateFunction_txx
#define __itkDiffusionTensor3DLinearInterpolateFunction_txx

#include "itkDiffusionTensor3DLinearInterpolateFunction.h"

namespace itk
{

template <class TData, class TCoordRep>
void
DiffusionTensor3DLinearInterpolateFunction<TData, TCoordRep>
::AllocateInterpolator()
{
  for( int i = 0; i < 6; i++ )
    {
    linearInterpolator[i] = LinearInterpolateImageFunctionType::New();
    this->m_Interpol[i] = linearInterpolator[i];
    }
}

} // end itk namespace

#endif
