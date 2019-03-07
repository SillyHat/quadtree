#ifndef _GEOMETRY_H
#define _GEOMETRY_H

#include <stdlib.h>

struct point {
	unsigned int x;
	unsigned int y;
    unsigned char value;
};

struct rectangle {
	unsigned int x;
	unsigned int y;
	unsigned int width;
	unsigned int height;
};

int is_point_inside_rectangle(struct point *pnt, struct rectangle *rect);

#endif
