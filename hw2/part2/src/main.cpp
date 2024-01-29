#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Employee
{
private:
    int id;
    int salary;
    int department;

public:
    Employee(int id, int salary, int department);
    ~Employee();
    void set_id(int id);
    void set_salary(int salary);
    void set_department(int department);
    int get_id();
    int get_salary();
    int get_department();
};

Employee::Employee(int id, int salary, int department) : id(id), salary(salary), department(department) {}

Employee::~Employee() {}

int Employee::get_id()
{
    return this->id;
}

int Employee::get_department()
{
    return this->department;
}

int Employee::get_salary()
{
    return this->salary;
}

void Employee::set_id(int id)
{
    this->id = id;
}

void Employee::set_salary(int salary)
{
    this->salary = salary;
}

void Employee::set_department(int department)
{
    this->department = department;
}

class Node
{
public:
    Employee data;
    Node *next;

    Node(Employee emp) : data(emp), next(nullptr) {}
};

class EmployeeList
{
private:
    Node *head;
    Node *last;
    int employee_counter;
    int max_id;

public:
    EmployeeList() : head(nullptr), last(nullptr), employee_counter(0), max_id(0) {}

    Node *get_head()
    {
        return this->head;
    }

    void ADD(int salary, int department)
    {
        max_id++;
        Employee newEmployee(max_id, salary, department);
        Node *newNode = new Node(newEmployee);
        if (head == nullptr)
        {
            head = newNode;
            last = newNode;
        }
        else
        {
            last->next = newNode;
            last = newNode;
        }
        employee_counter++;
    }

    void UPDATE(int id, int salary, int department)
    {
        Node *current = head;
        bool unfound = true;

        while (current != nullptr)
        {
            if (current->data.get_id() == id)
            {
                current->data.set_salary(salary);
                current->data.set_department(department);
                unfound = false;
                break;
            }
            current = current->next;
        }

        if (unfound)
        {
            cout << "ERROR: invalid ID to update";
        }
    }

    void DELETE(int id)
    {
        bool unfound = true;

        if (head == nullptr)
        {
            cout << "ERROR: There is no Employee";
        }
        else
        {
            if (head->data.get_id() == id)
            {
                Node *temp = head;
                head = head->next;
                delete temp;
                employee_counter--;
                unfound = false;
            }
            if (unfound)
            {
                Node *current = head;
                while (current->next != nullptr)
                {
                    if (current->next->data.get_id() == id)
                    {
                        Node *temp = current->next;
                        current->next = current->next->next;
                        delete temp;
                        employee_counter--;
                        unfound = false;
                        break;
                    }
                    current = current->next;
                }
            }

            if (unfound)
            {
                cout <<"ERROR: invalid ID to delete";
            }
        }
    }

    ~EmployeeList()
    {
        Node *current = head;
        while (current != nullptr)
        {
            Node *temp = current;
            current = current->next;
            delete temp;
        }
    }
};

int main(int argc, char **argv)
{
    fstream file(argv[1]);
    string satir = "";
    fstream operations(argv[2]);
    string operation = "";
    EmployeeList employeeList;

    if (file.is_open())
    {
        getline(file, satir);
        while (getline(file, satir))
        {
            int integer_employee_id, integer_employee_salary, integer_employee_department;
            sscanf(satir.c_str(), "%d;%d;%d", &integer_employee_id, &integer_employee_salary, &integer_employee_department);
            employeeList.ADD(integer_employee_salary, integer_employee_department);
        }
    }

    while (getline(operations, operation, ';'))
    {
        if (operation == "ADD")
        {
            string add_salary_str, add_department_str;
            getline(operations, add_salary_str, ';');
            getline(operations, add_department_str);
            int add_salary = stoi(add_salary_str);
            int add_department = stoi(add_department_str);
            employeeList.ADD(add_salary, add_department);
        }
        else if (operation == "UPDATE")
        {
            string update_id_str, update_salary_str, update_department_str;
            getline(operations, update_id_str, ';');
            getline(operations, update_salary_str, ';');
            getline(operations, update_department_str);
            int update_id = stoi(update_id_str);
            int update_salary = stoi(update_salary_str);
            int update_department = stoi(update_department_str);
            employeeList.UPDATE(update_id, update_salary, update_department);
        }
        else if (operation == "DELETE")
        {
            string delete_id_str;
            getline(operations, delete_id_str);
            int delete_id = stoi(delete_id_str);
            employeeList.DELETE(delete_id);
        }
    }
    operations.close();

    ofstream printer("linked_list_solution.csv");
    printer << "Employee_ID;Salary;Department\n";

    Node *current = employeeList.get_head();
    while (current != nullptr)
    {
        printer << current->data.get_id() << ";" << current->data.get_salary() << ";" << current->data.get_department() << '\n';
        current = current->next;
    }

    printer.close();

    return 0;
}
