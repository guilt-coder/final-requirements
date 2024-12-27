#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include <stdexcept>

using namespace std;

class MenuItem {
public:
    string name;
    double price;

    MenuItem(string n = "", double p = 0.0) : name(n), price(p) {}
};

class Order {
private:
    int orderQuantities[5] = {0};
    double total = 0.0;
    double taxRate = 0.1;
    double discount = 0.0;

public:
    void addItem(const MenuItem& item, int index) {
        orderQuantities[index]++;
        total += item.price;
    }

    void applyDiscount(double discountPercentage) {
        discount = total * (discountPercentage / 100);
    }

    double calculateTax() const {
        return (total - discount) * taxRate;
    }

    double calculateTotalWithTax() const {
        return (total - discount) + calculateTax();
    }

    void displayOrder(const MenuItem menuItems[], int menuSize) {
        cout << "\nYour Order:\n";
        cout << "-----------------------------\n";
        bool hasItems = false;
        for (int i = 0; i < menuSize; i++) {
            if (orderQuantities[i] > 0) {
                hasItems = true;
                cout << i + 1 << ". " << setw(20) << left << menuItems[i].name
                     << " x" << orderQuantities[i] << " $ "
                     << fixed << setprecision(2) << menuItems[i].price * orderQuantities[i] << "\n";
            }
        }
        if (!hasItems) {
            cout << "No items ordered yet!\n";
        } else {
            cout << "-----------------------------\n";
            cout << "Subtotal: $ " << fixed << setprecision(2) << total << "\n";
            cout << "Discount: $ " << fixed << setprecision(2) << discount << "\n";
            cout << "Tax: $ " << fixed << setprecision(2) << calculateTax() << "\n";
            cout << "Total: $ " << fixed << setprecision(2) << calculateTotalWithTax() << "\n";
        }
    }

    void saveBillToFile(const MenuItem menuItems[], int menuSize) {
        ofstream billFile("bill.txt");
        if (!billFile) {
            cout << "Error saving the bill to file!\n";
            return;
        }

        billFile << "Your Order:\n";
        billFile << "-----------------------------\n";
        for (int i = 0; i < menuSize; i++) {
            if (orderQuantities[i] > 0) {
                billFile << menuItems[i].name << " x" << orderQuantities[i] << " $ "
                         << fixed << setprecision(2) << menuItems[i].price * orderQuantities[i] << "\n";
            }
        }
        billFile << "-----------------------------\n";
        billFile << "Subtotal: $ " << fixed << setprecision(2) << total << "\n";
        billFile << "Discount: $ " << fixed << setprecision(2) << discount << "\n";
        billFile << "Tax: $ " << fixed << setprecision(2) << calculateTax() << "\n";
        billFile << "Total: $ " << fixed << setprecision(2) << calculateTotalWithTax() << "\n";
        billFile.close();

        cout << "Bill saved to 'bill.txt'!\n";
    }
};

// Main program
int main() {
    MenuItem menuItems[5] = {
        MenuItem("Burger", 5.99),
        MenuItem("Pizza", 8.49),
        MenuItem("Pasta", 7.25),
        MenuItem("Salad", 4.99),
        MenuItem("Soda", 1.99)
    };

    vector<Order> orders;
    int choice;

    do {
        cout << "\n--- Restaurant Menu System ---\n";
        cout << "1. View Menu\n";
        cout << "2. Place New Order\n";
        cout << "3. View All Orders\n";
        cout << "4. Save Last Order to File\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

        case 1: {
            cout << "\nMenu:\n";
            cout << "-----------------------------\n";
            for (int i = 0; i < 5; i++) {
                cout << i + 1 << ". " << setw(20) << left << menuItems[i].name
                     << " $ " << fixed << setprecision(2) << menuItems[i].price << "\n";
            }
            cout << "-----------------------------\n";
            break;
        }

        case 2: {
            Order newOrder;
            char anotherOrder = 'y';
            do {
                cout << "\nEnter the item number to order: ";
                int itemNumber;
                cin >> itemNumber;

                if (itemNumber > 0 && itemNumber <= 5) {
                    newOrder.addItem(menuItems[itemNumber - 1], itemNumber - 1);
                    cout << menuItems[itemNumber - 1].name << " added to your order!\n";
                } else {
                    cout << "Invalid menu item. Please try again.\n";
                }

                cout << "Do you want to add another item? (y/n): ";
                cin >> anotherOrder;
            } while (anotherOrder == 'y' || anotherOrder == 'Y');

            cout << "Enter discount percentage (if any): ";
            double discount;
            cin >> discount;
            newOrder.applyDiscount(discount);

            orders.push_back(newOrder);
            cout << "Order placed successfully!\n";
            break;
        }
        
        case 3: {
            if (orders.empty()) {
                cout << "No orders placed yet!\n";
            } else {
                for (size_t i = 0; i < orders.size(); i++) {
                    cout << "\nOrder " << i + 1 << ":\n";
                    orders[i].displayOrder(menuItems, 5);
                }
            }
            break;
        }
        
        case 4: {
            if (orders.empty()) {
                cout << "No orders to save!\n";
            } else {
                orders.back().saveBillToFile(menuItems, 5);
            }
            break;
        }
        
        case 5:
            cout << "Thank you for visiting! Goodbye.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice !=5);

    return 0;
}
// end of program