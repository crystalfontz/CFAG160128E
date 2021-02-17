# CFAF240320A0-024Sx-A1

Example Seeeduino (Arduino clone) code for the Crystalfontz CFAG160128E family of displays. More information about these displays can be found at the following links.

[CFAG160128E1-TMI-TZ](https://www.crystalfontz.com/product/cfag160128e1tmitz)\
[CFAG160128E-YYH-TZ](https://www.crystalfontz.com/product/cfag160128eyyhtz)

This code is also compatible with this old version that has been replaced by the "E1"
[CFAG160128E-TMI-TZ](https://www.crystalfontz.com/product/cfag160128etmitz)


## Connection Details
### 8080 parallel configuration
```c++
//   ARD      | Port  |            |  Function - 8080 Parallel   |
//------------+-------+------------+-----------------------------+
//  3.3V      |       | 3          |  POWER 3.3V                 |
//  GND	      |       | 2          |  GROUND                     |
// -----------+-------+------------+-----------------------------+
//  D8        | PORTC | 6          |  Write               (WR)   |
//  D9        | PORTC | 7          |  Read                (RD)   |
//  D10       | PORTB | 8          |  Chip Enable Signal  (CS)   |
//  D11       | PORTC | 9          |  Data/Command        (DC)   |
//  D12       | PORTB | 11         |  Reset            (RESET)   |
// -----------+-------+------------+-----------------------------+
//  D0        | PORTD | 12         |  (DB0)                      |
//  D1        | PORTD | 13         |  (DB1)                      |
//  D2        | PORTD | 14         |  (DB2)                      |
//  D3        | PORTD | 15         |  (DB3)                      |
//  D4        | PORTD | 16         |  (DB4)                      |
//  D5        | PORTD | 17         |  (DB5)                      |
//  D6        | PORTD | 18         |  (DB6)                      |
//  D7        | PORTD | 19         |  (DB7)                      |
```