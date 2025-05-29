//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ADMagPotBC.h"
#include "Function.h"

registerMooseObject("ElectromagneticsApp", ADMagPotBC);

InputParameters
ADMagPotBC::validParams()
{
  InputParameters params = ADIntegratedBC::validParams();
  params.addClassDescription(
      "Imposes the integrated boundary condition arising from integration by parts of a Helmholtz "
      "equation, when that term is set equal to the gradient of a coupled variable. ");
  params.addParam<FunctionName>(
      "func", 1.0, "Optional function coefficient for coupled gradient term.");
  params.addRequiredCoupledVar("coupled_val", "Coupled vector variable.");
  params.addParam<Real>(
      "sign", 1.0, "Sign of coupled gradient.");
  params.addParam<Real>(
      "coefficient", 1.0, "Coefficient of coupled gradient.");
  return params;
}

ADMagPotBC::ADMagPotBC(const InputParameters & parameters)
  : ADIntegratedBC(parameters),
    _sign(getParam<Real>("sign")),
    _coefficient(getParam<Real>("coefficient")),
    _func(getFunction("func")),
    _coupled_val(adCoupledVectorValue("coupled_val"))
{
}

ADReal
ADMagPotBC::computeQpResidual()
{
  return _func.value(_t, _q_point[_qp]) * (- _coefficient * _coupled_val[_qp] 
+ _grad_u[_qp]) * _normals[_qp];
}

