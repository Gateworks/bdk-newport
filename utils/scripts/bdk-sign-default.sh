#!/bin/sh
# ***********************license start***********************************
# Copyright (C) 2018 Marvell International Ltd.
# SPDX-License-Identifier: BSD-3-Clause
# https://spdx.org/licenses
# **********************license end**************************************
#
# This script is used by the BDK for all signing by default. The inputs to
# this script are three arguments:
#   ACTION: Action to perform, either "sign" or "get-pub"
#   KEY_NAME: Name of the key to use for signing or getting the public key
#       This parameter will always be either "hw-rot-private" or
#       "bdk-sign-private". Implementations can use these keywords to select
#       which private key to use.
#   OUTPUT: Name of the file to store the signature or public key
#   INPUT: Name of the file to sign when ACTION is "sign". Unused for
#       getting the public key with ACTION "get-pub".
#
# The type of signing performed is NIST P-256, or prime256v1 on OpenSSL
# terms. The implementation of this script uses the local OpenSSL
# implementation and stores all keys in the BDK directory "trust-keys".
# Anyone wanting to replace this implementation may define the environment
# variable BDK_SIGN_COMMAND to replace this behavior. Once BDK_SIGN_COMMAND
# is defined, the BDK will call BDK_SIGN_COMMAND instead of this script. See
# the BDK manual for more information about BDK_SIGN_COMMAND.
#

# Check that BDK_ROOT is defined
if [ "${BDK_ROOT}" = "" ]
then
    echo "The BDK_ROOT environment variable is not set"
    exit 1
fi

# Names for the input arguments
ACTION=$1
KEY_NAME=$2
OUTPUT=$3
INPUT=$4

# This is where we store the private key. The BDK doesn't access this key
# at all. It is only present for the script's OpenSSL implementation.
KEY=${BDK_ROOT}/trust-keys/${KEY_NAME}.pem

if [ "${ACTION}" = "sign" ]
then
    # We're doing a signing
    openssl dgst -sha256 -binary -sign ${KEY} -out ${OUTPUT} ${INPUT} || exit 1
elif [ "${ACTION}" = "get-pub" ]
then
    if test -f ${KEY}
    then
        true # Private key already exists, reuse it
    else
        # Generate a private key for us to use, stored insecurely
        openssl ecparam -name prime256v1 -genkey -noout -out ${KEY} || exit 1
    fi
    # Generate the matching public key
    openssl ec -in ${KEY} -pubout -out ${OUTPUT} > /dev/null 2>&1 || exit 1
else
    echo "ERROR: Invalid parameter 1, ${ACTION}, pass to $0"
    exit 1
fi

