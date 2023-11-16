#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bstdb.h"

const float MAX_SIZE = 131072;
float numerator = 1;
float denominator = 2;
int CHECK = 1;
int num_insertions;
int tot_num_nodes;

// Write your submission in this file
//
// A main function and some profiling tools have already been set up to test
// your code in the task2.c file. All you need to do is fill out this file
// with an appropriate Binary Search Tree implementation.
//
// The input data will be books. A book is comprised of a title and a word
// count. You should store both these values in the tree along with a unique
// integer ID which you will generate.
//
// We are aiming for speed here. A BST based database should be orders of
// magnitude faster than a linked list implementation if the BST is written
// correctly.
//
// We have provided an example implementation of what a linked list based
// solution to this problem might look like in the db/listdb.c file. If you
// are struggling to understand the problem or what one of the functions
// below ought to do, consider looking at that file to see if it helps your
// understanding.
//
// There are 6 functions you need to look at. Each is provided with a comment
// which explains how it should behave. The functions are:
//
//  + bstdb_init
//  + bstdb_add
//  + bstdb_get_word_count
//  + bstdb_get_name
//  + bstdb_stat
//  + bstdb_quit
//
// Do not rename these functions or change their arguments/return types.
// Otherwise the profiler will not be able to find them. If you think you
// need more functionality than what is provided by these 6 functions, you
// may write additional functions in this file.

typedef struct Tree_Node{
	int ID;
	int word_count;
	char *name;
    struct Tree_Node *left, *right;
} Tree_Node;

Tree_Node *ROOT;

int generateID(){

	int ID = (MAX_SIZE) * ((numerator)/(denominator));

	numerator = numerator + 2;

	if(numerator > denominator){
		denominator = denominator * 2;
		numerator = 1;
	}

	return ID;
}

void tree_delete(Tree_Node* root){
    if(root == NULL ){
        return;
    }

    tree_delete(root->left);
    tree_delete(root->right);

    free(root);

}

Tree_Node* new_Node(char *name, int wordCount ){

	size_t len_name;

    Tree_Node *temp = (Tree_Node*)malloc(sizeof(Tree_Node));
	if(temp){
		temp->word_count = wordCount;
    	temp->left = NULL;
    	temp->right = NULL;

		len_name = strlen(name)+1;
		temp->name = calloc(len_name, sizeof(char));
		if(temp->name){
			strcpy(temp->name, name);
		}else{
			free(temp);
			temp = NULL;
		}

	}
	
    return temp;

}


void tree_insert(Tree_Node** root, Tree_Node* current){

	Tree_Node* temp = *root;

    while(1){
        if(current->ID <= temp->ID){
            if(temp->left == NULL){
                temp->left = current;
                return;
            }
            temp = temp->left;
        }else{
            if(temp->right == NULL){
                temp->right = current;
                return;
            }
            temp = temp->right;
        }
    }

}

Tree_Node* tree_search(Tree_Node* root, int ID){
    
    if(root == NULL){
        return NULL;
    }

    if(ID == root->ID){
        return root;
    }
    
    if(ID <= root->ID){
        return tree_search(root->left, ID);
    }else{
        return tree_search(root->right, ID);
    }

    return NULL;
}


int
bstdb_init ( void ) {
	// This function will run once (and only once) when the database first
	// starts. Use it to allocate any memory you want to use or initialize 
	// some globals if you need to. Function should return 1 if initialization
	// was successful and 0 if something went wrong.
	return 1;
}

int
bstdb_add ( char *name, int word_count, char *author ) {
	
	// This function should create a new node in the binary search tree, 
	// populate it with the name, word_count and author of the arguments and store
	// the result in the tree.
	//
	// This function should also generate and return an identifier that is
	// unique to this document. A user can find the stored data by passing
	// this ID to one of the two search functions below.
	//
	// How you generate this ID is up to you, but it must be an integer. Note
	// that this ID should also form the keys of the nodes in your BST, so
	// try to generate them in a way that will result in a balanced tree.
	//
	// If something goes wrong and the data cannot be stored, this function
	// should return -1. Otherwise it should return the ID of the new node

	int i;

	if(CHECK == 1){
		struct Tree_Node *temp;

		temp = new_Node(name, word_count);
		if(!temp){
			return -1;
		}
		i = generateID();
		temp->ID = i;
		CHECK = 0;
		ROOT = temp;
		num_insertions++;
		return i;
	}else{
		struct Tree_Node *temp;

		temp = new_Node(name, word_count);
		if(!temp){
			return -1;
		}

		i = generateID();
		temp->ID = i;
		tree_insert(&ROOT, temp);
	}

	num_insertions++;
	return i;
}

int
bstdb_get_word_count ( int doc_id ) {
	// This is a search function. It should traverse the binary search tree
	// and return the word_count of the node with the corresponding doc_id.
	//
	// If the required node is not found, this function should return -1

	Tree_Node *temp = tree_search(ROOT, doc_id);
	if(temp == NULL){
		return -1;
	}else{
		return temp->word_count;
	}
}

char*
bstdb_get_name ( int doc_id ) {
	// This is a search function. It should traverse the binary search tree
	// and return the name of the node with the corresponding doc_id.
	//
	// If the required node is not found, this function should return NULL or 0
	Tree_Node *temp = tree_search(ROOT, doc_id);
	if(temp == NULL){
		return 0;
	}else{
		return temp->name;
	}
	return 0;
}

//Is the tree balanced

int max(int a, int b){
	if(a >= b){
		return a;
	}else{
		return b;
	}
}

int height(Tree_Node* root){
	if(root == NULL){
		return 0;
	}
	return 1 + max(height(root->left), height(root->right));
}

int isBalanced(Tree_Node *root){
	int LH, RH;

	if(root == NULL){
		return 1;
	}

	LH = height(root->left);
	RH = height(root->right);

	if(abs(LH - RH) <= 1 && isBalanced(root->left) && isBalanced(root->right)){
		return 1;
	}

	return 0;

}

//Node counting

int count_nodes(Tree_Node *root){
	if(root == NULL){
		return 0;
	}

	int L_node = count_nodes(root->left);
	int R_node = count_nodes(root->right);

	return 1 + L_node + R_node;

}

void
bstdb_stat ( void ) {
	// Use this function to show off! It will be called once after the 
	// profiler ends. The profiler checks for execution time and simple errors,
	// but you should use this function to demonstrate your own innovation.
	//
	// Suggestions for things you might want to demonstrate are given below,
	// but in general what you choose to show here is up to you. This function
	// counts for marks so make sure it does something interesting or useful.
	//
	//  + Check if your tree is balanced and print the result
	//
	//  + Does the number of nodes in the tree match the number you expect
	//    based on the number of insertions you performed?
	//
	//  + How many nodes on average did you need to traverse in order to find
	//    a search result? 
	//
	//  + Can you prove that there are no accidental duplicate document IDs
	//    in the tree?

	if(isBalanced(ROOT) == 1){
		printf("This tree is BALANCED!\n");
	}else{
		printf("This tree is NOT BALANCED!\n");
	}

	tot_num_nodes = count_nodes(ROOT);

	printf("There are %i nodes inserted\n", num_insertions);
	printf("There are %i nodes in the tree\n", tot_num_nodes);

}

void
bstdb_quit ( void ) {
	// This function will run once (and only once) when the program ends. Use
	// it to free any memory you allocated in the course of operating the
	// database.
	tree_delete(ROOT);
}

//gcc -Wall -g src/task2.c src/bstdb.c src/db/profiler.c src/db/database.c src/db/listdb.c -o task2 -lm
