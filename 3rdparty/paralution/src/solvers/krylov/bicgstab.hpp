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

#ifndef PARALUTION_KRYLOV_BICGSTAB_HPP_
#define PARALUTION_KRYLOV_BICGSTAB_HPP_

#include "../solver.hpp"

#include <vector>

namespace paralution {

template <class OperatorType, class VectorType, typename ValueType>
class BiCGStab : public IterativeLinearSolver<OperatorType, VectorType, ValueType> {
  
public:

  BiCGStab();
  virtual ~BiCGStab();

  virtual void Print(void) const;

  virtual void Build(void);
  virtual void Clear(void);

protected:

  virtual void SolveNonPrecond_(const VectorType &rhs,
                                VectorType *x);
  virtual void SolvePrecond_(const VectorType &rhs,
                             VectorType *x);

  virtual void PrintStart_(void) const;
  virtual void PrintEnd_(void) const;

  virtual void MoveToHostLocalData_(void);
  virtual void MoveToAcceleratorLocalData_(void);

private:

  VectorType r_, z_, q_;
  VectorType p_, v_, r0_, s_, t_;

};


}

#endif // PARALUTION_KRYLOV_BICGSTAB_HPP_

