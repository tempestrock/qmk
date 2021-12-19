#
# rules.mk
# Rules for making the firmware.
#

SRC += leader-key.c
SRC += oled.c
SRC += rotary-encoder.c
SRC += rgb-light.c
SRC += typing.c

LTO_ENABLE = yes

AUDIO_ENABLE = no          # Audio output on port C6
BACKLIGHT_ENABLE = no      # Enable keyboard backlight functionality on B7 by default
BLUETOOTH_ENABLE = no      # Enable Bluetooth with the Adafruit EZ-Key HID
BOOTMAGIC_ENABLE = no      # lite    # Only enable key to jump into bootlaoder
COMBO_ENABLE = no
COMMAND_ENABLE = no        # Commands for debug and configuration
CONSOLE_ENABLE = no        # Console for debug
ENCODER_ENABLE = yes       # Enables the use of one or more encoders
EXTRAKEY_ENABLE = yes      # Audio control and System control
FAUXCLICKY_ENABLE = no     # Use buzzer to emulate clicky switches
GRAVE_ESC_ENABLE = no
HD44780_ENABLE = no        # Enable support for HD44780 based LCDs
LEADER_ENABLE = yes        # Enable leader key
MAGIC_ENABLE = no
MIDI_ENABLE = no           # MIDI support
MOUSEKEY_ENABLE = no       # Mouse keys - save some space by disabling this flag
NKRO_ENABLE = no           # USB Nkey Rollover
OLED_DRIVER = SSD1306      # Enables the use of OLED displays
OLED_DRIVER_ENABLE = yes   # Enables the use of OLED displays
OLED_ENABLE = yes          # OLED enabling - save a lot of space by disabling this flag
RAW_ENABLE = no
RGBLIGHT_ENABLE = yes      # Enable keyboard RGB underglow
SLEEP_LED_ENABLE = no
SPACE_CADET_ENABLE = no
SPLIT_KEYBOARD = yes
SWAP_HANDS_ENABLE = no     # Allow swapping hands of keyboard
TAP_DANCE_ENABLE = no      # Allow tap dancing
UNICODE_ENABLE = no        # Unicode for Umlauts
VIRTSER_ENABLE = no
WPM_ENABLE = no
