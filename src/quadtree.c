#include "../include/quadtree.h"

/*
 * Static functions prototypes.
 */

static struct quadtree *quadtree_construct(struct quadtree *root, unsigned int level, struct rectangle *bounds);
static struct quadtree *quadtree_split(struct quadtree *root);

/*
 * Creating a new empty quadtree.
 */

struct quadtree *quadtree_create(struct quadtree *root, unsigned int x_lower_bound, unsigned int y_lower_bound, unsigned int width, unsigned int height)
{
	struct rectangle new_bounds = {x_lower_bound, y_lower_bound, width, height};
	return quadtree_construct(root, 0, &new_bounds);
}

/*
 * Here we try to insert a new element into a tree.
 */

struct quadtree *quadtree_insert(struct quadtree *root, struct point *pnt)
{
	if (root == NULL || pnt == NULL)
		return root;
	
	if (!is_point_inside_rectangle(pnt, root->bounds))
		return root;

	if (root->size < NODE_CAPACITY) {
		root->points[root->size].x = pnt->x;
		root->points[root->size].y = pnt->y;
        root->points[root->size].value = pnt->value;
		
		++root->size;
		return root;
	}

	if (root->level < MAX_TREE_DEPTH) {
		if (root->nw == NULL)
			quadtree_split(root);

		if (quadtree_insert(root->nw, pnt) != NULL)
			return root;
		if (quadtree_insert(root->ne, pnt) != NULL)
			return root;
		if (quadtree_insert(root->sw, pnt) != NULL)
			return root;
		if (quadtree_insert(root->se, pnt) != NULL)
			return root;
	}
	return root;
}

/*
 * Traversing a quadtree.
 */

void quadtree_traverse(struct quadtree *root)
{
	if (root == NULL)
		return;

	struct quadtree *ptr = root;

	for (unsigned int i = 0; i < ptr->level; ++i)
		printf("    ");

	printf("[%u, %u]->[%u, %u] | DATA: ", ptr->bounds->x, ptr->bounds->y,
		ptr->bounds->x + ptr->bounds->width, ptr->bounds->y + ptr->bounds->height);

	if (ptr->size == 0)
		printf("NULL");

	for (unsigned int i = 0; i < ptr->size; ++i)
		printf("(%u, %u)[%u] ", ptr->points[i].x, ptr->points[i].y , ptr->points[i].value);
	printf("\n");

	if (ptr->nw != NULL) {
		for (unsigned int i = 0; i < ptr->level; ++i)
			printf("    ");
		printf("NW:\n");
		quadtree_traverse(ptr->nw);
		for (unsigned int i = 0; i < ptr->level; ++i)
			printf("    ");
		printf("NE:\n");
		quadtree_traverse(ptr->ne);
		for (unsigned int i = 0; i < ptr->level; ++i)
			printf("    ");
		printf("SW:\n");
		quadtree_traverse(ptr->sw);
		for (unsigned int i = 0; i < ptr->level; ++i)
			printf("    ");
		printf("SE:\n");
		quadtree_traverse(ptr->se);
	}
}

/*
 * Clearing a memory allocated to a quadtree.
 */

void quadtree_destroy(struct quadtree *root)
{
	if (root == NULL)
		return;

	free(root->points);
	root->points = NULL;

	if (root->nw != NULL) {
		quadtree_destroy(root->nw);
		root->nw = NULL;
	}

	if (root->ne != NULL) {
		quadtree_destroy(root->ne);
		root->ne = NULL;
	}

	if (root->sw != NULL) {
		quadtree_destroy(root->sw);
		root->sw = NULL;
	}

	if (root->se != NULL) {
		quadtree_destroy(root->se);
		root->se = NULL;
	}
}

/*
 * Constructing and initializing a new quadtree node.
 */

static struct quadtree *quadtree_construct(struct quadtree *root, unsigned int level, struct rectangle *bounds)
{
	if (level > MAX_TREE_DEPTH)
		return NULL;

	root = (struct quadtree *)malloc(sizeof(struct quadtree));
	if (root != NULL) {
		root->points = (struct point *)malloc(sizeof(struct point) * NODE_CAPACITY);

		if (root->points == NULL) {
			free(root);
			return NULL;
		}

		root->bounds = (struct rectangle *)malloc(sizeof(struct rectangle));

		if (root->bounds == NULL) {
			free(root->points);
			free(root);
			return NULL;
		}

		root->level = level;
		root->size = 0;

		root->bounds->x = bounds->x;
		root->bounds->y = bounds->y;
		root->bounds->width = bounds->width;
		root->bounds->height = bounds->height;

		root->nw = NULL;
		root->ne = NULL;
		root->sw = NULL;
		root->se = NULL;
	}
	return root;
}

/*
 * Splitting a current node into a four subnodes.
 */

static struct quadtree *quadtree_split(struct quadtree *root)
{
	if (root == NULL)
		return NULL;

	unsigned subwidth = (unsigned)(root->bounds->width / 2);
	unsigned subheight = (unsigned)(root->bounds->height / 2);
	unsigned x = root->bounds->x;
	unsigned y = root->bounds->y;

	struct rectangle subbounds = {x, y, subwidth, subheight};
	root->sw = quadtree_construct(root->sw, root->level + 1, &subbounds);

	subbounds.x = x + subwidth;
	root->se = quadtree_construct(root->se, root->level + 1, &subbounds);

	subbounds.y = y + subheight;
	root->ne = quadtree_construct(root->ne, root->level + 1, &subbounds);

	subbounds.x = x;
	root->nw = quadtree_construct(root->nw, root->level + 1, &subbounds);

	return root;
}
