# Truck Window Retrofit

Retrofitted the manual crank windows on my 2002 Dodge Ram 1500 to 
automatic power windows using an Arduino, relays, motor drivers, and 
current sensing. Designed, wired, and documented entirely on my own. 
Also served as my Electronics class final.

[Full writeup and photos](https://portfolio-seven-mu-24.vercel.app/projects/truck-window-retrofit)

## How it works

The system has two circuits:

**Motor control** — Arduino Uno reads two debounced push buttons and 
controls a BTS7960 H-bridge motor driver. RPWM high rolls the window 
up, LPWM high rolls it down. A 20A Hall current sensor on the B- line 
detects stall current (~25A) when the window hits the end of travel, 
allowing the Arduino to cut the motor automatically.

**Car integration** — A 40/30A relay connects the motor driver to the 
car battery only when the ignition is on, preventing battery drain. 
A fuse tap into the "cluster overhead electric" fuse supplies the 12V 
low-power control line. A cracked-open cigarette lighter adapter steps 
12V down to 5V for the Arduino and sensors. A 30A inline fuse protects 
the high-power line.

A custom 3D-printed PLA adapter (press fit, printed in 5 tolerances) 
couples the motor spindle to the manual crank spindle.

## Parts

| Component | Details |
|---|---|
| Microcontroller | Arduino Uno |
| Motor | Dodge Ram window lift motor (12V DC) |
| Motor driver | BTS7960 43A H-bridge |
| Current sensor | ACS712 20A Hall sensor |
| Relay | 40/30A 5-pin automotive relay |
| Fuse tap | ATM mini dual fuse holder |
| Inline fuse | 30A |
| Power regulation | Cigarette lighter adapter (12V → 5V) |
| Wire | 12 AWG (high power), 18 AWG (control) |

## Pin mapping

| Arduino Pin | Connection |
|---|---|
| D5 | LPWM |
| D6 | RPWM |
| D7 | R_EN |
| D8 | L_EN |
| D12 | Up button |
| D13 | Down button |
| A5 | Current sensor output |

## Known issues / future improvements

- Control electronics currently zip-tied to floorboard — next step is 
  a custom PCB that consolidates everything into one clean board
- Buttons are breadboard-mounted — replacing with proper automotive 
  two-stage switches (half press = precise position, full press = 
  auto up/down)
- Current sensor stall detection is implemented in hardware but the 
  auto-up/down logic in firmware is not yet active (commented out)
- Passenger side window is the obvious next build
