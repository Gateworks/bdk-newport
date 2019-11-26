/* AAPL CORE Revision: 2.6.2
 *
 * Copyright (c) 2014-2017 Avago Technologies. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/* AAPL (ASIC and ASSP Programming Layer) support for gathering eye diagram
 * data from a SerDes slice (28nm only).
 */

/** Doxygen File Header
 ** @file
 ** @brief Declarations for eye math functions.
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
 * For examples, see also:  http:
 *                          http:
 *                          http:
 */
EXT double avago_qfunc(double Qval);
EXT double avago_qfuncinv(double BER);
EXT double avago_qfuncinv_half(double BER);

/* Given a set of X, Y coordinates (Avago_least_sqr_point's), return the slope and
 *  y_intercept of the line that best models the relationship of the points.
 */
EXT void avago_least_sqr(Avago_least_sqr_point *xyPoints, int nPoints, Avago_least_sqr_results *ret);

EXT int aapl_iround(double value);


typedef struct
{
    int nrows;
    int ncols;
    double *matrix[1];
} Avago_matrix_t;

EXT Avago_matrix_t *avago_matrix_construct(int nrows, int n_cols);
EXT void            avago_matrix_destruct(Avago_matrix_t *matrix);

EXT Avago_matrix_t *avago_matrix_transpose(const Avago_matrix_t *m);
EXT Avago_matrix_t *avago_matrix_multiply(const Avago_matrix_t *m1, const Avago_matrix_t *m2);
EXT Avago_matrix_t *avago_matrix_subtract(const Avago_matrix_t *m1, const Avago_matrix_t *m2);
EXT Avago_matrix_t *avago_matrix_construct_prbs_inverse(int dimension, int prbs_length, int bits_per_ui);
#if AAPL_ENABLE_FILE_IO
EXT void            avago_matrix_print(FILE *stream, Avago_matrix_t *matrix);
#endif


#endif

#endif
