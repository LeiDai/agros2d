// *************************************************************************
//
//    PARALUTION   www.paralution.com
//
//    Copyright (C) 2012-2013 Dimitar Lukarski
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// *************************************************************************

#ifndef PARALUTION_BASE_VECTOR_HPP_
#define PARALUTION_BASE_VECTOR_HPP_

#include "backend_manager.hpp"

namespace paralution {


// Forward declarations
template <typename ValueType>
class HostVector;

template <typename ValueType>
class AcceleratorVector;

template <typename ValueType>
class GPUAcceleratorVector;

template <typename ValueType>
class OCLAcceleratorVector;


/// Base class for all host/accelerator vectors
template <typename ValueType>
class BaseVector {
  
public:

  BaseVector();
  virtual ~BaseVector();

  /// Shows info about the object
  virtual void info(void) const = 0;

  /// Returns the size of the vector
  inline int get_size(void) const { return this->size_; }
  
  /// Copy the backend descriptor information
  void set_backend(const Paralution_Backend_Descriptor local_backend);

  /// Allocate a local vector with name and size
  virtual void Allocate(const int n) = 0;

  /// Initialize a vector with externally allocated data
  virtual void SetDataPtr(ValueType **ptr, const int size) = 0;
  /// Get a pointer from the vector data and free the vector object
  virtual void LeaveDataPtr(ValueType **ptr) = 0;


  /// Clear (free) the vector
  virtual void Clear(void) = 0;
  /// Set the values of the vector to zero 
  virtual void Zeros(void) = 0;
  /// Set the values of the vector to one
  virtual void Ones(void) = 0;
  /// Set the values of the vector to given argument
  virtual void SetValues(const ValueType val) = 0;

  /// Perform inplace permutation (forward) of the vector
  virtual void Permute(const BaseVector<int> &permutation) = 0;
  /// Perform inplace permutation (backward) of the vector
  virtual void PermuteBackward(const BaseVector<int> &permutation) = 0;

  /// Copy values from another vector
  virtual void CopyFrom(const BaseVector<ValueType> &vec) = 0;
  /// Copy values from another (float) vector
  virtual void CopyFromFloat(const BaseVector<float> &vec);
  /// Copy values from another (double) vector
  virtual void CopyFromDouble(const BaseVector<double> &vec);
  /// Copy values to another vector
  virtual void CopyTo(BaseVector<ValueType> *vec) const = 0;
  /// Copy data (not entire vector) from another vector with specified 
  /// src/dst offsets and size
  virtual void CopyFrom(const BaseVector<ValueType> &src,
                        const int src_offset,
                        const int dst_offset,
                        const int size) = 0;

  /// Copy a vector under specified permutation (forward permutation)
  virtual void CopyFromPermute(const BaseVector<ValueType> &src,
                               const BaseVector<int> &permutation) = 0;
  /// Copy a vector under specified permutation (backward permutation)
  virtual void CopyFromPermuteBackward(const BaseVector<ValueType> &src,
                                       const BaseVector<int> &permutation) = 0;

  /// Restriction operator based on restriction mapping vector
  virtual bool Restriction(const BaseVector<ValueType> &vec_fine, const BaseVector<int> &map);

  /// Prolongation operator based on restriction(!) mapping vector
  virtual bool Prolongation(const BaseVector<ValueType> &vec_coarse, const BaseVector<int> &map);

  /// Perform vector update of type this = this + alpha*x
  virtual void AddScale(const BaseVector<ValueType> &x, const ValueType alpha) = 0;
  /// Perform vector update of type this = alpha*this + x
  virtual void ScaleAdd(const ValueType alpha, const BaseVector<ValueType> &x) = 0;
  /// Perform vector update of type this = alpha*this + x*beta
  virtual void ScaleAddScale(const ValueType alpha, const BaseVector<ValueType> &x, 
                             const ValueType beta) = 0;
  /// Perform vector update of type this = alpha*this + x*beta + y*gamma
  virtual void ScaleAdd2(const ValueType alpha, const BaseVector<ValueType> &x, 
                         const ValueType beta, const BaseVector<ValueType> &y, 
                         const ValueType gamma) = 0;
  /// Perform vector scaling this = alpha*this
  virtual void Scale(const ValueType alpha) = 0;
  /// Compute partial sum
  virtual void PartialSum(const BaseVector<ValueType> &x) = 0;
  /// Compute dot (scalar) product, return this^T y
  virtual ValueType Dot(const BaseVector<ValueType> &x) const = 0;
  /// Compute L2 norm of the vector, return =  srqt(this^T this)
  virtual ValueType Norm(void) const = 0;
  /// Reduce vector
  virtual ValueType Reduce(void) const = 0;
  /// Perform point-wise multiplication (element-wise) of type this = this * x
  virtual void PointWiseMult(const BaseVector<ValueType> &x) = 0;
  /// Perform point-wise multiplication (element-wise) of type this = x*y
  virtual void PointWiseMult(const BaseVector<ValueType> &x, const BaseVector<ValueType> &y) = 0;


protected:

  /// The size of the vector
  int size_;

  /// Backend descriptor (local copy)
  Paralution_Backend_Descriptor local_backend_;
 
};



template <typename ValueType>
class AcceleratorVector : public BaseVector<ValueType> {
  
public:

  AcceleratorVector();
  virtual ~AcceleratorVector();

  /// Copy (accelerator vector) from host vector
  virtual void CopyFromHost(const HostVector<ValueType> &src) = 0;
  /// Copy (host vector) from accelerator vector
  virtual void CopyToHost(HostVector<ValueType> *dst) const = 0;

};


};

#endif // PARALUTION_BASE_VECTOR_HPP_