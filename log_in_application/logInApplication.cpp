#include "loginlib.h"
#include "loginlib.cpp"

int main(){
    
    cout << "Welcome in login Application!" << endl;
    loadExistingUsers(users);
    int choice = displayList();
    
    while(choice != 4){
        if (choice == 1){
            regestration();
        }
    }
}
