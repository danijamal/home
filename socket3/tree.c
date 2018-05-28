/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   tree.c
 * Author: dani
 *
 * Created on 26. Mai 2018, 07:08
 */

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

node_t* insertNode(node_t* node, long long dataIn)
{
    if(node == NULL){
        node=(node_t*)malloc(sizeof(node_t));
        node->left=NULL;
        node->right=NULL;
        node->data=dataIn;
    }
    else if(dataIn < node->data){
        node->left = insertNode(node->left, dataIn);
    }
    else if (dataIn > node->data){ 
        node->right = insertNode(node->right, dataIn);
    }
    return node;
}

node_t* searchNode(node_t *t_ptr, int key)
{
    if(t_ptr == NULL){
        return t_ptr;
    }
    else if(t_ptr->data > key){
        t_ptr=searchNode(t_ptr->left, key);
    }
    else if (t_ptr->data < key){
        t_ptr=searchNode(t_ptr->right, key);
    }
    else if (t_ptr->data == key){
        return t_ptr;   
    }
}

node_t* deleteNode(node_t *t_ptr, int key)
{
    if(t_ptr == NULL){
        return NULL;
    }
    
    if(t_ptr->data > key)
    {
        t_ptr->left = deleteNode(t_ptr->left, key);
    }
    else if (t_ptr->data < key)
    {
       t_ptr->right = deleteNode(t_ptr->right, key);
    }
    else //get it
    {
        //right child
        if (t_ptr->left == NULL)
        {
            node_t* tmp = t_ptr;
            t_ptr = t_ptr->right;
            free(tmp);
        }
        //left child
        else if (t_ptr->right == NULL)
        {
            node_t* tmp = t_ptr;
            t_ptr = t_ptr->left;
            free(tmp);
        }
        //no child
        else if (t_ptr->left == NULL && t_ptr->right == NULL)
        {
            free(t_ptr);
            t_ptr=NULL;
        }
        //two childes
        else {
            node_t *tmp = (node_t*)(findMin(t_ptr->right));
            t_ptr->data = tmp->data;
            t_ptr = deleteNode(t_ptr->right, tmp->data);
        }
    
    }
    return t_ptr;
}

node_t* deleteMin(node_t *t_ptr)
{
    int key;
    
    node_t* tmp = (node_t*)(findMin(t_ptr));
    t_ptr = deleteNode(t_ptr, tmp->data);
     
    return t_ptr;
}

node_t* deleteMax(node_t *t_ptr)
{
    int key;
    
    node_t* tmp = (node_t*)(findMax(t_ptr));
    t_ptr = deleteNode(t_ptr, tmp->data);
    
    return t_ptr;
}

node_t* deleteTree(node_t *t_ptr)
{
    if (t_ptr != NULL){
        t_ptr = deleteTree(t_ptr->left);
        t_ptr = deleteTree(t_ptr->right);
        free(t_ptr);
        t_ptr=NULL;
    }
    return t_ptr;
}

node_t* findMin(node_t *t_ptr)
{
    node_t* tmp = t_ptr;
    while (tmp->left != NULL){
        tmp = tmp->left;
    }
    return tmp;
}

node_t* findMax(node_t *t_ptr)
{
    node_t* tmp = t_ptr;
    while (tmp->right != NULL){
        tmp = tmp->right;
    }
    return tmp;
}

// LVR
void inorderPrint(node_t *t_ptr)
{
    if (t_ptr != NULL){
        inorderPrint(t_ptr->left);
        printf("%lld ->", t_ptr->data);
        inorderPrint(t_ptr->right);
    }
    return;
}

// LRV
void postorderPrint(node_t *t_ptr)
{
    if (t_ptr != NULL){
        postorderPrint(t_ptr->left);
        postorderPrint(t_ptr->right);
        printf("%lld ->", t_ptr->data);
    }
    return;
}
// VLR
void preorderPrint(node_t *t_ptr)
{
    if (t_ptr != NULL){
        printf("%lld ->", t_ptr->data);
        preorderPrint(t_ptr->left);
        preorderPrint(t_ptr->right);
    }
    return;
}

// LVR
void inorderWrite(FILE* file, node_t *t_ptr)
{
    if (t_ptr != NULL){
        inorderWrite(file, t_ptr->left);
        fprintf(file,"%lld\r\n", t_ptr->data);
        inorderWrite(file, t_ptr->right);
    }
    return;
}