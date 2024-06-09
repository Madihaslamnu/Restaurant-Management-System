#include "orderProcessing.cpp"
using namespace std;
// employee kyi password mai phele id then iska first and last name (all in small letters )for example
// id=100, First name=madiha , Last name=Aslam
// Password= 100madihaaslam
class AuthenticationAcessControl
{
public:
    bool AuthenticateUser(string ID, string passsword)
    {
        unsigned int enteredPassword = Hash(passsword);

        ifstream employeeFile("Employeedata.txt");
        if (!employeeFile)
        {
            cerr << "Error in openeing file" << endl;
            return false;
        }
        string line;
        while (getline(employeeFile, line))
        {
            stringstream ss(line);
            string role, fileID, name, salary, filePassword;
            getline(ss, fileID, ',');
            getline(ss, role, ',');
            getline(ss, name, ',');
            getline(ss, salary, ',');
            getline(ss, filePassword, ',');
            if (fileID == ID)
            {
                unsigned int file_Password;
                try
                {
                    file_Password = stoul(filePassword);
                }
                catch (invalid_argument &e)
                {
                    cerr << "Error: Invalid hashed password format." << endl;
                    employeeFile.close();
                    return false;
                }
                catch (out_of_range &e)
                {
                    cerr << "Error: Hashed password out of range for unsigned int." << endl;
                    employeeFile.close();
                    return false;
                }
                if (file_Password == enteredPassword)
                {
                    employeeFile.close();
                    return true;
                }
                else
                {
                    cout << "Incorrect password" << endl;
                    return false;
                }
            }
        }
        employeeFile.close();
        cout << "" << ID << " not found " << endl;
        return false;
    }
    unsigned int Hash(string data)
    {
        unsigned int result = 0;
        for (unsigned int ch : data)
            result = ch + (result << 4) + (result << 10) - result;
        return result;
    }
};
class Employee : public Validation
{
protected:
    string loginid;
    string role;
    string _name;
    double salary;
    string password;
    AuthenticationAcessControl a;

public:
    Employee() {}
    Employee(string _loginId, string _role, string name, double _salary, string _password) : loginid(_loginId), role(_role), _name(name), salary(_salary), password(_password) {}
    string getLoginId()
    {
        return loginid;
    }
    string getrole()
    {
        return role;
    }
    string getName()
    {
        return _name;
    }
    double getSalary()
    {
        return salary;
    }
    string getPassword()
    {
        return password;
    }
    // checking id that if it already exist or not
    bool checkID(string id)
    {
        try
        {
            ifstream inputFile("Employeedata.txt");
            if (!inputFile.is_open())
            {
                cerr << "Error opening file for reading!" << endl;
                return false;
            }
            string line;
            while (getline(inputFile, line))
            {
                stringstream ss(line);
                string token;
                getline(ss, token, ',');
                if (token == id)
                {
                    inputFile.close();
                    return true;
                }
            }
            inputFile.close();
        }
        catch (exception &error)
        {
            cerr << "Exception occurred: " << error.what() << endl;
        }
        return false;
    }
    bool Valid (string name)override
    {
        for (char c : name)
        {
            if (!isalpha(c) && !isspace(c))
            {
                return false;
            }
        }
        return true;
    }
    // ADD
    void addEmployee()
    {
        try
        {
            ofstream file("Employeedata.txt", ios::app);
            if (!file.is_open())
            {
                cerr << "Error opening file for writing!" << endl;
                return;
            }
            file.seekp(0, ios::end);
            if (file.tellp() == 0)
            {
                file << "=========== EMPLOYEE DATA =========\n";
                file << "Login ID,Role,Name,Salary,Password\n";
            }
            cout << "Enter login ID: ";
            cin >> loginid;
             if (checkID(loginid))
            {
                cout << "Employee with ID " << loginid << " already exist.Please choose a different ID" << endl;
                return;
            }
            cout << "Enter role: ";
            cin >> role;
            while (true)
            {
                cout << "Enter name: ";
                cin >> _name;
                if (Valid(_name))
                {
                    break;
                }
                else
                {
                    cout << "Invalid name, please enter again :)" << endl;
                }
            }
            cout << "Enter salary: ";
            cin >> salary;
            cout << "Enter password: ";
            cin >> password;
           
            unsigned int hashPassword = a.Hash(password);
            file << loginid << "," << role << "," << _name << "," << salary << "," << hashPassword << "\n";
            cout << "Employee added successfully." << endl;
            file.close();
        }
        catch (exception &error)
        {
            cerr << "Exception occurred: " << error.what() << endl;
        }
    }
    // REMOVE
    void removeEmployee()
    {
        try
        {
            string id;
            cout << "Enter ID  of employee you wnat to remove: " << endl;
            cin >> id;
            ifstream inputFile("Employeedata.txt");
            if (!inputFile.is_open())
            {
                cerr << "Error opening file for reading!" << endl;
                return;
            }
            vector<string> lines;
            string line;
            bool found = false;
            while (getline(inputFile, line))
            {
                stringstream ss(line);
                string token;
                getline(ss, token, ',');
                if (token != id)
                {
                    lines.push_back(line);
                }
                else
                {
                    found = true;
                }
            }
            inputFile.close();
            if (!found)
            {
                cout << "Employee with ID '" << id << "' not found." << endl;
                return;
            }
            ofstream outputFile("employeedata.txt");
            if (!outputFile.is_open())
            {
                cerr << "Error opening file for writing!" << endl;
                return;
            }
            for (const auto &line : lines)
            {
                outputFile << line << endl;
            }
            outputFile.close();
            cout << "Employee with ID '" << id << "' removed from the file." << endl;
        }
        catch (exception &error)
        {
            cerr << "Exception occurred: " << error.what() << endl;
        }
    }
    // UPDATE
    void updateEmployeeInfo()
    {
        try
        {
            cout << "Enter ID of employee you want to update: ";
            string ID;
            cin >> ID;
            ifstream inputFile("Employeedata.txt");
            if (!inputFile.is_open())
            {
                cerr << "Error opening file for reading!" << endl;
                return;
            }
            vector<string> lines;
            string line;
            bool found = false;
            while (getline(inputFile, line))
            {
                stringstream ss(line);
                string token;
                getline(ss, token, ',');
                if (token == ID)
                {
                    found = true;
                    string updatedline = token;
                    cout << "Enter role: ";
                    cin >> token;
                    updatedline += "," + token + ",";
                    while (true)
                    {
                        cout << "Enter name: ";
                        cin >> token;
                        if (Valid(token))
                        {
                            break;
                        }
                        else
                        {
                            cout << "Invalid name, please enter again :)" << endl;
                        }
                    }
                    updatedline += token + ",";
                    cout << "Enter new salary: ";
                    cin >> token;
                    updatedline += token + ",";
                    cout << "Enter new password: ";
                    cin >> token;
                    unsigned int hashedPssword = a.Hash(token);
                    updatedline += to_string(hashedPssword);
                    lines.push_back(updatedline);
                }
                else
                {
                    lines.push_back(line);
                }
            }
            inputFile.close();
            if (!found)
            {
                cout << "Employee with ID '" << ID << "' not found." << endl;
                return;
            }
            ofstream outputFile("employeedata.txt");
            if (!outputFile.is_open())
            {
                cerr << "Error opening file for writing!" << endl;
                return;
            }
            for (const auto &line : lines)
            {
                outputFile << line << endl;
            }
            outputFile.close();
            cout << "Employee with ID '" << ID << "' updated successfully." << endl;
        }
        catch (exception &error)
        {
            cerr << "Exception occurred: " << error.what() << endl;
        }
    }
    // DISPLAY
    void display_EmployeeData()
    {
        try
        {
            ifstream file("Employeedata.txt");
            if (!file.is_open())
            {
                cerr << "Error opening file for reading!" << endl;
                return;
            }
            string line;
            cout << "All Employees:" << endl;
            while (getline(file, line))
            {
                cout << line << endl;
            }
            file.close();
        }
        catch (exception &error)
        {
            cerr << "Exception occurred: " << error.what() << endl;
        }
    }
};
class Restaurant_Owner : public Employee
{
public:
    Restaurant_Owner() {}
    Restaurant_Owner(string _loginId, string _role, string _name, double _salary, string _password) : Employee(_loginId, _role, _name, _salary, _password) {}
    int displayMenu()
    {
        try
        {
            int owner_option;
            cout << ">>>>>>>>>>>>>>>>>>>>>    Login = Owner   <<<<<<<<<<<<<<<<" << endl;
            cout << "---------------------------------" << endl;
            cout << "1. Add Employee " << endl;
            cout << "2. Remove Employee " << endl;
            cout << "3. Update Employee " << endl;
            cout << "4. Display Employee data" << endl;
            cout << "5. Generate Customer feedback report" << endl;
            cout << "6. Generate Sales report"<<endl;
            cout << "7. Logout " << endl;
            cout << "Your option ......" << endl;
            cin >> owner_option;
            if (owner_option < 1 || owner_option > 7)
            {
                throw invalid_argument("Invalid option! Please enter a number between 1 and 7.");
            }
            return owner_option;
        }
        catch (exception &error)
        {
            cout << "Error occurred: " << error.what() << endl;
            return -1;
        }
    }
};

class Manager : public Employee
{
public:
    Manager() {}
    Manager(string _loginId, string _role, string _name, double _salary, string _password) : Employee(_loginId, _role, _name, _salary, _password) {}
    int displayMenu()
    {
        try
        {
            int manager_option;
            cout << ">>>>>>>>>>>>>>>>>>>>>    Login = MANAGER   <<<<<<<<<<<<<<<<" << endl;
            cout << "---------------------------------" << endl;
            cout << "1. Inventory managemnet " << endl;
            cout << "2. Menu managemnet " << endl;
            cout << "3 . Logout " << endl;
            cout << "Enter your option: " << endl;
            cin >> manager_option;
            if (manager_option < 1 || manager_option > 3)
            {
                throw invalid_argument("Invalid option! Please enter a number between 1 and 3.");
            }
            return manager_option;
        }
        catch (exception &error)
        {
            cout << "Error occurred: " << error.what() << endl;
            return -1;
        }
    }
};
class Customer
{
public:
    int displayMenu()
    {
        try
        {
            int customer_option;
            cout << " >>>>>>>>>>>>>>>>>    Login = CUSTOMER    <<<<<<<<<<<<<<<<" << endl;
            cout << "Main Menu >" << endl;
            cout << "---------------------------------" << endl;
            cout << "1. Display Menu " << endl;
            cout << "2. Place order generate bill" << endl;
            cout << "3. Modify order and generate bill " << endl;
            cout << "4. Cancel order " << endl;
            cout << "5.Customer feedback " << endl;
            cout << "6. Logout " << endl;
            cout << "Enter Your Option " << endl;
            cin >> customer_option;
            if (customer_option < 1 || customer_option > 6)
            {
                throw invalid_argument("Invalid option! Please enter a number between 1 and 6.");
            }
            return customer_option;
        }
        catch (exception &error)
        {
            cout << "Error occurred: " << error.what() << endl;
            return -1;
        }
    }
};
class Cashier : public Employee
{
    string Customer_First_name;
    string Customer_Last_name;
    string Customer_cell_number;
    string Customer_mode_of_payment;
    double Customer_total_bill;

public:
    Cashier() {}
    Cashier(string _loginId, string _role, string _name, double _salary, string _password, string _CustomerFirst_name, string _CustomerLast_name, string _Customercell_number, string _Customermode_of_payment, double _Customertotal_bill) : Employee(_loginId, _role, _name, _salary, _password), Customer_First_name(_CustomerFirst_name), Customer_Last_name(_CustomerLast_name), Customer_cell_number(_Customercell_number), Customer_mode_of_payment(_Customermode_of_payment), Customer_total_bill(_Customertotal_bill) {}
    int displayMenu()
    {
        try
        {
            int cashier_option;
            cout << " >>>>>>>>>>>>>>>>>    Login = CASHIER    <<<<<<<<<<<<<<<<" << endl;
            cout << "Main Menu >" << endl;
            cout << "---------------------------------" << endl;
            cout << "1. Add New Customer " << endl;
            cout << "2. View Customer Record " << endl;
            cout << "3. Logout " << endl;
            cout << "Enter Your Option " << endl;
            cin >> cashier_option;
            if (cashier_option < 1 || cashier_option > 3)
            {
                throw invalid_argument("Invalid option! Please enter a number between 1 and 3.");
            }
            return cashier_option;
        }
        catch (exception &error)
        {
            cout << "Error occurred: " << error.what() << endl;
            return -1;
        }
    }
    // ADDING CUSTOMER
    void add_details_of_customer()
    {
        ofstream file("Customerdata.txt", ios::app);
        if (!file.is_open())
        {
            cerr << "Error opening file for writing!" << endl;
            return;
        }
        file.seekp(0, ios::end);
        if (file.tellp() == 0)
        {
            file << "=========== CUSTOMER DATA =========\n";
            file << "Name,Cell Number, Mode of payment\n";
        }
        while (true)
        {
            cout << "Enter first name: ";
            cin >> Customer_First_name;
            ;
            if (Valid(Customer_First_name))
            {
                break;
            }
            else
            {
                cout << "Invalid name, please enter again :)" << endl;
            }
        }

        while (true)
        {
            cout << "Enter last name: ";
            cin >> Customer_Last_name;
            ;
            if (Valid(Customer_Last_name))
            {
                break;
            }
            else
            {
                cout << "Invalid name, please enter again :)" << endl;
            }
        }
        cout << "Enter cell number: ";
        cin >> Customer_cell_number;
        if (validPhoneNumber(Customer_cell_number))
        {
            cout << "Valid phone number!" << endl;
        }
        else
        {
            cout << "Invalid phone number!" << endl;
        }

        cout << "Enter mode of payment: ";
        cin >> Customer_mode_of_payment;
        file << Customer_First_name << "," << Customer_Last_name << "," << Customer_cell_number << "," << Customer_mode_of_payment << "\n";
        cout << "Customer added successfully." << endl;
        file.close();
    }
    // DISPALYING CUSTOMER
    void display_CustomerData()
    {
        ifstream file("Customerdata.txt");
        if (!file.is_open())
        {
            cerr << "Error opening file for reading!" << endl;
            return;
        }
        string line;
        while (getline(file, line))
        {
            cout << line << endl;
        }
        file.close();
    }
};
