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


/** Doxygen File Header
*  @file
*  @brief Math functions for eye plotting.
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
    if(adjusted >= max_errors) adjusted = max_errors - 1;

    return adjusted / max_errors;
}

double avago_qfunc(double Qval)
{


    double q2  = pow(Qval, 2);
    double BER = ((Qval < 0) ?
                1 - (exp(-q2 / 2) / ((1.64 * (-Qval)) + sqrt((0.76 * q2) + 4))) :
                    (exp(-q2 / 2) / ((1.64 *   Qval)  + sqrt((0.76 * q2) + 4))));

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



void avago_least_sqr(Avago_least_sqr_point *xyCollection, int dataSize, Avago_least_sqr_results * return_data)
{
    double SUMx = 0;
    double SUMy = 0;
    double SUMxy = 0;
    double SUMxx = 0;
    double SUMres = 0;
    double slope = 0;
    double y_intercept = 0;
    double SUM_Yres = 0;
    double AVGy = 0;
    double AVGx = 0;
    double Rsqr = 0;
    int i;

    if( xyCollection == NULL || dataSize == 0 )
    {
         return;
    }

    for( i = 0; i < dataSize; i++ )
    {
         SUMx = SUMx + (xyCollection + i)->x;
         SUMy = SUMy + (xyCollection + i)->y;
         SUMxy = SUMxy + (xyCollection + i)->x * (xyCollection + i)->y;
         SUMxx = SUMxx + (xyCollection + i)->x * (xyCollection + i)->x;
    }

    AVGy = SUMy / dataSize;
    AVGx = SUMx / dataSize;

    slope = (dataSize * SUMxy - SUMx * SUMy) / (dataSize * SUMxx - SUMx*SUMx);

    y_intercept = AVGy - slope * AVGx;

    for( i = 0; i < dataSize; i++ )
    {
         double Yres = pow(((xyCollection + i)->y - y_intercept - (slope * (xyCollection + i)->x)), 2);

         double res = pow((xyCollection + i)->y - AVGy, 2);

         SUM_Yres += Yres;

         SUMres += res;
    }

    Rsqr = (SUMres - SUM_Yres) / SUMres;

    return_data->slope = slope;
    return_data->y_intercept = y_intercept;
    return_data->Rsqr = Rsqr;
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
