# Peter's Kyria Keyboard <!-- omit in toc -->

![Peter's Keyboard Layout](resources/keymap.png)

---

- [Concept](#concept)
- [Keymap in Detail](#keymap-in-detail)
  - [Umlauts, ß, and €](#umlauts-ß-and-)
  - [Symbols](#symbols)
  - [Shift](#shift)
  - [Digits and Function Keys](#digits-and-function-keys)
  - [Simplification of Some Key Combinations](#simplification-of-some-key-combinations)
  - [Volume and Brightness](#volume-and-brightness)
  - [Page Up/Down and Tab Hopping](#page-updown-and-tab-hopping)
  - [Predefined Messages](#predefined-messages)
  - [OLEDs](#oleds)
- [Organization of the Source Code](#organization-of-the-source-code)
  - [Structure](#structure)
  - [Optimization](#optimization)
  - [Building the Firmware](#building-the-firmware)
  - [IDE](#ide)
  - [Conventions](#conventions)
- [Painting the Keyboard Layout](#painting-the-keyboard-layout)

---

## Concept

The basic concept of the design of this keymap is:

 - to put the most often used keys under the strongest fingers
 - to use only a few number of layers
 - to be as free as possible and not stick to any conventions

The layers of this keymap are the following:
1. Base layer (Colemak-PST which is Colemak-DH with some personal key swaps)
2. "Down" layer which handles the digit keys and the rest of the symbols
3. Function layer which takes care of F1 through F12
4. Lights layer handling the cool underglow LEDs

## Keymap in Detail

### Umlauts, ß, and €

Throughout the implementation of the keymap we assume that the attached PC has the German keyboard layout defined.

Umlauts can be found by double-tapping the 'normal' keys <kbd>a</kbd>, <kbd>o</kbd>, and <kbd>u</kbd>, respectively. The € sign is under the <kbd>e</kbd>.  
The <kbd>ß</kbd> is created by double-tapping <kbd>v</kbd>. I decided not to put it under the <kbd>s</kbd> key in order to still be able to tap <kbd>ss</kbd> in a fast manner.

### Symbols

Most of the symbols are either directly reachable (like <kbd>@</kbd>, <kbd>&</kbd>, <kbd>/</kbd>, or <kbd>.</kbd> and <kbd>,</kbd>) or only need either <kbd>Shift</kbd> (like <kbd>|</kbd> or <kbd>~</kbd>) or <kbd>Down</kbd> (like <kbd>'</kbd>, <kbd>"</kbd>, or the opening brackets) in order to be reached. Only a few symbols are left that need both <kbd>Shift</kbd> and <kbd>Down</kbd> but these are almost only the closing brackets which in turn show some symmetry to the opening brackets.

There are no "dead" symbols anymore: <kbd>^</kbd>, <kbd>´</kbd>, and <kbd>`</kbd> are implemented to be automatically tapped twice if the user taps them once in order to directly show them. In turn, no 'é' and other characters that rely on these symbols are possible to be typed anymore.

### Shift

The combination of symbols (normal, "shifted", and "downed" typing) often does not follow any standard. Instead it is based on what I find useful for an efficient typing.

Implementing this was quite a pain: You have to know and take into account the original combination of normal, "shifted", and "altgr"ed typing. If you e.g. want a key to be available directly when the key is pressed but originally this symbol is reachable via <kbd>Shift</kbd>, then you have to register (= press down) <kbd>Shift</kbd> first, register the "partner" key (= the key that is necessary to be pressed in order to get the actually wanted symbol to appear in combination with <kbd>Shift</kbd>), and then unregister (= release) <kbd>Shift</kbd> again. The same is true for symbols that are reachable via <kbd>AltGr</kbd>.  
All of this led to an implementation of various macros that handle the different cases of "normal", "shifted", and "altgr"ed typing. (To be found in `shift-handling.h`.)

### Digits and Function Keys

The digits 1, 2, 3, etc. go from right to left because that felt better for me.

The function keys are reachable via the same keys as the digits, e.g. <kbd>F1</kbd> is on the same key as <kbd>1</kbd>. Only the <kbd>Fn</kbd> key needs to be previously held or tapped.

### Simplification of Some Key Combinations

Due to the fact that I use some key combinations very often, I paid special attention to their location:

- <kbd>Ctrl</kbd>-<kbd>x</kbd>, <kbd>Ctrl</kbd>-<kbd>c</kbd>, and <kbd>Ctrl</kbd>-<kbd>v</kbd> lie directly next to each other, and the <kbd>Ctrl</kbd> key is also on the left hand keymap in order to be able to access the key combination with only one hand.
- <kbd>Ctrl</kbd>-<kbd>Shift</kbd>-<kbd>something</kbd> is easily reachable by tapping and holding the right <kbd>Ctrl</kbd> key twice. (Implemented as tap dance.)
- Similarly, <kbd>Ctrl</kbd>-<kbd>Alt</kbd>-<kbd>something</kbd> is easily reachable by tapping and holding the right <kbd>Ctrl</kbd> key three times. (Implemented as tap dance.)
- <kbd>Alt</kbd> and <kbd>Tab</kbd> are very close to each other in order to switch the application windows fast.
- <kbd>Right Ctrl</kbd> is available to get out of the Linux virtual machine easily.
- <kbd>Alt</kbd>-<kbd>some digit</kbd> to directly select a browser tab or a file in VSCode can be reached via double-tapping and holding the <kbd>Down</kbd> key and typing the respective digit key. (Implemented as tap dance.)
- etc.

### Volume and Brightness
The left rotary knob is defined to control the volume.  
Using it together with the <kbd>Down</kbd> key the brightness is controlled.

### Page Up/Down and Tab Hopping
The right encoder sends <kbd>PgUp</kbd> or <kbd>PgDn</kbd> on every turn.  
In combination with the <kbd>Down</kbd> key the encoder jumps to the next and the previous tab (e.g. in a browser, a terminal, or in VSCode).

### Predefined Messages

The leader key in the bottom right corner of the keyboard can be used for a lot of fancy key combinations. Currently, some short messages for the closing greeting at the end of emails are defined for <kbd>Lead</kbd>-<kbd>M</kbd>-<kbd>some digit</kbd> where <kbd>some digit</kbd> is of course again just the respective key like <kbd>T</kbd> for 1, <kbd>S</kbd> for 2, etc. So no holding of the <kbd>Down</kbd> key is necessary. Also the <kbd>Lead</kbd> key is tapped, not held.

### OLEDs
To be implemented: The OLEDs display the current layer at the top of the active layers stack, the Kyria logo, and the lock status (caps lock, num lock, scroll lock).

## Organization of the Source Code

### Structure

The source code is structured in a way that the handling of special functions can be found in different source files:

- `keymap.c`: The main file that includes the other `.h` files and contains the definition of the keymap layers. It also defines the `process_record_user()` function which handles the press and release events for each key and the global function
`matrix_scan_user()` but only as the hull to call the respective functions of the sub areas.
- `leader-key.c`: Handling of the 'leader key'.
- `oled.c`: Definition of messages on the displays (not yet implemented).
- `rotary-encoder.c`: Everything that has to do with the rotary knob.
- `shift-handling.h`: Definition of various C macros that take care of the redefinition of keys for "normal" and "shifted" pressing.
- `tapdance.c`: Handling the "tap dance", i.e. multiply typing and holding keys and getting different results from that.

In order for the `.c` files to be linked into the resulting firmware, they need
to be mentioned in `rules.mk` in the way `SRC += tapdance.c`.

### Optimization

Memory is a costly good, so optimization during the compilation and the linking is highly recommended. Is is helpful to set the right definitions in the file `rules.mk`. These determine which modules are finally included in the resulting firmware.

### Building the Firmware

There is a small script `bin/build-firmware.sh` available to build the firmware and copy the resulting `.hex` file into the `bin` directory. This way also the latest version of the firmware is stored in the Git repo.

### IDE

I use VSCode in combination with clang (version 12) to write and format the C code. The clang settings are as follows:

```
{ BasedOnStyle: LLVM, UseTab: Never, IndentWidth: 2, TabWidth: 2, BreakBeforeBraces: Attach, AllowShortIfStatementsOnASingleLine: false, IndentCaseLabels: false, ColumnLimit: 120, AccessModifierOffset: -4, NamespaceIndentation: All, FixNamespaceComments: false, AlignConsecutiveMacros: AcrossEmptyLines }
```

### Conventions

We use the long keycode names (like <kbd>KC_ENTER</kbd> and <kbd>KC_LSHIFT</kbd>) whenever we can. Only in the matrix definition of the
keymap we use the short names (like <kbd>KC_ENT</kbd> and <kbd>KC_LSFT</kbd>) because they fit better into the keyboard optics.

## Painting the Keyboard Layout

I used and still use the [keyboard layout editor](http://www.keyboard-layout-editor.com/) for painting the keyboard layout (see the image at the top of this page). This web-based application has various flaws:

- It is not updated anymore.
- Thus, it does not use TLS (`http` instead of `https`)!
- It is buggy when it comes to saving the results.

The definition of the layout is done in a `JSON` file which can be saved (downloaded) and (up)loaded. Unfortunately, the storage of the keymap is buggy. Therefore I need to handle two variants of the keymap. These two - and the resulting image - can be found in the `resources` directory.
