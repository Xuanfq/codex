#!/bin/bash

SCRIPT_DIR=$(cd $(dirname $0);pwd)

MODULE_TBS=$1   # module to be signed

/usr/src/linux-headers-$(uname -r)/scripts/sign-file sha256 \
    $SCRIPT_DIR/signing_key.priv \
    $SCRIPT_DIR/signing_key.x509 \
    $MODULE_TBS


