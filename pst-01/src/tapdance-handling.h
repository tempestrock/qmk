/*
 * tapdance-handling.h
 */

#ifndef TAPDANCE_HANDLING_H
#define TAPDANCE_HANDLING_H

#include <keymap_german.h>

// --------------- Tap Dance definitions ---------------

enum {
    A_TO_AE,
    E_TO_EUR,
    O_TO_OE,
    U_TO_UE,
    S_TO_SZ
};

#define TD_A_AE  TD(A_TO_AE)
#define TD_E_EUR TD(E_TO_EUR)
#define TD_O_OE  TD(O_TO_OE)
#define TD_U_UE  TD(U_TO_UE)
#define TD_S_SZ  TD(S_TO_SZ)

qk_tap_dance_action_t tap_dance_actions[] = {
    [A_TO_AE] = ACTION_TAP_DANCE_DOUBLE(KC_A, DE_ADIA),
    [E_TO_EUR] = ACTION_TAP_DANCE_DOUBLE(KC_E, DE_EURO),
    [O_TO_OE] = ACTION_TAP_DANCE_DOUBLE(KC_O, DE_ODIA),
    [U_TO_UE] = ACTION_TAP_DANCE_DOUBLE(KC_U, DE_UDIA),
    [S_TO_SZ] = ACTION_TAP_DANCE_DOUBLE(KC_S, DE_SS)
};

// TODO: Unclear: What happens with capital umlauts like Ä, Ö, Ü, and capital ß?

#endif
