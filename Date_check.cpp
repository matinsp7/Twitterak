#include <iostream>
#include <conio.h>
#include "Date.h"
using namespace std;

int main(){
    int d , m , y;
    bool flag=0;
    while (!flag){
        cout << "Day : ";
        cin >> d;
        cout << "Month : ";
        cin >> m;
        cout << "Year : ";
        cin >> y;
        Date a(d , m , y , flag);
    }
    system ("cls");
    cout << "Excelent";
    getch ();
    return 0;
}