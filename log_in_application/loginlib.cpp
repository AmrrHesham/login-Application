void loadExistingUsers(vector<UsersProfile>& users){ //function that load the file data in a vector of struct.

    while (!usersFile.eof()){
        UsersProfile nextUser;
        
        //put the file data in struct.
        usersFile >> nextUser.ID;
        usersFile >> nextUser.password;
        usersFile >> nextUser.email;
        usersFile >> nextUser.phoneNumber;

        users.push_back(nextUser); //push this data in vector.
    }
}
int displayList(){ //function that display list to user to choose from it.
    int choice;
    cout << "Please Choose:\n1.to regester.\n2.to login.\n3.to change password.\n4.to Exit." << endl;
    cin >> choice;
    return choice;
}

void regestration(){ //regestration function: 
 
    //enter id.
    cout << "Please Enter your ID:\nnote that(the ID can contain characters and underscore only) " << endl;
    cin >> newUser.ID;


    while (!filterID(newUser.ID)){ //if id is not on the standard form.
        cout << "this id is not on the standard format, Please enter another one: " << endl;
        cin >> newUser.ID;
    }
    cout << "ID entered successfully!" << endl; //id is correct.
    


    

    //enter email.
    cout << "Please Enter Your Email Address: " << endl;
    cin >> newUser.email;

    while(!filter1email(newUser.email) || !filter2email(newUser.email)){ //if email is not on the format or it is already exists.
        cout << "this email is already exist or it is not on the standard format, Please enter another one: " << endl;
        cin >> newUser.email;
    }
    cout << "Your Email entered successfully!" << endl;
    

    //enter phone number.
    cout << "Please enter your phoneNumber:\nnote that(the egyption phone number should strart with +20 " << endl;
    cin >> newUser.phoneNumber;



    while(!filterPhoneNumber(newUser.phoneNumber)){ //if phone number is not on the egyptian format(+20).
        cout << "this is invalid phone number, please enter valid one: " << endl;
        cin >> newUser.phoneNumber;
    }
    cout << "the phone number entered successfully!" << endl;
    

    //enter password
    validPassword(newUser.password);
    confirmPassword();
 
}


bool filterID(string ID){ //filter that check if id is on the standard format.(contain characters and underscore only).
    regex filter("((\\w+)(_)?(\\w+)?)");

    return regex_match(ID, filter);
}

bool filterPhoneNumber(string phoneNumber){ //filter that check if phone number is on the standard format(+20).
    regex filter("(\\+201)([0-2]{1}|(5){1})[0-9]{8}");
    return regex_match(phoneNumber, filter);
}

bool filter1email(string email){ //filter that check if email is already exist or not.
    string token;
    bool filter = false;
    usersFile.open("users.txt");

    while(!usersFile.eof()){
        usersFile >> token;

        if(email == token){ //if email is exist in file, return false.
            filter = false;
        }
        else{ //if email is not in file, return true.
            filter = true;
        }
    }

    usersFile.close();
    return filter;

}

bool filter2email(string email){ //function that check if email is on the standard format or not.
    regex filter("(\\w+)(\\.|_)?(\\#)?(\\&)?(\\*)?(\\$)?(\\%)?(\\^)?(\\+)?(\\=)?(\\{)?(\\})?(\\?)?(\\w*)@(\\w+)(\\.(\\w+))+");

    return regex_match(email, filter);
}

// showing strong password conditions for the user
void passConditions(){
    cout << "Strong and valid Password MUST contain:" << endl;
    cout << "1. Atleast 8 characters" << endl;
    cout << "2. Lower Case letters(a-z)" << endl;
    cout << "3. Upper Case letters(A-Z)" << endl;
    cout << "4. Numbers(0-9)" << endl;
    cout << "5. Symbols(@,$,!, etc.)" << endl;
    cout << endl;
}

// function to see if a password is valid
void validPassword(string password){

    passConditions();

    bool lowerCase = false;
    bool upperCase = false; // naming bolleans to check in user's password
    bool special   = false;
    bool number    = false;

    int validPass;

    // regex for all conditions.
    regex lowerCaseChar{ "[a-z]+" };
    regex upperCaseChar{ "[A-Z]+" };
    regex specialChar  { "^[!@#$%^&*()-_=+{}[]<>?/;:`~.']+$"};
    regex numberChar   { "[0-9]+" };


    cout << "enter a valid password: "; 
    changeChar();// instead of (cin >>)
    cout << endl;

    if(newUser.password.length() < 8){
        cout << "Password is too short!" << endl; // if password is short repeat
        cout << endl;
        validPassword(password);
    }
    else{
        lowerCase = regex_search(newUser.password, lowerCaseChar);
        upperCase = regex_search(newUser.password, upperCaseChar); // search for each condition in users password
        special   = regex_search(newUser.password, specialChar);   // if found bool = 1 (True)
        number    = regex_search(newUser.password, numberChar);    // if not bool = 0 (false)

        validPass = lowerCase + upperCase + special + number; // add booleans

        if(validPass < 3){
            cout << "Password isn't strong enough!" << endl;
            cout << endl; // if sum  < 3 then not strong pass
            validPassword(password);
        }
        else{
            cout << "Valid Password" << endl;
        }
    }
}

// confirm user's password
void confirmPassword(){
    string confPass;
    cout << "Confirm Password: ";
    char ch;
    ch = getch();
    while(ch != 13){ // same changeChar function but for password confirm
        if(ch == 8){
            if(confPass.size() > 0){
                confPass.pop_back();
                cout << '\b' << ' ' << '\b';
                ch = _getch();
            }
            else{
                cout <<' ' << '\b';
                ch = _getch();
            }
        }
        else{
            confPass.push_back(ch);
            cout << '*';
            ch = _getch();
        }
    }
    cout << endl;

    if(newUser.password == confPass){ // if passwrd and the confirm are the same
        cout << "Register was made Successfully" << endl;
        saveInfo(newUser.ID, newUser.email, newUser.password);

    }
    else{
        cout << "password and confirm password aren't the same!" << endl;
        confirmPassword(); // repeat if not the same
    }
}

// function to change each char to *
// this function is used instead of (cin >>)
void changeChar(){
    char ch;
    ch = getch();
    while(ch != 13){ // ASCII for new line
        if (ch == 8){ // ASCII for backspace
            if(newUser.password.size() > 0){
                newUser.password.pop_back();
                cout << '\b' << ' ' << '\b'; // backspace, space, backspace
                ch = _getch();
            }
            else{ // if no input was put and backspace was entered
                cout <<' ' << '\b'; // space backspace
                ch = _getch();
            }
        }
        else{
            newUser.password.push_back(ch);
            cout << '*'; // for each character change to * 
            ch = _getch();
        }
    }
}

// saving info if register was succeeded till confirm password
void saveInfo(string ID, string email, string password){
    ofstream usersFile;
    usersFile.open("users.txt", ios_base::app);
    usersFile << '\n' << ID << ' ' << ' ';
    usersFile << email << ' ' << ' ';
    usersFile << password << '\n';
    usersFile.close();

}