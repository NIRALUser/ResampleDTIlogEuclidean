/*=========================================================================

  Program:   Diffusion Applications
  Module:    $HeadURL: http://svn.slicer.org/Slicer4/trunk/Modules/CLI/ResampleDTIVolume/itkDiffusionTensor3DBSplineInterpolateImageFunction.txx $
  Language:  C++
  Date:      $Date: 2012-02-02 01:52:52 -0500 (Thu, 02 Feb 2012) $
  Version:   $Revision: 19197 $

  Copyright (c) Brigham and Women's Hospital (BWH) All Rights Reserved.

  See License.txt or http://www.slicer.org/copyright/copyright.txt for details.

==========================================================================*/
#ifndef __itkDiffusionTensor3DBSplineInterpolateImageFunction_txx
#define __itkDiffusionTensor3DBSplineInterpolateImageFunction_txx

#include "itkDiffusionTensor3DBSplineInterpolateImageFunction.h"

namespace itk
{

template <class TData, class TCoordRep>
DiffusionTensor3DBSplineInterpolateImageFunction<TData, TCoordRep>
::DiffusionTensor3DBSplineInterpolateImageFunction()
{
  m_SplineOrder = 1;
}

template <class TData, class TCoordRep>
void
DiffusionTensor3DBSplineInterpolateImageFunction<TData, TCoordRep>
::AllocateInterpolator()
{
  for( int i = 0; i < 6; i++ )
    {
    bSplineInterpolateFunction[i] = BSplineInterpolateFunction::New();
    bSplineInterpolateFunction[i]->SetSplineOrder( m_SplineOrder );
    this->m_Interpol[i] = bSplineInterpolateFunction[i];
    }
}

} // end itk namespace

#endif
