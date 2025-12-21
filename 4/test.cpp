#include "solution.cpp"

/*
* @return median
*/
double generate(std::vector<int>& first, std::vector<int>& second, size_t quantity, int seed){
    std::vector<int> data; data.reserve(quantity);

    std::mt19937 gen(seed); 
    std::uniform_int_distribution<> d(1, 10000);

    for (size_t i = 0; i < quantity; ++i){
        data.push_back(d(gen));
    }

    std::sort(data.begin(), data.end());

    for (auto i : data){
        if (gen() % 2){
            first.push_back(i);
        } else {
            second.push_back(i);
        }
    }

    if (quantity % 2){
        return data[quantity / 2];
    } else {
        return (data[quantity / 2] + data[quantity / 2 - 1]) / 2.0;
    }    
}

void test_(size_t iterations, int quantity = 15, int seed = 588){
    std::vector<int> f, s;

    Solution sol;

    for (size_t i{0}; i < iterations; ++i){
        f.clear(); s.clear();
        double ans = generate(f, s, quantity, seed);
        double res = sol.findMedianSortedArrays(f,s);
        if (ans - res){
            std::cout << "ERROR" << std::endl;
            std::cout << ans << " != " << res << std::endl;
            std::cout << "nums1:\n";
            for (auto num : f)
                std::cout << num << "\n";
            std::cout << "nums2:\n";
            for (auto num : s)
                std::cout << num << "\n";
	    break;
        }
    }

    std::cout << "All tests passed" << std::endl;
}

int main(){

    test_(100000);
    
}
