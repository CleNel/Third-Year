#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

Tree_Node* new_Node(char data){

    Tree_Node *temp = (Tree_Node*)malloc(sizeof(Tree_Node));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;

    return temp;

}

void tree_insert(Tree_Node** root, char data){
    
    Tree_Node* cur = *root;

    while(1){
        if(data <= cur->data){
            if(cur->left == NULL){
                Tree_Node *temp = (Tree_Node*)malloc(sizeof(Tree_Node));
                temp->data = data;
                temp->left = NULL;
                temp->right = NULL;

                cur->left = temp;
                return;
            }
            cur = cur->left;
        }else{
            if(cur->right == NULL){
                Tree_Node *temp = (Tree_Node*)malloc(sizeof(Tree_Node));
                temp->data = data;
                temp->left = NULL;
                temp->right = NULL;

                cur->right = temp;
                return;
            }
            cur = cur->right;
        }
    }

}

Tree_Node* create_bst (char data[]){
    Tree_Node *root = (Tree_Node*)malloc(sizeof(Tree_Node));
    root->data = data[0];
    root->left = NULL;
    root->right = NULL;

    int i = 1;
    while(data[i] != '\0'){
        tree_insert(&root, data[i]);
        i++;
    }

    return root;

}

Tree_Node* tree_search(Tree_Node* root, char data){
    
    if(root == NULL){
        return NULL;
    }

    if(data == root->data){
        return root;
    }
    
    if(data <= root->data){
        return tree_search(root->left, data);
    }else{
        return tree_search(root->right, data);
    }

    return NULL;
    
}

void tree_print_sorted(Tree_Node* root){

    if(root == NULL){
        return;
    }

     tree_print_sorted(root->left);

     printf("%c", root->data);

     tree_print_sorted(root->right);


}

void tree_delete(Tree_Node* root){
    if(root == NULL ){
        return;
    }

    tree_delete(root->left);
    tree_delete(root->right);

    free(root);

}
