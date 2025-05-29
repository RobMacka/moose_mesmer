//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "VectorBoundingBoxIC.h"
#include "libmesh/point.h"

registerMooseObject("MooseApp", VectorBoundingBoxIC);

defineLegacyParams(VectorBoundingBoxIC);

InputParameters
VectorBoundingBoxIC::validParams()
{
  InputParameters params = VectorInitialCondition::validParams();
  params.addRequiredParam<Real>("x1", "The x coordinate of the lower left-hand corner of the box");
  params.addRequiredParam<Real>("y1", "The y coordinate of the lower left-hand corner of the box");
  params.addParam<Real>("z1", 0.0, "The z coordinate of the lower left-hand corner of the box");

  params.addRequiredParam<Real>("x2", "The x coordinate of the upper right-hand corner of the box");
  params.addRequiredParam<Real>("y2", "The y coordinate of the upper right-hand corner of the box");
  params.addParam<Real>("z2", 0.0, "The z coordinate of the upper right-hand corner of the box");
  params.addParam<Real>(
      "in_x", 0.0, "A function that describes the x-component of the initial condition");
  params.addParam<Real>(
      "in_y", 0.0, "A function that describes the y-component of the initial condition");
  params.addParam<Real>(
      "in_z", 0.0, "A function that describes the z-component of the initial condition");
  params.addParam<Real>(
      "out_x", 0.0, "A function that describes the x-component of the initial condition");
  params.addParam<Real>(
      "out_y", 0.0, "A function that describes the y-component of the initial condition");
  params.addParam<Real>(
      "out_z", 0.0, "A function that describes the z-component of the initial condition");
  params.addParam<Real>(
      "int_width", 0.0, "The width of the diffuse interface. Set to 0 for sharp interface.");

  params.addClassDescription("VectorBoundingBoxIC allows setting the initial condition of a value inside "
                             "and outside of a specified box. The box is aligned with the x, y, z "
                             "axes");

  return params;
}

VectorBoundingBoxIC::VectorBoundingBoxIC(const InputParameters & parameters)
  : VectorInitialCondition(parameters),
    _x1(getParam<Real>("x1")),
    _y1(getParam<Real>("y1")),
    _z1(getParam<Real>("z1")),
    _x2(getParam<Real>("x2")),
    _y2(getParam<Real>("y2")),
    _z2(getParam<Real>("z2")),
    _in_x(getParam<Real>("in_x")),
    _in_y(getParam<Real>("in_y")),
    _in_z(getParam<Real>("in_z")),
    _out_x(getParam<Real>("out_x")),
    _out_y(getParam<Real>("out_y")),
    _out_z(getParam<Real>("out_z")),
    _bottom_left(_x1, _y1, _z1),
    _top_right(_x2, _y2, _z2),
    _int_width(getParam<Real>("int_width"))
{
}

RealVectorValue
VectorBoundingBoxIC::value(const Point & p)
{
  if (_int_width < 0.0)
    mooseError("'int_width' should be non-negative");

  if (_int_width == 0.0)
  {
    for (unsigned int i = 0; i < LIBMESH_DIM; ++i)
      if (p(i) < _bottom_left(i) || p(i) > _top_right(i))
        return RealVectorValue(
        _out_x, _out_y, _out_z);


    return RealVectorValue(
        _in_x, _in_y, _in_z);

  }
  else
  {
    Real f_in = 1.0;
    for (unsigned int i = 0; i < LIBMESH_DIM; ++i)
      if (_bottom_left(i) != _top_right(i))
        f_in *= 0.5 * (std::tanh(2.0 * (p(i) - _bottom_left(i)) / _int_width) -
                       std::tanh(2.0 * (p(i) - _top_right(i)) / _int_width));

    return RealVectorValue(_out_x, _out_y, _out_z) + (RealVectorValue(_in_x, _in_y, _in_z) - RealVectorValue(_out_x, _out_y, _out_z)) * f_in;
  }
}
