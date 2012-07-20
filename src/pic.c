/* pic_variance.c       2011-06-13 */

/* Copyright 2006 Emmanuel Paradis */
/* modified by JM Eastman to scale PICs by edge.lengths differing from those for which (unstandardized) PICs are computed */

/* This file was originally part of the R-package `ape'. */
/* See the file ../COPYING for licensing issues. */

#include <R.h>

void pic_variance(int *ntip, int *nnode, int *edge1, int *edge2, double *edge_len, double *var)
{
/* The tree must be in pruningwise order */
    int anc, d1, d2, ic, i, j, k;
    double sumbl;

    for (i = 0; i < *ntip * 2 - 3; i += 2) {
        j = i + 1;
	anc = edge1[i];
	d1 = edge2[i] - 1;
	d2 = edge2[j] - 1;
	sumbl = edge_len[i] + edge_len[j];
	ic = anc - *ntip - 1;
//	contr[ic] = phe[d1] - phe[d2];
//	if (*scaled) contr[ic] = contr[ic]/sqrt(sumbl);
	var[ic] = sumbl;
//	phe[anc - 1] = (phe[d1]*edge_len[j] + phe[d2]*edge_len[i])/sumbl;
		
	/* find the edge where `anc' is a descendant (except if at the root):
	   it is obviously below the j'th edge */
	if (j != *ntip * 2 - 3) {
	    k = j + 1;
	    while (edge2[k] != anc) k++;
	    edge_len[k] = edge_len[k] + edge_len[i]*edge_len[j]/sumbl;
	}
    }
}

/* pic.c       2006-11-13 */

/* Copyright 2006 Emmanuel Paradis */

/* This file is part of the R-package `ape'. */
/* See the file ../COPYING for licensing issues. */

//#include <R.h>

// modified to compute vertical (ancestor-descendant) contrasts

void pic_vertical(int *ntip, int *nnode, int *edge1, int *edge2,
		 double *edge_len, double *phe, double *contr, double *vcontr,
		 double *var_contr, int *var, int *scaled)
{
	/* The tree must be in pruningwise order */
    int anc, d1, d2, ic, i, j, k;
    double sumbl;
	
    for (i = 0; i < *ntip * 2 - 3; i += 2) {
        j = i + 1;
		anc = edge1[i];
		d1 = edge2[i] - 1;
		d2 = edge2[j] - 1;
		sumbl = edge_len[i] + edge_len[j];
		ic = anc - *ntip - 1;
		contr[ic] = phe[d1] - phe[d2];
		if (*scaled) contr[ic] = contr[ic]/sqrt(sumbl);
		if (*var) var_contr[ic] = sumbl;
		phe[anc - 1] = (phe[d1]*edge_len[j] + phe[d2]*edge_len[i])/sumbl;
		/* find the edge where `anc' is a descendant (except if at the root):
		 it is obviously below the j'th edge */
		if (j != *ntip * 2 - 3) {
			k = j + 1;
			while (edge2[k] != anc) k++;
			edge_len[k] = edge_len[k] + edge_len[i]*edge_len[j]/sumbl;
		}
    }
	
	// find vertical contrasts
	for (i = 0; i < *ntip * 2 - 2; i += 1) {
		d1 = edge2[i] - 1;
		d2 = edge1[i] - 1;
		vcontr[i]=phe[d1]-phe[d2];

	}
	
}
