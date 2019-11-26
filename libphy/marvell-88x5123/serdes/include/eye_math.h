/* AAPL CORE Revision: 2.3.0-alpha */

/* Copyright 2014-2015 Avago Technologies. All rights reserved.
 *
 * This file is part of the AAPL CORE library.
 *
 * AAPL CORE is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * AAPL CORE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with AAPL CORE.  If not, see http://www.gnu.org/licenses.
 */

/* AAPL (ASIC and ASSP Programming Layer) support for gathering eye diagram
 * data from a SerDes slice (28nm only).
 */

/** Doxygen File Header
*  @file
*  @brief Declarations for eye math functions.
 **/

#ifndef AVAGO_EYE_MATH_H_
#define AVAGO_EYE_MATH_H_

#ifdef AAPL_ENABLE_INTERNAL_FUNCTIONS

/** @cond INTERNAL */

/* Create an array of Avago_least_sqr_point's to pass into the avago_least_sqr function. */
typedef struct
{
    double x;
    double y;
} Avago_least_sqr_point;

/* The Avago_least_sqr_results struct contains the values that will be returned
 * by the avago_least_sqr function.
 */
typedef struct
{
    double slope;
    double y_intercept;
    double Rsqr;
} Avago_least_sqr_results;
/** @endcond */

EXT double avago_interpolate(const Avago_least_sqr_point *left, const Avago_least_sqr_point *right);

/* Given the errors and dwell time (in number of bits), return the BER. */
EXT double avago_calc_BER(bigint errors, bigint max_errors, float density);

/* The Q functions are used to scale the BER values for the bathtub curves.
 *   NOTE:  Q(x) is defined to range 1->0 as x ranges -inf -> +inf.  In this
 *   application BER ranges over 0..1.
 *       avago_qfunc()    = BER(Q)
 *       avago_qfuncinv() = Qinv(BER)
 *
 * For examples, see also:  http
 *                          http
 *                          http
 */
EXT double avago_qfunc(double Qval);
EXT double avago_qfuncinv(double BER);
EXT double avago_qfuncinv_half(double BER);

/* Given a set of X, Y coordinates (Avago_least_sqr_point's), return the slope and
 *  y_intercept of the line that best models the relationship of the points.
 */
EXT void avago_least_sqr(Avago_least_sqr_point *xyPoints, int nPoints, Avago_least_sqr_results *ret);

EXT int aapl_iround(double value);

#endif

#endif
