#include <iostream>
using namespace std;
int fibonacci(int n)
{
    if (n <= 1)
    {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}
void recursive(int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << fibonacci(i) << " ";
    }
    cout << endl;
}
void iterative(int n)
{
    int f0 = 0;
    int f1 = 0;
    f1 = 1;
    cout << f0 << " " << f1 << " ";
    int f2 = 0;
    for (int i = 2; i < n; i++)
    {
        f2 = f0 + f1;
        f0 = f1;
        f1 = f2;
        cout << f1 << " ";
    }
    cout << endl;
}
int main()
{
    recursive(10);
    cout << endl;
    iterative(10);
    return 0;
}