
# x509

## setup / genkey

use `./genkey.sh` to generate the key pair.


## usage

### for kernel module development

1. `./addmok.sh`
2. reboot
3. select "Enroll MOK", then continue to enroll mok
4. use `signmod.sh /path/to/xxx.ko` to sign the module(xxx.ko) you developed and built.


