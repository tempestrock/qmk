/*
 * typing.c
 * A simple implementation as replacement for a wpm (words per minute) algorithm.
 */

#include QMK_KEYBOARD_H

// A gap of this number of milliseconds between two keystrokes means that the user is idle:
#define IDLE_THRESHOLD 1500

// Timer to measure the time between two key strokes:
uint32_t typingTimer = 0;

/**
 * @return true if the user is currently typing, false otherwise.
 */
bool userIsTyping(void) {
  return (timer_elapsed32(typingTimer) < IDLE_THRESHOLD);
}

/**
 * Notify the timer that the user has just hit a key.
 */
void notifyTyping(void) {
  typingTimer = timer_read32();
}
