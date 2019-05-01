/*=========================================================================

  Program:   Diffusion Applications
  Module:    $HeadURL: http://svn.slicer.org/Slicer4/trunk/Modules/CLI/ResampleDTIVolume/itkDiffusionTensor3DLinearInterpolateFunction.h $
  Language:  C++
  Date:      $Date: 2012-02-02 01:52:52 -0500 (Thu, 02 Feb 2012) $
  Version:   $Revision: 19197 $

  Copyright (c) Brigham and Women's Hospital (BWH) All Rights Reserved.

  See License.txt or http://www.slicer.org/copyright/copyright.txt for details.

==========================================================================*/
#ifndef __itkDiffusionTensor3DLinearInterpolateFunction_h
#define __itkDiffusionTensor3DLinearInterpolateFunction_h

#include "itkDiffusionTensor3DInterpolateImageFunctionReimplementation.h"
#include <itkLinearInterpolateImageFunction.h>

namespace itk
{
/** \class DiffusionTensor3DInterpolateImageFunctionReimplementation
 *
 * Blockwise linear interpolation for diffusion tensor images
 */
template <class TData, class TCoordRep = double>
class DiffusionTensor3DLinearInterpolateFunction :
  public DiffusionTensor3DInterpolateImageFunctionReimplementation<TData, TCoordRep>
{
public:
  typedef TData                                                                          DataType;
  typedef DiffusionTensor3DLinearInterpolateFunction                                     Self;
  typedef DiffusionTensor3DInterpolateImageFunctionReimplementation<DataType, TCoordRep> Superclass;
  typedef typename Superclass::ImageType                                                 ImageType;
  typedef SmartPointer<Self>                                                             Pointer;
  typedef SmartPointer<const Self>                                                       ConstPointer;
  typedef LinearInterpolateImageFunction<ImageType,
                                         TCoordRep>                           LinearInterpolateImageFunctionType;

  /** Run-time type information (and related methods). */
  itkTypeMacro(DiffusionTensor3DLinearInterpolateFunction, DiffusionTensor3DInterpolateImageFunctionReimplementation);

  itkNewMacro(Self);
protected:
  void AllocateInterpolator();

  typename LinearInterpolateImageFunctionType::Pointer linearInterpolator[6];
};

} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkDiffusionTensor3DLinearInterpolateFunction.txx"
#endif

#endif
