#include <iostream>
#include <vector>
#include <map>
#include <fstream>
using namespace std;

// Base class Person
class Person {
protected:
    string name;
public:
    virtual void inputDetails() {
        cout << "Enter Name: ";
        getline(cin >> ws, name);
    }
    string getName() const { return name; }
};

// Admin class inherits Person
class Admin : public Person {
    string password;
public:
    Admin() {
        name = "admin";
        password = "123456789"; 
    }

    bool login(string user, string pass) {
        return (user == name && pass == password);
    }
};

// Customer class inherits Person
class Customer : public Person {
    int customerId;
    string phone;
public:
    Customer(int id) : customerId(id) {}
    void inputDetails() override {
        Person::inputDetails();
        cout << "Enter Phone: ";
        getline(cin, phone);
    }
    int getId() const { return customerId; }
    void display() const {
        cout << "Customer ID: " << customerId << ", Name: " << name << ", Phone: " << phone << endl;
    }
};

// Room class
class Room {
    int roomNo;
    string type;
    double price;
    bool booked;
public:
    Room(int r, string t, double p) : roomNo(r), type(t), price(p), booked(false) {}
    int getRoomNo() const { return roomNo; }
    string getType() const { return type; }
    double getPrice() const { return price; }
    bool isBooked() const { return booked; }

    void book() { booked = true; }
    void free() { booked = false; }

    void display() const {
        cout << "Room " << roomNo << " | Type: " << type << " | Rs. " << price << " | " << (booked ? "Booked" : "Available") << endl;
    }
};

// Booking class
class Booking {
protected:
    int bookingId;
    Customer customer;
    Room* room;
    int nights;
public:
    Booking(int id, Customer cust, Room* rm, int n)
        : bookingId(id), customer(cust), room(rm), nights(n) {
        room->book();
    }

    virtual void generateBill() const {
        double total = room->getPrice() * nights;
        double gst = total * 0.18;
        double grandTotal = total + gst;

        cout << "\n--- Bill ---\n";
        customer.display();
        cout << "Room No: " << room->getRoomNo() << "\nNights: " << nights;
        cout << "\nSubtotal: Rs. " << total << "\nGST (18%): Rs. " << gst;
        cout << "\nTotal: Rs. " << grandTotal << endl;
    }

    int getBookingId() const { return bookingId; }
    string getCustomerName() const { return customer.getName(); }

    virtual void cancelBooking() {
        room->free();
        cout << "Booking ID " << bookingId << " cancelled successfully.\n";
    }

    void saveToFile() const {
        ofstream file("booking_log.txt", ios::app);
        file << "BookingID: " << bookingId << ", Name: " << customer.getName()
             << ", Room: " << room->getRoomNo() << ", Nights: " << nights << "\n";
        file.close();
    }
};

// HotelSystem class
class HotelSystem {
    vector<Room> rooms;
    vector<Booking*> bookings;
    int nextRoomNo = 101;
    int nextBookingId = 1;
    int nextCustomerId = 1001;
public:
    void adminMenu() {
        int choice;
        do {
            cout << "\n--- Admin Menu ---\n1. Add Room\n2. View All Rooms\n3. View Bookings\n4. Logout\nChoice: ";
            cin >> choice;
            switch (choice) {
                case 1: addRoom(); break;
                case 2: showRooms(); break;
                case 3: showBookings(); break;
                case 4: cout << "Logging out...\n"; break;
                default: cout << "Invalid!\n";
            }
        } while (choice != 4);
    }

    void addRoom() {
        string type;
        double price;
        cout << "Enter Room Type (AC/Non-AC): ";
        cin >> type;
        cout << "Enter Price per Night: ";
        cin >> price;
        rooms.push_back(Room(nextRoomNo++, type, price));
        cout << "Room added successfully!\n";
    }

    void showRooms() const {
        cout << "\n--- Room List ---\n";
        for (const auto &room : rooms) {
            room.display();
        }
    }

    void customerMenu() {
        int choice;
        do {
            cout << "\n--- Customer Menu ---\n1. View Rooms\n2. Book Room\n3. Cancel Booking\n4. Back\nChoice: ";
            cin >> choice;
            switch (choice) {
                case 1: showRooms(); break;
                case 2: bookRoom(); break;
                case 3: cancelBooking(); break;
                case 4: break;
                default: cout << "Invalid!\n";
            }
        } while (choice != 4);
    }

    void bookRoom() {
        int nights, roomNo;
        showRooms();
        cout << "Enter Room Number to Book: ";
        cin >> roomNo;

        for (auto &room : rooms) {
            if (room.getRoomNo() == roomNo && !room.isBooked()) {
                cout << "Enter Nights to Stay: ";
                cin >> nights;
                Customer cust(nextCustomerId++);
                cust.inputDetails();

                Booking* newBooking = new Booking(nextBookingId++, cust, &room, nights);
                bookings.push_back(newBooking);

                newBooking->generateBill();
                newBooking->saveToFile();
                return;
            }
        }
        cout << "Invalid room number or already booked.\n";
    }

    void cancelBooking() {
        int id;
        cout << "Enter Booking ID to Cancel: ";
        cin >> id;
        for (auto it = bookings.begin(); it != bookings.end(); ++it) {
            if ((*it)->getBookingId() == id) {
                (*it)->cancelBooking();
                delete *it;
                bookings.erase(it);
                return;
            }
        }
        cout << "Booking ID not found.\n";
    }

    void showBookings() const {
        cout << "\n--- All Bookings ---\n";
        for (const auto &b : bookings) {
            cout << "Booking ID: " << b->getBookingId() << " | Customer: " << b->getCustomerName() << endl;
        }
    }

    ~HotelSystem() {
        for (auto b : bookings)
            delete b;
    }
};

int main() {
    HotelSystem hotel;
    Admin admin;
    int choice;

    do {
        cout << "\n=== Hotel Booking System ===\n";
        cout << "1. Admin Login\n2. Customer Menu\n3. Exit\nChoice: ";
        cin >> choice;
        if (choice == 1) {
            string user, pass;
            cout << "Username: ";
            cin >> user;
            cout << "Password: ";
            cin >> pass;
            if (admin.login(user, pass)) {
                cout << "Login Successful.\n";
                hotel.adminMenu();
            } else {
                cout << "Invalid Credentials.\n";
            }
        } else if (choice == 2) {
            hotel.customerMenu();
        } else if (choice == 3) {
            cout << "Exiting system...\n";
        } else {
            cout << "Invalid choice.\n";
        }
    } while (choice != 3);

    return 0;
}
