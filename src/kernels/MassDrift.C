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

// John F. Sevic
// Department of Electrical Engineering, UC Santa Cruz
// November 28, 2016
//
// This is the first kernal I have made from scratch. The initial goal was to
// create the diffusion operator with an arbitrary diffusivity, specified as a
// material property by _diffusivity.
//
// Following the success of this, which required a fair amount of coding, I
// added coupling, in this case T, so used coupledValue, not coupledGradient.
// Thus, in the present form, this kernel implements the following:
//
// 1. Diffusion operator on n, i.e. diffusion term of the transport equation
// 2. Ionic diffusion based on the Frenkel defect model is implemented by
//    a self-consistently coupled diffusion expression in T and Ea, the defect
//    activation energy.
// 3. The diffusion pre-factor, Do, is specified by a material property.
// 4. Activation energy is currently set at 0.1 eV.
// 5. _some_variable is temperature, T.

#include "MassDrift.h"

template<>
InputParameters validParams<MassDrift>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("some_variable", "Some variable.");
  return params;
}

MassDrift::MassDrift(const InputParameters & parameters) :
  Kernel(parameters),
  _some_variable(coupledValue("some_variable")),
  _diffusivity(getMaterialProperty<Real>("diffusivity"))
{}

Real MassDrift::computeQpResidual()
{
  return _grad_u[_qp] * _grad_test[_i][_qp];
}

Real MassDrift::computeQpJacobian()
{
  return _grad_phi[_j][_qp] * _grad_test[_i][_qp];
}
