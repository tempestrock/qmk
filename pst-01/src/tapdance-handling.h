/*
 * tapdance-handling.h
 */

#ifndef TAPDANCE_HANDLING_H
#define TAPDANCE_HANDLING_H

// --------------- Tap Dance definitions ---------------

enum {
    TD_A_TO_AE,
    TD_E_TO_EUR,
    TD_O_TO_OE,
    TD_U_TO_UE,
    TD_S_TO_SZ
};

#define TD_A_AE  TD(TD_A_TO_AE)
#define TD_E_EUR TD(TD_E_TO_EUR)
#define TD_O_OE  TD(TD_O_TO_OE)
#define TD_U_UE  TD(TD_U_TO_UE)
#define TD_S_SZ  TD(TD_S_TO_SZ)

qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_A_TO_AE] = ACTION_TAP_DANCE_DOUBLE(KC_A, DE_ae),
    [TD_E_TO_EUR] = ACTION_TAP_DANCE_DOUBLE(KC_E, DE_eur),
    [TD_O_TO_OE] = ACTION_TAP_DANCE_DOUBLE(KC_O, DE_oe),
    [TD_U_TO_UE] = ACTION_TAP_DANCE_DOUBLE(KC_U, DE_ue),
    [TD_S_TO_SZ] = ACTION_TAP_DANCE_DOUBLE(KC_S, DE_sz)
};

// TODO: Unclear: What happens with capital umlauts like Ä, Ö, Ü, and capital ß?

#endif
