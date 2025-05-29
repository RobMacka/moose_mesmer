//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ADCrapAFM.h"

registerMooseObject("ElectromagneticsApp", ADCrapAFM);

InputParameters
ADCrapAFM::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addClassDescription(
      "Kernel representing the contribution of the PDE term $cfu$, where $c$ and $f$ are constant "
      "and function coefficients, respectively, and $u$ is a vector variable.");
  params.addParam<Real>("A", "Exchange stiffness");
  params.addRequiredCoupledVar("m2", "Coupled variable.");
  return params;
}

ADCrapAFM::ADCrapAFM(const InputParameters & parameters)
  : ADKernel(parameters),

    _A(getParam<Real>("A")),

    _m2(coupledValue("m2"))
{
}

ADReal
ADCrapAFM::computeQpResidual()
{
  return _A * (_u[_qp] + _m2[_qp]) * _test[_i][_qp];
}
