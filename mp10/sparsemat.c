#include "sparsemat.h"
	
#include <stdio.h>
#include <stdlib.h>
	
/*
partners: mp31, nbadam2
load_tuples opens a file with the name 'input_file', reads the data from the file, and returns a matrix of the list of tuples type.
If any coordinates repeat in the input file, the newer coordinates overwrite the old line. If there is an entry with a value of 0 
then the corresponding node is deleted if it exists. The elements are returned in order.
gv_tuples returns the value of the element at the given row and column within the matrix.
set_tuples sets the element at row and col to value. If value is 0, it finds the node at row and col if it exists, and delete it 
from the list. We free the nodes from memory. For all other values, the function finds the correct location for the node within 
the sorted linked list. If the entry already exists, the function replaces the old value. If the entry doesn't exist, a node creates 
and inserts into the linked list. We also update the 'nz' variable of the struct.
save_tuples writes the data in a sparse matrix structure to a text file.
add_tuples adds two matrices together by traversing the linked lists of both matrices. We return NULL if addition between matA and 
matB is not possible.
destroy_tuples frees all memory associated with the given matrix.
*/	
	
	
	
sp_tuples * load_tuples(char* input_file)
{
    int row;
    int col;
    double val;
	
	FILE *file = fopen(input_file, "r"); // open file
	sp_tuples * matrix = (sp_tuples*)malloc(sizeof(sp_tuples));
	fscanf(file, "%d %d\n", &(matrix->m), &(matrix->n));
	
	matrix->nz =0;
	matrix->tuples_head = NULL; // initialize nodes
	
	while( feof(file) == 0) {
	    fscanf(file, "%d %d %lf\n", &row, &col, &val);
	    set_tuples(matrix, row, col, val);
	}

    fclose(file);	 

	return matrix;
}
	
	
	
double gv_tuples(sp_tuples * mat_t,int row,int col)
{
    sp_tuples_node * curr= mat_t-> tuples_head;

    while(curr!= NULL){
        if( (curr->row) == row && (curr->col) ==col )
            return curr->value;
        curr = curr->next;
    }

    return 0;
}
	


void deleteNode(sp_tuples * mat_t, int row, int col){
    sp_tuples_node * prev_node = NULL;
    sp_tuples_node * curr_node = mat_t -> tuples_head;

    if(curr_node-> row == row && curr_node-> col ==col){
        mat_t->tuples_head = curr_node->next;
        free(curr_node);
        mat_t-> nz--;
        return;
    }

    while(curr_node !=NULL) {
        if(curr_node-> row == row && curr_node-> col ==col){
            prev_node->next = curr_node->next;
            free(curr_node);
            mat_t-> nz--;
            return;
        }else{
            prev_node = curr_node;
            curr_node= curr_node->next;
        }
	}
}
	


void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{

    // if list is empty, allocate memory
    if(mat_t-> tuples_head == NULL){
        sp_tuples_node * node = (sp_tuples_node *)malloc(sizeof(sp_tuples_node));
        node->row = row;
        node->col = col;
        node->value = value;
        node->next = NULL;
        mat_t->tuples_head = node;
        mat_t->nz++;
        return;
    }
        
    // if value is 0, delete the node at row, col
    if(value == 0){
        deleteNode( mat_t, row, col );
        return;
    }

    sp_tuples_node * curr_node = mat_t->tuples_head;

    int index = row * mat_t->n + col;
    int curr_index = curr_node->row * mat_t->n + curr_node->col;

    if( index < curr_index ){
        if( curr_node->row == row && curr_node->col == col ){
            // if given index is before head index and the row and colums matches with the given, we update the value at that node
            curr_node->value = value;
        }else{
            // else, if given index is before head index, we allocate memory for node and place it as the head node
            sp_tuples_node * node = (sp_tuples_node *)malloc(sizeof(sp_tuples_node));
            node->row = row;
            node->col = col;
            node->value = value;
            node->next = curr_node;
            mat_t->tuples_head = node;
            mat_t->nz++;
            return;
        }
    }

    //iterate through nodes and update value if node already exists at index
    curr_node = mat_t->tuples_head;
    while( curr_node != NULL ){
        curr_index = curr_node->row * mat_t->n + curr_node->col;
        if( index == curr_index ){
            curr_node->value = value;
            return;
        }
        curr_node = curr_node->next;
    }
    
    //iterate through the list to find if node at middle or end of list; store the previous node so we can update the linnked list
    curr_node = mat_t->tuples_head;
    while( curr_node->next != NULL && (curr_node->next)->row * mat_t->n + (curr_node->next)->col < index){
        curr_node = curr_node->next;
    }

    //if we reach the end of the linked list, we allocate memory at the end and place the node as the new tail
    if( curr_node->next == NULL ){
        sp_tuples_node * node = (sp_tuples_node *)malloc(sizeof(sp_tuples_node));
        node->row = row;
        node->col = col;
        node->value = value;
        node->next = NULL;
        curr_node->next = node;
        mat_t->nz++;
        return;
    }

    //if the node is not at the end or beginning, we allocate memeory and place it in the middle 
    sp_tuples_node * node = (sp_tuples_node *)malloc(sizeof(sp_tuples_node));
    node->row = row;
    node->col = col;
    node->value = value;
    node->next = curr_node->next;
    curr_node->next = node;
    mat_t->nz++;
    return;

}
	
	
	
void save_tuples(char * file_name, sp_tuples * mat_t)
{
    
    FILE *file = fopen(file_name, "w");

    if(file == NULL){
        return;
    }

    fprintf(file, "%d %d\n", (mat_t->m), (mat_t->n));
    sp_tuples_node *node  = mat_t ->tuples_head;

    while(node != NULL){
        fprintf(file, "%d %d %lf\n", (node->row), (node-> col), (node->value));
        node = (node->next);
    }

    fclose(file);
}
	
	
	
	
sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){

    sp_tuples *matC = (sp_tuples*)malloc(sizeof(sp_tuples));
    matC->m = matA->m;
    matC->n = matA->n;
    matC->nz = 0;
    matC->tuples_head = NULL;

    if( matA->m != matB->m || matA->n != matB->n ){
        return NULL;
    }

    sp_tuples_node * node = matA->tuples_head;
    while(node != NULL){
        set_tuples(matC, node-> row, node->col, node->value);
        node = node->next;
    }

    node = matB->tuples_head;
    while(node != NULL){
        double C_value = gv_tuples(matC, node->row, node->col) + node->value;
        set_tuples(matC, node->row, node->col, C_value);
        node = node->next;
    }

    return matC;
}



sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){
    
	return matA;
}



void destroy_tuples(sp_tuples * mat_t){
    sp_tuples_node * node = (mat_t -> tuples_head);
    sp_tuples_node * temp = NULL;

    while(node !=NULL){
        temp = node->next;
        free(node);
        node = temp;
    }

    free(mat_t);
    return;
}  
