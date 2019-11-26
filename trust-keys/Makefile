# Value to use for the Fused Non-Volatile counter
NV_COUNT?=0

# Only use our default implementation if BDK_SIGN_COMMAND is not defined
BDK_SIGN_COMMAND?=$(BDK_ROOT)/utils/scripts/bdk-sign-default.sh

#
# Main target: all
#
.PHONY: all
all: bdk-sign.pub.sign

#
# Hardware fuses contain a SHA256 hash of a NIST256p/prime256v1 Elliptic curve
# public key. These targets create a public key
#
hw-rot-public.pem:
	$(BDK_SIGN_COMMAND) get-pub hw-rot-private $@

#
# All BDK signing for trusted boot uses a software root of trust key, signed by
# the hardware root of trust. This limits the number of items that must be
# signed by the hardware root of trust.
#
bdk-sign-public.pem:
	$(BDK_SIGN_COMMAND) get-pub bdk-sign-private $@

#
# BDK signing certificate, custom format
#
bdk-sign.pub: bdk-sign-public.pem
	$(BDK_ROOT)/bin/bdk-create-signed-public --key bdk-sign-public.pem --nv $(NV_COUNT) $@
bdk-sign.pub.sign: bdk-sign.pub hw-rot-public.pem
	$(BDK_ROOT)/bin/bdk-sign hw-rot-private bdk-sign.pub.sign bdk-sign.pub

#
# Cleanup
#
.PHONY: clean
clean:
	rm -f bdk-sign.pub bdk-sign.pub.sign *-public.pem
.PHONY: distclean
distclean: clean
	rm -f *-private.pem
