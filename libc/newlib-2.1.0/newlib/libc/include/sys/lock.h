#ifndef __SYS_LOCK_H__
#define __SYS_LOCK_H__

#if 0 /* Changed for the BDK */

/* dummy lock routines for single-threaded aps */

typedef int _LOCK_T;
typedef int _LOCK_RECURSIVE_T;
 
#include <_ansi.h>

#define __LOCK_INIT(class,lock) static int lock = 0;
#define __LOCK_INIT_RECURSIVE(class,lock) static int lock = 0;
#define __lock_init(lock) (_CAST_VOID 0)
#define __lock_init_recursive(lock) (_CAST_VOID 0)
#define __lock_close(lock) (_CAST_VOID 0)
#define __lock_close_recursive(lock) (_CAST_VOID 0)
#define __lock_acquire(lock) (_CAST_VOID 0)
#define __lock_acquire_recursive(lock) (_CAST_VOID 0)
#define __lock_try_acquire(lock) (_CAST_VOID 0)
#define __lock_try_acquire_recursive(lock) (_CAST_VOID 0)
#define __lock_release(lock) (_CAST_VOID 0)
#define __lock_release_recursive(lock) (_CAST_VOID 0)

#else /* Changed for the BDK */

#include "bdk-rlock.h"

typedef bdk_rlock_t _LOCK_T;
typedef bdk_rlock_t _LOCK_RECURSIVE_T;

#define __LOCK_INIT(class,lock) class bdk_rlock_t lock = {0,0};
#define __LOCK_INIT_RECURSIVE(class,lock) class bdk_rlock_t lock = {0,0};
#define __lock_init(lock) bdk_rlock_init(&lock)
#define __lock_init_recursive(lock) bdk_rlock_init(&lock)
#define __lock_close(lock) (_CAST_VOID 0)
#define __lock_close_recursive(lock) (_CAST_VOID 0)
#define __lock_acquire(lock) bdk_rlock_lock(&lock)
#define __lock_acquire_recursive(lock) bdk_rlock_lock(&lock)
#define __lock_try_acquire(lock) bdk_rlock_try_lock(&lock)
#define __lock_try_acquire_recursive(lock) bdk_rlock_try_lock(&lock)
#define __lock_release(lock) bdk_rlock_unlock(&lock)
#define __lock_release_recursive(lock) bdk_rlock_unlock(&lock)

#endif /* Changed for the BDK */

#endif /* __SYS_LOCK_H__ */
