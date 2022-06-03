# Project Requirements
- [ ] Must display following axes
  - [x] X
  - [x] Y
  - [x] Z
  - [x] W (tailstock / knee)
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
- [x] Zero all axes
- [ ] Trig calculators:
  - [ ] sin, asin
  - [ ] cos, acos
  - [ ] tan, atan

## Functions for Lathe Mode
- [ ] Configurable tool offsets
- [ ] Show tacho in RPM or surface speed (m/min, SFM)
- [ ] Measure taper
- [ ] Radius cutting mode:
- [ ] Ball turning (maybe this is an expansion of IJK mode?)


## Functions for Mill Mode
- [ ] Configurable tool length offsets
- [ ] Show tacho in RPM or surface speed (m/min, SFM)
  - [ ] Set edge finder / probe diameter
- [ ] Per-axis centre finding (1/2 button)
- [ ] Measure taper
- [ ] Hole pattern calculator (PCD)

## Functions for Surface Grinder Mode
¯\_(ツ)_/¯

## Detailed Lathe Functions

### Configurable tool offsets

#### To set tool offset

Each tool will be touched off and zeroed on a series of linear axes. This permits a drill in the tailstock to be zeroed (as long as the tailstock is not moved, and only the quill is extended). To perform:

Assuming a RH lathe turning tool in tool holder 1:

1. Press `TOOL CALL`.
2. Select tool `1`.
3. Press `TOOL SET`.
4. Touch off Z axis from the work (or take a facing cut with carriage locked).
5. Press `Z_0` to set the tool's current Z position in relation to the machine (`G53`).
6. Touch off X axis from the work (or take a cut with X axis locked), and measure the work diameter.
7. Enter the diameter, and DRO will calculate radius (and hence X axis offset from centre line `G53`).

The turning tool is now set with reference to the carriage position.

Assuming a drill in a taper in tailstock as tool `21`:

1. Press `TOOL CALL`.
2. Select tool `21`.
3. Press `TOOL SET`.
4. Touch off Z axis from the work.
5. Press `W_0` to set the tool's current W axis.

A single tool may have multiple cutting edges, for example a square 45 degree turning tool used for chamfers has two edges that might be used, one for chamfers towards the chuck and one for chamfers towards the tailstock. Here, using the tool corner for the offset may prove useful.

A single tool may also have 3 cutting edges, such as a specific grind on HSS for OD chamfers towards chuck, tailstock and ID chamfers for holes (the 'Tom Lipton grind'). For this, setting one corner (the 'top corner' as one tool and the chuck facing corner as a separate tool may be preferable. This will require multiple labels on the tool holder.

### Radius cutting mode

1. Set fillet dimensions, either start+end+centre offsets (like G2 XY IJK) or end point and radius (G2 XY R)
2. Set number of cuts
3. Move to first cut, crank X axis to zero, and feed Z axis until zero
4. back out, index next cut
5. repeat steps 3-4 until complete

## Detailed Mill Functions

### Hole pattern calculator (PCD)

1. Set centre XYZ
2. Set diameter of PCD
3. Set hole count
4. Set starting XYZ or starting angle
