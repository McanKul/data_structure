/* @Author
StudentN ame :< mehmetcan kul >
StudentID :< 150210076 >
Date :< 04/01/2024 > */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "header_doubly.cpp"

using namespace std;

int main(int argc, char const *argv[])
{
   DSL DSL(5);
   fstream dosya_oku(argv[1]);
   string satir = "";
   int global_max_id = 0;

   if (dosya_oku.is_open())
   {
      getline(dosya_oku, satir);
      while (getline(dosya_oku, satir))
      {
         int integer_employee_id, integer_employee_salary, integer_employee_department;
         sscanf(satir.c_str(), "%d;%d;%d", &integer_employee_id, &integer_employee_salary, &integer_employee_department);
         Employee *myemp = new Employee(integer_employee_id, integer_employee_salary, integer_employee_department);
         DSL.insert(myemp);
         global_max_id++;
      }
   }

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
         global_max_id++;
         Employee *myemp = new Employee(global_max_id,add_salary, add_department);
         DSL.insert(myemp);
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
         DSL.update(update_id, update_salary, update_department);
      }
      else if (operation == "DELETE")
      {
         string delete_id_str;
         getline(operations, delete_id_str);
         int delete_id = stoi(delete_id_str);
         DSL.remove(delete_id);
      }
   }
   operations.close();
   ofstream dosya("doubly_output.csv");
   DSL.dumpToFile(dosya);
   dosya.close();
   
}