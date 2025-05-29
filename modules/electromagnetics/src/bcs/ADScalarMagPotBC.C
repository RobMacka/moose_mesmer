//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ADScalarMagPotBC.h"
#include "Function.h"

registerMooseObject("ElectromagneticsApp", ADScalarMagPotBC);

InputParameters
ADScalarMagPotBC::validParams()
{
  InputParameters params = ADIntegratedBC::validParams();
  params.addClassDescription(
      "Imposes the integrated boundary condition arising from integration by parts of a Helmholtz "
      "equation, when that term is set equal to the gradient of a coupled variable. ");
  params.addParam<Real>("component", 1, "Component number");
  params.addRequiredCoupledVar("coupled_val", "Coupled vector variable.");
  params.addParam<Real>(
      "sign", 1.0, "Sign of coupled gradient.");
  params.addParam<Real>(
      "coefficient", 10000, "Ms");
  return params;
}

ADScalarMagPotBC::ADScalarMagPotBC(const InputParameters & parameters)
  : ADIntegratedBC(parameters),
    _sign(getParam<Real>("sign")),
    _coefficient(getParam<Real>("coefficient")),
    _component(getParam<Real>("component")),                                                                                          
    _coupled_val(adCoupledValue("coupled_val"))
{
}

ADReal
ADScalarMagPotBC::computeQpResidual()
{
  return (_coefficient * _coupled_val[_qp] + _grad_u[_qp](_component)) * _normals[_qp](_component);
}

