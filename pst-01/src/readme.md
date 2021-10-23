# Peter's Kyria Keyboard

![Peter's Keyboard Layout](../resources/keymap.png)

## Concept

The basic concept of the design of this keymap is:

 - to put the most often used keys under the strongest fingers
 - to use only a few number of layers
 - to be as free as possible and not stick to any conventions

The layers of this keymap are the following:
1. Base layer (Colemak-PST which is Colemak-DH with some personal key-swaps)
2. "Down" layer which handles all number keys and the rest of the symbols
3. Function layer which takes care of F1 through F12
4. Lights layer handling the cool underglow LEDs

## Things in Detail

### Umlauts and ß

Umlauts can be found by double-tapping the respective 'normal' keys <kbd>a</kbd>, <kbd>o</kbd>, and <kbd>u</kbd>.  
The <kbd>ß</kbd> is created by double-tapping <kbd>v</kbd>. I decided not to put it under the <kbd>s</kbd> key in order to still be able to tap <kbd>ss</kbd> in a fast manner.

### Volume
The left rotary encoder is programmed to control the volume whereas the right encoder sends <kbd>PgUp</kbd> or <kbd>PgDn</kbd> on every turn.

### OLEDs
The OLEDs display the current layer at the top of the active layers stack, the Kyria logo and lock status (caps lock, num lock, scroll lock).


## Organization of the Source Code

The source code is structured in a way that the handling of special functions can be found in different source files:

- `keymap.c`: The main file that includes all other `.h` files. It also contains the definition of the keymap layers.
- `leader-key.c`: Handling of the 'leader key'.
- `oled.c`: Definition of messages on the displays (not yet implemented).
- `rotary-encoder.c`: Everything that has to do with the rotary knob.
- `tapdance.c`: Handling the "tap dance", i.e. multiply typing and holding keys and getting different results from that.

In order for the `.c` files to be linked into the resulting firmware, they need
to be mentioned in `rules.mk` in the way `SRC += tapdance.c`.
