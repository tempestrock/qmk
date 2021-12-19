/*
 * layers.h
 * Declaration of the available keymap layers
 */

#ifndef LAYERS_H
#define LAYERS_H

/**
 * The layers of the keymap.
 */
enum layers {
  _COLEMAK_PST = 0,
  _DOWN,
  _FUNCTION
  // _LIGHTS
};

#define NUM_LAYERS     3
#define MAX_STRING_SIZE 9
extern const char layer_name[NUM_LAYERS][MAX_STRING_SIZE];

#endif /* LAYERS_H */
