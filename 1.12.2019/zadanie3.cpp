#include <iostream>

using namespace std;
#include <vector>
#include <ctime>
#include <cstdlib>

int main()
{
    srand(time(NULL));
    vector <string> TabOfClasses;
    int numberOfPlayers=0;
    string tmpPlayerName;
    string tmpClassName;
    cin >> numberOfPlayers;
    string TabOfPlayers[numberOfPlayers];
    for(int i = 0; i<numberOfPlayers; i++)
    {
        cin >> tmpClassName;
        TabOfClasses.push_back(tmpClassName);
    }
    for(int i = 0; i<numberOfPlayers; i++)
    {
        cin >> tmpPlayerName;
        TabOfPlayers[i]=tmpPlayerName;
    }
    for(int i = 0; i<numberOfPlayers; i++)
    {
        unsigned int tmpNumber=0;
        tmpNumber=rand()%TabOfClasses.size();
        cout << TabOfPlayers[i] << "-" << TabOfClasses[tmpNumber]<<endl;
        TabOfClasses.erase(TabOfClasses.begin()+tmpNumber);

    }
    return 0;
}

