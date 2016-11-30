[Mesh]
  file = mug.e
  uniform_refine = 1
[]

[Variables]
  active = 'convected'

  [./convected]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[Kernels]
  active = 'diff conv'

  [./diff]
    type = Diffusion
    variable = convected
  [../]

  [./conv]
    type = ExampleConvection
    variable = convected
    velocity = '0.0 0.0 0.0'
  [../]

  [./time_deriv_convected]
    type = TimeDerivative
    variable = convected
  [../]
[]

[BCs]
  active = 'bottom top'

  [./bottom]
    type = DirichletBC
    variable = convected
    boundary = 'bottom'
    value = 1
  [../]

  [./top]
    type = DirichletBC
    variable = convected
    boundary = 'top'
    value = 0
  [../]
[]

[Executioner]
  type = Transient
  solve_type = 'PJFNK'
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
  dt = 0.01
  num_steps = 10
[]

[Outputs]
  exodus = true
[]
