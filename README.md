# OpenDRO

## Description
OpenDRO is a project to make a DRO with Arduino(s) for machine tools, such as
lathes and milling machines.

## Layout
Several concepts currently exist, with only one design being actively persued
owing to hardware, time, interest, and so on. These designs are:
- [x] "Basic" - Single board with ATmega328. This is the active design.
  - [ ] 4 axes (these labels can be renamed on your enclosure! ;) ). Other axes
        likely work. I don't have everything to build up and test them yet. `X`
        axis will happen next, followed by `W` and `C` in that order.
    - [x] `Z` axis
    - [ ] `X` axis
    - [ ] `W` axis (tailstock)
    - [ ] `C` axis (rotation on spindle)
  - [ ] Unit selection
  - [ ] Zero each axis independently
    - [x] `Z` axis
    - [ ] `X` axis
    - [ ] `W` axis
    - [ ] `C` axis
- [ ] "Advanced" - Single board with ATmega2560 (not actively persued right now)
  - [ ] 4 axes
    - [x] `Z` axis
    - [ ] `X` axis
    - [ ] `W` axis (tailstock)
    - [ ] `C` axis (rotation on spindle)
  - [ ] Keypad for tool offset entry, tool call and other data entry.
- [ ] "Distributed" - Multiple boards, ATmega2560 main board, a daughterboard
      per axis containing a separate ATTiny85 for pulse counting and report back
      through I2C or SPI to main board (not actively persued right now).
    - [ ] Axis decoder code has been written, and is somewhere early in the git
          archives. This approach is not actively persued, the MCUs appear to be
          capable of handling the high interrupt speeds for human movements.
  - [ ] Keypad for tool offset entry, tool call and other data entry.
