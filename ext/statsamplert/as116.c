/* as116.f -- translated by f2c (version 20090411).
   You must link the resulting object file with libf2c:
	on Microsoft Windows system, link with libf2c.lib;
	on Linux or Unix systems, link with .../path/to/libf2c.a -lm
	or, if you install libf2c.a in a standard place, with -lf2c -lm
	-- in that order, at the end of the command line, as in
		cc *.o -lf2c -lm
	Source for libf2c is in /netlib/f2c/libf2c.zip, e.g.,

		http://www.netlib.org/f2c/libf2c.zip
*/
#include "math.h"
#include "as116.h"

typedef int logical;


#define dabs(x) (double)abs(x)
#define abs(x) ((x) >= 0 ? (x) : -(x))

#define TRUE_ (1)
#define FALSE_ (0)


static double alnorm_(double *x, logical *upper);
static double ppnd_(double *p, int *ier);






/* Table of constant values */

static logical c_false = FALSE_;

/* This file includes the Applied Statistics algorithm AS 66 for calculating */
/* the tail area under the normal curve, and two alternative routines which */
/* give higher accuracy.   The latter have been contributed by Alan Miller of */
/* CSIRO Division of Mathematics & Statistics, Clayton, Victoria.   Notice */
/* that each function or routine has different call arguments. */


static double alnorm_(double *x, logical *upper) {
    /* Initialized data */

    static double zero = 0.;
    static double a1 = 5.75885480458;
    static double a2 = 2.62433121679;
    static double a3 = 5.92885724438;
    static double b1 = -29.8213557807;
    static double b2 = 48.6959930692;
    static double c1 = -3.8052e-8;
    static double c2 = 3.98064794e-4;
    static double c3 = -.151679116635;
    static double c4 = 4.8385912808;
    static double c5 = .742380924027;
    static double one = 1.;
    static double c6 = 3.99019417011;
    static double d1 = 1.00000615302;
    static double d2 = 1.98615381364;
    static double d3 = 5.29330324926;
    static double d4 = -15.1508972451;
    static double d5 = 30.789933034;
    static double half = .5;
    static double ltone = 7.;
    static double utzero = 18.66;
    static double con = 1.28;
    static double p = .398942280444;
    static double q = .39990348504;
    static double r__ = .398942280385;

    /* System generated locals */
    double ret_val;


    /* Local variables */
    static double y, z__;
    static logical up;


/*         Algorithm AS66 Applied Statistics (1973) vol22 no.3 */

/*       Evaluates the tail area of the standardised normal curve */
/*       from x to infinity if upper is .true. or */
/*       from minus infinity to x if upper is .false. */

/* *** machine dependent constants */

    up = *upper;
    z__ = *x;
    if (z__ >= zero) {
	goto L10;
    }
    up = ! up;
    z__ = -z__;
L10:
    if (z__ <= ltone || (up && z__ <= utzero)) {
	goto L20;
    }
    ret_val = zero;
    goto L40;
L20:
    y = half * z__ * z__;
    if (z__ > con) {
	goto L30;
    }

    ret_val = half - z__ * (p - q * y / (y + a1 + b1 / (y + a2 + b2 / (y + a3)
	    )));
    goto L40;
L30:
    ret_val = r__ * exp(-y) / (z__ + c1 + d1 / (z__ + c2 + d2 / (z__ + c3 + 
	    d3 / (z__ + c4 + d4 / (z__ + c5 + d5 / (z__ + c6))))));
L40:
    if (! up) {
	ret_val = one - ret_val;
    }
    return ret_val;
} /* alnorm_ */

static double ppnd_(double *p, int *ier)
{
    /* Initialized data */

    static double split = .42;
    static double a0 = 2.50662823884;
    static double a1 = -18.61500062529;
    static double a2 = 41.39119773534;
    static double a3 = -25.44106049637;
    static double b1 = -8.4735109309;
    static double b2 = 23.08336743743;
    static double b3 = -21.06224101826;
    static double b4 = 3.13082909833;
    static double c0 = -2.78718931138;
    static double c1 = -2.29796479134;
    static double c2 = 4.85014127135;
    static double c3 = 2.32121276858;
    static double d1 = 3.54388924762;
    static double d2 = 1.63706781897;
    static double zero = 0.;
    static double one = 1.;
    static double half = .5;

    /* System generated locals */
    double ret_val;


    /* Local variables */
    static double q, r__;


/*       ALGORITHM AS 111, APPL.STATIST., VOL.26, 118-121, 1977. */

/*       PRODUCES NORMAL DEVIATE CORRESPONDING TO LOWER TAIL AREA = P. */

/* 	See also AS 241 which contains alternative routines accurate to */
/* 	about 7 and 16 decimal digits. */


    *ier = 0;
    q = *p - half;
    if (abs(q) > split) {
	goto L10;
    }

/*       0.08 < P < 0.92 */

    r__ = q * q;
    ret_val = q * (((a3 * r__ + a2) * r__ + a1) * r__ + a0) / ((((b4 * r__ + 
	    b3) * r__ + b2) * r__ + b1) * r__ + one);
    return ret_val;

/*       P < 0.08 OR P > 0.92, SET R = MIN(P,1-P) */

L10:
    r__ = *p;
    if (q > zero) {
	r__ = one - *p;
    }
    if (r__ <= zero) {
	goto L20;
    }
    r__ = sqrt(-log(r__));
    ret_val = (((c3 * r__ + c2) * r__ + c1) * r__ + c0) / ((d2 * r__ + d1) * 
	    r__ + one);
    if (q < zero) {
	ret_val = -ret_val;
    }
    return ret_val;
L20:
    *ier = 1;
    ret_val = zero;
    return ret_val;
} /* ppnd_ */

/* Subroutine */ 

int tetra(double *a, double *b, double *c__, double *d__, double *r__,
	 double *sdr, double *sdzero, double *threshold_x, double *threshold_y, int *itype, int *ifault)
{
    /* Initialized data */

    static double x[16] = { .9972638618f,.9856115115f,.9647622556f,.9349060759f,
	    .8963211558f,.8493676137f,.794483796f,.7321821187f,.6630442669f,
	    .5877157572f,.5068999089f,.4213512761f,.3318686023f,.2392873623f,
	    .1444719616f,.0483076657f };
    static double w[16] = { .00701861f,.0162743947f,.0253920653f,.0342738629f,
	    .042835898f,.0509980593f,.0586840935f,.0658222228f,.0723457941f,
	    .0781938958f,.0833119242f,.087652093f,.0911738787f,.0938443991f,
	    .0956387201f,.0965400885f };
    static double zero = 0.f;
    static double one = 1.f;
    static double two = 2.f;
    static double four = 4.f;
    static double six = 6.f;
    static double half = .5f;
    static double twopi = 6.28318531f;
    static double sqt2pi = 2.50662827f;
    static double rlimit = .9999f;
    static double rcut = .95f;
    static double uplim = 5.f;
    static double const__ = 1e-36f;
    static double chalf = 1e-18f;
    static double conv = 1e-8f;
    static double citer = 1e-6f;
    static int niter = 25;

    /* System generated locals */
    double r__1, r__2, r__3;


    /* Local variables */
    static double aa, bb, cc, dd;
    static int ie;
    static double dr, va, vb, wa, wb, rr, sr, ss, pab, pac, cof, vaa, waa, pdf, 
	    zab, zac, xla, xlb, sum, tot, amid;
    static double prob;
    static int iter;
    static double xlen, term, rrsq, delta;
    static int iquad;
    static double tempa, tempb, deriv;
    static int ksign, iterm;
    static double rrest;
    static int kdelta;
    static double probaa, probac, probab;
    static double rrprev, sumprv;


/*        ALGORITHM  AS 116 APPL. STATIST. (1977) VOL.26, NO.3 */

/*        TO COMPUTE THE TETRACHORIC CORRELATION (R) AND ITS STANDARD */
/*        ERRORS (SDR AND SDZERO) FROM THE FREQUENCIES OF A 2*2 TABLE */
/*        (A, B, C AND D) */
/*        X AND W ARE CONSTANTS USED IN GAUSSIAN QUADRATURE */


/*        INITIALIZATION */

    *r__ = zero;
    *sdzero = zero;
    *sdr = zero;
    *itype = 0;
    *ifault = 0;
    *threshold_x=zero;
    *threshold_y=zero;
    
/*       CHECK IF ANY CELL FREQUENCY IS NEGATIVE */

    if (*a < zero || *b < zero || *c__ < zero || *d__ < zero) {
	goto L92;
    }

/*       CHECK IF ANY FREQUENCY IS ZERO AND SET KDELTA */

    kdelta = 1;
    delta = zero;
    if (*a == zero || *d__ == zero) {
	kdelta = 2;
    }
    if (*b == zero || *c__ == zero) {
	kdelta += 2;
    }

/*        KDELTA=4 MEANS TABLE HAS ZERO ROW OR COLUMN, RUN IS TERMINATED */

    switch (kdelta) {
	case 1:  goto L4;
	case 2:  goto L1;
	case 3:  goto L2;
	case 4:  goto L92;
    }

/*        DELTA IS 0.0, 0.5 OR -0.5 ACCORDING TO WHICH CELL IS ZERO */

L1:
    delta = half;
    if (*a == zero && *d__ == zero) {
	*r__ = -one;
    }
    goto L4;
L2:
    delta = -half;
    if (*b == zero && *c__ == zero) {
	*r__ = one;
    }
L4:
    if (*r__ != zero) {
	*itype = 3;
    }

/*        STORE FREQUENCIES IN  AA, BB, CC AND DD */

    aa = *a + delta;
    bb = *b - delta;
    cc = *c__ - delta;
    dd = *d__ + delta;
    tot = aa + bb + cc + dd;

/*        CHECK IF CORRELATION IS NEGATIVE, ZERO, POSITIVE */

    if ((r__1 = aa * dd - bb * cc) < 0.f) {
	goto L7;
    } else if (r__1 == 0) {
	goto L5;
    } else {
	goto L6;
    }
L5:
    *itype = 4;

/*        COMPUTE PROBABILITIES OF QUADRANT AND OF MARGINALS */
/*        PROBAA AND PROBAC CHOSEN SO THAT CORRELATION IS POSITIVE. */
/*        KSIGN INDICATES WHETHER QUADRANTS HAVE BEEN SWITCHED */

L6:
    probaa = aa / tot;
    probac = (aa + cc) / tot;
    ksign = 1;
    goto L8;
L7:
    probaa = bb / tot;
    probac = (bb + dd) / tot;
    ksign = 2;
L8:
    probab = (aa + bb) / tot;

/*        COMPUTE NORMAL DEVIATES FOR THE MARGINAL FREQUENCIES */
/*        SINCE NO MARGINAL CAN BE ZERO, IE IS NOT CHECKED */

    zac = ppnd_((double*)&probac, &ie);
    zab = ppnd_((double*)&probab, &ie);

    *threshold_x=zab;    
    *threshold_y=zac;
/* Computing 2nd power */
    r__1 = zac;
/* Computing 2nd power */
    r__2 = zab;
    ss = exp(-half * (r__1 * r__1 + r__2 * r__2)) / twopi;

/*        WHEN R IS 0.0, 1.0 OR -1.0, TRANSFER TO COMPUTE SDZERO */

    if (*r__ != zero || *itype > 0) {
	goto L85;
    }

/*        WHEN MARGINALS ARE EQUAL, COSINE EVALUATION IS USED */

    if (*a == *d__ && *b == *c__) {
	goto L60;
    }

/*        INITIAL ESTIMATE OF CORRELATION IS YULES Y */

/* Computing 2nd power */
    r__2 = sqrt(aa * dd) - sqrt(bb * cc);
    rr = r__2 * r__2 / (r__1 = aa * dd - bb * cc, dabs(r__1));
    iter = 0;

/*        IF RR EXCEEDS RCUT, GAUSSIAN QUADRATURE IS USED */

L10:
    if (rr > rcut) {
	goto L40;
    }

/*        TETRACHORIC SERIES IS COMPUTED */

/*        INITIALIZATION */

    va = one;
    vb = zac;
    wa = one;
    wb = zab;
    term = one;
    iterm = 0;
    sum = probab * probac;
    deriv = zero;
    sr = ss;
L15:
    if (dabs(sr) > const__) {
	goto L20;
    }

/*        RESCALE TERMS TO AVOID OVERFLOWS AND UNDERFLOWS */

    sr /= const__;
    va *= chalf;
    vb *= chalf;
    wa *= chalf;
    wb *= chalf;

/*        FORM SUM AND DERIVATIVE OF SERIES */

L20:
    dr = sr * va * wa;
    sr = sr * rr / term;
    cof = sr * va * wa;

/*        ITERM COUNTS NO. OF CONSECUTIVE TERMS .LT. CONV */

    ++iterm;
    if (dabs(cof) > conv) {
	iterm = 0;
    }
    sum += cof;
    deriv += dr;
    vaa = va;
    waa = wa;
    va = vb;
    wa = wb;
    vb = zac * va - term * vaa;
    wb = zab * wa - term * waa;
    term += one;
    if (iterm < 2 || term < six) {
	goto L15;
    }

/*        CHECK IF ITERATION CONVERGED */

    if ((r__1 = sum - probaa, dabs(r__1)) > citer) {
	goto L25;
    }

/*        ITERATION HAS CONVERGED, SET ITYPE */

    *itype = term;
    goto L70;

/*        CALCULATE NEXT ESTIMATE OF CORRELATION */

L25:
    ++iter;

/*        IF TOO MANY ITERATlONS, RUN IS TERMINATED */

    if (iter >= niter) {
	goto L93;
    }
    delta = (sum - probaa) / deriv;
    rrprev = rr;
    rr -= delta;
    if (iter == 1) {
	rr += half * delta;
    }
    if (rr > rlimit) {
	rr = rlimit;
    }
    if (rr < zero) {
	rr = zero;
    }
    goto L10;

/*       GAUSSIAN QUADRATURE */

L40:
    if (iter > 0) {
	goto L41;
    }

/*       INITIALIZATION, IF THIS IS FIRST ITERATION */

    sum = probab * probac;
    rrprev = zero;

/*        INITIALIZATION */

L41:
    sumprv = probab - sum;
    prob = bb / tot;
    if (ksign == 2) {
	prob = aa / tot;
    }
    *itype = 1;

/*        LOOP TO FIND ESTIMATE OF CORRELATION */
/*        COMPUTATION OF INTEGRAL (SUM) BY QUADRATURE */

L42:
/* Computing 2nd power */
    r__1 = rr;
    rrsq = sqrt(one - r__1 * r__1);
    amid = half * (uplim + zac);
    xlen = uplim - amid;
    sum = zero;
    for (iquad = 1; iquad <= 16; ++iquad) {
	xla = amid + x[iquad - 1] * xlen;
	xlb = amid - x[iquad - 1] * xlen;

/*       TO AVOID UNDERFLOWS, TEMPA AND TEMPB ARE USED */

	tempa = (zab - rr * xla) / rrsq;
	if (tempa >= -six) {
/* Computing 2nd power */
	    r__1 = xla;
	    sum += w[iquad - 1] * exp(-half * (r__1 * r__1)) * alnorm_((
		    double*)&tempa, &c_false);
	}
	tempb = (zab - rr * xlb) / rrsq;
	if (tempb >= -six) {
/* Computing 2nd power */
	    r__1 = xlb;
	    sum += w[iquad - 1] * exp(-half * (r__1 * r__1)) * alnorm_((
		    double*)&tempb, &c_false);
	}
/* L44: */
    }
    sum = sum * xlen / sqt2pi;

/*        CHECK IF ITERATION HAS CONVERGED */

    if ((r__1 = prob - sum, dabs(r__1)) <= citer) {
	goto L70;
    }
    ++iter;

/*         IF TOO MANY ITERATIONS, RUN IS TERMINATED */

    if (iter >= niter) {
	goto L93;
    }

/*         ESTIMATE CORRELATION FOR NEXT ITERATION BY LINEAR INTERPOLATION */

    rrest = ((prob - sum) * rrprev - (prob - sumprv) * rr) / (sumprv - sum);

/*        IS ESTIMATE POSITIVE AND LESS THAN UPPER LIMIT */

    if (rrest > rlimit) {
	rrest = rlimit;
    }
    if (rrest < zero) {
	rrest = zero;
    }
    rrprev = rr;
    rr = rrest;
    sumprv = sum;

/*        IF ESTIMATE HAS SAME VALUE ON TWO ITERATIONS, STOP ITERATION */

    if (rr == rrprev) {
	goto L70;
    }
    goto L42;

/*        WHEN ALL MARGINALS ARE EQUAL THE COSINE FUNCTION IS USED */

L60:
    rr = -cos(twopi * probaa);
    *itype = 2;

/*        COMPUTE SDR */

L70:
    *r__ = rr;
/* Computing 2nd power */
    r__1 = *r__;
    rrsq = sqrt(one - r__1 * r__1);
    if (kdelta > 1) {
	*itype = -(*itype);
    }
    if (ksign == 1) {
	goto L71;
    }
    *r__ = -(*r__);
    zac = -zac;
    *threshold_y=zac;    
    
L71:
/* Computing 2nd power */
    r__1 = zac;
/* Computing 2nd power */
    r__2 = zab;
/* Computing 2nd power */
    r__3 = rrsq;
    pdf = exp(-half * (r__1 * r__1 - two * *r__ * zac * zab + r__2 * r__2) / (
	    r__3 * r__3)) / (twopi * rrsq);
    r__1 = (zac - *r__ * zab) / rrsq;
    pac = alnorm_((double*)&r__1, &c_false) - half;
    r__1 = (zab - *r__ * zac) / rrsq;
    pab = alnorm_((double*)&r__1, &c_false) - half;
/* Computing 2nd power */
    r__1 = pab;
/* Computing 2nd power */
    r__2 = pac;
    *sdr = (aa + dd) * (bb + cc) / four + r__1 * r__1 * (aa + cc) * (bb + dd) 
	    + r__2 * r__2 * (aa + bb) * (cc + dd) + two * pab * pac * (aa * 
	    dd - bb * cc) - pab * (aa * bb - cc * dd) - pac * (aa * cc - bb * 
	    dd);
    if (*sdr < zero) {
	*sdr = zero;
    }
    *sdr = sqrt(*sdr) / (tot * pdf * sqrt(tot));

/*        COMPUTE SDZERO */

L85:
/* Computing 2nd power */
    r__1 = tot;
    *sdzero = sqrt((aa + bb) * (aa + cc) * (bb + dd) * (cc + dd) / tot) / (
	    r__1 * r__1 * ss);
    if (*r__ == zero) {
	*sdr = *sdzero;
    }
    goto L99;

/*        ERROR TERMINATIONS */

L92:
    *ifault = 1;
L93:
    ++(*ifault);

L99:
    return 0;
} /* tetra_ */

