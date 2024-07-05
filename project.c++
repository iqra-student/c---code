#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <fstream>
#include <limits>
#include <conio.h>
#include <windows.h>
#include <vector>
using namespace std;
class Admin;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

const char USER_LOGIN = '1';
const char ADMIN_LOGIN = '2';
const char EXIT_PROGRAM = '3';

template <typename T>
std::string to_string(const T &value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

class Invoice
{
private:
    string timestamp;
    string fuelType;
    double amount;
    double volume;
    double pricePerUnit;
    string date;

public:
    Invoice(string fuel, double amt, double vol, double price) : fuelType(fuel), amount(amt), volume(vol), pricePerUnit(price)
    {
        // Generate timestamp
        time_t now = time(0);
        tm *ltm = localtime(&now);
        stringstream ss;
        ss << (ltm->tm_year + 1900) << "-" << (ltm->tm_mon + 1) << "-" << ltm->tm_mday;
        date = ss.str();
        ss.str("");
        ss << setw(2) << setfill('0') << ltm->tm_hour << ":" << setw(2) << setfill('0') << ltm->tm_min << ":" << setw(2) << setfill('0') << ltm->tm_sec;
        timestamp = ss.str();
        ofstream invoices("invoices.csv", ios::app);
        invoices << timestamp << "," << date << "," << fuel << "," << amt << "," << vol << endl;
        invoices.close();
    }

    void printInvoice() const
    {
        SetConsoleTextAttribute(h, 14);
        cout << "\n\n\n\t\t\t\t ========== Invoice ==========" << endl;
        cout << "\t\t\t\t Timestamp: " << timestamp << endl;
        cout << "\t\t\t\t Date: " << date << endl;
        cout << "\t\t\t\t Fuel Type: " << fuelType << endl;
        cout << "\t\t\t\t Amount (Rs): " << amount << endl;
        cout << "\t\t\t\t Volume (Liters/KGs): " << volume << endl;
        cout << "\t\t\t\t Price per Unit (Rs/Liter/KG): " << pricePerUnit << endl;
        cout << "\t\t\t\t =============================" << endl;
    }
    double getAmount() const
    {
        return amount;
    }

    double getVolume() const
    {
        return volume;
    }
};

class Salaries
{
private:
    double fillerManSalary;
    double managerSalary;
    double securityGuardSalary;
    double cashierSalary;
    double supervisorSalary;

public:
    Salaries(double fillerMan = 2000.0, double manager = 5000.0, double securityGuard = 1500.0, double cashier = 3000.0, double supervisor = 4000.0)
        : fillerManSalary(fillerMan), managerSalary(manager), securityGuardSalary(securityGuard), cashierSalary(cashier), supervisorSalary(supervisor) {}

    void displaySalaries() const
    {
        cout << "Salaries:" << endl;
        cout << "Filler Man: $" << fillerManSalary << endl;
        cout << "Manager: $" << managerSalary << endl;
        cout << "Security Guard: $" << securityGuardSalary << endl;
        cout << "Cashier: $" << cashierSalary << endl;
        cout << "Supervisor: $" << supervisorSalary << endl;
    }
};

class Shift
{
private:
    time_t startTime; // Start time of the shift
    int duration;     // Duration of the shift in seconds
    char shiftName;   // Shift name (A or B)

public:
    Shift()
    {
        startTime = time(NULL);  // Initialize start time to current time
        duration = 12 * 60 * 60; // 12 hours in seconds
        determineShift();
    }

    // Check if it's time to change the shift
    bool isTimeToChange()
    {
        time_t currentTime = time(NULL);
        return (currentTime - startTime >= duration);
    }

    // Change the shift
    void changeShift()
    {
        cout << "Changing shift..." << endl;
        startTime = time(NULL); // Update start time to current time
        determineShift();
    }

    // Determine the current shift
    void determineShift()
    {
        struct tm *timeinfo;
        timeinfo = localtime(&startTime);
        int hour = timeinfo->tm_hour;

        // Shift A: 00:00 to 11:59
        // Shift B: 12:00 to 23:59
        if (hour < 12)
        {
            shiftName = 'A';
        }
        else
        {
            shiftName = 'B';
        }
    }

    // Get the shift name
    char getShiftName() const
    {
        return shiftName;
    }

    // Get the real-world time in AM/PM format
    string getRealTime() const
    {
        struct tm *timeinfo;
        timeinfo = localtime(&startTime);
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%I:%M %p", timeinfo);
        return string(buffer);
    }
};

class Inventory
{
private:
    double petrolStock;
    double dieselStock;
    double CNGStock;

public:
    Inventory(double petrol = 25000.0, double diesel = 25000.0, double CNG = 5000.0)
        : petrolStock(petrol), dieselStock(diesel), CNGStock(CNG) {}

    void updateStock(double petrol, double diesel, double CNG)
    {
        // Update stock
        petrolStock += petrol;
        dieselStock += diesel;
        CNGStock += CNG;
    }

    void viewStock() const
    {
        int ch;
        cout << "Current Stock Levels:" << endl;
        cout << "Petrol: " << petrolStock << " liters" << endl;
        cout << "Diesel: " << dieselStock << " liters" << endl;
        cout << "CNG: " << CNGStock << " liters" << endl;

        if (petrolStock < 5000)
        {
            cout << "Your Petrol Stock is Less than 5000 litres " << endl;
            cout << "Would you want to Order 25000 litres Petrol for Tank Refill ( YES(1) || NO(2) ) ";
            cin >> ch;
            if (ch == 1)
            {
                cout << "New Stock Ordered." << endl;
            }
            else if (ch == 2)
            {
                cout << "Not Ordered." << endl;
            }
        }

        if (dieselStock < 5000)
        {
            cout << "Your Diesel Stock is Less than 5000 litres " << endl;
            cout << "Would you want to Order 25000 litres Diesel for Tank Refill ( YES(1) || NO(2) ) ";
            cin >> ch;
            if (ch == 1)
            {
                cout << "New Stcok Ordered." << endl;
            }
            else if (ch == 2)
            {
                cout << "Not Ordered." << endl;
            }
        }

        if (CNGStock < 2000)
        {
            cout << "Your CNG Stock is Less than 2500 litres " << endl;
            cout << "Would you want to Order 5000 litres CNG for Tank Refill ( YES(1) || NO(2) ) ";
            cin >> ch;
            if (ch == 1)
            {
                cout << "New Stcok Ordered." << endl;
            }
            else if (ch == 2)
            {
                cout << "Not Ordered." << endl;
            }
        }
    }
};

class Login
{
private:
    string username;
    string password;

public:
    Login(string u, string p) : username(u), password(p) {}

    bool authenticate(string enteredUsername, string enteredPassword)
    {
        return (username == enteredUsername && password == enteredPassword);
    }
};

class User
{
private:
    float current_petrol_price, current_diesel_price, current_cng_price;
    double total_petrol_refilled = 0, total_diesel_refilled = 0, total_cng_refilled = 0;
    double total_petrol_refilled_amt = 0, total_diesel_refilled_amt = 0, total_cng_refilled_amt = 0;
    Inventory &inventory;

public:
    User(Inventory &inv) : inventory(inv)
    {
        current_petrol_price = 294;
        current_diesel_price = 290;
        current_cng_price = 200;
        cout << "Current petrol price: " << current_petrol_price << endl;
        cout << "Current diesel price: " << current_diesel_price << endl;
        cout << "Current CNG price: " << current_cng_price << endl;
    }

    // User() {}
    void refillPetrol(Inventory &inventory, double current_petrol_price, Admin &admin);
    void refillDiesel(Inventory &inventory, double current_diesel_price, Admin &admin);
    void refillCNG(Inventory &inventory, double current_cng_price, Admin &admin);
    void showDetails()
    {
        cout << "=========================================================================" << endl;
        cout << "Petroleum Management Details:" << endl;
        cout << "Total liters of Petrol dispensed: " << total_petrol_refilled << endl;
        cout << "Total liters of Diesel dispensed: " << total_diesel_refilled << endl;
        cout << "Total KGs of CNG dispensed: " << total_cng_refilled << endl;
        cout << "Total money earned: " << total_petrol_refilled_amt + total_diesel_refilled_amt + total_cng_refilled_amt << " rs" << endl;
        cout << "=========================================================================" << endl;
    }
};
class Admin
{
private:
    double dailySalesPetrol;
    double dailySalesDiesel;
    double dailySalesCNG;
    double monthlySalesPetrol;
    double monthlySalesDiesel;
    double monthlySalesCNG;
    double fillerManSalary;
    double managerSalary;
    double securityGuardSalary;
    double cashierSalary;
    double supervisorSalary;
    double total_bills;
    int daysInMonth;

public:
    Admin() : dailySalesPetrol(0), dailySalesDiesel(0), dailySalesCNG(0),
              monthlySalesPetrol(0), monthlySalesDiesel(0), monthlySalesCNG(0),
              fillerManSalary(30000), managerSalary(150000), securityGuardSalary(25000), cashierSalary(60000), supervisorSalary(70000), total_bills(250000),
              daysInMonth(30) {}

    // Function declarations
    void displayMainMenu();
    bool isValidChoice(char choice);

    void recordDailySales(double petrol, double diesel, double cng);
    void updateMonthlySales();
    void viewDailySales();
    void viewMonthlySales();
    void calculateProfit();
    string getCurrentMonthAndYear();
    double getTotalSales() const;
    double getTotalExpenses() const;
    void writeMonthlyDataToCSV();
    void writeDailySalesToCSV();

    // Public member functions to retrieve monthly sales
    double getMonthlySalesPetrol() const { return monthlySalesPetrol; }
    double getMonthlySalesDiesel() const { return monthlySalesDiesel; }
    double getMonthlySalesCNG() const { return monthlySalesCNG; }

    void viewShift()
    {
        cout << "Viewing shift..." << endl;
        Shift shift; // Initialize shift

        // Output current shift and real-world time
        cout << "Current Shift: Shift " << shift.getShiftName() << endl;
        cout << "Current Time: " << shift.getRealTime() << endl;

        // Simulate time passing...
        // For demonstration purpose, you may need to change it to actual time passing mechanism

        // Check if it's time to change the shift
        if (shift.isTimeToChange())
        {
            shift.changeShift();
        }

        // Output current shift and real-world time again
        //        cout << "Updated Shift: Shift " << shift.getShiftName() << endl;
        //        cout << "Updated Time: " << shift.getRealTime() << endl;
    }

    void manageSalaries()
    {
        cout << "Managing salaries..." << endl;
        Salaries salary;
        salary.displaySalaries();
    }
};

void Admin::displayMainMenu()
{

    cout << "Choose an option:" << endl;
    cout << "1) Login as User" << endl;
    cout << "2) Login as Admin" << endl;
    cout << "3) Exit" << endl;
    cout << "===============================" << endl;
    cout << "Enter your choice: ";
}
// Function to validate user's choice
bool Admin::isValidChoice(char choice)
{
    return (choice == USER_LOGIN || choice == ADMIN_LOGIN || choice == EXIT_PROGRAM);
}
string getCurrentDate()
{
    // Get current time
    time_t now = time(0);

    // Convert to string
    tm *ltm = localtime(&now);
    int year = 1900 + ltm->tm_year;
    int month = 1 + ltm->tm_mon;
    int day = ltm->tm_mday;

    // Format the date as a string
    string currentDate = to_string(year) + "-" + (month < 10 ? "0" : "") + to_string(month) + "-" + (day < 10 ? "0" : "") + to_string(day);

    return currentDate;
}
void User::refillPetrol(Inventory &inventory, double current_petrol_price, Admin &admin)
{
    double refill_petrol_amt;
    cout << "Enter amount (rs) to be refilled for Petrol: ";
    cin >> refill_petrol_amt;

    double refill_petrol_volume = refill_petrol_amt / current_petrol_price;

    Invoice petrolInvoice("Petrol", refill_petrol_amt, refill_petrol_volume, current_petrol_price);
    petrolInvoice.printInvoice();

    inventory.updateStock(-refill_petrol_volume, 0, 0);
    admin.recordDailySales(refill_petrol_volume, 0, 0);
}

void User::refillDiesel(Inventory &inventory, double current_diesel_price, Admin &admin)
{
    double refill_diesel_amt;
    cout << "Enter amount (rs) to be refilled for Diesel: ";
    cin >> refill_diesel_amt;

    double refill_diesel_volume = refill_diesel_amt / current_diesel_price;

    Invoice dieselInvoice("Diesel", refill_diesel_amt, refill_diesel_volume, current_diesel_price);
    dieselInvoice.printInvoice();

    inventory.updateStock(0, -refill_diesel_volume, 0);
    admin.recordDailySales(0, refill_diesel_volume, 0);
}

void User::refillCNG(Inventory &inventory, double current_cng_price, Admin &admin)
{
    double refill_cng_amt;
    cout << "Enter amount (rs) to be refilled for CNG: ";
    cin >> refill_cng_amt;

    double refill_cng_volume = refill_cng_amt / current_cng_price;

    Invoice cngInvoice("CNG", refill_cng_amt, refill_cng_volume, current_cng_price);
    cngInvoice.printInvoice();

    inventory.updateStock(0, 0, -refill_cng_volume);
    admin.recordDailySales(0, 0, refill_cng_volume);
}
void Admin::recordDailySales(double petrol, double diesel, double cng)
{
    dailySalesPetrol += petrol;
    dailySalesDiesel += diesel;
    dailySalesCNG += cng;
}

void Admin::updateMonthlySales()
{
    // Calculate monthly sales by multiplying daily sales by number of days in a month
    monthlySalesPetrol = dailySalesPetrol * daysInMonth;
    monthlySalesDiesel = dailySalesDiesel * daysInMonth;
    monthlySalesCNG = dailySalesCNG * daysInMonth;

    // Reset daily sales after updating monthly sales
    dailySalesPetrol = 0;
    dailySalesDiesel = 0;
    dailySalesCNG = 0;
    writeMonthlyDataToCSV();
}
void Admin::writeMonthlyDataToCSV()
{
    ofstream file("monthly_data.csv", ios::app); // Open file in append mode
    if (file.is_open())
    {
        // Write headers if the file is empty
        if (file.tellp() == 0)
        {
            file << "Month, Petrol Sales (Liters), Petrol Sales (Revenue), Diesel Sales (Liters), Diesel Sales (Revenue), CNG Sales (Liters), CNG Sales (Revenue), Profit\n";
        }
        string CurrentMonth = getCurrentMonthAndYear();
        file << CurrentMonth << " , "
             << monthlySalesPetrol << ", " << monthlySalesPetrol * 294 << ", "
             << monthlySalesDiesel << ", " << monthlySalesDiesel * 290 << ", "
             << monthlySalesCNG << ", " << monthlySalesCNG * 200 << ", "
             << getTotalSales() - getTotalExpenses() << "\n";

        file.close();
        cout << "Monthly data written to CSV successfully." << endl;
    }
    else
    {
        cout << "Unable to open file for writing." << endl;
    }
}

void Admin::writeDailySalesToCSV()
{
    ofstream file("daily_sales.csv", ios::app); // Open file in append mode
    if (file.is_open())
    {
        // Write headers if the file is empty
        if (file.tellp() == 0)
        {
            file << "Date,Petrol (Liters),Petrol (Rs),Diesel (Liters),Diesel (Rs),CNG (Liters),CNG (Rs)" << endl;
        }

        // Get current date (you can replace this with your own method to get the date)
        string currentDate = getCurrentDate(); // Example date, replace with actual date

        // Write daily sales data to file
        file << currentDate << ","
             << fixed << setprecision(2) << dailySalesPetrol << "," << dailySalesPetrol * 294 << ","
             << fixed << setprecision(2) << dailySalesDiesel << "," << dailySalesDiesel * 290 << ","
             << fixed << setprecision(2) << dailySalesCNG << "," << dailySalesCNG * 200 << endl;

        file.close();
        cout << "Daily sales data has been written to 'daily_sales.csv'." << endl;
    }
    else
    {
        cout << "Unable to open file." << endl;
    }
}


string Admin::getCurrentMonthAndYear()
{
    // Get current time
    std::time_t now = std::time(0);

    // Convert current time to a struct tm
    std::tm *localTime = std::localtime(&now);

    // Get current month and year
    int month = localTime->tm_mon + 1;    // Month is 0-based, so add 1
    int year = localTime->tm_year + 1900; // Year is years since 1900

    // Convert month and year to string
    string monthStr = to_string(month);
    string yearStr = to_string(year);

    // Format the result
    string result = monthStr + "/" + yearStr;

    return result;
}

void Admin::viewDailySales()
{
    string currentDate = getCurrentDate();
    cout << "Current date: " << currentDate << endl;

    cout << "Daily Sales:" << endl;
    cout << "Petrol (Liters): " << fixed << setprecision(2) << dailySalesPetrol << " | Rs " << dailySalesPetrol * 294 << endl;
    cout << "Diesel (Liters): " << fixed << setprecision(2) << dailySalesDiesel << " | Rs " << dailySalesDiesel * 290 << endl;
    cout << "CNG (Liters): " << fixed << setprecision(2) << dailySalesCNG << " | Rs " << dailySalesCNG * 200 << endl;
    writeDailySalesToCSV();
}

void Admin::viewMonthlySales()
{
    string CurrentMonth = getCurrentMonthAndYear();
    cout << "Current Month: " << CurrentMonth << endl;
    cout << "Monthly Sales:" << endl;
    cout << "Petrol (Liters): " << fixed << setprecision(2) << monthlySalesPetrol << " | Rs " << monthlySalesPetrol * 294 << endl;
    cout << "Diesel (Liters): " << fixed << setprecision(2) << monthlySalesDiesel << " | Rs " << monthlySalesDiesel * 290 << endl;
    cout << "CNG (Liters): " << fixed << setprecision(2) << monthlySalesCNG << " | Rs " << monthlySalesCNG * 200 << endl;
}

void Admin::calculateProfit()
{
    double totalSales = getTotalSales();
    double totalExpenses = getTotalExpenses();
    double monthlyProfit = totalSales - totalExpenses;
    cout << "Monthly Profit: Rs " << fixed << setprecision(2) << monthlyProfit << endl;
    writeMonthlyDataToCSV();
}

double Admin::getTotalSales() const
{
    return monthlySalesPetrol * 294 + monthlySalesDiesel * 290 + monthlySalesCNG * 200;
}

double Admin::getTotalExpenses() const
{
    return fillerManSalary + managerSalary + securityGuardSalary + cashierSalary + supervisorSalary + total_bills;
}

int main()
{
    Inventory inventory;
    Admin admin;
    //    User user(inventory);
    Shift shift;
    string adminUsername = "admin";
    string adminPassword = "admin123";

    cin.clear();
    string check;
    cout << endl
         << endl
         << endl
         << endl
         << endl;
    SetConsoleTextAttribute(h, 11);
    cout << "\t\t\t\t\t WELCOME TO PETROLEUM MANAGEMENT SYSTEM!\n\n\n";
    Sleep(300);
    cout << "\n\n\t\t\t\t\t\tProject Prepared by:";
    Sleep(400);
    cout << "\n\n\t\t\t\t\t\t--------------------";
    Sleep(500);
    cout << "\n\n\t\t\t\t     IQRA YASMEEN       ";
    Sleep(1000);
    cout << "\n\n\t\t\t\t     M.ABDUL WASAY              ";
    Sleep(2000);
    cout << "\n\n\t\t\t\t     SYED MUJTABA GILLANI       ";
    Sleep(2000);
    cout << endl;
    system("cls");

    char loginChoice = '\0';
    bool isLoggedIn = false; // Track if a user or admin is logged in
    // SetConsoleTextAttribute(h, 10);
    User user(inventory);
    cout << "\n\n\n\t\t\t\t ========== Petroleum Management System ==========" << endl;

    while (true)
    {
        bool displayUserMenu = false; // Flag to control whether to display user menu

        if (!isLoggedIn)
        {
            // If not logged in, prompt for login choice
            SetConsoleTextAttribute(h, 12);
            cout << "\t\t\t\t Choose an option:" << endl;
            cout << "\t\t\t\t 1) Login as User" << endl;
            cout << "\t\t\t\t 2) Login as Admin" << endl;
            cout << "\t\t\t\t 3) Exit" << endl;
            cout << "\t\t\t\t ==================================================" << endl;
            cout << "\t\t\t\t Enter your choice: ";
            cin >> loginChoice;
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cout << endl;

            if (!admin.isValidChoice(loginChoice))
            {
                cout << "\t\t\t\t Sorry, invalid choice! Please try again." << endl;
                continue; // Show the menu again
            }
            if (cin.gcount() > 1 || (loginChoice != USER_LOGIN && loginChoice != ADMIN_LOGIN && loginChoice != EXIT_PROGRAM))
            {
                cout << "\t\t\t\t Invalid choice! Please enter a single digit." << endl;
                cin.clear(); // Clear error state
                continue;    // Restart the loop to prompt for login choice again
            }
        }

        switch (loginChoice)
        {
        case USER_LOGIN:
        {
            SetConsoleTextAttribute(h, 3);
            cout << "\t\t\t\t ---------- User Login ----------" << endl;
            isLoggedIn = true;      // Set login status to true after successful login
            displayUserMenu = true; // Set flag to true to display user menu
            break;
        }
        case ADMIN_LOGIN:
        {
            SetConsoleTextAttribute(h, 6);
            cout << "\t\t\t\t---------- Admin Login ----------" << endl;

            string enteredUsername;
            string enteredPassword;
            char ch;

            cout << "\t\t\t\tEnter username: ";
            cin >> enteredUsername;
            cout << "\t\t\t\tEnter password: ";
            ch = _getch();
            while (ch != 13)
            {
                if (ch != 8) // check if the character is not backspace
                {
                    enteredPassword.push_back(ch); // add the character to the password
                    cout << "*";                   // display an asterisk
                }
                else // if the character is backspace
                {
                    if (!enteredPassword.empty()) // check if the password is not empty
                    {
                        enteredPassword.pop_back(); // remove the last character from the password
                        cout << "\b \b";            // move the cursor back and clear the previous asterisk
                    }
                }
                ch = _getch();
            }
            cout << endl;

            if (enteredUsername == adminUsername && enteredPassword == adminPassword)
            {
                SetConsoleTextAttribute(h, 6);
                cout << "\t\t\t\t Admin login successful!" << endl;
                isLoggedIn = true; // Set login status to true after successful login
                while (isLoggedIn) // Loop while the admin is logged in
                {
                    cin.ignore();
                    char choice;
                    // SetConsoleTextAttribute(h, 6);
                    cout << "\n\n\t\t\t\t ========== Admin Menu ==========" << endl;
                    cout << "\t\t\t\t Choose an option:" << endl;
                    cout << "\t\t\t\t 1) View Daily Sales" << endl;
                    cout << "\t\t\t\t 2) View Monthly Sales" << endl;
                    cout << "\t\t\t\t 3) Calculate Monthly Profit" << endl;
                    cout << "\t\t\t\t 4) Salaries" << endl;
                    cout << "\t\t\t\t 5) Shifts" << endl;
                    cout << "\t\t\t\t 6) View Inventory" << endl;
                    cout << "\t\t\t\t 7) Logout" << endl;
                    cout << "\t\t\t\t ===============================" << endl;
                    cout << "\t\t\t\t Enter your choice: ";
                    cin >> choice;
                    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                    if (cin.gcount() > 1)
                    {
                        cout << "\t\t\t\t Invalid choice! Please enter a single digit." << endl;
                        cin.clear(); // Clear error state
                                     //          			  cin.ignore(numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
                        continue;    // Restart the loop
                    }
                    cout << endl;

                    switch (choice)
                    {
                    // Handle admin menu options
                    case '1':
                        admin.viewDailySales();
                        break;
                    case '2':
                        admin.updateMonthlySales();
                        admin.viewMonthlySales();
                        break;
                    case '3':
                        admin.calculateProfit();
                        break;
                    case '4':
                        admin.manageSalaries();
                        break;
                    case '5':
                        admin.viewShift();
                        if (shift.isTimeToChange())
                        {
                            shift.changeShift();
                        }
                        break;
                    case '6':
                        inventory.viewStock();
                        break;
                    case '7':
                        cout << "\t\t\t\t\t Logging out..." << endl;
                        isLoggedIn = false; // Logout
                        break;
                    default:
                        cout << "\t\t\t\t\t Invalid choice! Please try again." << endl;
                    }
                }
            }
            else
            {
                cout << "\t\t\t\t Invalid username or password! Please try again." << endl;
            }
            break;
        }
        case EXIT_PROGRAM:
            SetConsoleTextAttribute(h, 11);
            cout << "\t\t\t\t\t Exiting program..." << endl;
            return 0;
        default:
            cout << "\t\t\t\t\t Invalid choice! Please try again." << endl;
            break;
        }

        while (isLoggedIn && displayUserMenu)
        {
            char choice;
            SetConsoleTextAttribute(h, 14);
            cout << "\n\n\t\t\t\t ========== User Menu ==========" << endl;
            cout << "\t\t\t\t Choose an option:" << endl;
            cout << "\t\t\t\t 1) Refill Petrol" << endl;
            cout << "\t\t\t\t 2) Refill Diesel" << endl;
            cout << "\t\t\t\t 3) Refill CNG" << endl;
            cout << "\t\t\t\t 4) Logout" << endl;
            cout << "\t\t\t\t ===============================" << endl;
            cout << "\t\t\t\t Enter your choice: ";
            cin >> choice;
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cout << endl;

            if (cin.gcount() > 1 || (choice < '1' || choice > '4'))
            {
                cout << "\t\t\t Invalid choice! Please enter a single digit between 1 and 4." << endl;
                cin.clear(); // Clear error state
                continue;    // Restart the loop to prompt for user menu choice again
            }

            switch (choice)
            {
            case '1':
                user.refillPetrol(inventory, 294, admin);
                break;
            case '2':
                user.refillDiesel(inventory, 290, admin);
                break;
            case '3':
                user.refillCNG(inventory, 200, admin);
                break;
            case '4':
                isLoggedIn = false;      // Logout
                displayUserMenu = false; // Stop displaying user menu
                break;
            default:
                cout << "\t\t\t\t Invalid choice! Please try again." << endl;
                break;
            }
        }
    }

    return 0;
}