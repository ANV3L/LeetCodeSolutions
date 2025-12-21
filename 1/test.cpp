#include "solution.cpp"


int func(vector<int>& data, size_t n) {
    data.reserve(30);
    mt19937 rng(15);
    uniform_int_distribution<int> dist(-100, 100);
    
    for (size_t i = 0; i < n; ++i) {
        data.push_back(dist(rng));
    }
    
    size_t i = uniform_int_distribution<size_t>(0, n-1)(rng);
    size_t j = uniform_int_distribution<size_t>(0, n-1)(rng);
    while (j == i) j = uniform_int_distribution<size_t>(0, n-1)(rng);  // != i
    
    return data[i] + data[j];
}

void test_(size_t times){
    std::vector<int> data;
    std::vector<int> ans;
    Solution sol;

    while (times--){
        data.clear(); ans.clear();
        int target = func(data, 30);
        ans = sol.twoSum(data, target);
        if (data[ans[0]] + data[ans[1]] == target){
            // std::cout << "SUCCESS" << std::endl;
        } else {
            std::cout << "ERROR\n";
            std::cout << "Target: " << target << '\n';
            std::cout << "Parts: " << data[ans[0]] << ' ' << data[ans[1]] << std::endl;
            return;
        }
    }
    std::cout << "ALL TESTS DONE\n"; 
}

int main(){
    test_(10000);
}
