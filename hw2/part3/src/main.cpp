#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Employee
{
private:
    int id;
    int salary;
    int department;

public:
    Employee(int id = 0, int salary = 0, int department = 0);
    void set_id(int id);
    void set_salary(int salary);
    void set_department(int department);
    int get_id() const;
    int get_salary() const;
    int get_department() const;
};

Employee::Employee(int id, int salary, int department)
    : id(id), salary(salary), department(department) {}

int Employee::get_id() const
{
    return id;
}

int Employee::get_department() const
{
    return department;
}

int Employee::get_salary() const
{
    return salary;
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

vector<Employee> employees;
int max_id = 0;

void ADD(int salary, int department)
{
    max_id++;
    Employee myemp(max_id, salary, department);
    employees.push_back(myemp);
}

void UPDATE(int id, int salary, int department)
{
    bool unfound = true;

    for (size_t i = 0; i < employees.size(); i++)
    {
        if (employees[i].get_id() == id)
        {
            employees[i].set_salary(salary);
            employees[i].set_department(department);
            unfound = false;
            break;
        }
    }

    if (unfound)
    {
        cout << "ERROR: An invalid ID to update";
    }
}

void DELETE(int id)
{
    if (employees.empty())
    {
        cout << "ERROR: There is no Employee";
        return;
    }

    auto it = std::find_if(employees.begin(), employees.end(), [id](const Employee &emp)
                           { return emp.get_id() == id; });

    if (it != employees.end())
    {
        employees.erase(it);
    }
    else
    {
        cout << "ERROR: An invalid ID to delete";
    }
}
int main(int argc, char **argv)
{
    fstream dosya_oku(argv[1]);
    string satir = "";
    if (dosya_oku.is_open())
    {
        getline(dosya_oku, satir);
        while (getline(dosya_oku, satir))
        {
            char employee_salary[10];
            char employee_department[10];
            int counter = 0;
            int y = 0;
            int integer_employee_salary, integer_employee_department;
            int satir_uzunluk = satir.length();
            for (int i = 0; i < satir_uzunluk; i++)
            {
                if (counter == 0)
                {
                    if (satir[i] != ';')
                    {
                    }
                    else
                    {
                        counter += 1;
                        y = 0;
                    }
                }
                else if (counter == 1)
                {
                    if (satir[i] != ';')
                    {
                        employee_salary[y] = satir[i];
                        y++;
                    }
                    else
                    {
                        counter += 1;
                        y = 0;
                        integer_employee_salary = stoi(employee_salary);
                    }
                }
                else if (counter == 2)
                {
                    if (satir[i] != '\n' || satir[i] != '\0')
                    {
                        employee_department[y] = satir[i];
                        y++;
                        integer_employee_department = stoi(employee_department);
                    }
                }
            }
            ADD(integer_employee_salary, integer_employee_department);
        }
    }
    else
    {
        cout << "dosya açılamadı" << endl;
    };
    dosya_oku.close();

    fstream operations(argv[2]);
    string operation = "";

    while (getline(operations, operation, ';'))
    {
        if (operation == "ADD")
        {
            string add_salary_str, add_department_str;
            getline(operations, add_salary_str, ';');
            getline(operations, add_department_str);
            int add_salary = stoi(add_salary_str);
            int add_department = stoi(add_department_str);
            ADD(add_salary, add_department);
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
            UPDATE(update_id, update_salary, update_department);
        }
        else if (operation == "DELETE")
        {
            string delete_id_str;
            getline(operations, delete_id_str);
            int delete_id = stoi(delete_id_str);
            DELETE(delete_id);
        }
    }
    operations.close();

    ofstream printer("vector_solution.csv");
    printer << "Employee_ID;Salary;Department\n";
    for (size_t i = 0; i < employees.size(); i++)
    {
        printer << employees[i].get_id() << ";" << employees[i].get_salary() << ";" << employees[i].get_department() << '\n';
    }
    printer.close();
    return 0;
}
