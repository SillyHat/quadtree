#ifndef _QUADTREE_H
#define _QUADTREE_H

#include <stdio.h>
#include <stdlib.h>

#include "geometry.h"

#define MAX_TREE_DEPTH 4
#define NODE_CAPACITY 4

struct quadtree {
	unsigned int level;
	unsigned int size;
	unsigned int majority;
	struct rectangle *bounds;
	struct point *points;

	struct quadtree *nw;
	struct quadtree *ne;
	struct quadtree *sw;
	struct quadtree *se;
};

struct quadtree *quadtree_create(struct quadtree *root, unsigned int x_lower_bound, unsigned int y_lower_bound, unsigned int width, unsigned int height);
struct quadtree *quadtree_insert(struct quadtree *root, struct point *pnt);
void quadtree_traverse(struct quadtree *root);
void quadtree_destroy(struct quadtree *root);

#endif
