#include <iostream>

using namespace std;

int main()
{
//Mateusz Hinca

//Mariusz Krzyżopolski
    int x =0;
    int i =0;
    do
    {
        cin >> i;
        x=i+x;
    }
    while(i!=0);
    cout <<  "Liczba to: "<<endl;
    cout <<x;
    return 0;
}

