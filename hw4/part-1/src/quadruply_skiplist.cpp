/* @Author
StudentN ame :< mehmetcan kul >
StudentID :< 150210076 >
Date :< 04/01/2024 > */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "quadruply_header.cpp"
#include <time.h> // library
using namespace std;

int main(int argc, char const *argv[])
{

   clock_t start = clock(); // start to measure
   // QSL QSL(2);
   //  QSL QSL(10);
    QSL QSL(100);
   // QSL QSL(1000);
   // QSL QSL(500);
   //  QSL QSL(123);
   // QSL QSL(40);
   //  QSL QSL(5);
   //  QSL QSL(542);
   //  QSL QSL(123);
   //   bunları double da denedmi o yüzden burda yaptıkları belirtmedim
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
         QSL.insert(myemp);
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
         Employee *myemp = new Employee(global_max_id, add_salary, add_department);
         QSL.insert(myemp);
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
         QSL.update(update_id, update_salary, update_department);
      }
      else if (operation == "DELETE")
      {
         string delete_id_str;
         getline(operations, delete_id_str);
         int delete_id = stoi(delete_id_str);
         QSL.remove(delete_id);
      }
   }
   operations.close();
   clock_t end = clock(); // finish measure
   // measurement time in milliseconds
   //cout << (double)(end - start) * 1000;
   ofstream dosya("quadruply_output.csv");
   QSL.dumpToFile(dosya);
   dosya.close();
}