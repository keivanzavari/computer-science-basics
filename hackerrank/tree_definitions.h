#include <string>
#include <iostream>

/*
* node definition
*/
typedef struct node
{
    int value;
    struct node* left;
    struct node* right;
    int height;

    node(): height(-1), value(0), left(NULL), right(NULL){};
} node;


/**
* See https://en.wikipedia.org/wiki/Tree_traversal
* for more info
*/
/**
* a parth of depth first search
* - Check if the current node is empty / null.
* - Display the value part of the root (or current node).
* - Traverse the left subtree by recursively calling the pre-order function.
* - Traverse the right subtree by recursively calling the pre-order function.
*/
void preOrder(node * root) {
    if (root == NULL)
    {
        std::cout << std::endl;
        return;
    } else
        std::cout << root->value << " ";
    
    if (root->left != NULL) 
        preOrder(root->left);
    if (root->right != NULL) 
        preOrder(root->right);
    
}


/**
* - Check if the current node is empty / null.
* - Traverse the left subtree by recursively calling the post-order function.
* - Traverse the right subtree by recursively calling the post-order function.
* - Display the value part of the root (or current node).
*/
void postOrder(node *root) {
    if (root == NULL)
    {
        std::cout << std::endl;
        return;
    }
    
    if (root->left != NULL) 
        postOrder(root->left);
    if (root->right != NULL) 
        postOrder(root->right);
    std::cout << root->value << " ";
}


/**
* - Check if the current node is empty / null.
* - Traverse the left subtree by recursively calling the in-order function.
* - Display the value part of the root (or current node).
* - Traverse the right subtree by recursively calling the in-order function.
*/
void inOrder(node *root) {
    if (root == NULL)
    {
        std::cout << std::endl;
        return;
    }
    
    if (root->left != NULL) 
        inOrder(root->left);
    
    std::cout << root->value << " ";
    
    if (root->right != NULL) 
        inOrder(root->right);
}
