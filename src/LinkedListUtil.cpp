//
// Created by cchau on 12/27/2024.
//

#include "LinkedListUtil.h"

ListNode *LinkedListUtil::middleNode(ListNode *head) {
    if (!head || !head->next) {
        return head;
    }

    ListNode *slow = head;
    ListNode *fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

ListNode *LinkedListUtil::deleteDuplicates(ListNode *head) {
    if (!head || !head->next) {
        return head;
    }

    for (ListNode* currNode = head; currNode != nullptr;) {
        ListNode* nextNode = currNode->next;
        if (nextNode && currNode->val == nextNode->val) {
            currNode->next = nextNode->next;
            delete nextNode; // Crucial: delete the duplicate node
        } else {
            currNode = currNode->next;
        }
    }

    return head;
}

ListNode *LinkedListUtil::reverseBetween(ListNode *head, int left, int right) {
    if (head == nullptr || head->next == nullptr || left == right) {
        return head;
    }

    // Dummy node to handle cases where left == 1
    ListNode dummy(0);
    dummy.next = head;
    ListNode* pre = &dummy; // Node before the sublist to be reversed

    // Move 'pre' to the node immediately before the 'left' position
    for (int i = 1; i < left; ++i) {
        if (pre == nullptr) return nullptr; // left is greater than the length of list
        pre = pre->next;
    }

    ListNode* cur = pre->next; // Start of the sublist to be reversed

    // Reverse the sublist from left to right
    for (int i = 0; i < right - left; ++i) {
        ListNode* next = cur->next;
        if (next == nullptr) break; // right is beyond list length
        cur->next = next->next;
        next->next = pre->next;
        pre->next = next;
    }

    return dummy.next;
}
