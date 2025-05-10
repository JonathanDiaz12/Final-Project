#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_ITEMS = 100;

// Struct to represent a shopping item
struct Item {
    string name;
    int quantity;
};

// Function to display the main menu and get user choice
int displayMenu() {
    cout << "\nShopping List Menu:\n";
    cout << "1. View Shopping List\n";
    cout << "2. Add Item\n";
    cout << "3. Remove Item\n";
    cout << "4. Save List\n";
    cout << "5. Load List\n";
    cout << "6. Exit\n";
    cout << "Enter your choice (1-6): ";
    int choice;
    cin >> choice;
    if (cin.fail() || choice < 1 || choice > 6) {
        cin.clear();
        cin.ignore(1000, '\n');
        return -1; // Invalid input
    }
    return choice;
}

// Function to add an item (overloaded for default quantity)
int addItem(Item list[], int count, string name, int quantity) {
    if (count >= MAX_ITEMS) return count;
    list[count].name = name;
    list[count].quantity = quantity;
    return count + 1;
}

int addItem(Item list[], int count, string name) {
    return addItem(list, count, name, 1); // Default quantity = 1
}

// Function to display the list
int displayList(Item list[], int count) {
    if (count == 0) {
        cout << "\nYour shopping list is empty.\n";
        return 0;
    }
    cout << "\nShopping List:\n";
    for (int i = 0; i < count; i++) {
        cout << i + 1 << ". " << list[i].name << " (x" << list[i].quantity << ")\n";
    }
    return count;
}

// Function to remove an item
int removeItem(Item list[], int count, int index) {
    if (index < 0 || index >= count) return count;
    for (int i = index; i < count - 1; i++) {
        list[i] = list[i + 1];
    }
    return count - 1;
}

// Function to save list to file
int saveList(Item list[], int count, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) return -1;
    for (int i = 0; i < count; i++) {
        file << list[i].name << "," << list[i].quantity << "\n";
    }
    file.close();
    return count;
}

// Function to load list from file
int loadList(Item list[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) return 0;
    string line;
    int count = 0;
    while (getline(file, line) && count < MAX_ITEMS) {
        size_t comma = line.find(',');
        if (comma != string::npos) {
            list[count].name = line.substr(0, comma);
            list[count].quantity = stoi(line.substr(comma + 1));
            count++;
        }
    }
    file.close();
    return count;
}

int main() {
    Item shoppingList[MAX_ITEMS];
    int itemCount = 0;
    string filename = "shopping_list.txt";
    bool running = true;

    while (running) {
        int choice = displayMenu();
        switch (choice) {
            case 1:
                displayList(shoppingList, itemCount);
                break;
            case 2: {
                string name;
                int quantity;
                cout << "Enter item name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter quantity: ";
                cin >> quantity;
                if (cin.fail() || quantity < 1) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid quantity.\n";
                    break;
                }
                itemCount = addItem(shoppingList, itemCount, name, quantity);
                cout << "Item added.\n";
                break;
            }
            case 3: {
                displayList(shoppingList, itemCount);
                cout << "Enter item number to remove: ";
                int index;
                cin >> index;
                if (cin.fail() || index < 1 || index > itemCount) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid selection.\n";
                    break;
                }
                itemCount = removeItem(shoppingList, itemCount, index - 1);
                cout << "Item removed.\n";
                break;
            }
            case 4:
                if (saveList(shoppingList, itemCount, filename) >= 0)
                    cout << "List saved to file.\n";
                else
                    cout << "Error saving file.\n";
                break;
            case 5:
                itemCount = loadList(shoppingList, filename);
                cout << "List loaded from file.\n";
                break;
            case 6:
                running = false;
                break;
            default:
                cout << "Invalid option. Please try again.\n";
        }
    }

    return 0;
}
