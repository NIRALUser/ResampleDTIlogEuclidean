/*=========================================================================

  Program:   Diffusion Applications
  Module:    $HeadURL: http://svn.slicer.org/Slicer3/trunk/Applications/CLI/DiffusionApplications/ResampleDTI/itkDiffusionTensor3DNearestNeighborInterpolateFunction.h $
  Language:  C++
  Date:      $Date: 2010-04-29 11:58:49 -0400 (Thu, 29 Apr 2010) $
  Version:   $Revision: 13073 $

  Copyright (c) Brigham and Women's Hospital (BWH) All Rights Reserved.

  See License.txt or http://www.slicer.org/copyright/copyright.txt for details.

==========================================================================*/
#ifndef __itkDiffusionTensor3DNearestNeighborInterpolateFunction_h
#define __itkDiffusionTensor3DNearestNeighborInterpolateFunction_h


#include "itkDiffusionTensor3DInterpolateImageFunction.h"



namespace itk
{

/** \class DiffusionTensor3DInterpolateImageFunction
 * 
 * Implementation of the nearest neighborhood interpolation for diffusion tensor images
 */

template< class TData , class TCoordRep = double >
class DiffusionTensor3DNearestNeighborInterpolateFunction :
  public DiffusionTensor3DInterpolateImageFunction< TData , TCoordRep >
{
public:
  typedef TData DataType ;
  typedef DiffusionTensor3DNearestNeighborInterpolateFunction Self ;
  typedef DiffusionTensor3DInterpolateImageFunction< DataType > Superclass ;
  typedef typename Superclass::TensorDataType TensorDataType ;
  typedef typename Superclass::DiffusionImageType DiffusionImageType ;
  typedef typename Superclass::PointType PointType ;
  typedef SmartPointer< Self > Pointer ;
  typedef SmartPointer< const Self > ConstPointer ;
  typedef ImageFunction< DiffusionImageType , DataType , double > ImageFunctionType ;
  typedef typename Superclass::ContinuousIndexType ContinuousIndexType;
  itkNewMacro( Self ) ;
  ///Evaluate the value of a tensor at a given position
//  TensorDataType Evaluate( const PointType &point ) ;
  TensorDataType EvaluateAtContinuousIndex( const ContinuousIndexType & index ) const ;
protected:
};

}//end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkDiffusionTensor3DNearestNeighborInterpolateFunction.hxx"
#endif

#endif
