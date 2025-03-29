#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <iostream>
#include <fstream>

class Employee
{
private:
    int id;
    std::string name;
    double salary;

public:
    Employee() : id(0), name(""), salary(0.0) {}

    Employee(int _id, const std::string& _name, double _salary)
        : id(_id), name(_name), salary(_salary) {
    }

    // Copy constructor
    Employee(const Employee& other)
        : id(other.id), name(other.name), salary(other.salary) {
    }

    // Getters
    int getId() const { return id; }
    std::string getName() const { return name; }
    double getSalary() const { return salary; }

    // Setters
    void setId(int _id) { id = _id; }
    void setName(const std::string& _name) { name = _name; }
    void setSalary(double _salary) { salary = _salary; }

    // Comparison operators
    bool operator==(const Employee& other) const
    {
        return id == other.id;
    }

    // Output operator for display
    friend std::ostream& operator<<(std::ostream& os, const Employee& emp)
    {
        os << "ID: " << emp.id << ", Name: " << emp.name << ", Salary: " << emp.salary;
        return os;
    }

    // File operations
    void writeToFile(std::ofstream& outFile) const
    {
        outFile.write(reinterpret_cast<const char*>(&id), sizeof(id));

        int nameLength = name.length();
        outFile.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
        outFile.write(name.c_str(), nameLength);

        outFile.write(reinterpret_cast<const char*>(&salary), sizeof(salary));
    }

    void readFromFile(std::ifstream& inFile)
    {
        inFile.read(reinterpret_cast<char*>(&id), sizeof(id));

        int nameLength;
        inFile.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));

        char* nameBuffer = new char[nameLength + 1];
        inFile.read(nameBuffer, nameLength);
        nameBuffer[nameLength] = '\0';
        name = nameBuffer;
        delete[] nameBuffer;

        inFile.read(reinterpret_cast<char*>(&salary), sizeof(salary));
    }
};

#endif // EMPLOYEE_H