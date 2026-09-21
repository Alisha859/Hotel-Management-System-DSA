#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Custom utility function to avoid importing <algorithm>
int customMax(int a, int b) {
    return (a > b) ? a : b;
}

/* ==========================================================================
   1. LINKED LIST: Live Runtime Customer Tracker
   ========================================================================== */
class CustomerNode {
public:
    string name;
    int roomNo;
    CustomerNode* next;
    CustomerNode(string n, int r) {
        name = n;
        roomNo = r;
        next = NULL;
    }
};

class CustomerList {
private:
    CustomerNode* head;
public:
    CustomerList() { head = NULL; }

    void addCustomer(string name, int room) {
        CustomerNode* newNode = new CustomerNode(name, room);
        if (head == NULL) {
            head = newNode;
            return;
        }
        CustomerNode* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    void removeCustomer(int room) {
        if (head == NULL) return;
        if (head->roomNo == room) {
            CustomerNode* del = head;
            head = head->next;
            delete del;
            return;
        }
        CustomerNode* temp = head;
        while (temp->next != NULL && temp->next->roomNo != room) {
            temp = temp->next;
        }
        if (temp->next != NULL) {
            CustomerNode* del = temp->next;
            temp->next = temp->next->next;
            delete del;
        }
    }

    void display() {
        if (head == NULL) {
            cout << "No active customers checked in at this moment.\n";
            return;
        }
        CustomerNode* temp = head;
        while (temp != NULL) {
            cout << "Customer: " << temp->name << " | Room: " << temp->roomNo << "\n";
            temp = temp->next;
        }
    }

    ~CustomerList() {
        while (head != NULL) {
            CustomerNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

/* ==========================================================================
   2. QUEUE: Restaurant Orders Management (FIFO)
   ========================================================================== */
struct OrderItem {
    string itemName;
    int qty;
    int roomNo;
};

class OrderQueue {
private:
    OrderItem arr[100];
    int frontIdx, rearIdx;
public:
    OrderQueue() {
        frontIdx = -1;
        rearIdx = -1;
    }

    void enqueue(string item, int q, int room) {
        if (rearIdx == 99) {
            cout << "Kitchen order queue is full!\n";
            return;
        }
        if (frontIdx == -1) frontIdx = 0;
        rearIdx++;
        arr[rearIdx].itemName = item;
        arr[rearIdx].qty = q;
        arr[rearIdx].roomNo = room;
        cout << "Order placed into Kitchen Queue: " << item << " (x" << q << ") for Room " << room << "\n";
    }

    void dequeueAndServe() {
        if (frontIdx == -1 || frontIdx > rearIdx) {
            cout << "No pending restaurant orders in the processing queue.\n";
            return;
        }
        cout << "\n[KITCHEN COURIER] Serving " << arr[frontIdx].itemName
            << " x" << arr[frontIdx].qty << " to Room " << arr[frontIdx].roomNo << " successfully.\n";
        frontIdx++;
    }
};

/* ==========================================================================
   3. STACK: Payment History Archiving (LIFO)
   ========================================================================== */
struct PaymentRecord {
    int roomNo;
    int amountPaid;
    string method;
};

class PaymentStack {
private:
    PaymentRecord stackArr[100];
    int topIdx;
public:
    PaymentStack() { topIdx = -1; }

    void push(int room, int amount, string type) {
        if (topIdx == 99) return;
        topIdx++;
        stackArr[topIdx].roomNo = room;
        stackArr[topIdx].amountPaid = amount;
        stackArr[topIdx].method = type;
    }

    void displayHistory() {
        if (topIdx == -1) {
            cout << "No payment transactions have been logged yet.\n";
            return;
        }
        cout << "\n--- RECENT PAYMENTS TIMELINE (LIFO STACK) ---\n";
        for (int i = topIdx; i >= 0; i--) {
            cout << "Room: " << stackArr[i].roomNo << " | Paid: Rs " << stackArr[i].amountPaid
                << " | Method: " << stackArr[i].method << "\n";
        }
    }
};

/* ==========================================================================
   4. BINARY SEARCH TREE (BST): Room Verification Index
   ========================================================================== */
class BSTNode {
public:
    int roomNo;
    BSTNode* left, * right;
    BSTNode(int r) {
        roomNo = r;
        left = NULL;
        right = NULL;
    }
};

class RoomBST {
private:
    BSTNode* root;

    BSTNode* insertNode(BSTNode* node, int room) {
        if (node == NULL) return new BSTNode(room);
        if (room < node->roomNo) node->left = insertNode(node->left, room);
        else node->right = insertNode(node->right, room);
        return node;
    }

    bool searchNode(BSTNode* node, int room) {
        if (node == NULL) return false;
        if (node->roomNo == room) return true;
        if (room < node->roomNo) return searchNode(node->left, room);
        return searchNode(node->right, room);
    }

public:
    RoomBST() { root = NULL; }
    void insert(int room) { root = insertNode(root, room); }
    bool search(int room) { return searchNode(root, room); }
};

/* ==========================================================================
   5. AVL TREE: Self-Balancing Staff Hierarchy
   ========================================================================== */
class AVLNode {
public:
    int staffId;
    string name;
    string job;
    int salary;
    AVLNode* left, * right;
    int height;

    AVLNode(int id, string n, string j, int s) {
        staffId = id;
        name = n;
        job = j;
        salary = s;
        left = NULL;
        right = NULL;
        height = 1;
    }
};

class StaffAVL {
private:
    AVLNode* root;

    int getHeight(AVLNode* n) { return n ? n->height : 0; }

    int getBalanceFactor(AVLNode* n) {
        return n ? getHeight(n->left) - getHeight(n->right) : 0;
    }

    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = customMax(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = customMax(getHeight(x->left), getHeight(x->right)) + 1;
        return x;
    }

    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = customMax(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = customMax(getHeight(y->left), getHeight(y->right)) + 1;
        return y;
    }

    AVLNode* insertNode(AVLNode* node, int id, string name, string job, int salary) {
        if (node == NULL) return new AVLNode(id, name, job, salary);

        if (id < node->staffId)
            node->left = insertNode(node->left, id, name, job, salary);
        else if (id > node->staffId)
            node->right = insertNode(node->right, id, name, job, salary);
        else
            return node;

        node->height = 1 + customMax(getHeight(node->left), getHeight(node->right));
        int balance = getBalanceFactor(node);

        // Left Left Case
        if (balance > 1 && id < node->left->staffId) return rightRotate(node);
        // Right Right Case
        if (balance < -1 && id > node->right->staffId) return leftRotate(node);
        // Left Right Case
        if (balance > 1 && id > node->left->staffId) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        // Right Left Case
        if (balance < -1 && id < node->right->staffId) {
            node->right = leftRotate(node->right);
            return rightRotate(node);
        }
        return node;
    }

    void inOrderTraversal(AVLNode* root) {
        if (root != NULL) {
            inOrderTraversal(root->left);
            cout << "ID: " << root->staffId << " | Name: " << root->name
                << " | Job: " << root->job << " | Salary: Rs " << root->salary << "\n";
            inOrderTraversal(root->right);
        }
    }

public:
    StaffAVL() { root = NULL; }
    void insert(int id, string name, string job, int salary) {
        root = insertNode(root, id, name, job, salary);
    }
    void displayStaff() {
        if (root == NULL) {
            cout << "No dynamic staff records in the AVL system.\n";
            return;
        }
        inOrderTraversal(root);
    }
};

/* ==========================================================================
   6. MAX HEAP: Premium Transaction Tracker
   ========================================================================== */
class RevenueHeap {
private:
    int heap[100];
    int size;

    void heapifyUp(int index) {
        while (index > 0 && heap[(index - 1) / 2] < heap[index]) {
            int temp = heap[(index - 1) / 2];
            heap[(index - 1) / 2] = heap[index];
            heap[index] = temp;
            index = (index - 1) / 2;
        }
    }

public:
    RevenueHeap() { size = 0; }

    void insert(int value) {
        if (size >= 100) return;
        heap[size] = value;
        heapifyUp(size);
        size++;
    }

    void displayMaxRevenue() {
        if (size == 0) {
            cout << "No income values tracked inside the Max-Heap storage.\n";
            return;
        }
        cout << "Highest Standalone Revenue Record Detected: Rs " << heap[0] << "\n";
    }
};

/* ==========================================================================
   7. FILE MANAGER & CORE HOTEL BLUEPRINT ENTITIES
   ========================================================================== */
class FileManager {
public:
    static void append(string file, string data) {
        ofstream out(file, ios::app);
        if (out) {
            out << data << endl;
            out.close();
        }
    }

    static void display(string file) {
        ifstream in(file);
        if (!in) {
            cout << "No data configuration found matching (" << file << ").\n";
            return;
        }
        string line;
        cout << "\n=== HISTORICAL FILES DATA VIEW: " << file << " ===\n";
        while (getline(in, line)) {
            cout << line << endl;
        }
        in.close();
    }
};

class Admin {
public:
    static bool login(string& adminName) {
        string pass;
        cout << "Enter Admin Secure Token Password: ";
        cin >> pass;

        if (pass == "0053")      adminName = "Sumaira";
        else if (pass == "0026") adminName = "fatima";
        else if (pass == "0029") adminName = "alisha";
        else if (pass == "0050") adminName = "gul";
        else if (pass == "0034") adminName = "maryem";
        else {
            cout << " Invalid Password. Access Denied\n";
            return false;
        }

        ofstream out("admin_record.txt", ios::app);
        out << adminName << " Admin Login Session Validated\n";
        out.close();

        cout << adminName << " Admin Login Successful\n";
        return true;
    }
};

class Customer {
private:
    string name, phone, address;
public:
    void input() {
        cin.ignore();
        cout << "Enter Customer Name: ";
        getline(cin, name);

        // 11 digit mobile number enforcement system loop
        while (true) {
            cout << "Enter Phone Number (Must be exactly 11 digits): ";
            getline(cin, phone);
            if (phone.length() == 11) {
                // Ensure everything inside string is an explicit digit entry
                bool allDigits = true;
                for (char c : phone) {
                    if (c < '0' || c > '9') {
                        allDigits = false;
                        break;
                    }
                }
                if (allDigits) break;
            }
            cout << "Error: Contact formatting violation. Try again.\n";
        }

        cout << "Enter Address: ";
        getline(cin, address);
    }

    string record(int roomNo) {
        return "Name: " + name + " | Phone: " + phone + " | Address: " + address + " | Room: " + to_string(roomNo);
    }
    string getName() { return name; }
};

class Room {
public:
    int number;
    bool booked;
    Room() {
        number = 0;
        booked = false;
    }
    void setValues(int n) {
        number = n;
        booked = false;
    }
};

class Hotel {
private:
    Room rooms[70];
    int roomBill[70];
public:
    RoomBST bstVerifier;

    Hotel() {
        int idx = 0;
        for (int f = 1; f <= 7; f++) {
            for (int r = 1; r <= 10; r++) {
                int roomNumber = f * 100 + r;
                rooms[idx].setValues(roomNumber);
                roomBill[idx] = 0;
                bstVerifier.insert(roomNumber);
                idx++;
            }
        }
    }

    void showAvailable(int floor) {
        cout << "Available Rooms: ";
        for (int i = 0; i < 70; i++) {
            if (!rooms[i].booked && (rooms[i].number / 100 == floor)) {
                cout << rooms[i].number << " ";
            }
        }
        cout << endl;
    }

    bool available(int roomNo) {
        if (!bstVerifier.search(roomNo)) return false;
        for (int i = 0; i < 70; i++) {
            if (rooms[i].number == roomNo) return !rooms[i].booked;
        }
        return false;
    }

    void book(int roomNo) {
        for (int i = 0; i < 70; i++) {
            if (rooms[i].number == roomNo) rooms[i].booked = true;
        }
    }

    void checkout(int roomNo) {
        for (int i = 0; i < 70; i++) {
            if (rooms[i].number == roomNo) rooms[i].booked = false;
        }
    }

    int price(int floor, int buffet = 0) {
        if (floor == 4) return buffet ? 28000 : 20000;
        int p[] = { 0, 50000, 45000, 35000, 0, 17000, 14000, 11000 };
        return p[floor];
    }

    void setBill(int roomNo, int bill) {
        for (int i = 0; i < 70; i++) {
            if (rooms[i].number == roomNo) roomBill[i] = bill;
        }
    }

    int getBill(int roomNo) {
        for (int i = 0; i < 70; i++) {
            if (rooms[i].number == roomNo) return roomBill[i];
        }
        return 0;
    }

    void clearBill(int roomNo) {
        for (int i = 0; i < 70; i++) {
            if (rooms[i].number == roomNo) roomBill[i] = 0;
        }
    }
};

class Revenue {
public:
    static void save(string month, int amount) {
        ofstream out("revenue.txt", ios::app);
        if (out) {
            out << month << " " << amount << endl;
            out.close();
        }
    }

    static void showMonth(string month) {
        ifstream in("revenue.txt");
        string m;
        int amt, total = 0;
        while (in >> m >> amt) {
            if (m == month) total += amt;
        }
        in.close();
        cout << "Total Revenue for " << month << ": Rs " << total << endl;
    }
};

/* ==========================================================================
   8. SERVICES LAYER (ABSTRACTION & INHERITANCE)
   ========================================================================== */
class Service {
public:
    virtual void execute() = 0;
    virtual ~Service() {}
};

class RoomBooking : public Service {
private:
    Hotel& hotel;
    CustomerList& liveList;
    RevenueHeap& revHeap;
public:
    RoomBooking(Hotel& h, CustomerList& cl, RevenueHeap& rh) : hotel(h), liveList(cl), revHeap(rh) {}

    void execute() override {
        Customer customer;
        int floor, room, buffet = 0, days;
        string month;

        customer.input();

        cout << "Enter Floor (1-7): ";
        cin >> floor;
        if (floor < 1 || floor > 7) {
            cout << "Invalid Floor Number.\n";
            return;
        }

        hotel.showAvailable(floor);

        if (floor == 4) {
            cout << "Buffet? (1=Yes, 0=No): ";
            cin >> buffet;
        }

    ROOM_SELECTION:
        cout << "Enter Room Number: ";
        cin >> room;

        if (room / 100 != floor || !hotel.available(room)) {
            cout << "Room not available. Please choose another room on the same floor.\n";
            goto ROOM_SELECTION;
        }

        cout << "Enter Number of Days: ";
        cin >> days;

        hotel.book(room);
        liveList.addCustomer(customer.getName(), room);

        int rentPerDay = hotel.price(floor, buffet);
        int bill = rentPerDay * days;

        cout << "Rent per Day: Rs " << rentPerDay << endl;
        cout << "Days: " << days << endl;
        cout << "Total Bill: Rs " << bill << endl;

        cout << "Enter Month: ";
        cin >> month;

        // Centralized tracking - continuous archival records
        FileManager::append("customers.txt", customer.record(room));
        FileManager::append("rooms.txt", customer.getName() + " | Room: " + to_string(room) + " | Days: " + to_string(days) + " | Bill: Rs " + to_string(bill));

        Revenue::save(month, bill);
        revHeap.insert(bill);
        hotel.setBill(room, bill);

        cout << " Room Booked Successfully\n";
    }
};

class Restaurant : public Service {
private:
    Hotel& hotel;
    OrderQueue& orders;
    RevenueHeap& revHeap;
public:
    Restaurant(Hotel& h, OrderQueue& o, RevenueHeap& rh) : hotel(h), orders(o), revHeap(rh) {}

    void execute() override {
        int choice, qty;
        cout << "\n1.Pizza 1800\n2.Burger 500\n3.Pasta 1200\n4.Biryani 300\n5.Corn 200\n";
        cout << "Enter choice: ";
        cin >> choice;
        if (choice < 1 || choice > 5) {
            cout << "Invalid item selection.\n";
            return;
        }

        cout << "Enter quantity: ";
        cin >> qty;

        int price[] = { 0, 1800, 500, 1200, 300, 200 };
        string names[] = { "", "Pizza", "Burger", "Pasta", "Biryani", "Corn" };
        int orderBill = price[choice] * qty;

        cout << "\nOrder Bill: Rs " << orderBill << endl;

        int option;
        cout << "1. Dining\n2. Take Away / Room Delivery\nEnter Option: ";
        cin >> option;

        if (option == 1) {
            cout << "Please pay at counter. Thank you!\n";
        }
        else if (option == 2) {
            int roomNo;
            cout << "Enter Room Number: ";
            cin >> roomNo;

            if (!hotel.bstVerifier.search(roomNo)) {
                cout << "Invalid room specified.\n";
                return;
            }

            if (!hotel.available(roomNo)) {
                cout << "Room is booked. We will deliver your order to the room.\n";
                int oldBill = hotel.getBill(roomNo);
                hotel.setBill(roomNo, oldBill + orderBill);
                orders.enqueue(names[choice], qty, roomNo);
                cout << "Order amount added to room bill.\n";
                cout << "Updated Room Bill: Rs " << hotel.getBill(roomNo) << endl;
            }
            else {
                cout << "Your room is not booked. You can eat by dining.\n";
                return;
            }
        }
        else {
            cout << "Invalid choice selection.\n";
            return;
        }

        string month;
        cout << "Enter Month: ";
        cin >> month;
        Revenue::save(month, orderBill);
        revHeap.insert(orderBill);
    }
};

class Event : public Service {
private:
    RevenueHeap& revHeap;
public:
    Event(RevenueHeap& rh) : revHeap(rh) {}

    void execute() override {
        int hall, hours;
        string type, month;

        cout << "Event Type: ";
        cin.ignore();
        getline(cin, type);
        cout << "Hall (1=Upper, 2=Medium, 3=Common): ";
        cin >> hall;
        cout << "Hours: ";
        cin >> hours;

        int rate = (hall == 1) ? 200000 : (hall == 2) ? 150000 : 80000;
        int total = rate * hours;

        cout << "Event Charges: Rs " << total << endl;
        cout << "Enter Month: ";
        cin >> month;

        // Centralized revenue & log architecture
        Revenue::save(month, total);
        revHeap.insert(total);
        FileManager::append("events.txt", "Type: " + type + " | Bill: Rs " + to_string(total));
        cout << "Event booked successfully.\n";
    }
};

/* ==========================================================================
   9. MAIN CONTROL INTERFACE
   ========================================================================== */
int main() {
    Hotel hotel;
    CustomerList checkedInCustomers;
    OrderQueue kitchenQueue;
    PaymentStack invoiceHistory;
    StaffAVL staffDirectory;
    RevenueHeap financialHeap;

    // Seeding multiple default staff members inside dynamic balanced AVL tree
    staffDirectory.insert(101, "Ahmad", "Supervisor", 45000);
    staffDirectory.insert(102, "Zainab", "Manager", 65000);
    staffDirectory.insert(103, "Bilal", "Receptionist", 32000);
    staffDirectory.insert(104, "Ayesha", "Chef Executive", 75000);
    staffDirectory.insert(105, "Hamza", "Security Head", 40000);

    while (true) {
        cout << "\n===== SEVEN STAR HOTEL SYSTEM =====\n";
        cout << "1. Room Booking\n";
        cout << "2. Book Event\n";
        cout << "3. Restaurant Order Placing\n";
        cout << "4. Dispatch/Serve Next Restaurant Order\n";
        cout << "5. Add Staff (Admin)\n";
        cout << "6. View Staff Directory (AVL In-Order)\n";
        cout << "7. View Active Current Guests (Linked List)\n";
        cout << "8. View Historical Past Customer Records (Central File Log)\n";
        cout << "9. Checkout Room (With Secure Payment Checks)\n";
        cout << "10. View Payment History Records (Stack Log)\n";
        cout << "11. View Maximum Single Transaction (Heap Root)\n";
        cout << "12. Check Monthly Income Data (Admin)\n";
        cout << "13. Exit\n";
        cout << "Enter Choice: ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            string ignoreLine;
            getline(cin, ignoreLine);
            cout << "Invalid Selection Input Format.\n";
            continue;
        }

        switch (choice) {
        case 1: {
            Service* service = new RoomBooking(hotel, checkedInCustomers, financialHeap);
            service->execute();
            delete service;
            break;
        }
        case 2: {
            Service* service = new Event(financialHeap);
            service->execute();
            delete service;
            break;
        }
        case 3: {
            Service* service = new Restaurant(hotel, kitchenQueue, financialHeap);
            service->execute();
            delete service;
            break;
        }
        case 4: {
            kitchenQueue.dequeueAndServe();
            break;
        }
        case 5: {
            string adminName;
            if (Admin::login(adminName)) {
                int id, salary;
                string name, job;
                cout << "Enter Staff ID Code: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Staff Name: ";
                getline(cin, name);
                cout << "Enter Job Title: ";
                getline(cin, job);
                cout << "Enter Salary: ";
                cin >> salary;

                staffDirectory.insert(id, name, job, salary);
                FileManager::append("staff.txt", "ID: " + to_string(id) + " | Name: " + name + " | Job: " + job + " | Salary: " + to_string(salary));
                cout << "Staff Added Successfully to AVL Registry\n";
            }
            break;
        }
        case 6: {
            cout << "\n--- STAFF MEMBERS DIRECTORY VIEW (AVL TREE) ---\n";
            staffDirectory.displayStaff();
            break;
        }
        case 7: {
            cout << "\n--- LIVE REGISTERED GUESTS LIST (LINKED LIST) ---\n";
            checkedInCustomers.display();
            break;
        }
        case 8: {
            // Distinct separate case to read centralized archival customer database file
            FileManager::display("customers.txt");
            break;
        }
        case 9: {
            int r;
            cout << "Enter Room Number: ";
            cin >> r;

            if (!hotel.bstVerifier.search(r)) {
                cout << "Error: Invalid room number identifier matched.\n";
                break;
            }

            int bill = hotel.getBill(r);
            if (hotel.available(r) && bill == 0) {
                cout << "This target room structure is already unbooked and clear.\n";
                break;
            }

            if (bill > 0) {
                cout << "Pending Bill Check: Outstanding balance is Rs " << bill << endl;
                cout << "Has the bill been paid? (1 = Yes, 0 = No): ";
                int paid;
                cin >> paid;

                if (paid == 1) {
                    string method;
                    cout << "Enter Payment Method (Cash/Card): ";
                    cin >> method;

                    invoiceHistory.push(r, bill, method);
                    hotel.checkout(r);
                    hotel.clearBill(r);
                    checkedInCustomers.removeCustomer(r);
                    cout << "Payment received. Room Checked Out Successfully\n";
                }
                else {
                    cout << "Checkout denied. Please clear bill first.\n";
                }
            }
            else {
                hotel.checkout(r);
                checkedInCustomers.removeCustomer(r);
                cout << "Room system status updated cleanly.\n";
            }
            break;
        }
        case 10: {
            invoiceHistory.displayHistory();
            break;
        }
        case 11: {
            financialHeap.displayMaxRevenue();
            break;
        }
        case 12: {
            string adminName;
            if (Admin::login(adminName)) {
                string month;
                cout << "Enter Month: ";
                cin >> month;
                Revenue::showMonth(month);
                FileManager::display("revenue.txt");
            }
            break;
        }
        case 13: {
            cout << "Exiting System Components...\n";
            return 0;
        }
        default: {
            cout << "Invalid Menu Option Selected.\n";
            break;
        }
        }
    }
}
