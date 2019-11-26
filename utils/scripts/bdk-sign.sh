#!/bin/sh
# ***********************license start***********************************
# Copyright (C) 2018 Marvell International Ltd.
# SPDX-License-Identifier: BSD-3-Clause
# https://spdx.org/licenses
# **********************license end**************************************

# This script is used by the BDK for all signing. The inputs to this script
# are three arguments:
#   KEY_NAME: Name of the key to use for signing
#   OUTPUT: Name of the file to store the signature in
#   INPUT: Name of the file to sign
#
# The type of signing performed is NIST P-256, or prime256v1 on OpenSSL
# terms. Actual signing is performed using the replaceable script
# bdk-sign-default.sh. A customer may replace the script by defining the
# BDK_SIGN_COMMAND environment variable. This script adds the necessary
# AES128 padding to the standard signature file. This is needed so the
# files don't change size after they are encrypted. See the BDK manual
# for more information about BDK_SIGN_COMMAND.
#
# Argument details:
# KEY_NAME
# This is the logical name of the key to use for signing. The BDK will pass
# one of the following names:
#   hw-rot-private
#       This is the private key to go with the public key hash programmed
#       into the hardware ROT. It signs the following:
#           trust-keys/bdk-sign.pub
#           CSIB for target-bin/scp_bl1.exe
#           CSIB for target-bin/mcp_bl1.exe
#           CSIB for apps/boot/boot.bin
#   bdk-sign-private
#       This key is signed by hw-rot-private and used to sign all BDK files
#       after the initial boot.bin, signed above.
#
# OUTPUT
# The signature of a file is stored in an independent file with the same
# name, except ".sign" appended. The file is a ASN.1 encoded point on the
# EC curve padded to a multiple of 16 bytes, the AES128 key size.
#
# INPUT
# The format of the input file is arbitrary data

if [ "${BDK_ROOT}" = "" ]
then
    echo "The BDK_ROOT environment variable is not set"
    exit 1
fi

# Names for the input arguments
KEY_NAME=$1
OUTPUT=$2
INPUT=$3

# The BDK doesn't add any headers to the internal filesystem files. This
# means the BDK can't detect that AES128 encryption may add padding. Since
# the padding affects the signing result, we add the padding before doing
# the signing.
${BDK_ROOT}/bin/bdk-aes-pad ${INPUT} || exit 1

# Only use our default implementation if BDK_SIGN_COMMAND is not defined
if [ "${BDK_SIGN_COMMAND}" = "" ]
then
    BDK_SIGN_COMMAND=${BDK_ROOT}/utils/scripts/bdk-sign-default.sh
fi

# Perform the signature
${BDK_SIGN_COMMAND} sign ${KEY_NAME} ${OUTPUT} ${INPUT} || exit 1

# Like the input, AES128 s applied to the signing file too. Add the proper
# padding.
${BDK_ROOT}/bin/bdk-aes-pad ${OUTPUT} || exit 1

# Return good status
exit 0

