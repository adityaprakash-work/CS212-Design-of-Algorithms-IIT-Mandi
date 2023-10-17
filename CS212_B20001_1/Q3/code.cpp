// CS212 Assignment 1: Question 3, Aditya Prakash B20001
#include <iostream>

using namespace std;

//  Dr. Danny Denzongpa's GCD algorithm
int ddd_gcd(int a, int b)
{
    if (a == b)
    {
        return a;
    }

    if (a % 11 == 0 && b % 11 == 0)
    {
        return 11 * ddd_gcd(a / 11, b / 11);
    }
    else if (a % 11 == 0 && a % 2 != 0 && b % 11 != 0)
    {
        return ddd_gcd(a / 11, 2 * b);
    }
    else if (a % 11 == 0 && a % 2 == 0 && b % 11 != 0)
    {
        return ddd_gcd(a / 11, abs(a - b));
    }
    else if (b % 11 == 0 && b % 2 != 0 && a % 11 != 0)
    {
        return ddd_gcd(2 * a, b / 11);
    }
    else if (b % 11 == 0 && b % 2 == 0 && a % 11 != 0)
    {
        return ddd_gcd(abs(a - b), b / 11);
    }
    else
    {
        return ddd_gcd(abs(a - b), min(a, b));
    }
}

// Eucledian GCD algorithm
int euc_gcd(int a, int b)
{
    if (a == 0)
    {
        return b;
    }
    return euc_gcd(b % a, a);
}

// Driver code
int main()
{
    int a, b;
    cout << "Enter two integers a and b: ";
    cin >> a >> b;

    int ddd_result = ddd_gcd(a, b);
    int euc_result = euc_gcd(a, b);
    cout << "GCD of " << a << " and " << b << " using Dr. Danny Denzongpa's algorithm is " << ddd_result << endl;
    cout << "GCD of " << a << " and " << b << " using Eucledian algorithm is " << euc_result << endl;

    return 0;
}
