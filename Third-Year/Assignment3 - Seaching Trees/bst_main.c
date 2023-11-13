#include <stdio.h>
#include <stdlib.h>
#include "bst_skeleton.c"
#include "bst.h"

int main(){

    char arr[10] = "hskfhfurnf";
    Tree_Node *tree = create_bst(arr);
    tree_print_sorted(tree);

}