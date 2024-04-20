#!/bin/bash

# use to generate x509 key pair

CONFIG=x509.genkey
PUB_KEY=signing_key.x509
PRI_KEY=signing_key.priv

openssl req -x509 -new -nodes -utf8 -sha256 -days 36500 \
    -batch -config $CONFIG -outform DER \
    -out $PUB_KEY \
    -keyout $PRI_KEY

echo "public key is:	$PUB_KEY"
echo "private key is:	$PUB_KEY"

