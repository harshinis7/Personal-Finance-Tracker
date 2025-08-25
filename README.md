# Personal Finance Tracker (C++)

A simple **Personal Finance Tracker** written in C++ to help you track income, expenses, and savings goals.  
This project uses **arrays of structures**, supports **sorting, searching, filtering**, and can **save/load data** from a binary file.  
Includes a **bonus ASCII bar chart** for visualizing monthly spending.

---

## **Features**
- **Add transactions**: income or expense with date, category, amount, and note.
- **Display all records** in a clean table format.
- **Sort by amount** using bubble sort.
- **Search by category** to quickly find related transactions.
- **Filter expenses** greater than $100.
- **Save and load data** from a file (`finance.dat`).
- **ASCII monthly spending chart** showing expense patterns.

---

## **Tech Stack**
- Language: **C++ (Standard Library only)**
- Data storage: **Array of structures**
- File I/O: **Binary read/write using fstream**
- No external dependencies

---

## **Getting Started**

### **1. Clone the repository**
```bash
git clone https://github.com/<your-username>/personal-finance-tracker.git
cd personal-finance-tracker
2. Compile the program
Use any C++ compiler:

bash
Copy
Edit
g++ finance_tracker.cpp -o finance_tracker
3. Run the program
bash
Copy
Edit
./finance_tracker
