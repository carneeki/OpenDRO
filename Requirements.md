# Project Requirements
- [ ] Must display following axes
  - X
  - Y
  - Z
  - W (tailstock / knee)
  - Spindle position / Tachometer / Surface speed
- [ ] Lathe mode
- [ ] Mill mode
- [ ] Surface grinder mode
- [ ] Configurable distance counts per linear axis / per rev
- [ ] Configurable reset counts per linear axis / per rev

## Functions for All Modes
- [ ] Toggle linear units between mm / inches
- [ ] Toggle angular units between degrees, radians, grads
- [ ] Incremental distance counts
- [ ] Absolute distance counts
- [ ] Zero all axes
- [ ] Trig calculators:
  - [ ] sin, asin
  - [ ] cos, acos
  - [ ] tan, atan

## Functions for Lathe Mode
- [ ] Configurable tool offsets
- [ ] Show tacho in RPM or surface speed (m/min, SFM)
- [ ] Measure taper
- [ ] Radius cutting mode:
  1. Set fillet dimensions, either start+end+centre offsets (like G2 XY IJK) or end point and radius (G2 XY R)
  2. Set number of cuts
  3. Move to first cut, crank X axis to zero, and feed Z axis until zero
  4. back out, index next cut
  5. repeat steps 3-4 until complete
- [ ] Ball turning (maybe this is an expansion of IJK mode?)


## Functions for Mill Mode
- [ ] Configurable tool length offsets
- [ ] Show tacho in RPM or surface speed (m/min, SFM)
  - [ ] Set edge finder / probe diameter
- [ ] Per-axis centre finding (1/2 button)
- [ ] Measure taper
- [ ] Hole pattern calculator

## Functions for Surface Grinder Mode
¯\_(ツ)_/¯
