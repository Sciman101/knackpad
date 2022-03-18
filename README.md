# Knackpad
## An RP2040 based numpad
The knackpad is a simple, 17-key numpad with a 7 segment LCD and rotary encoder knob. It runs on custom firmware made with [arduino-pico](https://arduino-pico.readthedocs.io/) and features remappable action sets that can be switched on the fly.

# Design
I designed the knackpad to use random parts I had lying around. As such, it's kind of a mess in there. The most specific part is easily the Adafruit 7 segment display on the front, which can be swapped for other displays if you're willing to redesign the device a little. I also positioned the components with the idea of using it with my left hand - however, I want to create a second version of the files that can be mirrored while retaining the numpad's layout for the leftys out there.

# Keymaps
To define keymaps, you need to flash an `actions.ini` file to the pico's internal memory. This can be done through arduino-pico, as outlined [here](https://arduino-pico.readthedocs.io/en/latest/install.html#uploading-filesystem-images). Each of the number keys on the numpad corresponds to an input map, letting you have 10 in total. To access a keymap, hold the 'mode' key in the top left down and press one of the number keys. The system loads map 0 by default.

The `actions.ini` file is formatted as follows

```conf
[map0] ; The map to use, this corresponds to the key on the numpad. map0 is loaded by default

name=DFLT ; A 4-letter string to display on the 7-segment display when the map is selected

; The left hand side is the key to map, the right hand side it the action that will be sent over usb
k_0=escape
k_1=enter
k_2=backspace

; You can trigger multiple keypresses at once using the '+' symbol to join them
k_3=ctrl+s
; Prepending the key name with a caret will trigger when released
^k_3=alt+f4

; Prepending the action sequence with a ! will execute keys in order, instead of all at once
k_4=!h+e+l+l+o+space+w+o+r+l+d
; Prepending the action sequence with a '>' will cause the keyboard to type out the string following it
k_5=>Hello, world!

; Action sequences can be grouped using parenthases, and the previous modifiers can be chained in this manner
k_6=enter+(>Hello, world!)+enter

; You can escape a closing parenthases on a typing command with backslash
k_7=(ctrl+n)+(>System.out.println("Hello, world!"\);)

; To access the knob, use
dial_right=vol_up
dial_left=vol_down
dial_press=pause
; dial_left/dial_right do not have access to the 'released' modifier

[map1] ; Further maps
...
```

# Assembly

## BOM
- Raspberry Pi Pico (or other rp2040 microcontroller, you may need to modify the code to suit)
- MX compatible keyswitch (x17)
- [Adafruit 0.56" 7 segment display](https://www.adafruit.com/product/878)
- Rotary Encoder
- Little rubber feet (x4)
- Diode (x17) if using a matrix
- M3x8mm hex bolt (x6)

## Printed Parts
- Faceplate
- Base
- Knob

## Wiring
I thought, hey, the pico has more than enough GPIO to support each key being individually wired to a GPIO port, let's do that!

What a fool I was.

It *does* work, but I'd seriously reccomend using a matrix layout instead. I'll be adding a macro to the firmware once it's done to allow a matrix layout instead of directly wiring every key.