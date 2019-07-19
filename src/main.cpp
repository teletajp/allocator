#include <map>
#include <iostream>
#include "version.h"
#include "spec_allocator.h"
#include "fwd_list.h"
constexpr int factorial(unsigned int t)
{
       if(t)return t*factorial(t-1);
       else return 1;
}
int main(int argc, char const *argv[])
{
    std::map<int, int> num2fact_standart;
    num2fact_standart.emplace(std::make_pair(0,factorial(0)));
    num2fact_standart.emplace(std::make_pair(1,factorial(1)));
    num2fact_standart.emplace(std::make_pair(2,factorial(2)));
    num2fact_standart.emplace(std::make_pair(3,factorial(3)));
    num2fact_standart.emplace(std::make_pair(4,factorial(4)));
    num2fact_standart.emplace(std::make_pair(5,factorial(5)));
    num2fact_standart.emplace(std::make_pair(6,factorial(6)));
    num2fact_standart.emplace(std::make_pair(7,factorial(7)));
    num2fact_standart.emplace(std::make_pair(8,factorial(8)));
    num2fact_standart.emplace(std::make_pair(9,factorial(9)));

    for(auto [k,v]:num2fact_standart)
        std::cout << k << ' ' << v << std::endl;
    {
        std::map<int, int, std::less<int>, spec_allocator<std::pair<const int, int>, 10>> num2fact_nostandart;
        //std::cout << "end:" << num2fact_nostandart.end()._Ptr << std::endl;
        num2fact_nostandart.emplace(std::make_pair(0, factorial(0)));
        num2fact_nostandart.emplace(std::make_pair(1, factorial(1)));
        num2fact_nostandart.emplace(std::make_pair(2, factorial(2)));
        num2fact_nostandart.emplace(std::make_pair(3, factorial(3)));
        num2fact_nostandart.emplace(std::make_pair(4, factorial(4)));
        num2fact_nostandart.emplace(std::make_pair(5, factorial(5)));
        num2fact_nostandart.emplace(std::make_pair(6, factorial(6)));
        num2fact_nostandart.emplace(std::make_pair(7, factorial(7)));
        num2fact_nostandart.emplace(std::make_pair(8, factorial(8)));
        num2fact_nostandart.emplace(std::make_pair(9, factorial(9)));
        for (auto[k, v] : num2fact_nostandart)
            std::cout << k << ' ' << v << std::endl;
    }
    fwd_list<int> my_list_std_alloc;
    for (int i = 0; i < 10; i++)
        my_list_std_alloc.push_back(i);
   
    for(auto v :my_list_std_alloc)
        std::cout << v << std::endl;

    fwd_list<int, spec_allocator<int, 10>> my_list_my_alloc;
    for(int i = 0; i<10; i++)
        my_list_my_alloc.push_back(i);
   
    for (auto v : my_list_my_alloc)
        std::cout << v << std::endl;

    return 0;
}
