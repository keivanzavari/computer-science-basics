#include <iostream>
#include <unordered_set>

int main()
{


    const int n = 4;
    int set[n] = {1, 2, 3, 4} ;
    int sum = 9;

    std::unordered_set<int> hash_set;
    std::unordered_set<int>::iterator it;
    // check each element in array
    for (int i=0; i<n; i++)
    {
        // calculate S minus current element
        int complement = sum - set[i];

        // check if this number exists in hash table
        // if so then we found a pair of numbers that sum to S
        it = hash_set.find(complement);
        if ( it != hash_set.end() )
        {
            std::cout << "found: "  << *it << std::endl;
        }

        //number was not found. Put it in the map.
        hash_set.insert(set[i]);
    }

    std::cout << "\n--------------------" << std::endl;

    return 0;
}