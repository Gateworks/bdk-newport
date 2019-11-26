/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

#include "dram-internal.h"
#include "bdk-dram-init-structures.h"
#include "bdk-leveling-display-fcns.h"
#include "bdk-read-spd.h"
#include "bdk-early-lmc-init.h"
#include "bdk-deskew-training.h"
#include "bdk-hw-write-leveling.h"
#include "bdk-hw-read-leveling.h"
#include "bdk-sw-write-leveling.h"
#include "bdk-final-lmc-init.h"

#if 0
// FIXMELATER FIXMELATER
//return the settings from dram_config_reference_t values
#define GET_REF_VAR_REFERENCE(NAME) {#NAME, *refs-> ## NAME }  \
inline uint64_t get_ref_var(NAME, dram_config_reference_t *refs)    \
    return (uint64_t)(GET_REF_VAR_REFERENCE(NAME));

//Set variables in dram_config_reference_t
#define SET_REF_VAR_REFERENCE(NAME) {#NAME, *refs-> ## NAME }  \
inline void set_ref_var(NAME, dram_config_reference_t *refs, uint64_t value)    \
    SET_REF_VAR_REFERENCE(NAME) = (uint64_t)value;
#endif

