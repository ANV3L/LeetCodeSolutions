
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}

    void insert_back(int x) {
        ListNode* cur = this;
        while (cur->next) cur = cur->next;
        cur->next = new ListNode(x);
    }
};

#include "solution.cpp"

#include <random>
#include <algorithm>
#include <iostream>

#define SEED 704
#define ELEMENTS_QUANTITY 100000
#define LISTS_QUANTITY 1300

std::mt19937 gen(SEED);

std::vector<int> generVector(size_t quantity){

    std::uniform_int_distribution<int> dist(10, 1000);

    std::vector<int> res; res.reserve(quantity);

    for (size_t i{0}; i < quantity; ++i){
        res.push_back(dist(gen));
    }

    std::sort(res.begin(), res.end());

    return res;
}


void freeList(ListNode* head) {
    while (head) {
        ListNode* nxt = head->next;
        delete head;
        head = nxt;
    }
}

bool test_() {
    gen.seed(SEED);

    std::vector<int> ans = generVector(ELEMENTS_QUANTITY);

    std::vector<int> shuffled = ans;
    std::shuffle(shuffled.begin(), shuffled.end(), gen);

    std::vector<ListNode*> heads(LISTS_QUANTITY, nullptr);
    std::vector<ListNode*> tails(LISTS_QUANTITY, nullptr);

    std::uniform_int_distribution<size_t> pick(0, LISTS_QUANTITY - 1);

    for (int x : shuffled) {
        size_t idx = pick(gen);

        ListNode* n = new ListNode(x);
        if (!heads[idx]) {
            heads[idx] = tails[idx] = n;
        } else {
            tails[idx]->next = n;
            tails[idx] = n;
        }
    }

    std::vector<ListNode*> lists;
    lists.reserve(LISTS_QUANTITY);

    for (size_t i = 0; i < LISTS_QUANTITY; ++i) {
        std::vector<int> v;
        for (ListNode* p = heads[i]; p; p = p->next) v.push_back(p->val);

        std::sort(v.begin(), v.end());

        freeList(heads[i]);

        ListNode dummy(0);
        ListNode* tail = &dummy;
        for (int val : v) {
            tail->next = new ListNode(val);
            tail = tail->next;
        }
        lists.push_back(dummy.next);
    }

    Solution sol;
    ListNode* merged = sol.mergeKLists(lists);

    size_t pos = 0;
    for (ListNode* p = merged; p; p = p->next, ++pos) {
        if (pos >= ans.size()) {
            std::cout << "ERROR\n";
            freeList(merged);
            return true;
        }
        if (p->val != ans[pos]) {
            std::cout << "ERROR\n";
            freeList(merged);
            return true;
        }
    }

    if (pos != ans.size()) {
        std::cout << "ERROR\n";
        return true;
    }


    freeList(merged);
    return false;
}

int main(){
    for (size_t i{0}; i < 100; ++i)
        test_();
    std::cout << "ALL TESTS PASSED" << std::endl;
}