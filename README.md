🚀 C++ Doubly Linked List Library
A templated doubly linked list implementation with iterator support, built as a static library and used in a console application for employee management.

📜 Description
This project demonstrates the implementation of a doubly linked list as a C++ template class with full iterator support. The linked list is packaged as a static library and used in a console application that provides various employee management features.

The application allows users to:
✅ Add, delete, update, and search for employees
✅ Save and load employee data from binary or text files
✅ Sort employees by ID, Name, or Salary using either custom sorting methods or STL sort

This project serves as a great learning example of OOP, template programming, file handling, and static libraries in C++.

🛠️ Technologies Used
✅ C++ – Core programming language
✅ OOP (Object-Oriented Programming) – Encapsulation, inheritance, polymorphism
✅ Templates – For generic doubly linked list implementation
✅ Iterators – To allow iteration over the list
✅ Static Library – Encapsulating the linked list implementation
✅ File Handling – Binary & text file operations
✅ STL (Standard Template Library) – Sorting and vector operations

📥 Installation & Usage
🔹 Prerequisites
Ensure you have the following installed:

C++ Compiler (GCC, MSVC, or Clang)

IDE (Visual Studio, CodeBlocks, or VS Code with C++ extensions)

🔹 Steps to Run
Clone the repository

sh
Copy
Edit
git clone https://github.com/AhmedLGaiar/CPP-Project.git
cd CPP-Project
Build the Static Library
If using G++:

sh
Copy
Edit
g++ -c LinkedList.cpp -o LinkedList.o
ar rcs libLinkedList.a LinkedList.o
If using MSVC (Windows):

sh
Copy
Edit
cl /c LinkedList.cpp
lib /OUT:LinkedList.lib LinkedList.obj
Compile and Link the Console Application

sh
Copy
Edit
g++ -o main main.cpp -L. -lLinkedList
./main
Run the Application

Use the console menu to manage employees

🚀 Features
✔️ Templated Doubly Linked List with iterator support
✔️ Static Library for modularity
✔️ Add, Delete, Update, and Search Employees
✔️ File Handling (Binary & Text) for data persistence
✔️ Sorting by ID, Name, or Salary using STL or custom sorting

🎯 Bonus Features
Sorting employees using either custom sorting methods or STL sort

Implemented an efficient iterator to traverse the linked list

📌 Roadmap (Future Enhancements)
Add unit tests for linked list operations

Implement a GUI version (Qt or SFML)

Optimize memory management for large datasets

🤝 Contributing
Contributions are welcome!

Fork the repository

Create a new branch (feature-name)

Commit and push your changes

Open a pull request

📄 License
This project is licensed under the MIT License.

🔗 Connect
📧 Email: ahmedlgaiar@gmail.com
🐦 Twitter: https://x.com/ahmed_lgaiar
💼 LinkedIn: https://www.linkedin.com/in/ahmed-elgaiar/
