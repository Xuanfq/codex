#!/bin/bash

# use to import machine owner key

PUB_KEY=signing_key.x509

sudo mokutil --import $PUB_KEY  # then you need to input and set the password

cat << EOF
# please take actions by yourself:
# 1. reboot
# 2. select "Enroll MOK"
# 3. continue to enroll mok
EOF
