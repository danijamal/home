/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   tree.h
 * Author: dani
 *
 * Created on 26. Mai 2018, 07:09
 */

#ifndef TREE_H
#define TREE_H

typedef struct tree
{
    struct tree* left;
    struct tree* right;
    long long data;

}node_t;

node_t* findMin(node_t* t_ptr);
node_t* findMax(node_t *t_ptr);
node_t* insertNode(node_t* t_ptr, long long data_insert);
node_t* deleteNode(node_t *t_ptr, int key);
node_t* deleteTree(node_t *t_ptr);
node_t* deleteMin(node_t *t_ptr);
node_t* deleteMax(node_t *t_ptr);
node_t* searchNode(node_t *t_ptr, int key);
void inorderWrite(FILE* output, node_t* root);
void inorderPrint(node_t *t_ptr);
void postorderPrint(node_t *t_ptr);
void preorderPrint(node_t *t_ptr);
void print_tree(node_t *tree);
int _print_tree(node_t *tree, int is_left, int offset, int depth, char s[20][255]);

#endif /* TREE_H */

