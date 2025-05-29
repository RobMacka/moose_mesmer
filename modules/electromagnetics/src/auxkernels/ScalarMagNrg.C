//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ScalarMagNrg.h"

#include "metaphysicl/raw_type.h"

registerMooseObject("ElectromagneticsApp", ScalarMagNrg);

InputParameters
ScalarMagNrg::validParams()
{
  InputParameters params = AuxKernel::validParams();

  // Add a "coupling paramater" to get a variable from the input file.
  params.addRequiredCoupledVar("mx", "The magnetisation field.");
  params.addRequiredCoupledVar("my", "The magnetisation field.");
  params.addRequiredCoupledVar("mz", "The magnetisation field.");
  params.addRequiredCoupledVar("Hx", "The demagnetising magnetic field.");
  params.addRequiredCoupledVar("Hy", "The demagnetising magnetic field.");
  params.addRequiredCoupledVar("Hz", "The demagnetising magnetic field.");
  params.addParam<Real>("coefficient", 0.5, "Coefficient for energy integral");
  params.addParam<Real>("SatMag", 10000, "Coefficient for energy integral");
  params.addParam<Real>("Permeability", 1.26e-6, "Coefficient for energy integral");
  return params;
}

ScalarMagNrg::ScalarMagNrg(const InputParameters & parameters)
  : AuxKernel(parameters),

    _coupled_mx(coupledValue("mx")),

    _coupled_my(coupledValue("my")),

    _coupled_mz(coupledValue("mz")),

    _coupled_Hx(coupledValue("Hx")),

    _coupled_Hy(coupledValue("Hy")),

    _coupled_Hz(coupledValue("Hz")),

    _coeff(getParam<Real>("coefficient")),

    _mu0(getParam<Real>("Permeability")),

    _Ms(getParam<Real>("SatMag"))
{
}

Real
ScalarMagNrg::computeValue()
{
  // Access the gradient of the pressure at this quadrature point, then pull out the "component" of
  // it requested (x, y or z). Note, that getting a particular component of a gradient is done using
  // the parenthesis operator.
  return - (_coupled_mx[_qp]*_coupled_Hx[_qp]+_coupled_my[_qp]*_coupled_Hy[_qp]+_coupled_mz[_qp]*_coupled_Hz[_qp]) * _Ms * _coeff;
}