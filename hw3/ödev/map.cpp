#include <iostream>
#include <fstream>
#include <string>
#include <map>

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
   int get_id() const;
   int get_salary() const;
   int get_department() const;
};

Employee::Employee(int id = 0, int salary = 0, int department = 0) // constructer
{
   this->id = id;
   this->salary = salary;
   this->department = department;
}

Employee::~Employee()
{
}

int Employee::get_id() const
{
   return this->id;
}

int Employee::get_department() const
{
   return this->department;
}

int Employee::get_salary() const
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

class My_map   {
private:
   map<int, Employee> employees;

public:
   void add(int id, int salary, int department)
   {
      employees[id] = Employee(id, salary, department);
   }

   void update(int id, int salary, int department)
   {
      if (employees.find(id) != employees.end())
      {
         employees[id].set_salary(salary);
         employees[id].set_department(department);
      }
      else
      {
         cout << "ERROR: invalid ID to update\n";
      }
   }

   void remove(int id)
   {
      if (employees.find(id) != employees.end())
      {
         employees.erase(id);
      }
      else
      {
         cout << "ERROR: invalid ID to delete\n";
      }
   }

   void printToConsole() const
   {
      for (const auto &entry : employees)
      {
         cout << entry.first << endl;
      }
   }

   void printToFile(ofstream &dosya) const
   {
      dosya << "Employee_ID;Salary;Department\n";
      for (const auto &entry : employees)
      {
         dosya << entry.first << ";" << employees.at(entry.first).get_salary() << ";" << employees.at(entry.first).get_department() << endl;
      }
   }
};

int main(int argc, char const *argv[])
{
   int global_max_id = 0;
   My_map
   mini_map;
   ifstream dosya_oku(argv[1]);
   string satir = "";

   if (dosya_oku.is_open())
   {
      getline(dosya_oku, satir);
      while (getline(dosya_oku, satir))
      {
         int integer_employee_id, integer_employee_salary, integer_employee_department;
         sscanf(satir.c_str(), "%d;%d;%d", &integer_employee_id, &integer_employee_salary, &integer_employee_department);
         mini_map.add(integer_employee_id, integer_employee_salary, integer_employee_department);
         global_max_id++;
      }
   }

   dosya_oku.close();

   ifstream operations(argv[2]);
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
         global_max_id++;
         mini_map.add(global_max_id, add_salary, add_department);
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
         mini_map.update(update_id, update_salary, update_department);
      }
      else if (operation == "DELETE")
      {
         string delete_id_str;
         getline(operations, delete_id_str);
         int delete_id = stoi(delete_id_str);
         mini_map.remove(delete_id);
      }
   }

   operations.close();
   ofstream dosya("output.csv");
   mini_map.printToFile(dosya);
   dosya.close();
   return 0;
}
