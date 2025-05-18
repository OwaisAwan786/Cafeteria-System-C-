#include <iostream>
#include <fstream>
#include <ctime>
#include <limits>
#include <string>
#include <sstream>
#include <vector>
#include <windows.h>
#include <thread>
//#include <chrono>     // library in C++ is used for dealing with date and time functionalities.

using namespace std;


bool isNumeric(string str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

int getNumericInput() {
    string input;
    while (true) {
        cin >> input;
        if (isNumeric(input)) {
            return stoi(input);  // stoi is used to convert "string to an integer"
        } else {
            cout << "Invalid input. Please enter a numeric value: ";
            cin.clear();  // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
        }
    }
}
//--------------------------------------------------//

bool isAlphabetic(string str) {
    for (char c : str) {
        if (!isalpha(c)) {
            return false;
        }
    }
    return true;
}

string getAlphabeticInput() {
    string input;
    while (true) {
        cin >> input;
        if (isAlphabetic(input)) {
            return input;
        } else {
            cout << "Invalid input. Please enter alphabetic values only: ";
            cin.clear();  // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
        }
    }
}
bool isValidEmail(const string& email) {
    auto atPos = email.find('@');
    auto dotPos = email.find('.', atPos);
    return (atPos != string::npos && dotPos != string::npos && dotPos > atPos);
}
//--------------------------------------------------//

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void printArray(int arr[], int size, int i, int j, bool swapped) {
    for (int k = 0; k < size; k++) {
        if (k == i || k == j) {
            setColor(swapped ? 12 : 14); // Red for swaps, Yellow for comparisons
            cout << "[" << arr[k] << "]";
            setColor(7); // Default color
        } else {
            cout << " " << arr[k] << " ";
        }
    }
    if (swapped) {
        cout << " => Swapped ";
        setColor(12); // Red color for swaps
        cout << arr[i] << " and " << arr[j];
        setColor(7); // Default color
    }
    cout << endl;
}

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            printArray(arr, n, j, j+1, false); // Print before comparison
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
                printArray(arr, n, j, j+1, true); // Print after swap
            }
        }
    }
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        int minIdx = i;
        for (int j = i+1; j < n; j++) {
            printArray(arr, n, minIdx, j, false); // Print before comparison
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            swap(arr[i], arr[minIdx]);
            printArray(arr, n, i, minIdx, true); // Print after swap
        }
    }
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            printArray(arr, n, j, j+1, false); // Print before comparison
            arr[j + 1] = arr[j];
            printArray(arr, n, j, j+1, true); // Print after move
            j = j - 1;
        }
        arr[j + 1] = key;
        printArray(arr, n, j + 1, i, false); // Print after inserting the key
    }
}


void displayArray(int arr[], int n) {
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void sortingMenu() {
    int choice;
    int n;
    cout << "Choose a sorting option:" << endl;
    cout << "1. Selection Sort" << endl;
    cout << "2. Bubble Sort" << endl;
    cout << "3. Insertion Sort" << endl;
    cout << "Enter your choice: ";
    choice = getNumericInput();
    cout << "Enter the number of elements: ";
    n = getNumericInput();

    int* arr = new int[n];

    cout << "Enter the elements:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "Element " << i + 1 << ": ";
        arr[i] = getNumericInput();
    }

    switch (choice) {
        case 1:
            cout << "Initial array: ";
            displayArray(arr, n);
            selectionSort(arr, n);
            break;
        case 2:
            cout << "Initial array: ";
            displayArray(arr, n);
            bubbleSort(arr, n);
            break;
        case 3:
            cout << "Initial array: ";
            displayArray(arr, n);
            insertionSort(arr, n);
            break;
        default:
            cout << "Invalid choice!" << endl;
            delete[] arr;
            return;
    }

    cout << "Sorted array:" << endl;
    displayArray(arr, n);
    delete[] arr;
}

//--------------------------------------------------//

class FoodItem {
public:
    string name;
    int quantity;
    int price;
    FoodItem* next;

    FoodItem(const string& n, int q, int p) : name(n), quantity(q), price(p), next(nullptr) {}
};

//--------------------------------------------------//

class Menu {
//private:
   // FoodItem* head;

public:
FoodItem* head;
    Menu()  {
	head=nullptr;
	}

    ~Menu() {
        while (head) {
            FoodItem* temp = head;
            head = head->next;
            delete temp;
        }
    }


    bool login() {
        string username, password;
        string correctUsername = "admin";
        string correctPassword = "admin123";

        do {
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            if (username == correctUsername && password == correctPassword) {
                cout << "Login successful!" << endl;
                return true;
            } else {
                cout << "Invalid username or password! Please try again." << endl;
            }
        } while (true);
    }

//--------------------------------------------------//


void showIncomeForDay(const string& date) {
    ifstream transactionFile("C:transactions.txt");
    if (!transactionFile.is_open()) {
        cout << "Unable to open transactions file." << endl;
        return;
    }

    string line, transactionDate;
    double income, totalIncome = 0.0;

    while (getline(transactionFile, line)) {
        istringstream iss(line);
        if (!(iss >> transactionDate >> income)) {
            // Error in line format
            cout << "Error processing line: " << line << endl;
            continue;
        }
        if (transactionDate == date) {
            totalIncome += income;
        }
    }

    transactionFile.close();
    cout << "Total income for " << date << ": Rs." << totalIncome << endl;
}

//=========================================================//

  void displayAndReadMenuData(const string& menuFileName) {
    ifstream file(menuFileName);
    if (!file.is_open()) {
        cout << "File does not exist: " << menuFileName << endl;
        return;
    }

    string itemName;
    int itemQuantity, itemPrice;
    int count = 1;

    cout << "\n--- Menu ---" << endl;
    while (file >> itemName >> itemQuantity >> itemPrice) {
        cout << "Item " << count << ":\n";
        cout << "Name: " << itemName << endl;
        cout << "Quantity: " << itemQuantity << endl;
        cout << "Price: " << itemPrice << endl;
        cout << "-----------------------" << endl;

        // Add item to the menu
        addItemToMenu(itemName, itemQuantity, itemPrice);
        count++;
    }

    file.close();
    if (count == 1) {
        cout << "No items found in the menu." << endl;
    }
}

//--------------------------------------------------//

    void addItemToMenu(const string& name, int quantity, int price) {
        FoodItem* newItem = new FoodItem(name, quantity, price);
        if (!head) {
            head = newItem;
        } else {
            FoodItem* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newItem;
        }
    }

    void addItemToMenuAndWriteToFile(const string& name, int quantity, int price, const string& menuFileName) {
        addItemToMenu(name, quantity, price);
        ofstream file(menuFileName, ios::app);
        if (!file.is_open()) {
            cout << "Error opening menu file: " << menuFileName << endl;
            return;
        }

        file << name << " " << quantity << " " << price << endl;
        file.close();
        cout << "Menu data written to file successfully." << endl;
    }

//--------------------------------------------------//

void deleteItemFromMenu(const string& name) {
    if (!head) {
        cout << "Menu is empty." << endl;
        return;
    }

    // Deleting from the linked list
    FoodItem* temp = head;                 // doubly linked list
    FoodItem* prev = nullptr;

    while (temp != nullptr && temp->name != name) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Item not found: " << name << endl;
        return;
    }

    if (prev == nullptr) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }

    delete temp;
    cout << "Item deleted from the menu successfully." << endl;

    // Update the file
    ifstream infile("menu.txt");  // read data
    ofstream outfile("temp.txt"); // write data
    string itemName;
    int itemQuantity, itemPrice;

    while (infile >> itemName >> itemQuantity >> itemPrice) {
        if (itemName != name) {
            outfile << itemName << " " << itemQuantity << " " << itemPrice << endl;
        }
    }

    infile.close();
    outfile.close();

    remove("menu.txt");
    rename("temp.txt", "menu.txt");
}

//--------------------------------------------------//

    FoodItem* findItem(const string& name) const {
        FoodItem* temp = head;
        while (temp) {
            if (temp->name == name) {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }

//--------------------------------------------------//

    void quantityAvailable(const string& itemName) const {
        FoodItem* item = findItem(itemName);
        if (item) {
            cout << "Quantity Available for " << itemName << ": " << item->quantity << endl;
        } else {
            cout << "Item not found: " << itemName << endl;
        }
    }

//--------------------------------------------------//

    void purchaseItem(const string& name, int quantity) {
        FoodItem* item = findItem(name);
        if (item) {
            if (item->quantity >= quantity) {
                int totalPrice = item->price * quantity;
                cout << "\n-------------Purchase Summary:--------------" << endl;
                cout << "\nItem: " << item->name << endl;
                cout << "Quantity: " << quantity << endl;
                cout << "Total Price: " << totalPrice << endl;

                item->quantity -= quantity;
            } else {
                cout << "Insufficient quantity available for: " << item->name << endl;
            }
        } else {
            cout << "Item not found: " << name << endl;
        }
    }

//--------------------------------------------------//

  class Stack {
    private:
        struct Node {
            string data;
            Node* next;

            Node(const string& d)  {
			data=d;
			next=nullptr;
			}
        };

        Node* top;

    public:
        Stack() {
		top=nullptr;
		}

        ~Stack() {
            while (top) {
                pop();
            }
        }

        void push(const string& item) {
            Node* newNode = new Node(item);
            newNode->next = top;
            top = newNode;
        }

        void pop() {
            if (top) {
                Node* temp = top;
                top = top->next;
                delete temp;
            }
        }

        string getTop() const {
            return top ? top->data : "";
        }

        bool isEmpty() const {
            return top == nullptr;
        }


        void display() const {
            if (isEmpty()) {
                cout << "Stack is empty." << endl;
            } else {
                cout << "Menu Stack (Last to First):" << endl;
                Node* temp = top;
                while (temp) {
                    cout << temp->data << endl;
                    temp = temp->next;
                }
            }
        }
    };

    void manageMenuStack() {
        Stack menuStack;

        FoodItem* temp = head;
        while (temp) {
            menuStack.push(temp->name);
            temp = temp->next;
        }

        menuStack.display();
    }


//--------------------------------------------------//


    class Queue {
private:
    struct Node {
        string data;
        Node* next;

        Node(const string& d) {
		data=d;
		next=nullptr;
		}
    };

    Node* front;
    Node* rear;

public:
    Queue()  {
	front=nullptr;
	rear=nullptr;
	}

    ~Queue() {
        while (front) {
            dequeue();
        }
    }

    void enqueue(const string& item) {
        Node* newNode = new Node(item);
        if (!rear) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    void dequeue() {
        if (front) {
            Node* temp = front;
            front = front->next;
            if (!front) {
                rear = nullptr;
            }
            delete temp;
        }
    }

    string getFront() const {
        return front ? front->data : "";
    }

    bool isEmpty() const {
        return front == nullptr;
    }


    void display() const {
        if (isEmpty()) {
            cout << "Queue is empty." << endl;
        } else {
            cout << "Menu Queue (First to Last):" << endl;
            Node* temp = front;
            while (temp) {
                cout << temp->data << endl;
                temp = temp->next;
            }
        }
    }
};


void manageMenuQueue() {
    Queue menuQueue;

    FoodItem* temp = head;
    while (temp) {
        menuQueue.enqueue(temp->name);
        temp = temp->next;
    }

    menuQueue.display();
}
};
//--------------------------------------------------//

// CustomerNode class
class CustomerNode {
public:
    string name;
    string contact;
    string email;
    CustomerNode* next;

    CustomerNode(const string& n, const string& c, const string& e) {
        name = n;
        contact = c;
        email = e;
        next = nullptr;
    }
};

//--------------------------------------------------//

// CustomerList class
class CustomerList {
private:
    CustomerNode* head;

public:
    CustomerList()  {
	head=nullptr;
	}

    ~CustomerList() {
        while (head) {
            CustomerNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

//--------------------------------------------------//

    void addCustomer(const string& name, const string& contact, const string& email) {
        CustomerNode* newNode = new CustomerNode(name, contact, email);
        if (!head) {
            head = newNode;
        } else {
            CustomerNode* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void addCustomerAndWriteToFile(const string& name, const string& contact, const string& email, const string& customerFileName) {
        addCustomer(name, contact, email);

        ofstream file(customerFileName, ios::app);
        if (!file.is_open()) {
            cout << "Error opening customer file: " << customerFileName << endl;
            return;
        }

        file << name << " " << contact << " " << email << " " << endl;
        file.close();
        cout << "Customer data written to file successfully." << endl;
    }

//--------------------------------------------------//

    void displayAndReadCustomerData(const string& customerFileName) {
        ifstream file(customerFileName);
        if (!file.is_open()) {
            cout << "File does not exist: " << customerFileName << endl;
            return;
        }

        string name, contact, email;
        while (file >> name >> contact >> email) {
            cout << "\nCustomer Details:\n";
            cout << "Name: " << name << endl;
            cout << "Contact: " << contact << endl;
            cout << "Email: " << email << endl;
            cout << "-----------------------" << endl;

            addCustomer(name, contact, email);
        }

        file.close();
    }

//--------------------------------------------------//

   void deleteCustomerFromFile(const string& name, const string& customerFileName) {
        ifstream infile(customerFileName);
        if (!infile.is_open()) {
            cout << "Error opening customer file: " << customerFileName << endl;
            return;
        }

        ofstream outfile("temp.txt");
        if (!outfile.is_open()) {
            cout << "Error creating temporary file." << endl;
            infile.close();
            return;
        }

        string customerName, contact, email, address;
        bool found = false;

        while (infile >> customerName >> contact >> email >> address) {
            if (customerName != name) {
                outfile << customerName << " " << contact << " " << email << " " << address << endl;
            } else {
                found = true;
            }
        }

        infile.close();
        outfile.close();

        if (found) {
            remove(customerFileName.c_str());
            rename("temp.txt", customerFileName.c_str());
            cout << "Customer deleted successfully." << endl;
        } else {
            remove("temp.txt");
            cout << "Customer not found: " << name << endl;
        }
    }

};
//--------------------------------------------------//

// OrderNode class
class OrderNode {
public:
    string name;
    string email;
    string item;
    int quantity;
    time_t orderTime;
    OrderNode* next;

    OrderNode(const string& n, const string& e, const string& i, int q, time_t t) {
        name = n;
        email = e;
        item = i;
        quantity = q;
        orderTime = t;
        next = nullptr;
    }
};

//--------------------------------------------------//

// OrderQueue class
class OrderQueue {
private:
    OrderNode* front;
    OrderNode* rear;

public:
    OrderQueue(){

	front=nullptr;
	rear=nullptr;
	}

    ~OrderQueue() {
        while (front) {
            OrderNode* temp = front;
            front = front->next;
            delete temp;
        }
    }

//--------------------------------------------------//

    void placeOrder(const string& name, const string& email, const string& item, int quantity, time_t orderTime) {
        OrderNode* newNode = new OrderNode(name, email, item, quantity, orderTime);
        if (!rear) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    void placeOrderAndWriteToFile(const string& orderFileName, const string& name, const string& email, const string& item, int quantity, time_t orderTime) {
    placeOrder(name, email, item, quantity, orderTime);

    ofstream file(orderFileName, ios::app);
    if (!file.is_open()) {
        cout << "Error opening order file: " << orderFileName << endl;
        return;
    }

    file << name << " " << email << " " << item << " " << quantity << " " << orderTime << endl;
    file.close();
    cout << "Order placed and data written to file successfully." << endl;
}

//--------------------------------------------------//

void displayAndReadOrderData(const string& orderFileName) {
    ifstream file(orderFileName);
    if (!file.is_open()) {
        cout << "File does not exist: " << orderFileName << endl;
        return;
    }

    string name, email, item;
    int quantity;
    time_t orderTime;
    int count = 1;

    while (file >> name >> email >> item >> quantity >> orderTime) {

        cout << "\nOrder " << count << " Details:\n";
        cout << "Customer Name: " << name << endl;
        cout << "Email: " << email << endl;
        cout << "Item: " << item << endl;
        cout << "Quantity: " << quantity << endl;
        cout << "Order Time: " << ctime(&orderTime);

        placeOrder(name, email, item, quantity, orderTime);
        count++;
    }

    file.close();
}


};

//--------------------------------------------------//

bool loginUser(const string &username, const string &password, const string &filename) {
    ifstream userFile(filename);
    if (!userFile.is_open()) {
        cout << "Unable to open file for reading." << endl;
        return false;
    }

    string fileUsername, filePassword, fileContact, fileEmail;
    while (userFile >> fileUsername >> filePassword >> fileContact >> fileEmail) {
        if (fileUsername == username && filePassword == password) {
            userFile.close();
            return true;
        }
    }

    userFile.close();
    return false;
}

bool validateUsername(const string &username, const string &filename) {
    ifstream userFile(filename);
    if (!userFile.is_open()) {
        cout << "Unable to open file for reading." << endl;
        return false;
    }

    string fileUsername, filePassword, fileContact, fileEmail;
    while (userFile >> fileUsername >> filePassword >> fileContact >> fileEmail) {
        if (fileUsername == username) {
            userFile.close();
            return true;
        }
    }

    userFile.close();
    return false;
}

//--------------------------------------------------//



int main() {
    Menu menu;
    CustomerList customerList;
    OrderQueue orderQueue;

    string customerFileName = "customers.txt";
    string orderFileName = "orders.txt";
    string menuFileName = "menu.txt";
    string userFileName = "users.txt";
    const string incomeFileName = "transaction.txt";


    int choice;

    do {

        cout << "  __________************_________" << endl;
        cout << "\n--- Riphah Foodie Point ---" << endl;
        cout << "1. Admin" << endl;
        cout << "2. User" << endl;
        cout << "3. Exit" << endl;

        cout << "Enter your choice: ";

        choice = getNumericInput();

        switch (choice) {
            case 1: {
                menu.login();
                system("cls");
                int adminChoice;
                do {

                    cout << "  __________************_________" << endl;
                    cout << "\n--- Admin Management ---" << endl;
                    cout << "1. Manage Menu" << endl;
                    cout << "2. Manage Customers" << endl;
                  //  cout << "3. Show Income For a Day " << endl;
                    cout << "3. Back to Main Menu" << endl;

                    cout << "Enter your choice: ";
                    adminChoice = getNumericInput();

                    switch (adminChoice) {
                        case 1: {
                            int menuChoice;
                            do {

                                cout << "  __________************_________" << endl;
                                cout << "\n---  Menu Management ---" << endl;
                                cout << "1. Add Item to Menu" << endl;
                                cout << "2. Display Menu" << endl;
                                cout << "3. Delete Item from Menu" << endl;
                                cout << "4. Check Quantity Available" << endl;
                                cout << "5. Manage Menu Stack" << endl;
                                cout << "6. Manage Menu Queue" << endl;
                                cout << "7. Back to Admin Menu" << endl;

                                cout << "Enter your choice: ";
                                menuChoice = getNumericInput();

                                switch (menuChoice) {
                                    case 1: {
									system("cls");
									cout<<"Add Item to Menu"<<endl;
                                        string itemName;
                                        int itemQuantity, itemPrice;
                                        cout << "Enter item name: ";
                                        itemName = getAlphabeticInput();
                                        cout << "Enter quantity: ";
                                        itemQuantity = getNumericInput();
                                        cout << "Enter price: ";
                                        itemPrice = getNumericInput();
                                        menu.addItemToMenuAndWriteToFile(itemName, itemQuantity, itemPrice, menuFileName);
                                        break;
                                    }
                                    case 2:
                                    	system("cls");
                                    	cout<<"Menu Display"<<endl;
                                        menu.displayAndReadMenuData(menuFileName);
                                        break;
                                    case 3: {
                                    	system("cls");
                                    	cout<<"Delete Item from Menu"<<endl;
                                        string itemName;
                                        cout << "Enter item name to delete: ";
                                        itemName = getAlphabeticInput();
                                        menu.deleteItemFromMenu(itemName);
                                        break;
                                    }
                                    case 4: {
                                    	system("cls");
                                    	cout<<"Check Quantity Available"<<endl;
                                        string itemName;
                                        cout << "Enter item name to check quantity: ";
                                        itemName = getAlphabeticInput();
                                        menu.quantityAvailable(itemName);
                                        break;
                                    }

                                    case 5:
                                    	system("cls");
                                        menu.manageMenuStack();
                                        break;
                                    case 6:
                                    	system("cls");
                                        menu.manageMenuQueue();
                                        break;
                                    case 7:
                                    	system("cls");
                                        cout << "Returning to admin menu." << endl;
                                        break;

                                    default:
                                        cout << "Invalid choice. Please try again." << endl;
                                        break;
                                }
                            } while (menuChoice != 7);
                            break;
                        }

                        case 2: {
                        	system("cls");
                            int customerChoice;
                            do {

                                cout << "  __________************_________" << endl;
                                cout << "\n--- Customer Management ---" << endl;
                                cout << "1. Add Customer" << endl;
                                cout << "2. Display Customers" << endl;
                                cout << "3. Delete Customer" << endl;
                                cout << "4. Back to Admin Menu" << endl;
                                cout << "Enter your choice: ";
                                customerChoice = getNumericInput();

                                switch (customerChoice) {
                                     case 1: {
                system("cls");
                cout << "Add Customer" << endl;
                string name, contact, email;
                cout << "Enter customer name: ";
                name = getAlphabeticInput();
                do {
                    cout << "Enter contact no.: ";
                    cin >> contact;
                    if (contact.length() >= 10 && contact.length() <= 12 && isNumeric(contact)) {
                        cout << "Successfully entered\n";
                    } else {
                        cout << "Invalid\nEnter again\n";
                    }
                } while (contact.length() < 10 || contact.length() > 12 || !isNumeric(contact));
                do {
                    cout << "Enter email address: ";
                    cin >> email;
                    if (isValidEmail(email)) {
                        cout << "Successfully entered\n";
                    } else {
                        cout << "Invalid email. Enter again\n";
                    }
                } while (!isValidEmail(email));
//                cout << "Enter address: ";
//                cin >> address;
                customerList.addCustomerAndWriteToFile(name, contact, email, customerFileName);
                break;
            }
                                    case 2:
                                    	system("cls");
                                    	cout<<"Display Customer Data" <<endl;
                                        customerList.displayAndReadCustomerData(customerFileName);
                                        break;
                                    case 3: {
                                    	system("cls");
                                        string name;
                                        cout<<"Delete Customer" <<endl;
                                        cout << "Enter customer name to delete: ";
                                        name = getAlphabeticInput();
                                        customerList.deleteCustomerFromFile(name, customerFileName);
                                        break;
                                    }
                                    case 4:
                                    	system("cls");
                                        cout << "Returning to admin menu." << endl;
                                        break;
                                    default:
                                        cout << "Invalid choice. Please try again." << endl;
                                        break;
                                }
                            } while (customerChoice != 4);
                            break;
                        }

                     /*   case 3:
						{

                          string date;
                          cout << "Enter date (YYYY-MM-DD): ";
                          cin >> date;
                         menu.showIncomeForDay(date);
                            break;
                    }*/
                        case 3:
                            cout << "Returning to main menu." << endl;
                            break;
                        default:
                            cout << "Invalid choice. Please try again." << endl;
                            break;
                    }
                } while (adminChoice != 3);
                break;
        }
           case 2: {
    system("cls");
    int userChoice;
    cout << "1. Register" << endl;
    cout << "2. Login" << endl;
    cout << "Enter your choice: ";
    userChoice = getNumericInput();

    if (userChoice == 1) {
        // Registration process
        system("cls");
        string username, password, contact, email;
        cout << "Enter User name: ";
       // username = getAlphabeticInput();
        cout << "Enter Password: ";
        password = getNumericInput(); // Assuming password is numeric for simplicity

        do {
            cout << "\nEnter contact no.: ";
            cin >> contact;
            if (contact.length() >= 10 && contact.length() <= 12 && isNumeric(contact)) {
                cout << "Successfully entered\n";
            } else {
                cout << "Invalid\nEnter again\n";
            }
        } while (contact.length() < 10 || contact.length() > 12 || !isNumeric(contact));

        do {
            cout << "Enter email address: ";
            cin >> email;
            if (isValidEmail(email)) {
                cout << "Successfully entered\n";
            } else {
                cout << "Invalid email. Enter again\n";
            }
        } while (!isValidEmail(email));

        // Save user details to file
        ofstream userFile(userFileName, ios::app);
        if (userFile.is_open()) {
            userFile << username << " " << password << " " << contact << " " << email << endl;
            userFile.close();
            cout << "Registration successful. Please log in." << endl;
        } else {
            cout << "Unable to open file for writing." << endl;
        }
    } else if (userChoice == 2) {
        // Login process for registered user
        system("cls");
        string loginUsername, loginPassword;
        bool validUsername = false, validLogin = false;

        bool returnToMainMenu = false;
        do {
            cout << "Enter User name to login: ";
            loginUsername = getAlphabeticInput();
            if (validateUsername(loginUsername, userFileName)) {
                validUsername = true;
            } else {
                cout << "Invalid username. Please enter correct username." << endl;
                cout << "Press 1 to try again, or any other Numeric Value to go back to the main menu: ";
                int retryChoice;
                retryChoice = getNumericInput();
                if (retryChoice != 1) {
                    // Set the flag to return to the main menu
                    returnToMainMenu = true;
                    break;
                }
            }
        } while (!validUsername);

        if (returnToMainMenu) {
            break;
        }

        do {
            cout << "Enter Password: ";
            loginPassword = getNumericInput();

            if (loginUser(loginUsername, loginPassword, userFileName)) {
                validLogin = true;
            } else {
                cout << "Invalid password. Please enter correct password." << endl;
                cout << "Press 1 to try again, or any other Numeric Value to go back to the main menu: ";
                int retryChoice;
                retryChoice = getNumericInput();
                if (retryChoice != 1) {
                    // Set the flag to return to the main menu
                    returnToMainMenu = true;
                    break;
                }
            }
        } while (!validLogin);

        // If returnToMainMenu flag is set, return to the main menu
        if (returnToMainMenu) {
            break;
        }

        cout << "Login successful!" << endl;
        int choice;
        cout << "1. Riphah Order Management " << endl;
        cout << "2. Sorting step by step " << endl;
        cout << "3. Back to main menu " << endl;
        cout << "Enter your choice: ";
        choice = getNumericInput();
        switch (choice) {
            case 1: {
                int userMenuChoice;
                do {
                    //system("cls");
                    cout << "  __________************_________" << endl;
                    cout << "\n--- Riphah Order Management ---" << endl;
                    cout << "1. Display Menu" << endl;
                    cout << "2. Purchase item" << endl;
                    cout << "3. Place order" << endl;
                    cout << "4. Display Orders" << endl;
                    cout << "5. Check Quantity available" << endl << endl;
                    cout << "6. Back to Main Menu" << endl;

                    cout << "Enter your choice: ";
                    userMenuChoice = getNumericInput();

                    switch (userMenuChoice) {
                        case 1:
                            system("cls");
                            cout << " Menu Display " << endl;
                            menu.displayAndReadMenuData(menuFileName);
                            break;
                        case 2: {
                            system("cls");
                            cout << " Purchase Item " << endl;
                            string itemName;
                            int quantity;
                            double totalPrice;
                            cout << "Enter item name to purchase: ";
                            itemName = getAlphabeticInput();
                            cout << "Enter quantity to purchase: ";
                            quantity = getNumericInput();
                            menu.purchaseItem(itemName, quantity);
                            break;
                        }
                        case 3: {
                            system("cls");
                            cout << " Place Order " << endl;
                            string name, email, item;
                            int quantity;
                            cout << "Enter your name: ";
                            name = getAlphabeticInput();
                            do {
                                cout << "Enter email address: ";
                                cin >> email;
                                if (isValidEmail(email)) {
                                    cout << "Successfully entered\n";
                                } else {
                                    cout << "Invalid email. Enter again\n";
                                }
                            } while (!isValidEmail(email));
                            cout << "Enter item name: ";
                            item = getAlphabeticInput();
                            cout << "Enter quantity: ";
                            quantity = getNumericInput();
                            time_t orderTime = time(nullptr); // Get current time
                            orderQueue.placeOrderAndWriteToFile(orderFileName, name, email, item, quantity, orderTime);
                            break;
                        }
                        case 4:
                            system("cls");
                            cout << " Display Order Data " << endl;
                            orderQueue.displayAndReadOrderData(orderFileName);
                            break;
                        case 5: {
                            system("cls");
                            cout << " Check Quantity " << endl;
                            string itemName;
                            cout << "Enter item name to check quantity: ";
                            itemName = getAlphabeticInput();
                            menu.quantityAvailable(itemName);
                            break;
                        }
                        case 6:
                            system("cls");
                            cout << "Returning to main menu." << endl;
                            break;
                        default:
                            cout << "Invalid choice. Please try again." << endl;
                            break;
                    }
                } while (userMenuChoice != 6);
                break;
            }
            case 2: {
                system("cls");
                cout << " Sorting " << endl;
                sortingMenu();
                break;
            }
            case 3:
                system("cls");
                cout << "Returning to main menu." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } else {
        cout << "Invalid choice. Please try again." << endl;
    }
    break;
}

            case 3:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }

    } while (choice != 3);

    return 0;
}
