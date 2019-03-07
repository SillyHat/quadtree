#include "../include/decmatr.h"

static void decision_matrix_get_dims(unsigned int *dim_i, unsigned int *dim_j);
static void decision_matrix_init(unsigned int dim_i, unsigned int dim_j);
static void decision_matrix_free();

void decision_matrix_read()
{
	FILE *fp;
	fp = fopen("decmatr.txt", "r");
	
	fscanf(fp, "%u", &(decmatr.comm_lower_bound));
	fscanf(fp, "%u", &(decmatr.comm_upper_bound));
	fscanf(fp, "%u", &(decmatr.comm_step));
	
	fscanf(fp, "%u", &(decmatr.mess_lower_bound));
	fscanf(fp, "%u", &(decmatr.mess_upper_bound));
	fscanf(fp, "%u", &(decmatr.mess_step));
	
	unsigned int matr_dim_i = 0, matr_dim_j = 0;
	decision_matrix_get_dims(&matr_dim_i, &matr_dim_j);
	decision_matrix_init(matr_dim_i, matr_dim_j);
	
	for (unsigned int i = 0; i < matr_dim_i; ++i)
		for (unsigned int j = 0; j < matr_dim_j; ++j)
			fscanf(fp, "%hhu", &(decmatr.array[i][j]));
	
	fclose(fp);
}

struct quadtree* decision_matrix_encode()
{
	struct quadtree *qt = NULL;
	qt = quadtree_create(qt, decmatr.comm_lower_bound, decmatr.mess_lower_bound, decmatr.comm_upper_bound - decmatr.comm_lower_bound, decmatr.mess_upper_bound - decmatr.mess_lower_bound);
	
	unsigned int matr_dim_i = 0, matr_dim_j = 0;
	decision_matrix_get_dims(&matr_dim_i, &matr_dim_j);
	
	for (unsigned int i = 0; i < matr_dim_i; ++i) {
		for (unsigned int j = 0; j < matr_dim_j; ++j) {
				struct point p = {decmatr.comm_lower_bound + i * decmatr.comm_step, decmatr.mess_lower_bound + j * decmatr.mess_step, decmatr.array[i][j]};
				qt = quadtree_insert(qt, &p);
		}
	}
	
	quadtree_traverse(qt);
	decision_matrix_free();
	return qt;
}

static void decision_matrix_get_dims(unsigned int *dim_i, unsigned int *dim_j)
{
	*dim_i = ceil(((double)(decmatr.comm_upper_bound - decmatr.comm_lower_bound + 1) / decmatr.comm_step));
	*dim_j = ceil(((double)(decmatr.mess_upper_bound - decmatr.mess_lower_bound + 1) / decmatr.mess_step));
}

static void decision_matrix_init(unsigned int dim_i, unsigned int dim_j)
{
	decmatr.array = (unsigned char **)malloc(sizeof(char *) * dim_i);
	
	if (decmatr.array == NULL) {
		fprintf(stderr, "Cannot allocate memory for the matrix.\n");
		exit(1);
	}
	
	for (unsigned int i = 0; i < dim_i; ++i) {
		decmatr.array[i] = (unsigned char *)malloc(sizeof(unsigned char) * dim_j);
		if (decmatr.array[i] == NULL) {
			fprintf(stderr, "Cannot allocate memory for the matrix.\n");
			for (unsigned int j = 0; j < i; ++j)
				free(decmatr.array[j]);
			free(decmatr.array);
			exit(1);
		}
	}
}

static void decision_matrix_free()
{
	if (decmatr.array == NULL)
		return;
		
	unsigned int matr_dim_i = 0, matr_dim_j;
	decision_matrix_get_dims(&matr_dim_i, &matr_dim_j);
	
	for (unsigned int i = 0; i < matr_dim_i; ++i)
		if (decmatr.array[i] != NULL)
			free(decmatr.array[i]);
	
	free(decmatr.array);
}
