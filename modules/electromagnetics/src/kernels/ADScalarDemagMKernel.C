//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ADScalarDemagMKernel.h"

registerMooseObject("ElectromagneticsApp", ADScalarDemagMKernel);

InputParameters
ADScalarDemagMKernel::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addClassDescription(
      "Kernel representing the contribution of the PDE term $cfu$, where $c$ and $f$ are constant "
      "and function coefficients, respectively, and $u$ is a vector variable.");
  params.addParam<Real>("coeff", 10000.0, "Ms");
  params.addParam<Real>("component", 0, "The component to compute");
  params.addRequiredCoupledVar("v", "Coupled variable.");
  return params;
}

ADScalarDemagMKernel::ADScalarDemagMKernel(const InputParameters & parameters)
  : ADKernel(parameters),

    _coefficient(getParam<Real>("coeff")),

    _component(getParam<Real>("component")),

    _coupled_val(coupledValue("v"))
{
}

ADReal
ADScalarDemagMKernel::computeQpResidual()
{
  return (_coefficient * _coupled_val[_qp] - _grad_u[_qp](_component)) * _grad_test[_i][_qp](_component);
}