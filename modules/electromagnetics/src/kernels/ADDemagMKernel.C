//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ADDemagMKernel.h"

registerMooseObject("ElectromagneticsApp", ADDemagMKernel);

InputParameters
ADDemagMKernel::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addClassDescription(
      "Kernel representing the contribution of the PDE term $cfu$, where $c$ and $f$ are constant "
      "and function coefficients, respectively, and $u$ is a vector variable.");
  params.addParam<Real>("coeff", 1.0, "Coefficient multiplier for field.");
  params.addRequiredCoupledVar("coupled", "Coupled vector variable.");
  return params;
}

ADDemagMKernel::ADDemagMKernel(const InputParameters & parameters)
  : ADKernel(parameters),

    _coefficient(getParam<Real>("coeff")),

    _coupled_val(adCoupledVectorValue("coupled"))
{
}

ADReal
ADDemagMKernel::computeQpResidual()
{
  return (_coefficient * _coupled_val[_qp] - _grad_u[_qp]) * _grad_test[_i][_qp];
}