/***********************license start***********************************
* Copyright (c) 2003-2017  Cavium Inc. (support@cavium.com). All rights
* reserved.
*
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*
*   * Neither the name of Cavium Inc. nor the names of
*     its contributors may be used to endorse or promote products
*     derived from this software without specific prior written
*     permission.
*
* This Software, including technical data, may be subject to U.S. export
* control laws, including the U.S. Export Administration Act and its
* associated regulations, and may be subject to export or import
* regulations in other countries.
*
* TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
* AND WITH ALL FAULTS AND CAVIUM INC. MAKES NO PROMISES, REPRESENTATIONS OR
* WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT
* TO THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY
* REPRESENTATION OR DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT
* DEFECTS, AND CAVIUM SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES
* OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR
* PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT,
* QUIET POSSESSION OR CORRESPONDENCE TO DESCRIPTION. THE ENTIRE  RISK
* ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE LIES WITH YOU.
***********************license end**************************************/
#include <bdk.h>
#include <assert.h>
#include <sys/lock.h>

/* These locks are in the sys/lock.h header since they are used by the C
    library */

void bdk_rlock_init(bdk_rlock_t *lock)
{
    lock->count = 0;
    lock->owner = NULL;
}

void bdk_rlock_lock(bdk_rlock_t *lock)
{
    void *current = bdk_thread_get_id();

    if (lock->count && (current == lock->owner))
    {
        lock->count++;
        return;
    }
    assert(current != lock->owner);
    do
    {
        while ((volatile uint32_t)lock->count)
            bdk_thread_yield();
    } while (bdk_atomic_compare_and_store32(&lock->count, 0, 1) == 0);
    assert(lock->owner == NULL);
    lock->owner = current;
}

int bdk_rlock_try_lock(bdk_rlock_t *lock)
{
    void *current = bdk_thread_get_id();
    if (lock->count)
    {
        if (current == lock->owner)
        {
            lock->count++;
            return 0;
        }
        else
            return -1;
    }
    else
    {
        assert(current != lock->owner);
        if (bdk_atomic_compare_and_store32(&lock->count, 0, 1))
        {
            assert(lock->owner == NULL);
            lock->owner = current;
            return 0;
        }
        else
            return -1;
    }
}

void bdk_rlock_unlock(bdk_rlock_t *lock)
{
    void *current = bdk_thread_get_id();
    assert(current == lock->owner);
    assert(lock->count > 0);
    if (lock->count == 1)
    {
        lock->owner = NULL;
        BDK_WMB;
        lock->count = 0;
        BDK_WMB;
    }
    else
        lock->count--;
}

