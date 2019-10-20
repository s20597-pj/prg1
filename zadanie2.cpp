#include <iostream>

using namespace std;

int main()
{
//Mateusz Hinca
//Mariusz Krzyżopolski
    int x=0;
    cin >> x;
    for (int i =0; i<x+1; i++)
    {
        cout <<' ';
    }
    cout << '*'<<endl;
    for(int i =0; i<x-1; i++)
    {
        for(int j=0 ; j<x-i; j++)
        {
            cout << " ";
        }
        cout << "*";
        for(int g=0 ; g<(i+0.5)*2; g++)
        {
            cout << " ";
        }
        cout << '*'
             <<endl;
    }

    for(int i =x-1; i>=0; i--)
    {
        for(int j=0 ; j<x-i; j++)
        {
            cout << " ";
        }
        cout << "*";
        for(int g=0 ; g<(i+0.5)*2; g++)
        {
            cout << " ";
        }
        cout << '*'
             <<endl;
    }
        for (int i =0; i<x+1; i++)
    {
        cout <<' ';
    }
    cout << '*'<<endl;
    return 0;
}

