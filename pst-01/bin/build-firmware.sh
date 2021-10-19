#! /bin/bash

RESULT_DIR=../../../qmk_home/.build/
RESULT_FILE=${RESULT_DIR}/splitkb_kyria_rev1_pst-01.hex

qmk compile

echo "Copying resulting .hex file."
cp ${RESULT_FILE} .
