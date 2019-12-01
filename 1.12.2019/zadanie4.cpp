#include <iostream>

using namespace std;
#include <vector>
#include <ctime>
#include <cstdlib>

int main()
{

    string board[10][10];
    int numberOfPoints = 0;

    cin >> numberOfPoints;
    for(int i =0; i<10; i++)
    {
        for(int j =0; j<10; j++)
        {
            board[i][j]=" ";
        }
    }
    int firstNumber=0;
    int secondNumber=0;
    for(int i =0; i<numberOfPoints; i++)
    {
        cin >> firstNumber;
        cin >> secondNumber;
        board[firstNumber][secondNumber]="*";
    }
    for(int i =9; i>=0; i--)
    {
        for(int j =0; j<10; j++)
        {
            cout <<board[i][j];
        }
        cout << endl;
    }
    return 0;
}

