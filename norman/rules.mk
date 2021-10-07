#HOWTO build
#make kyria:namron:flash

BOOTLOADER = qmk-dfu

#reduce build size
EXTRAFLAGS += -flto

MOUSEKEY_ENABLE = yes      # Mouse keys
TAP_DANCE_ENABLE=yes
OLED_DRIVER_ENABLE = yes   # Enables the use of OLED displays
ENCODER_ENABLE = yes       # ENables the use of one or more encoders
RGBLIGHT_ENABLE = yes      # Enable keyboard RGB underglow
BOOTMAGIC_ENABLE = lite    # Only enable key to jump into bootlaoder
EXTRAKEY_ENABLE = yes      # Audio control and System control
CONSOLE_ENABLE = no        # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
NKRO_ENABLE = no           # USB Nkey Rollover
BACKLIGHT_ENABLE = no      # Enable keyboard backlight functionality on B7 by default
MIDI_ENABLE = no           # MIDI support
UNICODE_ENABLE = no        # Unicode
BLUETOOTH_ENABLE = no      # Enable Bluetooth with the Adafruit EZ-Key HID
AUDIO_ENABLE = no          # Audio output on port C6
FAUXCLICKY_ENABLE = no     # Use buzzer to emulate clicky switches
HD44780_ENABLE = no        # Enable support for HD44780 based LCDs

SPLIT_TRANSPORT = mirror
