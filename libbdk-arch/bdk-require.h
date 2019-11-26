/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * Functions and macros to control what parts of the BDK are linked in
 *
 * <hr>$Revision: 49448 $<hr>
 * @defgroup require Component linking control
 * @{
 */

/**
 * Optional parts of the BDK code are pulled in by adding
 * BDK_REQUIRE() lines to the function bdk_require_depends().
 * Component symbols are defined as weak so that they are not
 * linked in unless a BDK_REQUIRE() pulls them in.
 */
#define BDK_REQUIRE(component)                                  \
    do                                                          \
    {                                                           \
        extern char __bdk_require_symbol_##component;           \
        bdk_warn_if(__bdk_require_symbol_##component,           \
            "Require of %s failed\n", #component);              \
    } while (0)

/**
 * The following macro defines a special symbol in a C file to
 * define it as a require component. Referencing this symbol
 * causes all objects defined in the C file to be pulled in. This
 * symbol should only be referenced by using the BDK_REQUIRE()
 * macro in the function bdk_require_depends().
 */
#define BDK_REQUIRE_DEFINE(component)           \
    char __bdk_require_symbol_##component;      \
    char __bdk_is_required_symbol_##component

/**
 * Return if a component has been required. Useful for if
 * statements around referencing of weak symbols.
 */
#define BDK_IS_REQUIRED(component)                                          \
    ({int is_required;                                                      \
    do                                                                      \
    {                                                                       \
        extern char __bdk_is_required_symbol_##component __attribute__((weak));\
        is_required = (&__bdk_is_required_symbol_##component != NULL);      \
    } while (0);                                                            \
    is_required;})


/**
 * The require macros use weak symbols to control if components
 * are linked in. All directly referenced symbols in a component
 * must be defined a weak. This causes the component to only be
 * pulled in by the linker if the symbol defined by
 * BDK_REQUIRE_DEFINE is used.
 */
#define BDK_WEAK __attribute__((weak))

/**
 * This function is not defined by the BDK libraries. It must be
 * defined by all BDK applications. It should be empty except for
 * containing BDK_REQUIRE() lines. The bdk-init code has a strong
 * reference to bdk_requires_depends() which then contains strong
 * references to all needed components.
 */
extern void __bdk_require_depends(void);

/** @} */
