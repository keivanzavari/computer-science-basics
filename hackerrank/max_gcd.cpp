#include <bits/stdc++.h>

using namespace std;

void printVec(vector<int> A, char name){
    cout << name << ": ";
    for (int i=0; i<A.size(); i++)
        cout << A[i] << ", ";

    cout << endl;

}

int maximumGcdAndSum(vector <int> A, vector <int> B) {

    // gcd greatest common divisor
    int n = A.size();
    int max_gcd = -100;
    int gcd = 1;
    int max_sum = 0;
    int idx_a = 0;
    int idx_b = 0;

    for (int i=0; i< n; i++)
    {
        if (A[i]< max_gcd)
            continue;
        for (int j=0; j< n; j++)
        {
            if (B[j]< max_gcd)
                continue;
            
            if ((A[i] == 1) || (B[j] == 1))
                gcd = 1;
            else
                gcd = std::__gcd(A[i], B[j]);
            
            if (max_gcd < gcd)
            {
                max_gcd = gcd;
                max_sum = A[i]+ B[j];

                // register the indices of gcd
                idx_a = i;
                idx_b = j;

            } 
            else if (max_gcd == gcd) 
            {

                // if the same gcd appears, 
                // check which ones' sum is bigger
                if ((A[i]+ B[j]) >= (A[idx_a]+ B[idx_b]))
                {
                    max_sum = A[i]+ B[j];
                    // register the indices of gcd
                    idx_a = i;
                    idx_b = j;
                }
                else
                {
                    max_sum = A[idx_a]+ B[idx_b];
                }

            } 
        } // end of for j
    
    } // end of for i

    cout << "pair: " << A[idx_a] << ", " << B[idx_b]
    << "\t  max gcd: " << max_gcd <<"\t max sum: " << max_sum << endl;

    return max_sum;
}

int main() {
    int n;
    cin >> n;

    // 1<= Ai, Bi <= 1e6;


    vector<int> A(n);
    for(int A_i = 0; A_i < n; A_i++){
       // cin >> A[A_i];
       A[A_i] = A_i*2+3;
    }
    vector<int> B(n);
    for(int B_i = 0; B_i < n; B_i++){
       // cin >> B[B_i];
       B[B_i] = B_i+7;

    }
    int res = maximumGcdAndSum(A, B);
    cout << res << endl;

    printVec(A,'A');
    printVec(B, 'B');

    return 0;
}
