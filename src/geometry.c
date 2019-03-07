#include "../include/geometry.h"

int is_point_inside_rectangle(struct point *pnt, struct rectangle *rect)
{
	if (pnt == NULL || rect == NULL)
		return -1;
	
	return (pnt->x >= rect->x && pnt->x < rect->x + rect->width &&
		pnt->y >= rect->y && pnt->y < rect->y + rect->height) ? 1 : 0;
}
