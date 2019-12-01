#include <iostream>

using namespace std;
#include <vector>

int main()
{
    vector <int> someTab;
    float someNumber=0;
    float someMean=0;
    do
    {
        cin>>someNumber;
        someTab.push_back(someNumber);
    }
    while(someNumber!=0);

    for(int i = 0; i<someTab.size()-1; i++)
    {
        someMean=someTab[i]+someMean;
        cout<<someMean<<" "<<someTab[i]<<endl;
    }

    float sizeTab = someTab.size()-1;

    cout << someMean/sizeTab;

    return 0;
}

