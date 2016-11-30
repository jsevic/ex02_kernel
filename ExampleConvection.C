/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "ExampleConvection.h"

template<>
InputParameters validParams<ExampleConvection>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredCoupledVar("some_variable", "Some variable.");
  return params;
}

// Fix error here where we were calculating volumetric flux density as V^2
// versus (grad(V))^2, April 18. Changed function call from coupledValue
// to coupledGradient and declared as coupledGradient in the .h file.

ExampleConvection::ExampleConvection(const InputParameters & parameters) :
    Kernel(parameters),
    _some_variable(coupledGradient("some_variable")),
    _diffusivity(getMaterialProperty<Real>("diffusivity"))
{}

Real ExampleConvection::computeQpResidual()
{
  return _test[_i][_qp]*(_some_variable[_qp]*_some_variable[_qp])*(_diffusivity[_qp])*(-1);
}

Real ExampleConvection::computeQpJacobian()
{
  return _test[_i][_qp]*(_diffusivity[_qp]*_some_variable[_qp]*_some_variable[_qp]*_phi[_j][_qp])*(1);
}
