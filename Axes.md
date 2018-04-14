## Axes
- Z (saddle on lathe, quill on mill)
- X (cross slide on lathe, long on mill)
- W (tail stock quill on lathe, Y axis on mill)
- C (rotary axis: spindle on lathe, rotary table on mill)
- S (spindle tacho on mill / lathe)

## Interrupt definitions
| Pin Description | Pin Name     | PC Interrupt | PCICR Bit | Pin Label |
|-----------------|--------------|--------------|-----------|-----------|
| Axis Z A        | `PK0`        | `PCINT16`    | 2         | `A8`      |
| Axis Z B        | `PK1`        | `PCINT17`    | 2         | `A9`      |
| Axis Z Z        | No interrupt |              |           |           |
| Axis X A        | `PK2`        | `PCINT18`    | 2         | `A10`     |
| Axis X B        | `PK3`        | `PCINT19`    | 2         | `A11`     |
| Axis X Z        | No interrupt |              |           |           |
| Axis W A        | `PK4`        | `PCINT20`    | 2         | `A12`     |
| Axis W B        | `PK5`        | `PCINT21`    | 2         | `A13`     |
| Axis W Z        | No interrupt |              |           |           |
| Axis C A        | `PK6`        | `PCINT22`    | 2         | `A14`     |
| Axis C B        | `PK7`        | `PCINT23`    | 2         | `A15`     |
| Axis S A        | `PB7`        | `PCINT7`     | 0         | `D13`     |

# Axis transition table
`x` = no change
| Prev Port | New Port  | Instruction |
|-----------|-----------|-------------|
| xxxx xx00 | xxxx xx01 | count_z++;  |
| xxxx xx00 | xxxx xx10 | count_z--;  |
| xxxx xx01 | xxxx xx11 | count_z++;  |
| xxxx xx01 | xxxx xx00 | count_z--;  |
| xxxx xx11 | xxxx xx10 | count_z++;  |
| xxxx xx11 | xxxx xx01 | count_z--;  |
| xxxx xx10 | xxxx xx00 | count_z++;  |
| xxxx xx10 | xxxx xx11 | count_z--;  |
|-----------|-----------|-------------|
| xxxx 00xx | xxxx 01xx | count_x++;  |
| xxxx 00xx | xxxx 10xx | count_x--;  |
| xxxx 01xx | xxxx 11xx | count_x++;  |
| xxxx 01xx | xxxx 00xx | count_x--;  |
| xxxx 11xx | xxxx 10xx | count_x++;  |
| xxxx 11xx | xxxx 01xx | count_x--;  |
| xxxx 10xx | xxxx 00xx | count_x++;  |
| xxxx 10xx | xxxx 11xx | count_x--;  |
|-----------|-----------|-------------|
| xx00 xxxx | xx01 xxxx | count_w++;  |
| xx00 xxxx | xx10 xxxx | count_w--;  |
| xx01 xxxx | xx11 xxxx | count_w++;  |
| xx01 xxxx | xx00 xxxx | count_w--;  |
| xx11 xxxx | xx10 xxxx | count_w++;  |
| xx11 xxxx | xx01 xxxx | count_w--;  |
| xx10 xxxx | xx00 xxxx | count_w++;  |
| xx10 xxxx | xx11 xxxx | count_w--;  |
|-----------|-----------|-------------|
| 00xx xxxx | 01xx xxxx | count_c++;  |
| 00xx xxxx | 10xx xxxx | count_c--;  |
| 01xx xxxx | 11xx xxxx | count_c++;  |
| 01xx xxxx | 00xx xxxx | count_c--;  |
| 11xx xxxx | 10xx xxxx | count_c++;  |
| 11xx xxxx | 01xx xxxx | count_c--;  |
| 10xx xxxx | 00xx xxxx | count_c++;  |
| 10xx xxxx | 11xx xxxx | count_c--;  |
|-----------|-----------|-------------|
This allows XOR on previous port state with new port state, and to shift bits
to detect changes.
