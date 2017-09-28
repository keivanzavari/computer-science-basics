/* you only have to complete the function given below.  
Node is defined as  

struct node
{
    int data;
    node* left;
    node* right;
};

*/



/**
* a parth of depth first search
* - Check if the current node is empty / null.
* - Display the data part of the root (or current node).
* - Traverse the left subtree by recursively calling the pre-order function.
* - Traverse the right subtree by recursively calling the pre-order function.
*/
void preOrder(node * root) {
    if (root == NULL)
    {
        std::cout << std::endl;
        return;
    } else
        std::cout << root->data << " ";
    
    if (root->left != NULL) 
        preOrder(root->left);
    if (root->right != NULL) 
        preOrder(root->right);
    
}



/**
* - Check if the current node is empty / null.
* - Traverse the left subtree by recursively calling the post-order function.
* - Traverse the right subtree by recursively calling the post-order function.
* - Display the data part of the root (or current node).
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
    std::cout << root->data << " ";
}
