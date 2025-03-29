#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include "../EmployeeLib/Employee.h"
#include "../EmployeeLib/FileManager.h"
#include "../EmployeeLib/LinkedList.h"

using namespace std;

// Function prototypes
void DisplayMenu(int selected);
void AddEmployee(LinkedList<Employee>& employees);
void DisplayEmployees(const LinkedList<Employee>& employees);
void SearchEmployeeById(const LinkedList<Employee>& employees);
void SearchEmployeeByName(const LinkedList<Employee>& employees);
void DeleteEmployee(LinkedList<Employee>& employees);
void UpdateEmployee(LinkedList<Employee>& employees);
void SaveEmployees(const LinkedList<Employee>& employees);
void LoadEmployees(LinkedList<Employee>& employees);
void SortEmployees(LinkedList<Employee>& employees);
void gotoxy1(int x, int y);
void SetColorAndBackground(int ForgC, int BackC);

// Menu options
const char* menu[] = {
    "Add new Employee",
    "Display all Employees",
    "Search Employee by ID",
    "Search Employee by Name",
    "Delete Employee by ID",
    "Update Employee data by ID",
    "Sort Employees",
    "Save Employees to file",
    "Load Employees from file",
    "Exit"
};
const int menuCount = sizeof(menu) / sizeof(menu[0]);

int main()
{
    LinkedList<Employee> employees;
    int selected = 0;
    bool isRunning = true;

    do {
        system("cls");
        gotoxy1(50, 3);
        SetColorAndBackground(15, 0);
        cout << "======== Employee Management System ========";
        gotoxy1(50, 4);
        cout << "Use arrow keys to navigate, Enter to select, Esc to exit";

        // Display menu items
        for (int i = 0; i < menuCount; i++) {
            gotoxy1(50, 6 + i * 2);
            if (i == selected) {
                SetColorAndBackground(15, 1);  // White text on blue background for selected
            }
            else {
                SetColorAndBackground(15, 0);  // White text on black background
            }
            cout << menu[i];
        }

        // Handle key input
        int key = _getch();
        if (key == 0 || key == 224) { // Special keys (arrows)
            key = _getch();
        }

        switch (key) {
        case 72: // Up arrow
            --selected;
            if (selected < 0) selected = menuCount - 1;
            break;
        case 80: // Down arrow
            ++selected;
            if (selected >= menuCount) selected = 0;
            break;
        case 13: // Enter key
            SetColorAndBackground(15, 0);
            system("cls");

            switch (selected) {
            case 0: AddEmployee(employees); break;
            case 1: DisplayEmployees(employees); break;
            case 2: SearchEmployeeById(employees); break;
            case 3: SearchEmployeeByName(employees); break;
            case 4: DeleteEmployee(employees); break;
            case 5: UpdateEmployee(employees); break;
            case 6: SortEmployees(employees); break;  // New sorting option
            case 7: SaveEmployees(employees); break;
            case 8: LoadEmployees(employees); break;
            case 9: isRunning = false; break;
            }

            if (selected != 8) {
                cout << "\nPress any key to continue...";
                _getch();
            }
            break;
        case 27: // Escape key
            isRunning = false;
            break;
        }

    } while (isRunning);

    system("cls");
    gotoxy1(50, 10);
    cout << "Exiting program..." << endl;

    return 0;
}

void DisplayMenu(int selected)
{
    system("cls");
    cout << "======== Employee Management System ========" << endl;
    cout << "Use 'w' and 's' keys to navigate, Enter to select, Esc to exit" << endl << endl;

    for (int i = 0; i < menuCount; i++) {
        cout << (i == selected ? "> " : "  ") << menu[i] << endl;
    }
}

void AddEmployee(LinkedList<Employee>& employees)
{
    int id;
    string name;
    double salary;

    cout << "Enter Employee ID: ";
    cin >> id;
    cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

    cout << "Enter Employee Name: ";
    getline(cin, name);

    cout << "Enter Employee Salary: ";
    cin >> salary;
    cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

    Employee emp(id, name, salary);
    employees.Add(emp);

    cout << "Employee added successfully!" << endl;
}

void DisplayEmployees(const LinkedList<Employee>& employees)
{
    if (employees.Size() == 0)
    {
        cout << "No employees to display." << endl;
        return;
    }

    cout << "======== Employee List ========" << endl;
    employees.Display();
}

void SearchEmployeeById(const LinkedList<Employee>& employees)
{
    int searchId;
    cout << "Enter Employee ID to search: ";
    cin >> searchId;
    cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

    Employee searchEmp;
    searchEmp.setId(searchId);

    auto result = employees.Search(searchEmp);

    if (result != nullptr)
    {
        cout << "Employee found: " << *(result->data) << endl;
    }
    else
    {
        cout << "Employee not found with ID: " << searchId << endl;
    }
}

void SearchEmployeeByName(const LinkedList<Employee>& employees)
{
    string searchName;
    cout << "Enter Employee Name to search: ";
    getline(cin, searchName);

    bool found = false;

    for (auto it = employees.begin(); it != employees.end(); ++it)
    {
        if (it->getName() == searchName)
        {
            cout << "Employee found: " << *it << endl;
            found = true;
        }
    }

    if (!found)
    {
        cout << "No employees found with name: " << searchName << endl;
    }
}

void DeleteEmployee(LinkedList<Employee>& employees)
{
    int deleteId;
    cout << "Enter Employee ID to delete: ";
    cin >> deleteId;
    cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

    Employee deleteEmp;
    deleteEmp.setId(deleteId);

    if (employees.Delete(deleteEmp))
    {
        cout << "Employee with ID " << deleteId << " deleted successfully!" << endl;
    }
    else
    {
        cout << "Employee not found with ID: " << deleteId << endl;
    }
}

void UpdateEmployee(LinkedList<Employee>& employees)
{
    int updateId;
    cout << "Enter Employee ID to update: ";
    cin >> updateId;
    cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

    Employee searchEmp;
    searchEmp.setId(updateId);

    auto result = employees.Search(searchEmp);

    if (result != nullptr)
    {
        Employee& emp = *(result->data);

        string name;
        double salary;

        cout << "Current Employee data: " << emp << endl;

        cout << "Enter new Name (leave empty to keep current): ";
        string newName;
        getline(cin, newName);
        if (!newName.empty())
        {
            emp.setName(newName);
        }

        cout << "Enter new Salary (enter 0 to keep current): ";
        double newSalary;
        cin >> newSalary;
        cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        if (newSalary != 0)
        {
            emp.setSalary(newSalary);
        }

        cout << "Employee updated successfully!" << endl;
    }
    else
    {
        cout << "Employee not found with ID: " << updateId << endl;
    }
}

void SaveEmployees(const LinkedList<Employee>& employees)
{
    int fileType;
    string filename;

    cout << "Save as:\n1. Binary file\n2. Text file\nEnter choice: ";
    cin >> fileType;
    cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

    cout << "Enter filename: ";
    getline(cin, filename);

    bool success = false;

    if (fileType == 1)
    {
        if (!filename.empty() && filename.find('.') == string::npos)
        {
            filename += ".bin";
        }
        success = FileManager::SaveEmployeesToBinaryFile(employees, filename);
    }
    else if (fileType == 2)
    {
        if (!filename.empty() && filename.find('.') == string::npos)
        {
            filename += ".txt";
        }
        success = FileManager::SaveEmployeesToTextFile(employees, filename);
    }
    else
    {
        cout << "Invalid choice." << endl;
        return;
    }

    if (success)
    {
        cout << "Employees saved successfully to " << filename << endl;
    }
    else
    {
        cout << "Failed to save employees to file." << endl;
    }
}

void LoadEmployees(LinkedList<Employee>& employees)
{
    int fileType;
    string filename;

    cout << "Load from:\n1. Binary file\n2. Text file\nEnter choice: ";
    cin >> fileType;
    cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

    cout << "Enter filename: ";
    getline(cin, filename);

    bool success = false;

    if (fileType == 1)
    {
        if (!filename.empty() && filename.find('.') == string::npos)
        {
            filename += ".bin";
        }
        success = FileManager::LoadEmployeesFromBinaryFile(employees, filename);
    }
    else if (fileType == 2)
    {
        if (!filename.empty() && filename.find('.') == string::npos)
        {
            filename += ".txt";
        }
        success = FileManager::LoadEmployeesFromTextFile(employees, filename);
    }
    else
    {
        cout << "Invalid choice." << endl;
        return;
    }

    if (success)
    {
        cout << "Employees loaded successfully from " << filename << endl;
    }
    else
    {
        cout << "Failed to load employees from file." << endl;
    }
}

void SortEmployees(LinkedList<Employee>& employees) {
    // Sub-menu for sorting options
    const char* sortMenu[] = {
        "Sort by ID",
        "Sort by Name",
        "Sort by Salary",
        "Back to Main Menu"
    };
    const int sortMenuCount = sizeof(sortMenu) / sizeof(sortMenu[0]);

    int selected = 0;
    bool inSortMenu = true;

    do {
        system("cls");
        gotoxy1(50, 3);
        SetColorAndBackground(15, 0);
        cout << "======== Sort Employees ========";
        gotoxy1(50, 4);
        cout << "Use arrow keys to navigate, Enter to select";

        // Display sort menu items
        for (int i = 0; i < sortMenuCount; i++) {
            gotoxy1(50, 6 + i * 2);
            if (i == selected) {
                SetColorAndBackground(15, 1);
            }
            else {
                SetColorAndBackground(15, 0);
            }
            cout << sortMenu[i];
        }

        // Handle key input
        int key = _getch();
        if (key == 0 || key == 224) {
            key = _getch();
        }

        switch (key) {
        case 72: // Up arrow
            --selected;
            if (selected < 0) selected = sortMenuCount - 1;
            break;
        case 80: // Down arrow
            ++selected;
            if (selected >= sortMenuCount) selected = 0;
            break;
        case 13: // Enter key
            SetColorAndBackground(15, 0);
            system("cls");

            switch (selected) {
            case 0: // Sort by ID
                employees.SortBy([](const Employee& a, const Employee& b) {
                    return a.getId() < b.getId();
                    });
                cout << "Employees sorted by ID." << endl;
                break;
            case 1: // Sort by Name
                employees.SortBy([](const Employee& a, const Employee& b) {
                    return a.getName() < b.getName();
                    });
                cout << "Employees sorted by Name." << endl;
                break;
            case 2: // Sort by Salary
                employees.SortBy([](const Employee& a, const Employee& b) {
                    return a.getSalary() < b.getSalary();
                    });
                cout << "Employees sorted by Salary." << endl;
                break;
            case 3: // Back to main menu
                inSortMenu = false;
                break;
            }

            if (selected != 3) {
                cout << "\nPress any key to continue...";
                _getch();
            }
            break;
        case 27: // Escape key
            inSortMenu = false;
            break;
        }
    } while (inSortMenu);
}

void gotoxy1(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void SetColorAndBackground(int ForgC, int BackC)
{
    WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
}