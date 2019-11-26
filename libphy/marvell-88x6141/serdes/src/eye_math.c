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


/** Doxygen File Header
 ** @file
 ** @brief Math functions for eye plotting.
 **/

#define AAPL_ENABLE_INTERNAL_FUNCTIONS
#include "aapl.h"

#if AAPL_ENABLE_EYE_MEASUREMENT || AAPL_ENABLE_ESCOPE_MEASUREMENT || AAPL_ENABLE_PHASE_CALIBRATION

#include "eye_math.h"


/** @cond INTERNAL */

double avago_calc_BER(bigint errors, bigint max_errors, float density)
{
    double adjusted = (double)errors / density;

    if(adjusted <  0.0)        adjusted = 0.0;
    if(adjusted >= max_errors) adjusted = (double)(max_errors - 1);

    return adjusted / max_errors;
}

double avago_qfunc(double Qval)
{


    double Q = Qval > 19.0 ? 19.0 : Qval;
    double q2  = Q * Q;
    double BER = ((Q < 0) ?
                1 - (exp(-q2 / 2) / ((1.64 * (-Q)) + sqrt((0.76 * q2) + 4))) :
                    (exp(-q2 / 2) / ((1.64 *   Q)  + sqrt((0.76 * q2) + 4))));

    return BER;
}

double avago_qfuncinv(double BER)
{
    return((BER <= 0.0) ? +12 :
           (BER <= 0.5) ? avago_qfuncinv_half(BER) :
           (BER >= 1.0) ? -12 :
                          -avago_qfuncinv_half(1 - BER));
}


double avago_qfuncinv_half(double BER)
{

     double log_of_BER = log(BER);
     double a = 0,  b = 10, c = 0;
     double fa = 0, fb = 0;
     int side = 0;

     double avago_qfuncinv_err = 1e-6;
     int qloops = 0;

     while (++qloops <= 10000)
     {
           double a2 = pow(a, 2);
           double b2 = pow(b, 2);
           double c2, fc;
           if (fa == 0) {fa = log_of_BER - log(exp(-a2 / 2) / ((1.64 * a)  + sqrt((0.76 * a2) + 4)));}
           if (fb == 0) {fb = log_of_BER - log(exp(-b2 / 2) / ((1.64 * b)  + sqrt((0.76 * b2) + 4)));}

           c  = ((a * fb) - (b * fa)) / (fb - fa);
           c2 = pow(c, 2);
           fc = log_of_BER - log(exp(-c2 / 2) / ((1.64 * c)  + sqrt((0.76 * c2) + 4)));

           if ((fabs(a - c) < avago_qfuncinv_err) || (fabs(b - c) < avago_qfuncinv_err)) break;




           if ((fa > 0 && fc > 0) || (fa < 0 && fc < 0) || (fa == 0 && fc == 0))
                                         {a = c; fa = 0; if (side == -1) {fb /= 2;} else {side = -1;}}
           else                          {b = c; fb = 0; if (side == +1) {fa /= 2;} else {side = +1;}}

     }

     return(c);

}



void avago_least_sqr(
    Avago_least_sqr_point *points,    /**< [in] Array of points */
    int n,                            /**< [in] Size of points array */
    Avago_least_sqr_results *results) /**< [out] Results */
{
    double SUMx  = 0.0;
    double SUMxx = 0.0;
    double SUMxy = 0.0;
    double SUMy  = 0.0;
    double SUMyy = 0.0;
    double divider;
    int i;

    for( i = 0; i < n; i++ )
    {
        SUMx  += points[i].x;
        SUMxx += points[i].x * points[i].x;
        SUMxy += points[i].x * points[i].y;
        SUMy  += points[i].y;
        SUMyy += points[i].y * points[i].y;
    }

    divider = n * SUMxx - SUMx * SUMx;
    if( divider == 0 )
    {
        results->slope = 0;
        results->y_intercept = 0;
        results->Rsqr = 0;
    }
    else
    {
        results->slope       = (SUMxy * n - SUMx * SUMy) / divider;
        results->y_intercept = (SUMy * SUMxx - SUMx * SUMxy) / divider;

        divider = (SUMxx - SUMx * SUMx / n) * (SUMyy - SUMy * SUMy / n);
        if( divider == 0 )
            results->Rsqr = 0;
        else
        {
            double numerator = SUMxy - SUMx * SUMy / n;
            results->Rsqr = numerator * numerator / divider;
        }
    }

}

double avago_interpolate(
    const Avago_least_sqr_point *left,
    const Avago_least_sqr_point *right)
{
    double x_range = left->x - right->x;
    double y_range = left->y - right->y;
    if( y_range == 0 )
        return (left->x + right->x) / 2;

    return right->x + (x_range * (-right->y / y_range));
}

/** @details     Round a floating point number to the nearest integer (away
 **              from zero).
 ** @param value Number to round.
 ** @return      Nearest integer.
 **/

int aapl_iround(double value)
{
    int result = (int) value;

    if      ((value > 0) && (value - result >=  0.5)) ++result;
    else if ((value < 0) && (value - result <= -0.5)) --result;

    return result;
}

/** @endcond */

#endif


#if AAPL_ENABLE_ESCOPE_MEASUREMENT
/** @cond INTERNAL */

/** @brief  Allocates an nrows x ncols matrix with double elements.
 ** @return Returns a pointer to matrix.
 **/
Avago_matrix_t *avago_matrix_construct(int nrows, int ncols)
{
    Avago_matrix_t *matrix = (Avago_matrix_t *) AAPL_MALLOC(sizeof(Avago_matrix_t) + nrows*sizeof(double*) + nrows*ncols*sizeof(double));
    if( matrix )
    {
        int i;
        matrix->nrows = nrows;
        matrix->ncols = ncols;

        matrix->matrix[0] = (double *) (&matrix->matrix[nrows]);
        for( i = 1; i < nrows; i++ )
            matrix->matrix[i] = matrix->matrix[i-1] + ncols;
    }
#if AAPL_ENABLE_FILE_IO
    else
        fprintf(stderr,"Matrix[%dx%d] memory allocation failure.\n",nrows,ncols);
#endif
    return matrix;
}

/** @brief  Releases the matrix memory. */
void avago_matrix_destruct(Avago_matrix_t *matrix)
{
    if( matrix )
        AAPL_FREE(matrix);
}

/** @brief Transposes the input matrix into a new matrix which is returned.
 ** @return Returns the matrix transposition.
 **         The returned value should be freed by a call to avago_matrix_destruct().
 **/
Avago_matrix_t *avago_matrix_transpose(const Avago_matrix_t *matrix_in)
{
    Avago_matrix_t *transpose = avago_matrix_construct(matrix_in->ncols, matrix_in->nrows);
    if( transpose )
    {
        int r, c;
        for( r = 0; r < matrix_in->nrows; r++ )
            for( c = 0; c < matrix_in->ncols; c++ )
                transpose->matrix[c][r] = matrix_in->matrix[r][c];
    }
    return transpose;
}

/** @brief Calculates the difference between the matrices.
 ** @return Returns the matrix difference (m1 - m2).
 **         The returned value should be freed by a call to avago_matrix_destruct().
 **/
Avago_matrix_t *avago_matrix_subtract(const Avago_matrix_t *m1, const Avago_matrix_t *m2)
{
    Avago_matrix_t *result;
    if( !m1 || !m2 || m1->ncols != m2->ncols || m1->nrows != m2->nrows )
        return 0;

    result = avago_matrix_construct(m1->nrows, m1->ncols);
    if( result )
    {
        int r, c;
        for( r = 0; r < m1->nrows; r++ )
            for( c = 0; c < m1->ncols; c++ )
                result->matrix[r][c] = m1->matrix[r][c] - m2->matrix[r][c];
    }
    return result;
}

/** @brief Multiplies the input matrices.
 ** @return Returns the matrix product.
 **         The returned value should be freed by a call to avago_matrix_destruct().
 **/
Avago_matrix_t *avago_matrix_multiply(const Avago_matrix_t *m1, const Avago_matrix_t *m2)
{
    Avago_matrix_t *product;

    if( !m1 || !m2 || m1->ncols != m2->nrows )
        return 0;

    product = avago_matrix_construct(m1->nrows, m2->ncols);
    if( product )
    {
        int r;
        for( r = 0; r < m1->nrows; r++ )
        {
            int c;
            for( c = 0; c < m2->ncols; c++)
            {
                double sum = 0.0;
                int k;
                for( k = 0; k < m1->ncols; k++)
                    sum += m1->matrix[r][k] * m2->matrix[k][c];
                product->matrix[r][c] = sum;
            }
        }
    }
    return product;
}

/** @brief Constructs the inverse of a PRBS matrix and its transform.
 ** @details If bits_per_ui == 1, the PRBS input matrix is formed of
 **          -1 (for zero) and 1 values.
 ** @details If bits_per_ui == 2, the PRBS input matrix is formed of values
 **          -1 (for zero) -1/3 (for 1), 1/3 (for 2) and 1 (for 3) values.
 ** @details All last row values for the PRBS input matrix are set to 1.0.
 ** @details Result is inverse(PRBS * transform(PRBS)).
 ** @return Returns inverse matrix.
 **/
Avago_matrix_t *avago_matrix_construct_prbs_inverse(
    int dimension,      /**< [in] Number of rows */
    int prbs_length,    /**< [in] PRBS pattern length */
    int bits_per_ui)    /**< [in] Set to 1 for NRZ input, 2 for PAM4 input */
{
    int n = dimension - 1;
    if( n >= prbs_length )
        return 0;
    if( bits_per_ui == 1 )
    {
        Avago_matrix_t *inverse = avago_matrix_construct(dimension, dimension);
        double num = prbs_length + 1 - n;
        int denom = prbs_length * num - n;
        double d = num / denom;
        double v = 1.0 / denom;
        int r, c;
        for( r = 0; r < n; r++ )
        for( c = 0; c < n; c++ )
            inverse->matrix[r][c] = v;
        for( r = 0; r < dimension; r++ )
        {
            inverse->matrix[n][r] = -v;
            inverse->matrix[r][n] = -v;
            inverse->matrix[r][r] = d;
        }
        return inverse;
    }
    else if( bits_per_ui == 2 )
    {
        Avago_matrix_t *inverse = avago_matrix_construct(dimension, dimension);
        double D = (prbs_length * 5 - 4) / 9.0;
        double w = 1.0 / (prbs_length * (n - D - 1) + n);
        double d = (1 - w * (prbs_length + 1)) / (D + 1);
        double v = d - 1.0 / (D + 1);
        double p = (1 - n * w) / prbs_length;

        int r, c;
        for( r = 0; r < n; r++ )
        for( c = 0; c < n; c++ )
            inverse->matrix[r][c] = v;
        for( r = 0; r < dimension; r++ )
        {
            inverse->matrix[n][r] = w;
            inverse->matrix[r][n] = w;
            inverse->matrix[r][r] = d;
        }
        inverse->matrix[dimension-1][dimension-1] = p;
        return inverse;
    }
    return 0;
}

#if AAPL_ENABLE_FILE_IO
/** @brief   Prints matrix to a FILE stream.
 ** @return  void
 **/
void avago_matrix_print(FILE *stream, Avago_matrix_t *matrix)
{
    if( matrix )
    {
        int r;
        fprintf(stream, "matrix[%d,%d]:\n", matrix->nrows, matrix->ncols);
        for( r = 0; r < matrix->nrows; r++ )
        {
            int c;
            fprintf(stream, "%3d: ", r);
            for( c = 0; c < matrix->ncols; c++ )
                fprintf(stream, "%g ", matrix->matrix[r][c]);
            fprintf(stream, "\n");
        }
    }
    else
        fprintf(stream, "Print of NULL matrix.\n");
}
#endif

/** @endcond */
#endif
