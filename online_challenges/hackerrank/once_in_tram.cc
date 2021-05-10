#include <bits/stdc++.h>

using namespace std;

/*
* calculates 10 to the given power
* in a recursive way
*/
int power10(int p){
    if (p==0){
        return 1;
    }

    return 10*pow10(p-1);
}

/*
* This should work, with a bit of tweaking, for all bases.
* for other bases the operators '+,-' should be tested. 
* here we only use it for base 10 numbers
*/
int sumDigits(int x){
    
    // i=1;
    // // 123 >> 3
    // int p = 10; 
    // int digit = x%p
    // // 123 >> 120 >> 12
    // x = (x - digit)/p
    // i=2;
    // // 12 >> 2
    // digit = x%p;
    // x = (x - digit)/p

    int sum =0;
    int digit =0;
    int base = 10;

    while (x >= base){
        // get the most right digit, lowest power of 
        digit = x%base;

        sum += digit;

        x = (x - digit)/base;

    }
    sum += x;

    return sum;

}

string onceInATram(int x) {
    // Complete this function
    int r3 = x%1000;
    int l3 = (x - r3)/1000;
    
    cout << "[1] right: " << r3 << "  left: " << l3 << endl;
    bool condition = true;
    while (condition)
    {
        r3++;

        if (r3 == 1000)
        {
            r3 = 0;
            l3++;
            cout << "[2] right: " << r3 << "  left: " << l3 << endl;
        }

        if (sumDigits(r3) == sumDigits(l3))
        {
            condition = false;
            cout << "[3] right: " << r3 << "  left: " << l3 << endl;
            break;
        }
    }
    
    string str = "";
    
    if (r3<10)
        str = std::to_string(l3) + "00" + std::to_string(r3);
    else if (r3 < 100)
        str = std::to_string(l3) + "0" + std::to_string(r3);
    else
        str = std::to_string(l3) + std::to_string(r3);

    return str;
}

int main() {
    int x;
    cin >> x;


    if (1e5 <= x && x <= (1e6-2))
    {
        // failed 100456
        string result = onceInATram(x);
        cout << result << endl;
    }

    return 0;
}
