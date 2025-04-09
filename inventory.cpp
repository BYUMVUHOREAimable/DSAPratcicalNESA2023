#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;

// Structure to hold item information
struct InventoryItem {
    string id;
    string name;
    int quantity;
    string regDate;
};

// Function prototypes
void addItem(const string& id, const string& name, int quantity, const string& regDate, const string& filename);
vector<InventoryItem> readItemsFromCSV(const string& filename);
void listItems(const string& filename);
void displayHelp();
string toLower(const string& str);
bool isValidDate(const string& date);
string getCurrentDate();

const string CSV_FILE = "inventory.csv";

int main() {
    cout << "Rwanda Coding Academy Inventory System" << endl;
    cout << "Type 'help' for available commands" << endl;

    string command;
    while (true) {
        cout << "\n> ";
        getline(cin, command);

        // Convert command to lowercase for case-insensitive comparison
        string lowerCommand = toLower(command);

        if (lowerCommand == "exit") {
            cout << "Exiting the inventory system. Goodbye!" << endl;
            break;
        }
        else if (lowerCommand.substr(0, 7) == "itemadd") {
            // Parse itemadd command
            vector<string> tokens;
            istringstream iss(command);
            string token;
            
            // Skip the command itself
            iss >> token;
            
            // Get all arguments
            while (iss >> token) {
                tokens.push_back(token);
            }

            // Check if we have all required arguments
            if (tokens.size() < 4) {
                cout << "Error: Invalid format for itemadd command." << endl;
                cout << "Usage: itemadd <item_id> <item_name> <quantity> <registration_date>" << endl;
                continue;
            }

            // Extract values
            string id = tokens[0];
            string name;
            
            // Item name might contain spaces, so we need to handle it differently
            // Join all tokens except the last two (quantity and date) as the name
            for (size_t i = 1; i < tokens.size() - 2; ++i) {
                if (i > 1) name += " ";
                name += tokens[i];
            }

            int quantity;
            try {
                quantity = stoi(tokens[tokens.size() - 2]);
            } catch (...) {
                cout << "Error: Quantity must be a number." << endl;
                continue;
            }

            string regDate = tokens.back();
            
            // Validate date format (YYYY-MM-DD)
            if (!isValidDate(regDate)) {
                cout << "Error: Invalid date format. Please use YYYY-MM-DD." << endl;
                continue;
            }

            // Add the item
            addItem(id, name, quantity, regDate, CSV_FILE);
            cout << "Item added successfully." << endl;
        }
        else if (lowerCommand == "itemslist") {
            listItems(CSV_FILE);
        }
        else if (lowerCommand == "help") {
            displayHelp();
        }
        else {
            cout << "Error: Unknown command. Type 'help' for available commands." << endl;
        }
    }

    return 0;
}

// Function to add an item to the CSV file
void addItem(const string& id, const string& name, int quantity, const string& regDate, const string& filename) {
    ofstream outFile;
    outFile.open(filename, ios::app); // Append mode
    
    if (outFile.is_open()) {
        outFile << id << "," << name << "," << quantity << "," << regDate << "\n";
        outFile.close();
    } else {
        cerr << "Error: Unable to open file for writing." << endl;
    }
}

// Function to read items from CSV file
vector<InventoryItem> readItemsFromCSV(const string& filename) {
    vector<InventoryItem> items;
    ifstream inFile(filename);
    
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            // Skip empty lines
            if (line.empty()) continue;
            
            istringstream iss(line);
            string token;
            InventoryItem item;
            
            // Read ID
            if (getline(iss, token, ',')) {
                item.id = token;
            }
            
            // Read Name
            if (getline(iss, token, ',')) {
                item.name = token;
            }
            
            // Read Quantity
            if (getline(iss, token, ',')) {
                try {
                    item.quantity = stoi(token);
                } catch (...) {
                    item.quantity = 0;
                }
            }
            
            // Read Registration Date
            if (getline(iss, token, ',')) {
                item.regDate = token;
            }
            
            items.push_back(item);
        }
        inFile.close();
    }
    
    return items;
}

// Function to list items in alphabetical order
void listItems(const string& filename) {
    vector<InventoryItem> items = readItemsFromCSV(filename);
    
    // Sort items by name
    sort(items.begin(), items.end(), [](const InventoryItem& a, const InventoryItem& b) {
        return a.name < b.name;
    });
    
    // Display header
    cout << string(90, '-') << endl;
    cout << left << setw(20) << "| Item ID" 
         << setw(30) << "| Item Name" 
         << setw(20) << "| Quantity" 
         << setw(20) << "| Reg Date" << "|" << endl;
    cout << string(90, '-') << endl;
    
    // Display each item
    for (const auto& item : items) {
        cout << "| " << left << setw(18) << item.id 
             << "| " << setw(28) << item.name 
             << "| " << setw(18) << item.quantity 
             << "| " << setw(18) << item.regDate << "|" << endl;
    }
    
    cout << string(90, '-') << endl;
}

// Function to display help information
void displayHelp() {
    cout << "\nCommands syntaxes:\n";
    cout << "------------------------------------------------------------\n";
    cout << "itemadd <item_id> <item_name> <quantity> <registration_date>\n";
    cout << "    Adds a new item to the inventory.\n";
    cout << "    Example: itemadd ID123 Laptop 15 2023-05-20\n\n";
    cout << "itemslist\n";
    cout << "    Lists all items in the inventory in alphabetical order.\n\n";
    cout << "help\n";
    cout << "    Displays this help information.\n\n";
    cout << "exit\n";
    cout << "    Exits the program.\n";
    cout << "------------------------------------------------------------\n";
}

// Utility function to convert string to lowercase
string toLower(const string& str) {
    string lowerStr;
    for (char c : str) {
        lowerStr += tolower(c);
    }
    return lowerStr;
}

// Function to validate date format (YYYY-MM-DD)
bool isValidDate(const string& date) {
    if (date.length() != 10) return false;
    if (date[4] != '-' || date[7] != '-') return false;
    
    // Check if all other characters are digits
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (!isdigit(date[i])) return false;
    }
    
    // Basic checks for year, month, day
    int year = stoi(date.substr(0, 4));
    int month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8, 2));
    
    if (year < 1900 || year > 2100) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
    
    // Additional checks for specific months
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30) return false;
    }
    
    // February check (ignoring leap years for simplicity)
    if (month == 2 && day > 28) return false;
    
    return true;
}

// Function to get current date in YYYY-MM-DD format
string getCurrentDate() {
    time_t now = time(nullptr);
    tm* ltm = localtime(&now);
    
    ostringstream oss;
    oss << (1900 + ltm->tm_year) << "-"
        << setw(2) << setfill('0') << (1 + ltm->tm_mon) << "-"
        << setw(2) << setfill('0') << ltm->tm_mday;
    
    return oss.str();
}