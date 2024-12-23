
#pragma once

#include "cst_vc.h"
typedef struct _VocoderSetup {
	int fprd;
	int iprd;
	int seed;
	int pd;
	unsigned long next;
	Boolean gauss;
	double p1;
	double pc;
	double pj;
	double pade[21];
	double *ppade;
	double *c, *cc, *cinc, *d1;
	double rate;

	int sw;
	double r1, r2, s;

	int x;

	/* for postfiltering */
	int size;
	double *d;
	double *g;
	double *mc;
	double *cep;
	double *ir;
	int o;
	int irleng;

	/* for MIXED EXCITATION */
	int ME_order;
	int ME_num;
	double *hpulse;
	double *hnoise;

	double *xpulsesig;
	double *xnoisesig;

	const double *const *h;

} VocoderSetup;