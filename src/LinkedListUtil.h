//
// Created by cchau on 12/27/2024.
//

#ifndef PLAYGROUND_LINKEDLISTUTIL_H
#define PLAYGROUND_LINKEDLISTUTIL_H


#include <vector>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class LinkedListUtil {
public:
    ListNode* middleNode(ListNode* head);
    ListNode* deleteDuplicates(ListNode* head);
    ListNode* reverseBetween(ListNode* head, int left, int right);
};


#endif //PLAYGROUND_LINKEDLISTUTIL_H
