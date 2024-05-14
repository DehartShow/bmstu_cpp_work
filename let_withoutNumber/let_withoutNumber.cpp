//
// Created by dehart on 21.03.24.
//
#include <gtest/internal/gtest-type-util.h>

#include <cassert>
#include <iostream>

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  explicit ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode *AddTwoNumbers(ListNode *l1, ListNode *l2) {
  ListNode *head = new ListNode();
  ListNode *current = head;
  int carry = 0;
  while (l1 || l2 || carry) {
    int sum = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + carry;
    carry = sum / 10;
    current->next = new ListNode(sum % 10);
    current = current->next;

    l1 = l1 ? l1->next : nullptr;
    l2 = l2 ? l2->next : nullptr;
  }
  return head->next;
}
int main() {
  // Test case 1: 342 + 465 = 807
  ListNode* l1 = new ListNode(2, new ListNode(4, new ListNode(3)));
  ListNode* l2 = new ListNode(5, new ListNode(6, new ListNode(4)));
  ListNode* result = AddTwoNumbers(l1, l2);

  std::cout << "Test case 1: ";
  while (result != nullptr) {
    std::cout << result->val << " ";
    result = result->next;
  }
  std::cout << std::endl;
}
