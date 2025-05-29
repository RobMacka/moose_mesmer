//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ADHField.h"

registerMooseObject("ElectromagneticsApp", ADHField);

InputParameters
ADHField::validParams()
{
  InputParameters params = ADVectorKernel::validParams();
  params.addClassDescription(
      "Set the kernel variable to a specified component of the gradient of a coupled variable.");
  params.addRequiredCoupledVar("v", "Coupled variable to match gradient component of");
  return params;
}

ADHField::ADHField(const InputParameters & parameters)
  : ADVectorKernel(parameters),
    _v_var(coupled("v")),
    _grad_v(adCoupledGradient("v"))
{
}

ADReal
ADHField::computeQpResidual()
{
  return (_u[_qp] + _grad_v[_qp]) * _test[_i][_qp];
}
