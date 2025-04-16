# 🏨 Hotel Booking System (C++ | OOPs Project)

A console-based Hotel Booking System developed using **Object-Oriented Programming (OOP)** principles in **C++**. The system provides functionalities for **room management, customer booking, billing, and admin operations**, making it a complete mini project for showcasing OOP concepts in interviews or college submissions.

---

##  Features

- Admin login with room management capabilities
- Add, view, and manage hotel rooms
- Customer room booking with stay duration input
- Auto-generated bill with GST calculation
- Booking cancellation support (polymorphism used)
- File handling for saving booking logs
- Clean menu-driven UI for both Admin and Customer

---

## OOP Concepts Used

| Concept         | Description                                            |
|----------------|--------------------------------------------------------|
| **Encapsulation** | Private data members, getter/setter functions        |
| **Inheritance**   | `Customer` and `Admin` inherited from `Person`      |
| **Polymorphism**  | Virtual `cancelBooking()` method in `Booking`       |
| **Abstraction**   | Modular classes for Booking, Room, Customer, Admin  |
| **File Handling** | Logs stored in `booking_log.txt` using file streams |
| **STL**           | `vector` for rooms and booking storage              |

---


---

##  How to Run

1. **Download the file:**

   Download or clone the file `hotelbookingsystem.cpp` to your local machine.

2. **Open Terminal or Command Prompt** in the folder where the file is saved.

3. **Compile the program using g++:**

   ```bash
   g++ hotelbookingsystem.cpp -o hotel
   hotel.exe     

