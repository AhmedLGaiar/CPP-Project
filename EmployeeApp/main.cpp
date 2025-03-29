#include <iostream>
#include <string>
#include <limits>
#include "../EmployeeLib/Employee.h"
#include "../EmployeeLib/FileManager.h"
#include "../EmployeeLib/LinkedList.h"

using namespace std;

// Function prototypes
void DisplayMenu();
void AddEmployee(LinkedList<Employee>& employees);
void DisplayEmployees(const LinkedList<Employee>& employees);
void SearchEmployeeById(const LinkedList<Employee>& employees);
void SearchEmployeeByName(const LinkedList<Employee>& employees);
void DeleteEmployee(LinkedList<Employee>& employees);
void UpdateEmployee(LinkedList<Employee>& employees);
void SaveEmployees(const LinkedList<Employee>& employees);
void LoadEmployees(LinkedList<Employee>& employees);

int main()
{
    LinkedList<Employee> employees;
    int choice;

    do
    {
        DisplayMenu();

        // Input validation
        while (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number: ";
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
            AddEmployee(employees);
            break;
        case 2:
            DisplayEmployees(employees);
            break;
        case 3:
            SearchEmployeeById(employees);
            break;
        case 4:
            SearchEmployeeByName(employees);
            break;
        case 5:
            DeleteEmployee(employees);
            break;
        case 6:
            UpdateEmployee(employees);
            break;
        case 7:
            SaveEmployees(employees);
            break;
        case 8:
            LoadEmployees(employees);
            break;
        case 0:
            cout << "Exiting program..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }

        cout << endl;
    } while (choice != 0);

    return 0;
}

void DisplayMenu()
{
    cout << "======== Employee Management System ========" << endl;
    cout << "1. Add new Employee" << endl;
    cout << "2. Display all Employees" << endl;
    cout << "3. Search Employee by ID" << endl;
    cout << "4. Search Employee by Name" << endl;
    cout << "5. Delete Employee by ID" << endl;
    cout << "6. Update Employee data by ID" << endl;
    cout << "7. Save Employees to file" << endl;
    cout << "8. Load Employees from file" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter your choice: ";
}

void AddEmployee(LinkedList<Employee>& employees)
{
    int id;
    string name;
    double salary;

    cout << "Enter Employee ID: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Employee Name: ";
    getline(cin, name);

    cout << "Enter Employee Salary: ";
    cin >> salary;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

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