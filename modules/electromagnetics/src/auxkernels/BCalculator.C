//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "BCalculator.h"

registerMooseObject("ElectromagneticsApp", BCalculator);

InputParameters
BCalculator::validParams()
{
  InputParameters params = VectorAuxKernel::validParams();
  params.addClassDescription(
      "Kernel representing the contribution of the PDE term $cfu$, where $c$ and $f$ are constant "
      "and function coefficients, respectively, and $u$ is a vector variable.");
  params.addParam<Real>("coeff", 1.0, "Coefficient multiplier for field.");
  params.addRequiredCoupledVar("mag", "Coupled vector variable.");
  params.addRequiredCoupledVar("field", "Coupled vector variable.");
  return params;
}

BCalculator::BCalculator(const InputParameters & parameters)
  : VectorAuxKernel(parameters),

    _coefficient(getParam<Real>("coeff")),

    _coupled_m(coupledVectorValue("mag")),

    _coupled_H(coupledVectorValue("field"))
{
}

RealVectorValue
BCalculator::computeValue()
{
  return (_coupled_H[_qp] + (_coefficient * _coupled_m[_qp]));
}