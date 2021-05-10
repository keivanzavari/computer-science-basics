#include <bits/stdc++.h>

using namespace std;

vector <int> leftRotation(vector <int> a, int d) {
    // Complete this function
    int n = a.size();
    vector <int> rotated(n);
    int idx = 0;

    // we don't really need to rotate the vector itself
    // we only need to change the index.
    // rotated is filled up by the data from a on the following indices:
    // d, d+1, ..., n-1, 0, 1, ..., d-1
    for (int i=0; i < n; i++)
    {
        idx = (i+d)%n;
        rotated[i] = a[idx];
    }

    return rotated;    
}

int main() {
    int n = 8;
    int d = 5;
    
    // cin >> n >> d;
    vector<int> a(n);
    for(int a_i = 0; a_i < n; a_i++){
       a[a_i] = a_i;
    }
    vector <int> result = leftRotation(a, d);
    for (ssize_t i = 0; i < result.size(); i++) {
        cout << result[i] << (i != result.size() - 1 ? " " : "");
    }
    cout << endl;


    return 0;
}
