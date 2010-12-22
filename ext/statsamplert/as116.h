#ifndef AS116_H
#define AS116_H

// A, B,C__, D__ -> the four cell frequencies [[A,B],[C,D]]
// R__ -> The tetrachoric correlation
// sdr -> The standard deviation of r
// sdzero -> standard deviation of r, appropiate to test that correlation is 0
// itype-> numerical method used
// ifault-> error indicator 
//  0->normal
//  1->iteration did not converge
//  2->tabla has at most one nonzero row or column

int tetra(double *a, double *b, double *c__, double *d__, double *r__,
	 double *sdr, double *sdzero, double *tx, double *ty, int *itype, int *ifault);

#endif

