//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "AuxKernel.h"

class ScalarMagNrg : public AuxKernel
{
public:
  static InputParameters validParams();

  ScalarMagNrg(const InputParameters & parameters);

protected:
  virtual Real computeValue() override;

  Real _coeff;

  Real _Ms;

  const VariableValue & _coupled_mx;

  const VariableValue & _coupled_my;

  const VariableValue & _coupled_mz;

  const VariableValue & _coupled_Hx;

  const VariableValue & _coupled_Hy;

  const VariableValue & _coupled_Hz;

  Real _mu0;

};
