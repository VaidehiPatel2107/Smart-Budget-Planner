#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// ─────────────────────────────────────────
//  STRUCT: Holds one budget category
// ─────────────────────────────────────────
struct Category {
    string name;
    double limit;
    double spent;
};

// ─────────────────────────────────────────
//  FUNCTION: Add a new category
// ─────────────────────────────────────────
void addCategory(vector<Category>& categories) {
    Category c;
    cout << "\nEnter category name (e.g. Food, Travel): ";
    cin >> c.name;
    cout << "Enter spending limit for " << c.name << ": Rs. ";
    cin >> c.limit;
    c.spent = 0;
    categories.push_back(c);
    cout << "Category '" << c.name << "' added with limit Rs. " << c.limit << "\n";
}

// ─────────────────────────────────────────
//  FUNCTION: Add an expense to a category
// ─────────────────────────────────────────
void addExpense(vector<Category>& categories) {
    if (categories.empty()) {
        cout << "\nNo categories found! Please add a category first.\n";
        return;
    }

    cout << "\nAvailable Categories:\n";
    for (int i = 0; i < categories.size(); i++) {
        cout << "  " << i + 1 << ". " << categories[i].name << "\n";
    }

    int choice;
    cout << "Select category number: ";
    cin >> choice;

    if (choice < 1 || choice > categories.size()) {
        cout << "Invalid choice!\n";
        return;
    }

    double amount;
    cout << "Enter amount spent (Rs.): ";
    cin >> amount;

    categories[choice - 1].spent += amount;

    double remaining = categories[choice - 1].limit - categories[choice - 1].spent;

    cout << "\nExpense added!\n";

    // ── ALERTS ──
    if (categories[choice - 1].spent > categories[choice - 1].limit) {
        cout << "⚠️  WARNING: You have EXCEEDED the limit for '"
             << categories[choice - 1].name << "' by Rs. "
             << (categories[choice - 1].spent - categories[choice - 1].limit) << "!\n";
    } else if (remaining <= categories[choice - 1].limit * 0.2) {
        cout << "⚠️  ALERT: Only Rs. " << remaining
             << " remaining in '" << categories[choice - 1].name << "'. Almost at limit!\n";
    }
}

// ─────────────────────────────────────────
//  FUNCTION: Show full budget summary
// ─────────────────────────────────────────
void showSummary(const vector<Category>& categories) {
    if (categories.empty()) {
        cout << "\nNo categories to show.\n";
        return;
    }

    cout << "\n";
    cout << "========================================\n";
    cout << "        BUDGET SUMMARY\n";
    cout << "========================================\n";
    cout << left << setw(12) << "Category"
         << setw(10) << "Limit"
         << setw(10) << "Spent"
         << setw(10) << "Remaining"
         << "Status\n";
    cout << "----------------------------------------\n";

    double totalLimit = 0, totalSpent = 0;

    for (const auto& c : categories) {
        double remaining = c.limit - c.spent;
        string status;

        if (c.spent > c.limit)
            status = "OVER LIMIT!";
        else if (remaining <= c.limit * 0.2)
            status = "Near Limit";
        else
            status = "OK";

        cout << left << setw(12) << c.name
             << setw(10) << c.limit
             << setw(10) << c.spent
             << setw(10) << remaining
             << status << "\n";

        totalLimit += c.limit;
        totalSpent += c.spent;
    }

    cout << "----------------------------------------\n";
    cout << left << setw(12) << "TOTAL"
         << setw(10) << totalLimit
         << setw(10) << totalSpent
         << setw(10) << (totalLimit - totalSpent) << "\n";
    cout << "========================================\n";
}

// ─────────────────────────────────────────
//  MAIN FUNCTION
// ─────────────────────────────────────────
int main() {
    vector<Category> categories;
    int choice;

    cout << "====================================\n";
    cout << "   SMART BUDGET PLANNER\n";
    cout << "====================================\n";

    while (true) {
        cout << "\n--- MAIN MENU ---\n";
        cout << "1. Add Category\n";
        cout << "2. Add Expense\n";
        cout << "3. View Budget Summary\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addCategory(categories); break;
            case 2: addExpense(categories);  break;
            case 3: showSummary(categories); break;
            case 4:
                cout << "\nGoodbye! Track your expenses wisely!\n";
                return 0;
            default:
                cout << "Invalid option. Try again.\n";
        }
    }

    return 0;
}
