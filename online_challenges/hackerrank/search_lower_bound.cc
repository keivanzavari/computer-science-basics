#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>


/* 
* binary search, similar to lower_bound of std::vector class
*/
int lowerBound(const std::vector<int> & ar, int val)
{
    int size = ar.size();
    if (size == 0)
        return 0;
    int end = size-1;
    int begin = 0;
    int idx = (end-begin)/2;
    int mid_val = ar[idx];
    if (mid_val == val)
        return idx;

    std::cout << "idx: " << idx << " val:" << mid_val << std::endl;
    std::cout << "end: " << end << " begin:" << begin << std::endl;

    int no_iter=0;
    while ((mid_val != val) && (no_iter < size))
    {
        std::cout << "val: " << mid_val << " given:" << val << std::endl;

        if (mid_val > val) {
            end = idx-1;
        }
        else if (mid_val < val) {
            begin = idx+1;
        }

        idx = begin+(end-begin)/2;
        mid_val = ar[idx];

        no_iter++;
        std::cout << "idx: " << idx << " val:" << mid_val << std::endl;
        std::cout << "end: " << end << " begin:" << begin << std::endl;

    }
    
    return idx;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int v;
    std::cout << "value: ";
    std::cin >> v;
    
    int n;
    std::cout << "array size: ";
    std::cin >> n;
    std::vector<int> ar(n);
    
    std::cout << "vec values: ";
    for (int i=0; i<n; i++)
        std::cin >> ar[i];
    

    int idx = lowerBound(ar, v);
    std::cout << "\nlowerBound: " << idx << std::endl;
    

    std::vector<int>::iterator it = std::lower_bound(ar.begin(), ar.end(), v);
    // std::cout << "lower_bound: " << std::endl;
    // std::cout << it-ar.begin() << std::endl;
    return 0;
}