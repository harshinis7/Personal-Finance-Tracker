#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;

const int MAX_TRANSACTIONS = 100;

struct Transaction {
    char type[10];       // "income" or "expense"
    char category[50];
    char date[11];       // format YYYY-MM-DD
    double amount;
    char note[50];
};

Transaction transactions[MAX_TRANSACTIONS];
int countTransactions = 0;

// Function declarations
void addTransaction();
void displayTransactions();
void sortByAmount();
void filterExpenses();
void searchByCategory();
void saveToFile(const char* filename);
void loadFromFile(const char* filename);
void showMonthlySpending();

int main() {
    loadFromFile("finance.dat");
    int choice;

    do {
        cout << "\n--- Personal Finance Tracker ---\n";
        cout << "1. Add Transaction\n";
        cout << "2. Display All Transactions\n";
        cout << "3. Sort by Amount\n";
        cout << "4. Filter Expenses > $100\n";
        cout << "5. Search by Category\n";
        cout << "6. Show Monthly Spending Chart\n";
        cout << "7. Save and Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: addTransaction(); break;
            case 2: displayTransactions(); break;
            case 3: sortByAmount(); break;
            case 4: filterExpenses(); break;
            case 5: searchByCategory(); break;
            case 6: showMonthlySpending(); break;
            case 7: saveToFile("finance.dat"); break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 7);

    return 0;
}

// Add a new transaction
void addTransaction() {
    if (countTransactions >= MAX_TRANSACTIONS) {
        cout << "Transaction limit reached!\n";
        return;
    }

    cout << "Enter type (income/expense): ";
    cin.getline(transactions[countTransactions].type, 10);

    cout << "Enter category: ";
    cin.getline(transactions[countTransactions].category, 50);

    cout << "Enter date (YYYY-MM-DD): ";
    cin.getline(transactions[countTransactions].date, 11);

    cout << "Enter amount: ";
    cin >> transactions[countTransactions].amount;
    cin.ignore();

    cout << "Enter note: ";
    cin.getline(transactions[countTransactions].note, 50);

    countTransactions++;
    cout << "Transaction added successfully.\n";
}

// Display all transactions
void displayTransactions() {
    cout << "\n"
         << left << setw(10) << "Type"
         << setw(15) << "Category"
         << setw(12) << "Date"
         << setw(10) << "Amount"
         << "Note\n";
    cout << "-------------------------------------------------------------\n";

    for (int i = 0; i < countTransactions; i++) {
        cout << left << setw(10) << transactions[i].type
             << setw(15) << transactions[i].category
             << setw(12) << transactions[i].date
             << setw(10) << fixed << setprecision(2) << transactions[i].amount
             << transactions[i].note << "\n";
    }
}

// Sort transactions by amount (ascending)
void sortByAmount() {
    for (int i = 0; i < countTransactions - 1; i++) {
        for (int j = i + 1; j < countTransactions; j++) {
            if (transactions[i].amount > transactions[j].amount) {
                Transaction temp = transactions[i];
                transactions[i] = transactions[j];
                transactions[j] = temp;
            }
        }
    }
    cout << "Transactions sorted by amount.\n";
}

// Show all expenses greater than $100
void filterExpenses() {
    cout << "\nExpenses over $100:\n";
    for (int i = 0; i < countTransactions; i++) {
        if (strcmp(transactions[i].type, "expense") == 0 && transactions[i].amount > 100) {
            cout << transactions[i].date << " | "
                 << transactions[i].category << " | "
                 << transactions[i].amount << " | "
                 << transactions[i].note << "\n";
        }
    }
}

// Search transactions by category
void searchByCategory() {
    char searchCat[50];
    cout << "Enter category to search: ";
    cin.getline(searchCat, 50);

    cout << "\nResults for category '" << searchCat << "':\n";
    for (int i = 0; i < countTransactions; i++) {
        if (strcmp(transactions[i].category, searchCat) == 0) {
            cout << transactions[i].date << " | "
                 << transactions[i].type << " | "
                 << transactions[i].amount << " | "
                 << transactions[i].note << "\n";
        }
    }
}

// Save all transactions to a binary file
void saveToFile(const char* filename) {
    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        cout << "Error saving file!\n";
        return;
    }
    outFile.write((char*)&countTransactions, sizeof(countTransactions));
    outFile.write((char*)transactions, sizeof(Transaction) * countTransactions);
    outFile.close();
    cout << "Data saved to " << filename << "\n";
}

// Load transactions from a binary file
void loadFromFile(const char* filename) {
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        cout << "No existing data file found.\n";
        return;
    }
    inFile.read((char*)&countTransactions, sizeof(countTransactions));
    inFile.read((char*)transactions, sizeof(Transaction) * countTransactions);
    inFile.close();
    cout << "Data loaded from " << filename << "\n";
}

// Show monthly spending as ASCII chart
void showMonthlySpending() {
    double monthTotal[13] = {0};
    char monthStr[3];

    for (int i = 0; i < countTransactions; i++) {
        if (strcmp(transactions[i].type, "expense") == 0) {
            strncpy(monthStr, transactions[i].date + 5, 2);
            monthStr[2] = '\0';
            int month = atoi(monthStr);
            if (month >= 1 && month <= 12) {
                monthTotal[month] += transactions[i].amount;
            }
        }
    }

    cout << "\nMonthly Spending (ASCII Chart):\n";
    for (int m = 1; m <= 12; m++) {
        cout << setw(2) << m << ": ";
        int bars = static_cast<int>(monthTotal[m] / 10); // scale: $10 = 1 bar
        for (int b = 0; b < bars; b++) cout << "|";
        cout << "  $" << fixed << setprecision(2) << monthTotal[m] << "\n";
    }
}
