
#include "BugsLife.h" // header file

int main() {
    map<int, func> menuOptions;

    // TODO add calls to methods for each menu option
//    menuOptions[1] = ;
//    menuOptions[2] = ;
//    menuOptions[3] = ;
//    menuOptions[4] = ;
//    menuOptions[5] = ;
//    menuOptions[6] = ;
//    menuOptions[7] = ;
//    menuOptions[8] = ;

    int choice = 0;
    string temp;
    do {
        cout << "Please enter an option from the menu (-1 to end): ";
        cin >> choice;
        getline(cin, temp);
        cout << endl;
        if(menuOptions.count(choice))
        {
            menuOptions[choice]();
        }
        else if(choice!=-1)
        {
            cout << "Invalid input, please select a corresponding number from the menu"<<endl;
        }
        cout << "\n\n\n";
    }while(choice!=-1);
    return 0;
}
