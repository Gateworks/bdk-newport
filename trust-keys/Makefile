# Value to use for the Fused Non-Volatile counter
NV_COUNT?=0

#
# Main target: all
#
.PHONY: all
all: bdk-sign.pub.sign

#
# Hardware fuses contain a SHA256 hash of a NIST256p/prime256v1 Elliptic curve
# public key. These targets create a public and private key pair
#
hw-rot-private.pem:
	openssl ecparam -name prime256v1 -genkey -noout -out $@

#
# All BDK signing for trusted boot uses a software root of trust key, signed by
# the hardware root of trust. This limits the number of items that must be
# signed by the hardware root of trust to two, the TBL1FW and the this
# certificate.
#
bdk-sign-private.pem:
	openssl ecparam -name prime256v1 -genkey -noout -out $@

#
# BDK signing certificate, custom format
#
bdk-sign.pub: bdk-sign-private.pem
	$(BDK_ROOT)/bin/bdk-create-signed-public --key $^ --nv $(NV_COUNT) $@
bdk-sign.pub.sign: bdk-sign.pub hw-rot-private.pem
	openssl dgst -sha256 -binary -sign hw-rot-private.pem -out bdk-sign.pub.sign bdk-sign.pub
	$(BDK_ROOT)/bin/bdk-aes-pad bdk-sign.pub.sign

#
# Cleanup
#
.PHONY: clean
clean:
	rm -f bdk-sign.pub bdk-sign.pub.sign
.PHONY: distclean
distclean: clean
	rm -f hw-rot-private.pem bdk-sign-private.pem
