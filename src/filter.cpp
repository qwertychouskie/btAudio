// adapted from https://www.earlevel.com/main/2012/11/26/biquad-c-source-code/

#include "filter.h"

filter::filter(float Fc,float fs, int ncascs,int type){
		_ncascs  = constrain(ncascs,1,5);
		float K = tan(PI * Fc/fs);
		float norm;
		for(int i=0;i<ncascs;i++){
			z1[i]=0.0;
			z2[i]=0.0;
			float Q= 1/(2*cos(PI/(ncascs*4)+i*PI/(ncascs*2)));
			switch (type) {
			 case lowpass:
			    norm = 1 / (1 + K / Q + K * K);
				b0[i] = K * K * norm;
				b1[i] = 2 * b0[i];
				b2[i] = b0[i];
				a1[i] = 2 * (K * K - 1) * norm;
				a2[i] = (1 - K / Q + K * K) * norm;
				break;
             case highpass:
				norm = 1 / (1 + K / Q + K * K);
				b0[i] = 1 * norm;
				b1[i] = -2 * b0[i];
				b2[i] = b0[i];
				a1[i] = 2 * (K * K - 1) * norm;
				a2[i] = (1 - K / Q + K * K) * norm;
				break;
			}
			
		}
	}
