//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "AuxKernel.h"

class BScalarCalculator; 

class BScalarCalculator : public AuxKernel
{
public:
  static InputParameters validParams();

  BScalarCalculator(const InputParameters & parameters);

protected:
  virtual Real computeValue() override;

  Real _coefficient;

  const VariableValue & _coupled_m;

  const VariableValue & _coupled_H;
};
