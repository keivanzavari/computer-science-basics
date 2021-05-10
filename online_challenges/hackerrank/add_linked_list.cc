#include <iostream>

/**
 * Definition for singly-linked list.
 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
    ListNode() : val(0), next(NULL) {}
};

int printList(ListNode *traverse) {
    if (traverse == NULL) {  
        std::cout << std::endl ;
        return -1;
    }
    std::cout << traverse->val << " " ;
    printList(traverse->next);
    return 0;
}

ListNode * addTwoLists(ListNode * l1, ListNode * l2, int above_ten=0)
{
    ListNode * sum = new ListNode;
    if (l1 == NULL || l2 == NULL) 
    {
        // std::cout << "reached end" << std::endl ;
        return NULL;
    }

    int next_above_ten = 0;
    sum->val = l1->val  + l2->val + above_ten;
    if (sum->val >= 10)
    {
        sum->val %= 10;
        next_above_ten = 1;
    }
    
    sum->next = addTwoLists(l1->next , l2->next, next_above_ten);
    return sum;
}

int main()
{
    // ListNode l1(2);
    // ListNode *l1_ptr = &l1;


    ListNode *head = NULL;
    for (int i = 3; i > 0; i--) {
        ListNode *newEntry = new ListNode;
        switch (i)
        {
            case 3: newEntry->val=4; break;
            case 2: newEntry->val=6; break;
            case 1: newEntry->val=5; break;
        }
        newEntry->next = head;
        head = newEntry;
    }


    ListNode * l1_ptr = new ListNode;
    l1_ptr = head;
    printList(l1_ptr);

    head = NULL;
    for (int i = 3; i > 0; i--) {
        ListNode *newEntry = new ListNode;
        switch (i)
        {
            case 3: newEntry->val=3; break;
            case 2: newEntry->val=4; break;
            case 1: newEntry->val=2; break;
        }
        newEntry->next = head;
        head = newEntry;
    }
    ListNode * l2_ptr = head;
    // l1_ptr = head;
    printList(l2_ptr);

    ListNode * l3_ptr = new ListNode;

    l3_ptr = addTwoLists(l1_ptr, l1_ptr);
    printList(l3_ptr);


    return 0;
}