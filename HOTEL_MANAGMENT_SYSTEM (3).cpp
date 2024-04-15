#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cstring>
using namespace std;

struct Bill {
    double roomCharges;
    double serviceCharges;
    double tax;
    double totalAmount;
};

struct Customer {
    int roomnumber;
    string name;
    string address;
    string phonenumber;
    string nationality;
    string email;
    int period;
    string arrivaldate;
    Bill bill;
};

bool login();
void bookRoom(Customer &s);
void displayRooms(Customer &s);
void changePassword();
void viewRecords(Customer &s);
void deleteRecord(Customer &s);
void searchCustomer(Customer &s);
void editRecord(Customer &s);
double calculateRoomCharges(const Customer &customer);
double calculateServiceCharges(const Customer &customer);
double calculateTax(const Customer &customer);
void calculateBill(Customer &customer);
void displayBill(const Customer &customer);

const int MAX_ROOMS = 10; 
const double roomRate = 100.0;
const double serviceCharges = 50.0; 
const double taxRate = 0.10;

int main() {
    time_t timee;
    time(&timee);
    char choice;
    Customer s;

    if (!login()) {
        return 0;
    }

    while (true) {
        cin.get();
        system("cls");
        system("color 0D");
        cout << "\n" << setw(90) << "MANU PAGE" << endl;
        cout << setw(92) << " ..........\n\n";
        cout << setw(110) << "[ Please choose an option from the menu ]:\n\n";
        cout << setw(96) << " 1. Reserve a Room\n";
        cout << setw(98) << "---------------------\n";
        cout << setw(103) << " 2. View Customer Records\n";
        cout << setw(105) << "----------------------------\n";
        cout << setw(104) << " 3. Remove Customer Record\n";
        cout << setw(106) << "-----------------------------\n";
        cout << setw(103) << " 4. Search for a Customer\n";
        cout << setw(103) << "--------------------------\n";
        cout << setw(102) << " 5. Edit Customer Record\n";
        cout << setw(103) << "--------------------------\n";
        cout << setw(97) << " 6. Change Password\n";
        cout << setw(103) << "--------------------------\n";
        cout << setw(86) << " 7. Exit\n";
        cout << setw(94) << "---------------\n\n\n";
        cout <<"\n\n"<<setw(102) << ctime(&timee);
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case '1':
            bookRoom(s);
            break;
        case '2':
            viewRecords(s);
            break;
        case '3':
            deleteRecord(s);
            break;
        case '4':
            searchCustomer(s);
            break;
        case '5':
            editRecord(s);
            break;
        case '6':
            changePassword();
            break;
        case '7':
            system("cls");
            cout <<"\n\n"<<setw(102)<< "*****APPRECIATE YOUR CHOICE!*****";
            cout <<"\n\n"<<setw(102)<< "THANK YOU FOR CHOOSING OUR SERVICES";
            exit(0);
            system("cls");
            
        default:
            system("cls");
            cout << "Invalid Selection";
            cout << "\n Press any key to continue";
            cin.get();
        }
    }

    return 0;
}




bool login() {
    system("cls");
    string username, password, fileUsername, filePassword;
    const string filename = "login.txt";
    int attempts = 0;

    ifstream infile(filename);
    if (!infile.is_open()) {
    system("cls");
    system("color 0A");
    cout << "\n" << setw(100)<< "**************************************************";
    cout << "\n" << setw(100)<< "*  WELCOME TO THE HOTEL MANAGEMENT SYSTEM        *";
    cout << "\n" << setw(101)<< "**************************************************\n";
     cout << "\n" << setw(86)<< "Create Login Account\n" ;
     cout << setw(88)<< "          ......................\n\n";
     cout << "\n" << setw(80)<< "ENTER USERNAME: ";
        getline(cin, username);
        cout << setw(80)<< "ENTER PASSWORD: ";
        getline(cin, password); 
        ofstream outfile(filename);
        
        if (outfile.is_open()) {
            outfile << username << " " << password;
            outfile.close();
            cout << "\n" << setw(76)<< "Welcome, " << username << "!\n";
            cout << "\n" << setw(95) << right<<"Press Enter Key To Go To Manu Page:";
            //cin.get();
            return true;

        } else {
            cout << "Error creating Account. Please try again later.";
            return false;
        }
    } else {
        infile >> fileUsername >> filePassword;
        infile.close();
    }

     system("cls");
     system("color 0A");
    cout << "\n" << setw(100)<< "**************************************************";
    cout << "\n" << setw(100)<< "*  WELCOME TO THE HOTEL MANAGEMENT SYSTEM        *";
    cout << "\n" << setw(102)<< " **************************************************\n\n";
    cout << "\n" << setw(82)<< "     LOGIN PAGE" << endl;
    cout << setw(82)<< "          .........."<<endl;

    while (attempts < 3) {
        cout << "\n" << setw(82)<< "ENTER USERNAME: ";
        getline(cin, username);
        cout << setw(82)<< "ENTER PASSWORD: ";
        getline(cin, password);
        
        if (username == fileUsername &&password == filePassword) {
             cout << "\n" << setw(79)<< "Welcome, " << username << "!\n";
             cout << "\n" << setw(95) << right<<"Press Enter Key To GO TO Manu Page:";
            return true;
        } else {
            attempts++;
            cout << "\n\n" << setw(100)<< "Invalid username or password. Please try again.\n";
        }
    }

    cout << "\n\n" << setw(100) << right<< "Too many failed attempts. Please try again later.";
    return false;
}

void bookRoom(Customer &s) {
    system("cls");
    char choice;
    bool roomReserved = false; 
    do {
        displayRooms(s); // Display free and reserved rooms
        cout << "\n" << setw(105) << "Enter Customer Details:";
        cout << "\n" << setw(107) << "**************************";
        cout << "\n\n" << setw(112) << "Enter Room number (1 to 10):";
        cin >> s.roomnumber;

        if (s.roomnumber < 1 || s.roomnumber > MAX_ROOMS) {
            cout << setw(100) << "Invalid room number. Please choose a room between 1 and " << MAX_ROOMS << ".\n";
           
            continue;
        }

        ifstream roomFile("room.txt");

    
        roomReserved = false;

        int fileRoomNumber;
        while (roomFile >> fileRoomNumber >> s.name >> s.address >> s.phonenumber >> s.nationality >> s.email >> s.period >> s.arrivaldate) {
            if (fileRoomNumber == s.roomnumber) {
                roomReserved = true;
                cout << setw(130) << "Sorry! The room is already reserved. Please choose an available room.\n";
                break; // Exit the loop if the room is reserved
            }
        }

        roomFile.close();

        if (!roomReserved) {
            
            cin.ignore(); 
            cout << "\n" << setw(85) << "Enter Name:";
            getline(cin, s.name); 

            cout << "\n" << setw(88) << "Enter Address:";
            getline(cin, s.address); 

            cout << "\n" << setw(93) << "Enter Phone Number:";
            getline(cin, s.phonenumber); 

            cout << "\n" << setw(92) << "Enter Nationality:";
            getline(cin, s.nationality); 

            cout << "\n" << setw(86) << "Enter Email:";
            getline(cin, s.email); 

            cout << "\n" << setw(98) << "Enter Period ('x' days):";
            cin >> s.period;

            calculateBill(s);
            displayBill(s);

            cout << "\n\n" << setw(120) << "Do you agree with the total amount? (Y/N): ";
            cin >> choice;

            if (toupper(choice) == 'Y') {
                
                ofstream b_room("room.txt", ios::app);
                if (!b_room.is_open()) {
                    cout << setw(100) << "Sorry! The file could not be opened";
                    return;
                }

                b_room << s.roomnumber << " " << s.name << " " << s.address << " " << s.phonenumber << " " << s.nationality << " " << s.email << " " << s.period << " " << s.arrivaldate << " " << s.bill.totalAmount << endl;
                b_room.close();

                cout << "\n\n" << setw(110) << "Room is successfully booked!!";
            } else {
                cout << "\n\n" << setw(105) << "Booking canceled. Please choose another room.";
            }
        }

        
        cout << "\n\n" << setw(117) << "Do you want to book another room? (Y/N): ";
        cin >> choice;
        system("cls");

    } while (toupper(choice) == 'Y');
}


void displayRooms(Customer &s) {
    ifstream roomFile("room.txt");
    if (!roomFile.is_open()) {

        return;
    }

    cout <<setw(100)<< "Room Status:\n\n";
    cout <<setw(100)<< "Room Number\tStatus\n";
    cout <<setw(107)<< "----------------------------\n";

    bool reservedRooms[MAX_ROOMS + 1] = {false};  // Initialize all rooms as available

    // Use a separate object for reading room information
    string line;
    while (getline(roomFile, line)) {
        istringstream iss(line);

        if (iss >> s.roomnumber >> s.name >> s.address >> s.phonenumber >> s.nationality >> s.email >> s.period >> s.arrivaldate) {
            if (s.roomnumber >= 1 && s.roomnumber <= MAX_ROOMS) {
                reservedRooms[s.roomnumber] = true;
            }
        }
    }

    roomFile.close();

    for (int i = 1; i <= MAX_ROOMS; ++i) {
        cout <<setw(83)<< i << "\t\t";
        if (reservedRooms[i]) {
            cout << "Reserved\n";
        } else {
            cout << "Available\n";
        }
    }
}


void calculateBill(Customer &customer) {
    customer.bill.roomCharges = calculateRoomCharges(customer);
    customer.bill.serviceCharges = calculateServiceCharges(customer);
    customer.bill.tax = calculateTax(customer);
    customer.bill.totalAmount = customer.bill.roomCharges + customer.bill.serviceCharges + customer.bill.tax;
}

double calculateRoomCharges(const Customer &customer) {
    double roomCharges = roomRate * customer.period;
    return roomCharges;
}
// Function to display bill
void displayBill(const Customer &customer) {

     cout << "\n" << setw(103) << "Billing Details";
     cout << "\n" << setw(104) << "-----------------";
     cout << "\n" << setw(100) << "Room Charges: "<<"------$" << customer.bill.roomCharges;
     cout << "\n" << setw(103) << "Service Charges: "<<"----$" << customer.bill.serviceCharges;
     cout << "\n" << setw(91) << "Tax: " <<"-------------$" << customer.bill.tax;
     cout << "\n" << setw(100) << "Total Amount: " <<"------$" << customer.bill.totalAmount;

}


double calculateServiceCharges(const Customer &customer) {

    
    return serviceCharges;
}

// Function to calculate tax based on the total bill amount
double calculateTax(const Customer &customer) {

    
    double totalAmount = customer.bill.roomCharges + customer.bill.serviceCharges;
    
    double tax = totalAmount * taxRate;

    return tax;
}


void viewRecords(Customer &s) {
    ifstream f("room.txt");

    if (!f.is_open()) {
        cout << "Error opening file. Exiting.\n";
        exit(0);
    }

    system("cls");
    cout << setw(136) << setfill('-') << "\n" << setfill(' ');
    cout << setw(4) << "ROOM" << setw(12) << "NAME" << setw(15) << "ADDRESS" << setw(20) << "PHONENUMBER"
     << setw(20) << "NATIONALITY" << setw(25) << "EMAIL" << setw(20) << "PERIOD" << setw(20) << "TOTAL FEE\n";
    cout << setw(136) << setfill('-') << "\n" << setfill(' ');

    string line;
    while (getline(f, line)) {
        istringstream iss(line);
        if (iss >> s.roomnumber >> s.name >> s.address >> s.phonenumber >> s.nationality >> s.email >> s.period >> s.arrivaldate) {
            cout <<"\n"<< setw(2) << s.roomnumber << setw(14) << s.name << setw(16) << s.address << setw(19)<< s.phonenumber
                 << setw(18) << s.nationality << setw(30) << s.email << setw(15) << s.period <<setw(20)<< s.arrivaldate<<"\n";
        }
    }

    cout <<"\n"<<setw(136) << setfill('-') << "\n" << setfill(' ');
    f.close();

    // Add a system pause to keep the console window open
    cout << "\nPress Enter to continue...";
    cin.get();
}


void deleteRecord(Customer &s) {
    ifstream file("room.txt");
    ofstream temp("temp.txt");
    int i = 1;
    int roomnumber;

    if (!temp.is_open()) {
        cout << "Error opening temporary file.\n";
        exit(0);
    }

    if (!file.is_open()) {
        cout << "Error opening room file.\n";
        exit(0);
    }

    system("cls");
   
      cout <<"\n"<<setw(120)<< "Enter the Room Number of the hotel to be deleted from the database: ";
     
    cin >> roomnumber;

    while (file >> s.roomnumber >> s.name >> s.address >> s.phonenumber >> s.nationality >> s.email >> s.period >> s.arrivaldate) {
        if (s.roomnumber == roomnumber) {
            i = 0;
            continue;
        } else {
            temp << s.roomnumber << " " << s.name << " " << s.address << " " << s.phonenumber << " " << s.nationality << " " << s.email << " " << s.period << " " << s.arrivaldate << endl;
        }
    }

    if (i == 1) {
        cout <<"\n"<<setw(112)<< "Records of Customer in this Room number is not found!!";
      
    } else {
        cout <<"\n"<<setw(110)<< "The Customer is successfully removed....";
    }

    file.close();
    temp.close();
    remove("room.txt");
    rename("temp.txt", "room.txt");
    cin.get();
}


void searchCustomer(Customer &s) {
    system("cls");
    ifstream file("room.txt");
    int roomnumber; 
    int flag = 1;

    if (!file.is_open())
        exit(0);

    cout <<"\n"<<setw(120)<< "Enter Room number of the customer to search its details: ";
    cin >> roomnumber; 

    if (file.fail()) {
        cout <<"\n"<<setw(118)<<"Invalid input. Please enter a valid room number.\n";
        cin.get();
        file.close();
        return;
    }

    while (file >> s.roomnumber >> s.name >> s.address >> s.phonenumber >> s.nationality >> s.email >> s.period >> s.arrivaldate) {
        if (s.roomnumber == roomnumber) {
             flag = 0;
             cout <<"\n"<<setw(100)<< "Record Found";
             cout <<"\n"<<setw(103)<< "--------------\n ";
             cout << "\n" << setw(80) << "Room Number:" << setw(31) << setfill('-') << s.roomnumber << setfill(' ');
             cout <<"\n"<<setw(73)<< "Name:"<<setw(40)<< setfill('-') <<s.name<< setfill(' ');
             cout <<"\n"<<setw(76)<< "Address:" <<setw(40)<< setfill('-') <<s.address<< setfill(' ');
             cout <<"\n"<<setw(81)<< "Phone number:" <<setw(35)<< setfill('-') <<s.phonenumber<< setfill(' ');
             cout <<"\n"<<setw(80)<< "Nationality:" <<setw(34)<< setfill('-') <<s.nationality<< setfill(' ');
             cout <<"\n"<<setw(74)<< "Email:" <<setw(45)<< setfill('-') <<s.email<< setfill(' ');
             cout <<"\n"<<setw(75)<< "Period:" <<setw(36)<< setfill('-') <<s.period<< setfill(' ');
            break;
        }
    }

    if (flag == 1) {
       cout <<"\n"<<setw(110)<< "Requested Customer could not be found!";
    }

    cin.get();
    file.close();
}


void editRecord(Customer &s) {
    ifstream file("room.txt");
    ofstream temp("temp.txt");
    int roomnumber;

    if (!file.is_open()) {
         cout << "\n" << setw(95)<< "Error opening room file.\n";
        
        exit(0);
    }

    if (!temp.is_open()) {
       cout << "\n" << setw(98)<< "Error opening temporary file.\n";
       
        exit(0);
    }

    system("cls");

    char choice = 'y';

    while (tolower(choice) == 'y') {
        int k = 1;
        bool recordFound = false; // Flag to track whether the record is found or not

        cout <<"\n"<<setw(105)<< "Enter Room number of the customer to edit:";
                
        cin >> roomnumber;

        while (file >> s.roomnumber >> s.name >> s.address >> s.phonenumber >> s.nationality >> s.email >> s.period) {
            if (s.roomnumber == roomnumber) {
                k = 0;
                recordFound = true; // Set flag to indicate that the record is found

                cout << "\n" << setw(85) << "Enter Name:";
               
                cin.ignore(); 
                getline(cin, s.name);

                cout << "\n" << setw(88) << "Enter Address:";
                getline(cin, s.address);

                cout << "\n" << setw(93) << "Enter Phone Number:";
                getline(cin, s.phonenumber);

                cout << "\n" << setw(92) << "Enter Nationality:";
                getline(cin, s.nationality);

                cout << "\n" << setw(86) << "Enter Email:";
                getline(cin, s.email);

                cout << "\n" << setw(98) << "Enter Period ('x' days):";
                cin >> s.period;
            }

            // Write the record to the temporary file
            temp << s.roomnumber << " " << s.name << " " << s.address << " " << s.phonenumber << " " << s.nationality << " " << s.email << " " << s.period << " " << s.arrivaldate << endl;
        }

        if (k == 1) {
           cout << "\n\n" << setw(95)<< "THE RECORD DOESN'T EXIST!!!!";
                
        } else if (recordFound) {
            cout << "\n\n" << setw(102)<< "THE RECORD IS SUCCESSFULLY EDITED!!!";
                
        }

        cout <<"\n"<<setw(106)<< "Do you want to edit another record? (y/n): ";
                
        cin >> choice;
    }

    // Close and rename the files at the end
    file.close();
    temp.close();
    remove("room.txt");
    rename("temp.txt", "room.txt");

    {
       
}
}


void changePassword() {
  
   string currentUsername, currentPassword, newUsername, newPassword,fileUsername,filePassword;

  
   system("cls");
   cout <<setw(90)<<"Enter your current username: ";
   cin >> currentUsername;
   cout <<setw(90)<< "Enter your current password: ";
   cin >> currentPassword;
  
   ifstream infile("login.txt");
   if (infile.is_open()) {
       infile >> fileUsername >> filePassword;
       infile.close();
   } else {
       cout <<"\n\n"<<setw(100)<< "Error opening file. Please try again later.\n\n";
   }

   // Check the entered username and password match  in the file
   if (currentUsername == fileUsername && currentPassword == filePassword) {
      
       cout <<"\n"<<setw(88)<< "Enter your new username: ";
       cin >> newUsername;
       cout <<setw(88)<< "Enter your new password: ";
       cin >> newPassword;
       
       
       ofstream outfile("login.txt");
       if (outfile.is_open()) {
          
           outfile << newUsername << " " << newPassword;
           outfile.close();

          
            cout <<"\n\n"<<setw(105)<< "***** Username and password successfully changed *****\n";
       } else {
            cout <<setw(100)<< "Error opening file. Please try again later.\n";
       }
   } else {
      
       cout <<"\n"<<setw(96)<<"***** Invalid username or password *****\n";
   }

   cin.ignore();

   cout <<setw(99)<< "Press Enter to return to the main menu:\n";
}

















