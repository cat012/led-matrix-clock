# led-matrix-clock
  8x8 LED matrix MAX7219 DS1307 ATmega328P

                           ________________ 
                          |arduino pro mini|
                          |  16MHz/8=2MHz  |
                          |                |
                          (tx/d1)      (raw)
                          (rx/d0)      (gnd)------- GND
                          (rst)        (rst)
                          (gnd)        (vcc)------- +3.3V
                          (2/d2)     (a3/c3)
     DS1307 I2C Data------(3/d3)     (a2/c2)
     DS1307 I2C Clock-----(4/d4)     (a1/c1)
     MAX7219 SPI Clock ---(5/d5)     (a0/c0)
     MAX7219 SPI CS ------(6/d6)     (13/b5)
     MAX7219 SPI Data ----(7/d7)     (12/b4)
                          (8/b0)     (11/b3)
                          (9/b1)     (10/b3)
                          |                |
                           ---------------- 
