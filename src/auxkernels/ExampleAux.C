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

#include "ExampleAux.h"

template<>
InputParameters validParams<ExampleAux>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addParam<Real>("value", 0.0, "Scalar value used for our auxiliary calculation");
  params.addRequiredCoupledVar("coupled", "Coupled variable");
  return params;
}

ExampleAux::ExampleAux(const InputParameters & parameters) :
    AuxKernel(parameters),

    _coupled_gradient(coupledGradient("coupled")),

    _diffusivity(getMaterialProperty<Real>("diffusivity"))

{
}

Real
ExampleAux::computeValue()
{
  return (_coupled_gradient[_qp](1))*(_diffusivity[_qp]);
}
