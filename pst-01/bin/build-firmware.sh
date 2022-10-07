#! /bin/bash

# -------------- the main function --------------

main() {
  prepare
  print_config
  compile_qmk_code
  copy_result_to_some_places
}

# -------------- initial preparations and includes --------------

# Set the current directory to be able to run this script from anywhere:
readonly script_dir=$(cd "$(dirname "$0")" && pwd)
cd "${script_dir}"

#
# Preparations in order to run the script smoothly.
#
prepare() {
  set -eo pipefail # Stop this script from executing as soon as an error occurs.

  local result_dir="../../../qmk_home/.build"
  readonly result_file="${result_dir}/splitkb_kyria_rev1_pst-01.hex"
}

#
# Prints the config - just to be sure we are on the right track.
# Should be:
#   multibuild.keymap=default
#   user.keyboard=splitkb/kyria/rev1
#   user.keymap=pst-01
#   user.qmk_home=/home/peter/dev/qmk/qmk_home
#
print_config() {
  echo "[INFO] Currently used config:"
  # qmk config user.keymap=pst-01
  qmk config
  echo
}

#
# Compiles the actual code.
# There is no need to cd into our source directory as the config tells qmk where to find it.
#
compile_qmk_code() {
  echo "[INFO] Compiling code."
  qmk compile
}

#
# Copies the resulting hex file into our source directory and to the place where the flashing takes place.
#
copy_result_to_some_places() {
  echo "[INFO] Copying resulting .hex file to local bin directory."
  cp ${result_file} .

  echo "[INFO] Copying resulting .hex file to the flashy place."
  cp ${result_file} ~/documents/vmshare/qmk/compiled_hexes
}

# -------------- calling the main function --------------

main "${@}"
