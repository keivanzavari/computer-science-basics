#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

void printArray(const std::vector<int> & array)
{
    std::cout << "\n------ print --------" << std::endl;
    std::cout << "array: " << std::endl;
    for (int i=0; i<array.size() ; i++)
        std::cout << array[i] << " ";
    std::cout <<  std::endl;

}

/*
* sorting the last element
*/
void sortLastElement(std::vector<int> & ar)
{
    int n = ar.size();
    int last_val = ar[n-1];
    for (int idx = n-1; idx >= 0; idx--)
    {
        if ((ar[idx-1] > last_val) && (idx != 0))
        {
            ar[idx] = ar[idx-1];
            // std::cout << "shifting... ";

        } else {
            ar[idx] = last_val;
            // std::cout << "replacing... " << last_val;
            break;
        }
    }
}

/*
* extension of sorting the last element to sorting the whole array
*/
void insertionSort(std::vector<int> & ar)
{
    int n = ar.size();
    for (int ii=1; ii<n; ii++)
    {
        std::cout << "ii index " << ii << std::endl;
        std::cout << "---------------" << std::endl;
        printArray(ar);

        int last_val = ar[ii];
        for (int idx = ii; idx >= 0; idx--)
        {
            if ((ar[idx-1] > last_val) && (idx != 0))
            {
                ar[idx] = ar[idx-1];
                // std::cout << "shifting... ";

            } else {
                ar[idx] = last_val;
                // std::cout << "replacing... " << last_val;
                break;
            }
        }
            
    }
    
}

int main() {
    
    int n;
    std::cout << "array size: ";
    std::cin >> n;
    std::vector<int> ar(n);
    
    std::cout << "vec values: ";
    for (int i=0; i<n; i++)
        std::cin >> ar[i];
    
    // sortLastElement(ar);
    insertionSort(ar);
    printArray(ar);

    return 0;
}