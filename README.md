# OpenDRO

## Description
OpenDRO is a project to make a DRO with Arduino(s) for machine tools, such as
lathes and milling machines.

## Layout
The general architecture is to use 3 (or more) ATtiny85 units to do low level
reads, quickly. They send the number of counts of the encoder to a master
controller (likely an ATmega328 or similar) when polled over an I2C bus.

## TODO
- [x] Write the axis_decoder
- [ ] Confirm the axis_decoders work (and does NOT skip counts when moved)
  - [ ] If lost counts, attempt 16MHz or 20MHz operation, and try reading `PORTB` bits rather than `digitalRead()`
- [ ] Write a master
  - [ ] Buttons and functions to the master
- [ ] Design a board schematic
- [ ] Design a board layout
- [ ] Design an enclosure
- [ ] Construct the first unit
  - [ ] Fab the first PCB
  - [ ] Order components
  - [ ] Assemble first PCB
  - [ ] Insert board into enclosure
  - [ ] Test out the wazoo
