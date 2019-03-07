#ifndef _DECMATR_H
#define _DECMATR_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "quadtree.h"

struct decision_matrix {    
	unsigned int comm_lower_bound;
	unsigned int comm_upper_bound;
	unsigned int comm_step;
	
	unsigned int mess_lower_bound;
	unsigned int mess_upper_bound;
	unsigned int mess_step;
	
	unsigned char **array;
};

struct decision_matrix decmatr;

void decision_matrix_read();
struct quadtree* decision_matrix_encode();

#endif
