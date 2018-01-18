# OpenDRO

## Description
OpenDRO is a project to make a DRO with Arduino(s) for machine tools, such as
lathes and milling machines.

## Layout
The general architecture is to use 3 (or more) ATtiny85 units to do low level
reads, quickly. They send the number of counts of the encoder to a master
controller (likely an ATmega328 or similar) when polled over an I2C bus.

## TODO
TODO List:

- [ ] Confirm the axis_decoders work (and do NOT skip counts when moved)
- [ ] Write a master
-   [ ] Buttons and functions to the master
- [ ] Design a board schematic
- [ ] Design a board layout
- [ ] Design an enclosure
- [ ] Construct the first unit
-   [ ] Fab the first PCB
-   [ ] Order components
-   [ ] Assemble first PCB
-   [ ] Insert board into enclosure
-   [ ] Test out the wazoo
