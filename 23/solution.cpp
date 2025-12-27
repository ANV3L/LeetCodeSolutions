#include <queue>
#include <vector>

using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    struct Cmp{
        bool operator()(const ListNode* first, const ListNode* second) const {
            return first->val > second->val;
        }
    };

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        std::priority_queue<ListNode*, std::vector<ListNode*>, Cmp> que;

        for (auto* it : lists){
            if (it)
                que.push(it);
        }

        ListNode node{};
        ListNode* tail = &node;

        while (!que.empty()) {
            ListNode* temp = que.top();
            que.pop();

            tail->next = temp;
            tail = temp;

            if (temp->next) que.push(temp->next);
        }

        tail->next = nullptr;
        return node.next;

    }
};