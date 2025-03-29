#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <fstream>
#include <string>
#include "pch.h"
#include "LinkedList.h"
#include "Employee.h"

class FileManager
{
public:
    // Save employees to binary file
    static bool SaveEmployeesToBinaryFile(const LinkedList<Employee>& employees, const std::string& filename)
    {
        std::ofstream outFile(filename, std::ios::binary);
        if (!outFile)
        {
            return false;
        }

        int count = employees.Size();
        outFile.write(reinterpret_cast<const char*>(&count), sizeof(count));

        for (auto it = employees.begin(); it != employees.end(); ++it)
        {
            it->writeToFile(outFile);
        }

        outFile.close();
        return true;
    }

    // Load employees from binary file
    static bool LoadEmployeesFromBinaryFile(LinkedList<Employee>& employees, const std::string& filename)
    {
        std::ifstream inFile(filename, std::ios::binary);
        if (!inFile)
        {
            return false;
        }

        int count;
        inFile.read(reinterpret_cast<char*>(&count), sizeof(count));

        for (int i = 0; i < count; i++)
        {
            Employee emp;
            emp.readFromFile(inFile);
            employees.Add(emp);
        }

        inFile.close();
        return true;
    }

    // Save employees to text file
    static bool SaveEmployeesToTextFile(const LinkedList<Employee>& employees, const std::string& filename)
    {
        std::ofstream outFile(filename);
        if (!outFile)
        {
            return false;
        }

        for (auto it = employees.begin(); it != employees.end(); ++it)
        {
            outFile << it->getId() << "," << it->getName() << "," << it->getSalary() << std::endl;
        }

        outFile.close();
        return true;
    }

    // Load employees from text file
    static bool LoadEmployeesFromTextFile(LinkedList<Employee>& employees, const std::string& filename)
    {
        std::ifstream inFile(filename);
        if (!inFile)
        {
            return false;
        }

        std::string line;
        while (std::getline(inFile, line))
        {
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);

            if (pos1 != std::string::npos && pos2 != std::string::npos)
            {
                int id = std::stoi(line.substr(0, pos1));
                std::string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
                double salary = std::stod(line.substr(pos2 + 1));

                Employee emp(id, name, salary);
                employees.Add(emp);
            }
        }

        inFile.close();
        return true;
    }
};

#endif // FILE_MANAGER_H