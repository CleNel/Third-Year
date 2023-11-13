#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

void tree_insert(Tree_Node** root, char data){
    
    Tree_Node* cur = *root;

    while(1){
        if(data <= cur->data){
            if(cur->left == NULL){
                Tree_Node *temp = (Tree_Node*)malloc(sizeof(Tree_Node));
                temp->data = data;
                temp->left = NULL;
                temp->right = NULL;

                temp->left = temp;
                return;
            }
            cur = cur->left;
        }else{
            if(cur->right == NULL){
                Tree_Node *temp = (Tree_Node*)malloc(sizeof(Tree_Node));
                temp->data = data;
                temp->left = NULL;
                temp->right = NULL;

                temp->left = temp;
                return;
            }
            cur = cur->right;
        }
    }

/*
    if(data <= cur->data){
        if(cur->left=NULL){
            Tree_Node *temp = (Tree_Node*)malloc(sizeof(Tree_Node));
            temp->data = data;
            temp->left = NULL;
            temp->right = NULL;

            temp->left = temp;
            return;
        }else{
            tree_insert(cur->left, data);
        }

        if(cur->right=NULL){
            Tree_Node *temp = (Tree_Node*)malloc(sizeof(Tree_Node));
            temp->data = data;
            temp->left = NULL;
            temp->right = NULL;

            temp->right = temp;
            return;
        }else{
            tree_insert(cur->right, data);
        }
    } */
}

Tree_Node* create_bst (char data[]){
    Tree_Node *root = (Tree_Node*)malloc(sizeof(Tree_Node));
    root->data = data[0];
    root->left = NULL;
    root->right = NULL;

    Tree_Node **temp = &root;

    int i = 0;
    while(data[i] != '\0'){
        tree_insert(temp, data[i]);
        printf("insert %i ", i);
        i++;
    }

    printf("done\n");

    return root;

}

Tree_Node* tree_search(Tree_Node* root, char data){
    
    if(root->data == data){
        return root;
    }else if(data > root->data){
        tree_search(root->right, data);
    }else if(data < root->data){
        tree_search(root->left, data);
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