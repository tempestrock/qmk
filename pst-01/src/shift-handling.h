/*
 * shift-handling.h
 * Special shift handling for symbols.
 * We define the handling of symbols quite on our own, including the combination of symbols that lie
 * on the <Shift>-<whatever> keys. This leads to various combinations of what needs to be caught when
 * a symbol key is pressed: Each key may be pressed without or with the <Shift> key. 
 */

#ifndef SHIFT_HANDLING_H
#define SHIFT_HANDLING_H

/*
| Character | my keymap | US keymap |
├───────────┼───────────┼───────────┤
|  -        | no shift  | no shift  |
|  _        | shift (-) | shift (-) |
|  .        | no shift  | no shift  |
|  :        | shift (.) | shift (;) |
|  ,        | no shift  | no shift  |
|  ;        | shift (,) | no shift  |
|  ‘        | no shift  | no shift  |
|  “        | shift (‘) | shift (‘) |
|  !        | no shift  | shift (1) |
|  ?        | no shift  | shift (/) |
|  +        | no shift  | shift (=) |
|  #        | shift (+) | shift (3) |
|  =        | no shift  | no shift  |
|  *        | shift (=) | shift (8) |
|  %        | no shift  | shift (5) |
|  &        | shift (%) | shift (7) |
|  ^        | no shift  | shift (6) |
|  `        | shift (^) | no shift  |
|  ´        |  no shift
|  /        | no shift  | no shift  |
|  ~        | shift (/) | no shift? |
|  $        | no shift  | shift (4) |
|  paragraph
|  <        | no shift  | shift (,) |
|  >        | shift (<) | shift (.) |
|  {        | no shift  | shift ([) |
|  }        | shift (}) | shift (]) |
|  (        | no shift  | shift (9) |
|  )        | shift (() | shift (0) |
|  [        | no shift  | no shift  |
|  ]        | shift ([) | no shift  |
*/

/*
 * Partner definitions: Which key needs to be pressed together with <Shift> in order to get the actual key.
 * PK stands for 'partner key'.
 */
#define PK_AT KC_2
#define PK_PIPE KC_BSLASH
#define PK_DOT KC_DOT
#define PK_COLON KC_SCLN
#define PK_LBRACKET KC_LBRC
#define PK_RBRACKET KC_RBRC

/*
 * Handling of special keys for the case that:
 *  - normal usage shall create a key press of a key code that needs <Shift>,
 *  - shift usage shall create a key press of a key code that does not need <Shift>.
 * @param kc1 the key code for the normal usage that is to be pressed directly
 * @param kc2 the key code for shift usage that is to be pressed directly
 */
#define NNOSHIFT_SNOSHIFT(kc1,kc2) \
  if (record->event.pressed) { \
    if (!(get_mods() & MOD_BIT(KC_LSHIFT))) { \
      /* press the 1st key directly without shift */ \
      register_code(kc1); \
    } else { \
      /* Shift is pressed but we don't want that. --> turn off shift */ \
      unregister_code(KC_LSHIFT); \
      register_code(kc2); \
      /* Turn on shift again so that lifting the shift key afterwards makes sense */ \
      register_code(KC_LSHIFT); \
    } \
  } else { \
    unregister_code(kc1); \
    unregister_code(kc2); \
  } \
  return false;

/*
 * Handling of special keys for the case that:
 *  - normal usage shall create a key press of a key code that does not need <Shift>,
 *  - shift usage shall create a key press of a key code that needs <Shift>.
 * @param kc1 the key code for the normal usage that is to be pressed directly
 * @param kc2 the key code for shift usage that results in the wanted key code when <Shift> is pressed
 */
#define NNOSHIFT_SSHIFT(kc1,kc2) \
  if (record->event.pressed) { \
    if (!(get_mods() & MOD_BIT(KC_LSHIFT))) { \
      /* press the 1st key without shift */ \
      register_code(kc1); \
    } else { \
      /* Shift is already pressed. Now press kc2 in order to get the actually wanted result */ \
      register_code(kc2); \
    } \
  } else { \
    unregister_code(kc1); \
    unregister_code(kc2); \
  } \
  return false;

/*
 * Handling of special keys for the case that:
 *  - normal usage shall create a key press of a key code that needs <Shift>,
 *  - shift usage shall create a key press of a key code that does not need <Shift>.
 * @param kc1 the key code for the normal usage that results in the wanted key code when <Shift> is pressed
 * @param kc2 the key code for shift usage that is to be pressed directly
 */
#define NSHIFT_SNOSHIFT(kc1,kc2) \
  if (record->event.pressed) { \
    if (!(get_mods() & MOD_BIT(KC_LSHIFT))) { \
      /* Shift key not pressed. In order to get the resulting key pressed, we need to press <Shift>-kc1 */ \
      register_code(KC_LSHIFT); \
      register_code(kc1); \
      unregister_code(KC_LSHIFT); \
    } else { \
      /* Shift is pressed but we don't want that. --> turn off shift */ \
      unregister_code(KC_LSHIFT); \
      register_code(kc2); \
      /* Turn on shift again so that lifting the shift key afterwards makes sense */ \
      register_code(KC_LSHIFT); \
    } \
  } else { \
    unregister_code(kc1); \
    unregister_code(kc2); \
  } \
  return false;

/*
 * Handling of special keys for the case that:
 *  - normal usage (without <Shift> key) shall create a key press of a key code that needs <Shift>,
 *  - shift usage shall create a key press of a key code that needs <Shift>.
 * @param kc1 the key code for the normal usage that results in the wanted key code when <Shift> is pressed
 * @param kc2 the key code for shift usage that results in the wanted key code when <Shift> is pressed
 */
#define NSHIFT_SSHIFT(kc1,kc2) \
  if (record->event.pressed) { \
    if (!(get_mods() & MOD_BIT(KC_LSHIFT))) { \
      /* Shift key not pressed. In order to get the resulting key pressed, we need to press <Shift>-kc1 */ \
      register_code(KC_LSHIFT); \
      register_code(kc1); \
      unregister_code(KC_LSHIFT); \
    } else { \
      /* Shift is already pressed. Now press kc2 in order to get the actually wanted result */ \
      register_code(kc2); \
    } \
  } else { \
    unregister_code(kc1); \
    unregister_code(kc2); \
  } \
  return false;

#endif