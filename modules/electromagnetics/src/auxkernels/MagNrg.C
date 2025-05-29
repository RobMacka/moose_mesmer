//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "MagNrg.h"

#include "metaphysicl/raw_type.h"

registerMooseObject("ElectromagneticsApp", MagNrg);

InputParameters
MagNrg::validParams()
{
  InputParameters params = AuxKernel::validParams();

  // Add a "coupling paramater" to get a variable from the input file.
  params.addRequiredCoupledVar("m", "The magnetisation field.");
  params.addRequiredCoupledVar("H", "The demagnetising magnetic field.");
  params.addParam<Real>("coefficient", 0.5, "Coefficient for energy integral");
  params.addParam<Real>("SatMag", 10000, "Coefficient for energy integral");
  params.addParam<Real>("Permeability", 1.26e-6, "Coefficient for energy integral");
  return params;
}

MagNrg::MagNrg(const InputParameters & parameters)
  : AuxKernel(parameters),

    _coupled_m(coupledVectorValue("m")),

    _coupled_H(coupledVectorValue("H")),

    _coeff(getParam<Real>("coefficient")),

    _mu0(getParam<Real>("Permeability")),

    _Ms(getParam<Real>("SatMag"))
{
}

Real
MagNrg::computeValue()
{
  // Access the gradient of the pressure at this quadrature point, then pull out the "component" of
  // it requested (x, y or z). Note, that getting a particular component of a gradient is done using
  // the parenthesis operator.
  return - (_coupled_m[_qp].contract(_coupled_H[_qp]) * _Ms * _coeff);
}