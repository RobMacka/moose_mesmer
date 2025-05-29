//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ADScalarHField.h"

registerMooseObject("ElectromagneticsApp", ADScalarHField);

InputParameters
ADScalarHField::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addClassDescription(
      "Set the kernel variable to a specified component of the gradient of a coupled variable.");
  params.addRequiredCoupledVar("v", "Coupled variable to match gradient component of");
  params.addParam<Real>("component", "The component to compute");
  return params;
}

ADScalarHField::ADScalarHField(const InputParameters & parameters)
  : ADKernel(parameters),
    _component(getParam<Real>("component")),
    _v_var(coupled("v")),
    _grad_v(adCoupledGradient("v"))
{
}

ADReal
ADScalarHField::computeQpResidual()
{
  return (_u[_qp] + _grad_v[_qp](_component)) * _test[_i][_qp];
}
