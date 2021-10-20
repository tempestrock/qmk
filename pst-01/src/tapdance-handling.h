/*
 * tapdance-handling.h
 * Declarations for the tapdance handling
 */

#ifndef TAPDANCE_HANDLING_H
#define TAPDANCE_HANDLING_H

/**
 * Shortcuts for an easier use in keymaps
 */
#define TD_A_AE  TD(A_TO_AE)
#define TD_E_EUR TD(E_TO_EUR)
#define TD_O_OE  TD(O_TO_OE)
#define TD_U_UE  TD(U_TO_UE)
#define TD_S_SZ  TD(S_TO_SZ)
#define TD_SPDWN TD(SPACE_DOWN)

/**
 * Indexes for the tap_dance_actions array
 */
enum {
  A_TO_AE,
  E_TO_EUR,
  O_TO_OE,
  U_TO_UE,
  S_TO_SZ,
  SPACE_DOWN
};

#endif
