#include "BillingAndReport.cpp"
// no need to include inventory it will be called from menuManagement
// whatever functions of inventory are do it usually make an obj of inventory than call functions
// dont include one class/file twice it will cause errors
// zains file need to be updated

void welcomeheader()
{
    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
    cout << "\n<<<<<<<<<<<<<<<<<<  WELCOME TO ZAMATA <<<<<<<<<<<<<<<<<<<<<\n"
         << endl;
    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
}

int main()
{
    Manager _manager;
    Cashier _cashier;
    Restaurant_Owner _owner;
    Customer _customer;
    Employee Employee1;
    AuthenticationAcessControl au;
    BillingPayment _payment;
    Reporting _report;
    MenuManagement m;
    OrderProcessing _order;
    Inventory _inventory;

    string userid, password, _role;
    bool loggedIn = false;

    while (true)
    {
        cout << endl;
        cout << endl;

        welcomeheader();
        cout << endl;
        cout << endl;

        cout << "Enter role('Customer' or 'Manager' or 'Owner' or 'Cashier' ): " << endl;
        cin >> _role;

        if (_role != "Customer" && _role != "customer" && _role != "Manager" && _role != "manager" && _role != "Owner" && _role != "owner" && _role != "Cashier" && _role != "cashier")
        {
            cout << "Invalid user role! Please enter a valid role." << endl;
            continue; //  it will continue to prompt for the role
        }

        if (_role != "Customer" && _role != "customer")
        {
            cout << "\nEnter user ID ( enter integer): " << endl;
            cin >> userid;
            cout << "Enter Password: ";
            cin >> password;
            if (!au.AuthenticateUser(userid, password))
            {
                cout << "Authentication failed!" << endl;
                continue;
            }
            cout << "User login successfully!" << endl;
            loggedIn = true;
        }
        else
        {
            loggedIn = true; // Directly set to true for customers
        }

        while (loggedIn)
        {
            if (_role == "Manager" || _role == "manager")
            {
                int Manager_option = _manager.displayMenu();
                switch (Manager_option)
                {
                case 1:
                {
                    // Inventory Management
                    int inventoryOption;
                    string items[100];
                    cout << "1. Add items\n2. Restock items\n3. Show items that need to be restock\n4. View inventory\nEnter option: ";
                    cin >> inventoryOption;
                    switch (inventoryOption)
                    {
                    case 1:
                    {
                        cout << "Enter item name: ";
                        string itemName;
                        cin >> itemName;

                        cout << "Enter item quantity: ";
                        int itemQuantity;
                        cin >> itemQuantity;

                        cout << "Enter item price: ";
                        double itemPrice;
                        cin >> itemPrice;

                        cout << "Enter item stock: ";
                        char itemStock;
                        cin >> itemStock;

                        _inventory.addItems(itemName, itemQuantity, itemPrice, itemStock);
                        break;
                    }
                    case 2:
                        _inventory.restock();
                        break;
                    case 3:
                        _inventory.show();
                        break;
                    case 4:
                        _inventory.view();
                        break;
                    case 5:
                        loggedIn = false; // Logout
                        break;
                    default:
                        cout << "Invalid option!" << endl;
                        break;
                    }
                    break;
                }
                case 2:
                {
                    // menu Management
                    int stockOption;
                    cout << "1. Add Menu\n2. Remove Menu\n3. Update Menu\n4. Display Menu\n5. logout\n Enter option: ";
                    cin >> stockOption;
                    switch (stockOption)
                    {
                    case 1:
                        m.additems();
                        break;
                    case 2:
                        m.RemoveItems();
                        break;
                    case 3:
                        m.UpdateItem();
                        break;
                    case 4:
                        m.displayMenu();
                        break;
                    case 5:
                        loggedIn = false; // Logout
                        break;
                    default:
                        cout << "Invalid option!" << endl;
                        break;
                    }
                    break;
                }

                case 3:
                    loggedIn = false; // Logout
                    break;
                }
            }

            else if (_role == "Owner" || _role == "owner")
            {
                int owner_option = _owner.displayMenu();
                switch (owner_option)
                {
                case 1:
                    _owner.addEmployee();
                    break;
                case 2:
                    _owner.removeEmployee();
                    break;
                case 3:
                    _owner.updateEmployeeInfo();
                    break;
                case 4:
                    _owner.display_EmployeeData();
                    break;
                case 5:
                    _report.GenerateCustomerFeedbackReports();
                    break;
                case 6:
                    _report.GenerateSalesReport();
                    break;
                case 7:
                    loggedIn = false; // Logout
                    break;
                default:
                    break;
                }
            }
            else if (_role == "Cashier" || _role == "cashier")
            {
                int Cashier_option = _cashier.displayMenu();
                switch (Cashier_option)
                {
                case 1:
                    _cashier.add_details_of_customer();
                    break;
                case 2:
                    _cashier.display_CustomerData();
                    break;
                case 3:
                    loggedIn = false; // Logout
                    break;
                default:
                    break;
                }
            }

            else if (_role == "Customer" || _role == "customer")
            {
                int Customer_option = _customer.displayMenu();

                switch (Customer_option)
                {
                case 1:
                    m.displayMenu();
                    break;
                case 2:
                {
                    vector<pair<string, int>> orderList = _order.placeOrder();
                    _payment.GenerateBill(orderList);
                    break;
                }
                case 3:
                {

                    vector<pair<string, int>> orderList = _order.modifyOrder();
                    _payment.GenerateBill(orderList);
                    break;
                }
                case 4:
                    _order.cancelOrder();
                    break;
                case 5:
                    _payment.CustomerFeedback();
                    break;
                case 6:
                    loggedIn = false; // Logout
                    break;
                default:
                    break;
                }
            }

            if (!loggedIn)
            {
                cout << "Logged out successfully!" << endl;
                break; // Break out of inner loop and return to login
            }
        }
    }
}
