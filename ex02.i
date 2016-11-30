# John F. Sevic
# Department of Electrical Engineering, UC Santa Cruz

# November 28, 2016
#
# This MOOSE deck is evolved from Example 3 into self-consistent electrothermal
# simulation of the Kate Norris selector-memristor structure. The initial
# results of that simulation were publised in Juan's SPIE '16 paper and
# in my first-author paper in TED '17.
#
# Mass transport assuming a Frenkel transport model is implemented presently.
# To start, a thin-film sample on the unit rectangle is assumed, with unit
# defect density on the top boundary, ground density on the bottom, and zero
# flux density on the sides.
#
# The Frenkel ionic transport model is a continuum approximtion that relies on
# a T-dependent diffusion coefficient for defect density and T- and V-dependent
# mobility model model. The initial goal is to decouple T and V to illustrate
# the correct conductivity v. T and then to add self-consistent simulation of
# V and T. These two terms show up on the diffusion and advection terms of
# transport PDE.
#
# There are three kernels (later four, including a source term) to construct
# the PDE: these are the mass ionic diffusion, mass ionic drift, the intertial
# term (for transient simulation), and the source term due to the battery.
#
#


[Mesh]
  type = GeneratedMesh
  dim = 2
  xmin = 0
  xmax = 1
  ymin = 0
  ymax = 1
  nx = 20
  ny = 20
[]

[Variables]
  [./n]
    # Ionic particle density per unit volume, n.
    order = FIRST
    family = LAGRANGE
    initial_condition = 0
  [../]
[]

[AuxVariables]
  [./sigma]
    # Electrical conductivity, sigma = mobility * density.
    order = FIRST
    family = MONOMIAL
  [../]
[]

[Kernels]
  [./DiffusiveMassTransport]
    type = MassDiffusion
    variable = n
    some_variable = 0.01
  [../]
[]

[AuxKernels]
    [./conductivity]
    type = ExampleAux
    variable = sigma
    coupled = n
  [../]
[]

[BCs]
  [./top]
    type = NeumannBC
    variable = n
    boundary = 2
    value = -100
  [../]
  [./bottom]
    type = DirichletBC
    variable = n
    boundary = 0
    value = 10.0
  [../]
  [./right]
    type = NeumannBC
    variable = n
    boundary = 1
    value = 0.0
  [../]
  [./left]
    type = NeumannBC
    variable = n
    boundary = 3
    value = 0.0
  [../]
[]

[Materials]
  [./TaO_DiffusionPreFactor]
    type = DiffusionPreFactor
    block = 0
    independent_vals = '0 1'
    dependent_vals = '1.0 1.0'
  [../]
[]

[Executioner]
  type = Steady
[]

[Outputs]
  exodus = true
[]
