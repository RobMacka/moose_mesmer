[Mesh]
       type = FileMesh
       file = 'long_box_smaller.msh'
#    [gen]
#          type = GeneratedMeshGenerator
#          dim = 3
#          nx = 64
#          ny = 64
#          nz = 64
#          xmin = -64
#          xmax = 64
#          ymin = -64
#          ymax = 64
#          zmin = -64
#          zmax = 64
#    []
[]

# Correct value for mu0 in our units is 7.85398e6!

[Variables]
	[m1x]
        family = LAGRANGE
        order = FIRST
	[]
	[m1y]
        family = LAGRANGE
        order = FIRST
	[]
	[m1z]
        family = LAGRANGE
        order = FIRST
	[]
  [m2x]
        family = LAGRANGE
        order = FIRST
	[]
	[m2y]
        family = LAGRANGE
        order = FIRST
	[]
	[m2z]
        family = LAGRANGE
        order = FIRST
	[]
  [Happx]
  family = LAGRANGE
  order = FIRST
  []
  [Happy]
  family = LAGRANGE
  order = FIRST
  []
  [Happz]
  family = LAGRANGE
  order = FIRST
  []
	# [phi]
	# []
        # [Hx]
        # family = LAGRANGE
        # order = FIRST
        # []
        # [Hy]
        # family = LAGRANGE
        # order = FIRST
        # []
        # [Hz]
        # family = LAGRANGE
        # order = FIRST
        # []
[]

[AuxVariables]
  # [MSEnergyDens]
  # []
	# [Bx]
  #       family = LAGRANGE
  #       order = FIRST
	# []
	# [By]
  #       family = LAGRANGE
  #       order = FIRST
	# []
	# [Bz]
  #       family = LAGRANGE
  #       order = FIRST
	# []
[]

[AuxKernels]
# [./bxcalc]
#     type = BScalarCalculator
#     variable = Bx
#     permeability = 7.85398e6
#     satmag = 0.00086
#     mag = mx
#     field = Hx
# [../]
# [./bycalc]
#     type = BScalarCalculator
#     variable = By
#     permeability = 7.85398e6
#     satmag = 0.00086
#     mag = my
#     field = Hy
# [../]
# [./bzcalc]
#     type = BScalarCalculator
#     variable = Bz
#     permeability = 7.85398e6
#     satmag = 0.00086
#     mag = mz
#     field = Hz
# [../]
#  [./Ems]
#   type = ScalarMagnetostatNrgDens
#   variable = MSEnergyDens
#   mx = mx
#   my = my
#   mz = mz
#   Hx = Hx
#   Hy = Hy
#   Hz = Hz
#   SatMag = 0.00086
#   Permeability = 7.85398e6
#  [../]
[]

[Kernels]
[zeeman_m1x]
  type = AllenCahn
  variable = m1x
  args = 'm1y m1z Happx Happy Happz'
  mob_name = mobility
  f_name = zeeman1
  block = 'Magnet'
[]
[zeeman_m1y]
  type = AllenCahn
  variable = m1y
  args = 'm1x m1z Happx Happy Happz'
  mob_name = mobility
  f_name = zeeman1
  block = 'Magnet'
[]
[zeeman_m1z]
  type = AllenCahn
  variable = m1z
  args = 'm1x m1y Happx Happy Happz'
  mob_name = mobility
  f_name = zeeman1
  block = 'Magnet'
[]
[zeeman_m2x]
  type = AllenCahn
  variable = m2x
  args = 'm2y m2z Happx Happy Happz'
  mob_name = mobility
  f_name = zeeman2
  block = 'Magnet'
[]
[zeeman_m2y]
  type = AllenCahn
  variable = m2y
  args = 'm2x m2z Happx Happy Happz'
  mob_name = mobility
  f_name = zeeman2
  block = 'Magnet'
[]
[zeeman_m2z]
  type = AllenCahn
  variable = m2z
  args = 'm2x m2y Happx Happy Happz'
  mob_name = mobility
  f_name = zeeman2
  block = 'Magnet'
[]
[./normalhappx]
type = NullKernel
variable = Happx
[../]
[./normalhappy]
type = NullKernel
variable = Happy
[../]
[./normalhappz]
type = NullKernel
variable = Happz
[../]
# [./demagx]
#     type = ADScalarDemagMKernel
#     variable = phi
#     v = mx
#     coeff = 0.00086 #Ms, here assumed to be 10000 A m^-1
#     component = 0
#     block = 'Magnet'
# [../]
# [./demagy]
#     type = ADScalarDemagMKernel
#     variable = phi
#     v = my
#     coeff = 0.00086 #Ms, here assumed to be 10000 A m^-1
#     component = 1
#     block = 'Magnet'
# [../]
# [./demagz]
#     type = ADScalarDemagMKernel
#     variable = phi
#     v = mz
#     coeff = 0.00086 #Ms, here assumed to be 10000 A m^-1
#     component = 2
#     block = 'Magnet'
# [../]
# [./demag_fs]
#     type = NewADDiffusion
#     variable = phi
#     block = 'Space Buffer'
# [../]
# [./normalx]
# type = NullKernel
# variable = mx
# [../]
# [./normaly]
# type = NullKernel
# variable = my
# [../]
# [./normalz]
# type = NullKernel
# variable = mz
# [../]
# [./phi_to_Hx]
#   type = ADScalarHField
#   variable = Hx
#   v = phi
#   component = 0
# [../]
# [./phi_to_Hy]
#   type = ADScalarHField
#   variable = Hy
#   v = phi
#   component = 1
# [../]
# [./phi_to_Hz]
#   type = ADScalarHField
#   variable = Hz
#   v = phi
#   component = 2
# [../]
# [magnetostatic_mx]
#   type = AllenCahn
#   variable = mx
#   args = 'my mz Hx Hy Hz'
#   mob_name = mobility
#   f_name = magnetostatic
#   block = 'Magnet'
# []
# [magnetostatic_my]
#   type = AllenCahn
#   variable = my
#   args = 'mx mz Hx Hy Hz'
#   mob_name = mobility
#   f_name = magnetostatic
#   block = 'Magnet'
# []
# [magnetostatic_mz]
#   type = AllenCahn
#   variable = mz
#   args = 'mx my Hx Hy Hz'
#   mob_name = mobility
#   f_name = magnetostatic
#   block = 'Magnet'
# []
# [expmagnetostatic_hx]
#   type = AllenCahn
#   variable = Hx
#   args = 'mx my mz Hy Hz'
#   mob_name = mobility
#   f_name = magnetostatic
#   block = 'Magnet'
# []
# [expmagnetostatic_hy]
#   type = AllenCahn
#   variable = Hy
#   args = 'mx my mz Hx Hz'
#   mob_name = mobility
#   f_name = magnetostatic
#   block = 'Magnet'
# []
# [expmagnetostatic_hz]
#   type = AllenCahn
#   variable = Hz
#   args = 'mx my mz Hx Hy'
#   mob_name = mobility
#   f_name = magnetostatic
#   block = 'Magnet'
# []
[anisotropy_m1x]
  type = AllenCahn
  variable = m1x
  args = 'm1y m1z'
  mob_name = mobility
  f_name = anisotropy1
  block = 'Magnet'
[]
[anisotropy_m1y]
  type = AllenCahn
  variable = m1y
  args = 'm1x m1z'
  mob_name = mobility
  f_name = anisotropy1
  block = 'Magnet'
[]
[anisotropy_m1z]
  type = AllenCahn
  variable = m1z
  args = 'm1x m1y'
  mob_name = mobility
  f_name = anisotropy1
  block = 'Magnet'
[]
[anisotropy_m2x]
  type = AllenCahn
  variable = m2x
  args = 'm2y m2z'
  mob_name = mobility
  f_name = anisotropy2
  block = 'Magnet'
[]
[anisotropy_m2y]
  type = AllenCahn
  variable = m2y
  args = 'm2x m2z'
  mob_name = mobility
  f_name = anisotropy2
  block = 'Magnet'
[]
[anisotropy_m2z]
  type = AllenCahn
  variable = m2z
  args = 'm2x m2y'
  mob_name = mobility
  f_name = anisotropy2
  block = 'Magnet'
[]
[constraint_m1x]
  type = AllenCahn
  variable = m1x
  args = 'm1y m1z'
  mob_name = mobility
  f_name = penalty1
  block = 'Magnet'
[]
[constraint_m1y]
  type = AllenCahn
  variable = m1y
  args = 'm1x m1z'
  mob_name = mobility
  f_name = penalty1
  block = 'Magnet'
[]
  [constraint_m1z]
  type = AllenCahn
  variable = m1z
  args = 'm1x m1y'
  mob_name = mobility
  f_name = penalty1
  block = 'Magnet'
[]
[constraint_m2x]
  type = AllenCahn
  variable = m2x
  args = 'm2y m2z'
  mob_name = mobility
  f_name = penalty2
  block = 'Magnet'
[]
[constraint_m2y]
  type = AllenCahn
  variable = m2y
  args = 'm2x m2z'
  mob_name = mobility
  f_name = penalty2
  block = 'Magnet'
[]
  [constraint_m2z]
  type = AllenCahn
  variable = m2z
  args = 'm2x m2y'
  mob_name = mobility
  f_name = penalty2
  block = 'Magnet'
[]
# [restraint_mx]
# type = AllenCahn
# variable = mx
# mob_name = mobility
# f_name = penalty1
# block = 'Space'
# []
# [restraint_my]
# type = AllenCahn
# variable = my
# mob_name = mobility
# f_name = penalty2
# block = 'Space'
# []
# [restraint_mz]
# type = AllenCahn
# variable = mz
# mob_name = mobility
# f_name = penalty3
# block = 'Space'
# []
# [./exchange_mx]
#    type = ACInterface
#    variable = mx
#    args = 'my mz'
#    mob_name = mobility
#    kappa_name = 'A'
#     block = 'Magnet'
# [../]
# [./exchange_my]
#    type = ACInterface
#   variable = my
#    args = 'mx mz'
#    mob_name = mobility
#    kappa_name = 'A'
#   block = 'Magnet'
# [../]
# [./exchange_mz]
#    type = ACInterface
#    variable = mz
#    args = 'my mx'
#    mob_name = mobility
#    kappa_name = 'A'
#   block = 'Magnet'
# [../]
[./m1x_dt]
  type = TimeDerivative
  variable = m1x
   block = 'Magnet'
[../]
[./m1y_dt]
  type = TimeDerivative
  variable = m1y
   block = 'Magnet'
[../]
[./m1z_dt]
  type = TimeDerivative
  variable = m1z
   block = 'Magnet'
[../]
[./m2x_dt]
  type = TimeDerivative
  variable = m2x
   block = 'Magnet'
[../]
[./m2y_dt]
  type = TimeDerivative
  variable = m2y
   block = 'Magnet'
[../]
[./m2z_dt]
  type = TimeDerivative
  variable = m2z
   block = 'Magnet'
[../]
[m1x_afm]
  type = ADImprovedAFM
  variable = m1x
  A = 125
  m2 = m2x
[../]
[m2x_afm]
  type = ADImprovedAFM
  variable = m2x
  A = 125
  m2 = m1x
[../]
[m1y_afm]
  type = ADImprovedAFM
  variable = m1y
  A = 125
  m2 = m2y
[../]
[m2y_afm]
  type = ADImprovedAFM
  variable = m2y
  A = 125
  m2 = m1y
[../]
[m1z_afm]
  type = ADImprovedAFM
  variable = m1z
  A = 125
  m2 = m2z
[../]
[m2z_afm]
  type = ADImprovedAFM
  variable = m2z
  A = 125
  m2 = m1z
[../]
# [./Hx_dt]
#   type = TimeDerivative
#   variable = Hx
# [../]
# [./Hy_dt]
#   type = TimeDerivative
#   variable = Hy
# [../]
# [./Hz_dt]
#   type = TimeDerivative
#   variable = Hz
# [../]
[]

# [InterfaceKernels]
# [./penalty_interface_z]
#   type = CoupledPenaltyInterfaceDiffusion
#   variable = Hz
#   neighbor_var = Hz
#   boundary = 'Front Back'
#   penalty = 1e6
# [../]
# []

[ICs]
    [./m1z]
			type = FunctionIC
      variable = m1z
			function = 1
      block = 'Magnet'
		[]
    [./m1x]
      type = FunctionIC
      variable = m1x
      function = 0
      block = 'Magnet'
    []
    [./m1y]
      type = FunctionIC
      variable = m1y
      function = 0
      block = 'Magnet'
    []
    [./m2z]
			type = FunctionIC
      variable = m2z
			function = 0
      block = 'Magnet'
		[]
    [./m2x]
      type = FunctionIC
      variable = m2x
      function = 1
      block = 'Magnet'
    []
    [./m2y]
      type = FunctionIC
      variable = m2y
      function = 0
      block = 'Magnet'
    []
    # [./phi]
		# 	type = FunctionIC
    #   variable = phi
		# 	function = 0
		# []
    [./h1]
			type = FunctionIC
      variable = Happz
			function = 1.59155e-3 #Field of 1 millitesla
#			function = 7.95775e-7 #Field of 1 millitesla
      block = 'Magnet'
		[]
    [./h2]
      type = FunctionIC
      variable = Happx
      function = 0
      block = 'Magnet'
    []
    [./h3]
      type = FunctionIC
      variable = Happy
      function = 0
      block = 'Magnet'
    []
[]

# [Adaptivity]
#  steps = 1
#  marker = marker
#  [./Markers/marker]
#      type = BoxMarker
#      bottom_left = '-16 -16 -48'
#      top_right = '16 16 48'
#      inside = refine
#      outside = do_nothing
#  [../]
# []

[BCs]
   # [./boundary1]
   #     type = DirichletBC
   #     variable = mx
   #     boundary = 'Left2 Right2 Top2 Bottom2 Front2 Back2'
   #     value = 0
   # [../]
   # [./boundary2]
   #     type = DirichletBC
   #     variable = my
   #     boundary = 'Left2 Right2 Top2 Bottom2 Front2 Back2'
   #     value = 0
   # [../]
   # [./boundary3]
   #     type = DirichletBC
   #     variable = mz
   #     boundary = 'Left2 Right2 Top2 Bottom2 Front2 Back2'
   #     value = 0
   # [../]
   # [./boundary_match1]
   #     type = DirichletBC
   #     variable = mx
   #     boundary = 'Left Right Top Bottom Front Back'
   #     value = 0
   # [../]
   #  [./boundary_match2]
   #      type = DirichletBC
   #      variable = my
   #      boundary = 'Left Right Top Bottom Front Back'
   #      value = 0
   #  [../]
   #  [./boundary_match3]
   #      type = DirichletBC
   #      variable = mz
   #      boundary = 'Left Right Top Bottom Front Back'
   #      value = 1
   #  [../]
    # [./boundary_sphere]
    #     type = DirichletBC
    #     variable = phi
    #     boundary = 'Infinity'
    #     value = 0
    # [../]
   # [./boundary5]
   #     type = ADScalarMagPotBC
   #     variable = phi
   #     coefficient = 0.00086
   #     boundary = 'Left2 Right2 Top2 Bottom2 Front2 Back2'
   #     mz = mz
   #     mx = mx
   #     my = my
   # [../]
   # [./boundary6]
   #     type = ADScalarMagPotBC
   #     variable = phi
   #     coefficient = 0.00086
   #     boundary = 'Left Right Top Bottom Front Back'
   #     mz = mz
   #     mx = mx
   #     my = my
   # [../]
    # [./boundary2]
    #     type = ADScalarMagPotBC
    #     variable = phi
    #     coefficient = 10000
    #     boundary = 'Surface'
    #     mz = mz
    #     mx = mx
    #     my = my
    # [../]
[]
#For 8x8x32 cuboid, get Nz = 0.1045, theory gives = 0.10845

[Postprocessors]
[m1z_max]
  type = ElementExtremeValue
  variable = m1z
  value_type = max
[]
[m1z_min]
  type = ElementExtremeValue
  variable = m1z
  value_type = min
[]
[m2z_max]
  type = ElementExtremeValue
  variable = m2z
  value_type = max
[]
[m2z_min]
  type = ElementExtremeValue
  variable = m2z
  value_type = min
[]
# [magnetostat_nrg_total]
#   type = ElementIntegralVariablePostprocessor
#   variable = MSEnergyDens
#   block = 'Magnet'
# []
# [magnetostat_nrg_surf1]
#   type = SideIntegralVariablePostprocessor
#   variable = MSEnergyDens
#   boundary = 'Front'
# []
# [magnetostat_nrg_surf2]
#   type = SideIntegralVariablePostprocessor
#   variable = MSEnergyDens
#   boundary = 'Back'
# []
# [magnetostat_nrg_surf3]
#   type = SideIntegralVariablePostprocessor
#   variable = MSEnergyDens
#   boundary = 'Left'
# []
# [magnetostat_nrg_surf4]
#   type = SideIntegralVariablePostprocessor
#   variable = MSEnergyDens
#   boundary = 'Right'
# []
# [magnetostat_nrg_surf5]
#   type = SideIntegralVariablePostprocessor
#   variable = MSEnergyDens
#   boundary = 'Bottom'
# []
# [magnetostat_nrg_surf6]
#   type = SideIntegralVariablePostprocessor
#   variable = MSEnergyDens
#   boundary = 'Top'
# []
# [leech1]
#   type = ElementL2Norm
#   variable = mx
#   block = "Space"
# []
# [leech2]
#   type = ElementL2Norm
#   variable = my
#   block = "Space"
# []
# [leech3]
#   type = ElementL2Norm
#   variable = mz
#   block = "Space"
# []
[]

[Materials]
  [./consts]
    type = GenericConstantMaterial
    prop_names  = 'Fx  mobility  A     zero   K1 lambda lambda_100 lambda_111 mu_0 Ms killer' #killer
    prop_values = '0   1         250  0    0.3  25000 -0.000016 -0.000007 7.85398e6 0.00086 1000' #100000
  [../]
    [./anisotropy1]
        type = DerivativeParsedMaterial
        f_name = anisotropy1
        function = 'K1*(1 - m1z^2)' #-constants are the lambdas
                args = 'm1x m1y m1z'
                material_property_names = 'K1'
    [../]
    [./anisotropy2]
        type = DerivativeParsedMaterial
        f_name = anisotropy2
        function = 'K1*(1 - m2z^2)' #-constants are the lambdas
                args = 'm2x m2y m2z'
                material_property_names = 'K1'
    [../]
    # [./magnetostatic]
    #     type = DerivativeParsedMaterial
    #     f_name = magnetostatic
    #     function = '-mu_0*0.5*Ms*(mx*Hx+my*Hy+mz*Hz)' #-constants are the lambdas
    #             args = 'mx my mz Hx Hy Hz'
    #             material_property_names = 'mu_0 Ms'
    # [../]
    [./zeeman1]
    type = DerivativeParsedMaterial
    f_name = zeeman1
    function = '- mu_0 * Ms * (m1x * Happx + m1y * Happy + m1z * Happz)' #-constants are the lambdas
            args = 'm1x m1y m1z Happx Happy Happz'
            material_property_names = 'mu_0 Ms'
    [../]
    [./zeeman2]
    type = DerivativeParsedMaterial
    f_name = zeeman2
    function = '- mu_0 * Ms * (m2x * Happx + m2y * Happy + m2z * Happz)' #-constants are the lambdas
            args = 'm2x m2y m2z Happx Happy Happz'
            material_property_names = 'mu_0 Ms'
    [../]
        [./penalty1]
        type = DerivativeParsedMaterial
        f_name = penalty1
        function = 'lambda*(1-sqrt(m1x^2 + m1y^2 + m1z^2))^2' #-constants are the lambdas
                args = 'm1x m1y m1z'
                material_property_names = 'lambda'
    [../]
    [./penalty2]
    type = DerivativeParsedMaterial
    f_name = penalty2
    function = 'lambda*(1-sqrt(m2x^2 + m2y^2 + m2z^2))^2' #-constants are the lambdas
            args = 'm2x m2y m2z'
            material_property_names = 'lambda'
[../]
[]

[Preconditioning]
  [./pc]
    type = SMP
    full = true
    #petsc_options = '-snes_converged_reason'
    #petsc_options_iname = '-ksp_type -pc_type -sub_pc_type -snes_max_it -sub_pc_factor_shift_type -pc_asm_overlap -snes_atol -snes_rtol '
    #petsc_options_value = 'gmres asm lu 100 NONZERO 2 1E-8 1E-10'
  [../]
[]

[Executioner]
type = Transient
scheme = 'bdf2'

solve_type = 'PJFNK'
petsc_options_iname = '-ksp_type -pc_type -sub_pc_type -snes_max_it -sub_pc_factor_shift_type -pc_asm_overlap -snes_atol -snes_rtol '
petsc_options_value = 'gmres asm lu 100 NONZERO 2 1E-8 1E-10'

l_max_its = 1000
l_tol = 1.0e-6

nl_max_its = 50
nl_rel_tol = 1.0e-8
nl_abs_tol = 1.0e-10

steady_state_detection = True
steady_state_tolerance = 1e-4

[./TimeStepper]
  type = IterationAdaptiveDT
  optimal_iterations = 9
  iteration_window = 2
  growth_factor = 1.1
  cutback_factor = 0.75
  dt = 1
[../]
[]

[Outputs]
checkpoint = true
  [./exodus]
    type = Exodus
  [../]
  [./csv]
    type = CSV
  [../]
[]
