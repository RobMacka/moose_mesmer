//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "ADTimeKernel.h"

class ADImprovedAFM : public ADTimeKernel
{
public:
  static InputParameters validParams();

  ADImprovedAFM(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual();

  /// Gradient of the coupled variable
  const VariableValue & _m2;

  Real _A;
};
