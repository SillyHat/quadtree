#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/decmatr.h"
#include "../include/quadtree.h"

int main(int argc, char *argv[])
{
	srand(time(NULL));
    
    decision_matrix_read();
    
    struct quadtree *qt = NULL;
    
    qt = decision_matrix_encode();
    
	return 0;
}
