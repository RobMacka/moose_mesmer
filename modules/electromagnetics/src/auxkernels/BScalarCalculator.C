//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "BScalarCalculator.h"

registerMooseObject("ElectromagneticsApp", BScalarCalculator);

InputParameters
BScalarCalculator::validParams()
{
  InputParameters params = AuxKernel::validParams();
  params.addClassDescription(
      "Kernel representing the contribution of the PDE term $cfu$, where $c$ and $f$ are constant "
      "and function coefficients, respectively, and $u$ is a vector variable.");
  params.addParam<Real>("coeff", 10000, "Ms");
  params.addRequiredCoupledVar("mag", "Coupled variable.");
  params.addRequiredCoupledVar("field", "Coupled variable.");
  return params;
}

BScalarCalculator::BScalarCalculator(const InputParameters & parameters)
  : AuxKernel(parameters),

    _coefficient(getParam<Real>("coeff")),

    _coupled_m(coupledValue("mag")),

    _coupled_H(coupledValue("field"))
{
}

Real
BScalarCalculator::computeValue()
{
  return 4.0 * libMesh::pi * 1.0e-7 * _coupled_H[_qp] * _coupled_m[_qp];
}