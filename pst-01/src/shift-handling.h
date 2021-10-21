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
 * Partner definitions: Which key needs to be pressed together with <Shift> in order to get the actual key.
 * PK stands for 'partner key'.
 */
#define PK_AT         DE_Q    // altgr(Q) --> @
#define PK_PIPE       DE_LABK // altgr(<) --> |
#define PK_LCURLBRKT  DE_7    // altgr(7) --> {
#define PK_RCURLBRKT  DE_0    // altgr(0) --> }
#define PK_LPAREN     DE_8    // shift(8) --> (
#define PK_RPAREN     DE_9    // shift(9) --> )
#define PK_LBRACKET   DE_8    // altgr(8) --> [
#define PK_RBRACKET   DE_9    // altgr(9) --> ]
#define PK_SLASH      DE_7    // shift(7) --> /
#define PK_TILDA      DE_PLUS // altgr(+) --> ~
#define PK_PERCENT    DE_5    // shift(5) --> %
#define PK_AMPERSAND  DE_6    // shift(6) --> &
#define PK_GRAVE      DE_ACUT // shift(´) --> `
#define PK_EQUAL      DE_0    // shift(0) --> =
#define PK_ASTERISK   DE_PLUS // shift(+) --> *
#define PK_UNDERSCORE DE_MINS // shift(-) --> _
#define PK_DOLLAR     DE_4    // shift(4) --> $
#define PK_PARAGRAPH  DE_3    // shift(3) --> §

/*
 * Handling of special keys for the case that:
 *  - normal usage shall create a key press of a key code that does not need <Shift>,
 *  - shift usage shall create a key press of a key code that does not need <Shift>.
 * @param kc1 the key code for the normal usage that is to be pressed directly
 * @param kc2 the key code for shift usage that is to be pressed directly
 */
#define NNOSHIFT_SNOSHIFT(kc1, kc2)                                                                                    \
  if (record->event.pressed) {                                                                                         \
    if (!(get_mods() & MOD_BIT(KC_RSHIFT))) {                                                                          \
      /* press the 1st key directly without shift */                                                                   \
      register_code(kc1);                                                                                              \
    } else {                                                                                                           \
      /* Shift is pressed but we don't want that. --> turn off shift */                                                \
      unregister_code(KC_RSHIFT);                                                                                      \
      register_code(kc2);                                                                                              \
      /* Turn on shift again so that lifting the shift key afterwards makes sense */                                   \
      register_code(KC_RSHIFT);                                                                                        \
    }                                                                                                                  \
  } else {                                                                                                             \
    unregister_code(kc1);                                                                                              \
    unregister_code(kc2);                                                                                              \
  }                                                                                                                    \
  return false;

/*
 * Handling of special keys for the case that:
 *  - normal usage shall create a key press of a key code that does not need <Shift> but needs <Altgr>,
 *  - shift usage shall create a key press of a key code that does not need <Shift> but needs <Altgr>.
 * @param pk1 the partner key code for the normal usage that is to be pressed in combination with Altgr
 * @param pk2 the partner key code for shift usage that is to be pressed in combination with Altgr
 */
#define NALTGR_SALTGR(pk1, pk2)                                                                                        \
  if (record->event.pressed) {                                                                                         \
    if (!(get_mods() & MOD_BIT(KC_RSHIFT))) {                                                                          \
      /* press the 1st key directly without shift but with Altgr */                                                    \
      register_code(KC_ALGR);                                                                                          \
      register_code(pk1);                                                                                              \
      unregister_code(KC_ALGR);                                                                                        \
    } else {                                                                                                           \
      /* Shift is pressed but we don't want that. --> turn off shift but turn on Altgr */                              \
      unregister_code(KC_RSHIFT);                                                                                      \
      register_code(KC_ALGR);                                                                                          \
      register_code(pk2);                                                                                              \
      unregister_code(KC_ALGR);                                                                                        \
      /* Turn on shift again so that lifting the shift key afterwards makes sense */                                   \
      register_code(KC_RSHIFT);                                                                                        \
    }                                                                                                                  \
  } else {                                                                                                             \
    unregister_code(pk1);                                                                                              \
    unregister_code(pk2);                                                                                              \
  }                                                                                                                    \
  return false;

/*
 * Handling of special keys for the case that:
 *  - normal usage shall create a key press of a key code that does not need <Shift>,
 *  - shift usage shall create a key press of a key code that needs <Shift>.
 * @param kc1 the key code for the normal usage that is to be pressed directly
 * @param pk2 the partner key code for shift usage that results in the wanted key code when <Shift> is pressed
 */
#define NNOSHIFT_SSHIFT(kc1, pk2)                                                                                      \
  if (record->event.pressed) {                                                                                         \
    if (!(get_mods() & MOD_BIT(KC_RSHIFT))) {                                                                          \
      /* press the 1st key without shift */                                                                            \
      register_code(kc1);                                                                                              \
    } else {                                                                                                           \
      /* Shift is already pressed. Now press pk2 in order to get the actually wanted result */                         \
      register_code(pk2);                                                                                              \
    }                                                                                                                  \
  } else {                                                                                                             \
    unregister_code(kc1);                                                                                              \
    unregister_code(pk2);                                                                                              \
  }                                                                                                                    \
  return false;

/*
 * Handling of special keys for the case that:
 *  - normal usage shall create a key press of a key code that does not need <Shift> but is a dead key (e.g. ^)
 *  - shift usage shall create a key press of a key code that needs <Shift> and is a dead key (e.g. `).
 * @param kc1 the key code for the normal usage that is to be pressed directly
 * @param pk2 the partner key code for shift usage that results in the wanted key code when <Shift> is pressed
 */
#define NNOSHIFTDEAD_SSHIFTDEAD(kc1, pk2)                                                                              \
  if (record->event.pressed) {                                                                                         \
    if (!(get_mods() & MOD_BIT(KC_RSHIFT))) {                                                                          \
      /* press the 1st key twice without shift in order to make the dead key alive */                                  \
      tap_code(kc1);                                                                                                   \
      register_code(kc1);                                                                                              \
    } else {                                                                                                           \
      /* Shift is already pressed. Now press pk2 twice in order to get the actually wanted result and to make the dead \
       * key alive */                                                                                                  \
      tap_code(pk2);                                                                                                   \
      register_code(pk2);                                                                                              \
    }                                                                                                                  \
  } else {                                                                                                             \
    unregister_code(kc1);                                                                                              \
    unregister_code(pk2);                                                                                              \
  }                                                                                                                    \
  return false;

/*
 * Handling of special keys for the case that:
 *  - normal usage shall create a key press of a key code that does not need <Shift> but is a dead key (e.g. ^)
 *  - shift usage shall do nothing
 * @param kc1 the key code for the normal usage that is to be pressed directly
 */
#define NNOSHIFTDEAD_SNONE(kc1)                                                                                        \
  if (record->event.pressed) {                                                                                         \
    if (!(get_mods() & MOD_BIT(KC_RSHIFT))) {                                                                          \
      /* press the 1st key twice without shift in order to make the dead key alive */                                  \
      tap_code(kc1);                                                                                                   \
      register_code(kc1);                                                                                              \
    }                                                                                                                  \
  } else {                                                                                                             \
    unregister_code(kc1);                                                                                              \
  }                                                                                                                    \
  return false;

/*
 * Handling of special keys for the case that:
 *  - normal usage shall create a key press of a key code that needs <Shift>,
 *  - shift usage shall create a key press of a key code that does not need <Shift>.
 * @param pk1 the partner key code for the normal usage that results in the wanted key code when <Shift> is pressed
 * @param kc2 the key code for shift usage that is to be pressed directly
 */
#define NSHIFT_SNOSHIFT(pk1, kc2)                                                                                      \
  if (record->event.pressed) {                                                                                         \
    if (!(get_mods() & MOD_BIT(KC_RSHIFT))) {                                                                          \
      /* Shift key not pressed. In order to get the resulting key pressed, we need to press <Shift>-pk1 */             \
      register_code(KC_RSHIFT);                                                                                        \
      register_code(pk1);                                                                                              \
      unregister_code(KC_RSHIFT);                                                                                      \
    } else {                                                                                                           \
      /* Shift is pressed but we don't want that. --> turn off shift */                                                \
      unregister_code(KC_RSHIFT);                                                                                      \
      register_code(kc2);                                                                                              \
      /* Turn on shift again so that lifting the shift key afterwards makes sense */                                   \
      register_code(KC_RSHIFT);                                                                                        \
    }                                                                                                                  \
  } else {                                                                                                             \
    unregister_code(pk1);                                                                                              \
    unregister_code(kc2);                                                                                              \
  }                                                                                                                    \
  return false;

/*
 * Handling of special keys for the case that:
 *  - normal usage shall create a key press of a key code that needs <Shift>,
 *  - shift usage shall create a key press of a key code that does not need <Shift> but needs <Altgr>.
 * @param pk1 the partner key code for the normal usage that results in the wanted key code when <Shift> is pressed
 * @param pk2 the partner key code for shift usage that is to be pressed in combination with Altgr
 */
#define NSHIFT_SALTGR(pk1, pk2)                                                                                        \
  if (record->event.pressed) {                                                                                         \
    if (!(get_mods() & MOD_BIT(KC_RSHIFT))) {                                                                          \
      /* Shift key not pressed. In order to get the resulting key pressed, we need to press <Shift>-pk1 */             \
      register_code(KC_RSHIFT);                                                                                        \
      register_code(pk1);                                                                                              \
      unregister_code(KC_RSHIFT);                                                                                      \
    } else {                                                                                                           \
      /* Shift is pressed but we don't want that. --> turn off shift but turn on Altgr */                              \
      unregister_code(KC_RSHIFT);                                                                                      \
      register_code(KC_ALGR);                                                                                          \
      register_code(pk2);                                                                                              \
      unregister_code(KC_ALGR);                                                                                        \
      /* Turn on shift again so that lifting the shift key afterwards makes sense */                                   \
      register_code(KC_RSHIFT);                                                                                        \
    }                                                                                                                  \
  } else {                                                                                                             \
    unregister_code(pk1);                                                                                              \
    unregister_code(pk2);                                                                                              \
  }                                                                                                                    \
  return false;

/*
 * Handling of special keys for the case that:
 *  - normal usage shall create a key press of a key code that needs <Shift>,
 *  - shift usage shall create a key press of a key code that needs <Shift>.
 * @param pk1 the partner key code for the normal usage that results in the wanted key code when <Shift> is pressed
 * @param pk2 the partner key code for shift usage that results in the wanted key code when <Shift> is pressed
 */
#define NSHIFT_SSHIFT(pk1, pk2)                                                                                        \
  if (record->event.pressed) {                                                                                         \
    if (!(get_mods() & MOD_BIT(KC_RSHIFT))) {                                                                          \
      /* Shift key not pressed. In order to get the resulting key pressed, we need to press <Shift>-pk1 */             \
      register_code(KC_RSHIFT);                                                                                        \
      register_code(pk1);                                                                                              \
      unregister_code(KC_RSHIFT);                                                                                      \
    } else {                                                                                                           \
      /* Shift is already pressed. Now press pk2 in order to get the actually wanted result */                         \
      register_code(pk2);                                                                                              \
    }                                                                                                                  \
  } else {                                                                                                             \
    unregister_code(pk1);                                                                                              \
    unregister_code(pk2);                                                                                              \
  }                                                                                                                    \
  return false;

#endif /* SHIFT_HANDLING_H */
