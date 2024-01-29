#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Employee {
private:
    int id;
    int salary;
    int department;

public:
    Employee(int id, int salary, int department);
    ~Employee();
    void setID(int id);
    void setSalary(int salary);
    void setDepartment(int department);
    int getID();
    int getSalary();
    int getDepartment();
};

Employee::Employee(int id, int salary, int department) : id(id), salary(salary), department(department) {}

Employee::~Employee() {}

int Employee::getID() {
    return this->id;
}

int Employee::getDepartment() {
    return this->department;
}

int Employee::getSalary() {
    return this->salary;
}

void Employee::setID(int id) {
    this->id = id;
}

void Employee::setSalary(int salary) {
    this->salary = salary;
}

void Employee::setDepartment(int department) {
    this->department = department;
}

class Node {
public:
    Employee data;
    Node *next;

    Node(Employee emp) : data(emp), next(nullptr) {}
};

class EmployeeList {
private:
    Node *head;
    Node *last;
    int employeeCount;
    int maxID;

public:
    EmployeeList() : head(nullptr), last(nullptr), employeeCount(0), maxID(0) {}

    Node *getHead() {
        return this->head;
    }

    void addEmployee(int salary, int department) {
        maxID++;
        Employee newEmployee(maxID, salary, department);
        Node *newNode = new Node(newEmployee);
        if (head == nullptr) {
            head = newNode;
            last = newNode;
        } else {
            last->next = newNode;
            last = newNode;
        }
        employeeCount++;
    }

    void updateEmployee(int id, int salary, int department) {
        Node *current = head;
        bool notFound = true;

        while (current != nullptr) {
            if (current->data.getID() == id) {
                current->data.setSalary(salary);
                current->data.setDepartment(department);
                notFound = false;
                break;
            }
            current = current->next;
        }

        if (notFound) {
            cout << "ERROR: invalid ID to update" << endl;
        }
    }

    void deleteEmployee(int id) {
        bool notFound = true;

        if (head == nullptr) {
            cout << "ERROR: There is no employee" << endl;
        } else {
            if (head->data.getID() == id) {
                Node *temp = head;
                head = head->next;
                delete temp;
                employeeCount--;
                notFound = false;
            }
            if (notFound) {
                Node *current = head;
                while (current->next != nullptr) {
                    if (current->next->data.getID() == id) {
                        Node *temp = current->next;
                        current->next = current->next->next;
                        delete temp;
                        employeeCount--;
                        notFound = false;
                        break;
                    }
                    current = current->next;
                }
            }

            if (notFound) {
                cout << "ERROR: invalid ID to delete" << endl;
            }
        }
    }

    ~EmployeeList() {
        Node *current = head;
        while (current != nullptr) {
            Node *temp = current;
            current = current->next;
            delete temp;
        }
    }
};

int main(int argc, char **argv) {
    fstream file(argv[1]);
    string line = "";
    fstream operations(argv[2]);
    string operation = "";
    EmployeeList employeeList;

    if (file.is_open()) {
        getline(file, line); // Skip the header
        while (getline(file, line)) {
            int id, salary, department;
            sscanf(line.c_str(), "%d;%d;%d", &id, &salary, &department);
            employeeList.addEmployee(salary, department);
        }
    }

    while (getline(operations, operation, ';')) {
        if (operation == "ADD") {
            string addSalaryStr, addDepartmentStr;
            getline(operations, addSalaryStr, ';');
            getline(operations, addDepartmentStr);
            int addSalary = stoi(addSalaryStr);
            int addDepartment = stoi(addDepartmentStr);
            employeeList.addEmployee(addSalary, addDepartment);
        } else if (operation == "UPDATE") {
            string updateIdStr, updateSalaryStr, updateDepartmentStr;
            getline(operations, updateIdStr, ';');
            getline(operations, updateSalaryStr, ';');
            getline(operations, updateDepartmentStr);
            int updateId = stoi(updateIdStr);
            int updateSalary = stoi(updateSalaryStr);
            int updateDepartment = stoi(updateDepartmentStr);
            employeeList.updateEmployee(updateId, updateSalary, updateDepartment);
        } else if (operation == "DELETE") {
            string deleteIdStr;
            getline(operations, deleteIdStr);
            int deleteId = stoi(deleteIdStr);
            employeeList.deleteEmployee(deleteId);
        }
    }
    operations.close();

    ofstream printer("linked_list_solution.csv");
    printer << "Employee_ID;Salary;Department\n";

    Node *current = employeeList.getHead();
    while (current != nullptr) {
        printer << current->data.getID() << ";" << current->data.getSalary() << ";" << current->data.getDepartment() << '\n';
        current = current->next;
    }

    printer.close();

    return 0;
}
