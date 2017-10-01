/*
Print elements of a linked list on console 
head pointer input could be NULL as well for empty list
Node is defined as 
struct Node
{
    int data;
    struct Node *next;
}
*/

#include <iostream>

struct Node {
    int data;
    Node *next;
    Node(int x) : data(x), next(NULL) {}
    Node() : data(0), next(NULL) {}
};

void Print(Node *head)
{
    if (head==NULL)
    {
        std::cout << std::endl;
        return;
    }

    std::cout << head->data << " ";
    Print(head->next);

}

Node* Insert(Node *head,int data)
{
    if (head == NULL)
    {
        std::cout << "null with data..." << data << std::endl;

        Node * tail = new Node;
        tail->data = data;
        return tail;   
    }
    else if (head->next == NULL)
    {
        Node * tail = new Node;
        tail->data = data;
        head->next = tail;
        return head;
    }
    
    Node * return_node = new Node;
    return_node = Insert(head->next, data);

    return return_node;
}

int main()
{


    if (0){
        Node *node = new Node;
        node->data = 300;

        for (int i=0; i<3; i++)
        {
            Node * tmp_node = new Node;
            tmp_node->data = i;
            tmp_node->next = node;
            node = tmp_node;
        }
        std::cout << "initialized, now print: " << std::endl;
        Print (node);
        delete node;
    }
    {
        Node * tmp_node;
        Print(tmp_node);

        std::cout << "initialized, now Insert: " << std::endl;
        tmp_node = Insert(tmp_node,5);
        tmp_node = Insert(tmp_node,3);
        Print(tmp_node);
    }
    
    return 0;
}