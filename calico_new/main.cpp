#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

class Worker {
private:
    int empID;
    int empSalary;
    int empDepartment;

public:
    Worker(int id, int salary, int department);
    void setID(int id);
    void setSalary(int salary);
    void setDepartment(int department);
    int getID() const;
    int getSalary() const;
    int getDepartment() const;
};

Worker::Worker(int id, int salary, int department) : empID(id), empSalary(salary), empDepartment(department) {}

int Worker::getID() const {
    return empID;
}

int Worker::getDepartment() const {
    return empDepartment;
}

int Worker::getSalary() const {
    return empSalary;
}

void Worker::setID(int id) {
    empID = id;
}

void Worker::setSalary(int salary) {
    empSalary = salary;
}

void Worker::setDepartment(int department) {
    empDepartment = department;
}

vector<Worker> employees;

void addEmployee(int salary, int department) {
    int maxEmpID = employees.empty() ? 0 : (*max_element(employees.begin(), employees.end(), [](const Worker &a, const Worker &b) {
        return a.getID() < b.getID();
    })).getID();

    employees.emplace_back(maxEmpID + 1, salary, department);
}

void updateEmployee(int id, int salary, int department) {
    auto it = find_if(employees.begin(), employees.end(), [id](const Worker &w) {
        return w.getID() == id;
    });

    if (it != employees.end()) {
        it->setSalary(salary);
        it->setDepartment(department);
    } else {
        cout << "ERROR: An invalid ID to update" << endl;
    }
}

void deleteEmployee(int id) {
    auto it = remove_if(employees.begin(), employees.end(), [id](const Worker &w) {
        return w.getID() == id;
    });

    if (it != employees.end()) {
        employees.erase(it, employees.end());
    } else {
        cout << "ERROR: An invalid ID to delete" << endl;
    }
}

int main(int argc, char **argv) {
    fstream employeeFile(argv[1]);
    string employeeLine;

    if (employeeFile.is_open()) {
        getline(employeeFile, employeeLine); // Skip header
        while (getline(employeeFile, employeeLine)) {
            int empID, empSalary, empDepartment;
            sscanf(employeeLine.c_str(), "%d;%d;%d", &empID, &empSalary, &empDepartment);

            employees.emplace_back(empID, empSalary, empDepartment);
        }
        employeeFile.close();
    } else {
        cout << "Error: Unable to open the file." << endl;
        return 1;
    }

    fstream operationsFile(argv[2]);
    string operation;

    while (getline(operationsFile, operation, ';')) {
        if (operation == "ADD") {
            string addSalaryStr, addDepartmentStr;
            getline(operationsFile, addSalaryStr, ';');
            getline(operationsFile, addDepartmentStr);

            int addSalary = stoi(addSalaryStr);
            int addDepartment = stoi(addDepartmentStr);

            addEmployee(addSalary, addDepartment);
        } else if (operation == "UPDATE") {
            string updateIDStr, updateSalaryStr, updateDepartmentStr;
            getline(operationsFile, updateIDStr, ';');
            getline(operationsFile, updateSalaryStr, ';');
            getline(operationsFile, updateDepartmentStr);

            int updateID = stoi(updateIDStr);
            int updateSalary = stoi(updateSalaryStr);
            int updateDepartment = stoi(updateDepartmentStr);

            updateEmployee(updateID, updateSalary, updateDepartment);
        } else if (operation == "DELETE") {
            string deleteIDStr;
            getline(operationsFile, deleteIDStr);

            int deleteID = stoi(deleteIDStr);

            deleteEmployee(deleteID);
        }
    }
    operationsFile.close();

    ofstream resultFile("vector_solution.csv");
    resultFile << "Employee_ID;Salary;Department\n";

    for (const auto &employee : employees) {
        resultFile << employee.getID() << ";" << employee.getSalary() << ";" << employee.getDepartment() << '\n';
    }
    resultFile.close();

    return 0;
}
