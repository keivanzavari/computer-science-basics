
#include <bits/stdc++.h>
#include <cstdlib> 

void printArray(const std::vector<int> & array)
{
    std::cout << "\n------ print --------" << std::endl;
    std::cout << "array: " << std::endl;
    for (int i=0; i<array.size() ; i++)
        std::cout << array[i] << " ";
    std::cout <<  std::endl;

}


bool comp(std::string i, std::string j)
{
    if (i.size() != j.size())
        return (i.size() < j.size());

    return (i<j); 
}

int main(){
    int n;
    std::cin >> n;
    std::vector<std::string> unsorted(n);
    for(int unsorted_i = 0; unsorted_i < n; unsorted_i++){
       std::cin >> unsorted[unsorted_i];
    }

    std::sort(unsorted.begin(),unsorted.end(),comp);
    
    std::cout << std::endl;
    for(int unsorted_i = 0; unsorted_i < n; unsorted_i++){
       std::cout << unsorted[unsorted_i] << "\n";
    }
    return 0;
}
