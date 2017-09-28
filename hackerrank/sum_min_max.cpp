#include <bits/stdc++.h>

using namespace std;

void giveSumMinMax(const vector<int> a, long & sum_min, long & sum_max){
    int idx_min = 0;
    int idx_max = 0;
    sum_min = sum_max = 0;
    for (int i=0; i < 5; i++){
        if (a[i] < a[idx_min])
            idx_min = i;
        if (a[i] > a[idx_max])
            idx_max = i;
    }
    
    // we only need to find the index of min & max value
    // of the array. The the maximum sum is the one without
    // the min value of the array
    for (int i=0; i < 5; i++){
        if (i != idx_min)
            sum_max += a[i];
        if (i != idx_max)
            sum_min += a[i];
    }
}
int main() {
    vector<int> arr(5);
    for(int arr_i = 0; arr_i < 5; arr_i++){
       cin >> arr[arr_i];
    }
    // 1 < arr_i < 1e9
    long sum_min, sum_max;
    giveSumMinMax(arr, sum_min, sum_max);
    
    cout << sum_min << " " << sum_max << endl;
    return 0;
}
