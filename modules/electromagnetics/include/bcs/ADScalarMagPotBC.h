//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "ADIntegratedBC.h"

class ADScalarMagPotBC : public ADIntegratedBC
{
public:
  static InputParameters validParams();

  ADScalarMagPotBC(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

private:
  Real _sign;

  Real _coefficient;

  Real _component;

  const ADVariableValue & _coupled_val;
};
