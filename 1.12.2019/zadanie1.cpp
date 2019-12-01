#include <iostream>

using namespace std;
#include <vector>

int main()
{
    vector <int> someTab;

    int someNumber=0;
    int someIf=5;
    for(int i = 0; someIf!=0; i++)
    {
        cin>>someNumber;
        someIf=someNumber;
       someTab.push_back(someNumber);
    }

    for(int i = 0; i<someTab.size()-1; i++)
    {
        cout << someTab[i]<<" ";
    }


    return 0;
}

