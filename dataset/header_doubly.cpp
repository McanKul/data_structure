/* @Author
StudentN ame :< mehmetcan kul >
StudentID :< 150210076 >
Date :< 04/01/2024 > */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class Employee // class tanÄ±mlÄ±yoruz
{
private:
   int id;
   int salary;
   int department;

public:
   Employee(int id, int salary, int department) : id(id), salary(salary), department(department){};
   ~Employee(){};
   int get_id()
   {
      return this->id;
   };

   int get_department()
   {
      return this->department;
   };

   int get_salary()
   {
      return this->salary;
   };

   void set_id(int id) // for set id
   {
      this->id = id;
   };

   void set_salary(int salary) // for set salary
   {
      this->salary = salary;
   };

   void set_department(int department) // for set department
   {
      this->department = department;
   };
};

class DSL_Node
{
private:
   Employee *data;
   DSL_Node *next;
   DSL_Node *below;

public:
   DSL_Node(Employee *data) : data(data), next(nullptr), below(nullptr){};
   ~DSL_Node(){

   };

   DSL_Node *get_next()
   {
      return this->next;
   };

   DSL_Node *get_below()
   {
      return this->below;
   };

   Employee *get_data()
   {
      return this->data;
   };

   void set_next(DSL_Node *value)
   {
      this->next = value;
   };

   void set_below(DSL_Node *value)
   {
      this->below = value;
   };

   void set_data(Employee *value)
   {
      this->data = value;
   };
};

class DSL
{
private:
   DSL_Node *start;
   DSL_Node *end;
   int height;
   int height_for_random;

public:
   DSL(int height_in)
   {
      srand(static_cast<unsigned int>(time(nullptr)));
      this->height_for_random = 1;
      this->start = nullptr;
      this->end = nullptr;
      this->height = height_in;
      Employee *sentinal1 = new Employee(-1, 0, 0);
      Employee *sentinal2 = new Employee(9999999, 0, 0);
      for (int i = 0; i < height_in; i++)
      {
         DSL_Node *start_node = new DSL_Node(sentinal1);
         DSL_Node *end_node = new DSL_Node(sentinal2);
         if (start == nullptr)
         {
            start = start_node;
            end = end_node;
         }
         else
         {
            start_node->set_below(this->start);
            end_node->set_below(this->end);
            start = start_node;
            end = end_node;
         }
         start->set_next(end);
      }
   };
   ~DSL(){

   };
   void insert(Employee *data)
   {
      // random sayÄ± Ã¼retme
      int random = rand() % 2 + 1;
      // random sayÄ± Ã¼retme kÄ±smÄ± bitti

      if ((random == 1) && (this->height_for_random < this->height))
      {
         this->height_for_random++;
      }
      else if ((random == 1) && (this->height_for_random == this->height))
      {
         this->height_for_random = 1;
      }
      /// eski add performası iyi değil
      // DSL_Node *temp = start;
      // DSL_Node *temp_header = nullptr;
      // for (int i = 0; i < (this->height - this->height_for_random); i++)
      // {
      //    temp = temp->get_below();
      // }
      // for (int i = 0; i < (this->height_for_random); i++)
      // {
      //    DSL_Node *new_node = new DSL_Node(data);
      //    while (temp->get_next()->get_data()->get_id() < data->get_id())
      //    {
      //       temp = temp->get_next();
      //    }
      //    if (temp_header == nullptr)
      //    {
      //       new_node->set_next(temp->get_next());
      //       temp->set_next(new_node);
      //       temp_header = new_node;
      //    }
      //    else
      //    {
      //       new_node->set_next(temp->get_next());
      //       temp->set_next(new_node);
      //       temp_header->set_below(new_node);
      //       temp_header = new_node;
      //    }
      //    if (temp->get_below() != nullptr)
      //    {
      //       temp = temp->get_below();
      //    }
      // };


      //üsttekine kısasla daha verimli çünkü skiplistin atlama özelliğini daha iyi kullanıyor
      DSL_Node *temp = start;
      DSL_Node *temp_header = nullptr;
      int height_for_add = this->height;
      for (int i = 0; i < (this->height); i++)
      {
         while (temp->get_next()->get_data()->get_id() < data->get_id())
         {
            temp = temp->get_next();
         }
         if (height_for_add <= (this->height - (this->height - this->height_for_random)))//ekleme yüksekliği eşik değer gibi bir şey eğer eşiği aşmıyorsa ekleme yapmıyor. atlama devam ediyor
         {
            DSL_Node *new_node = new DSL_Node(data);
            if (temp_header == nullptr)
            {
               new_node->set_next(temp->get_next());
               temp->set_next(new_node);
               temp_header = new_node;
            }
            else
            {
               new_node->set_next(temp->get_next());
               temp->set_next(new_node);
               temp_header->set_below(new_node);
               temp_header = new_node;
            }
         }
         if (temp->get_below() != nullptr)
         {
            temp = temp->get_below();
         }
         height_for_add--;
      };
   }

   bool search_for_update(int search_id, DSL_Node *(&test_emp))
   {
      DSL_Node *temp = this->start;
      for (int i = 0; i < this->height; i++)
      {
         while ((temp->get_next()->get_data()->get_id() < search_id))
         {
            temp = temp->get_next();
         }

         if (temp->get_next()->get_data()->get_id() == search_id)
         {
            test_emp = temp->get_next();
            return true;
         }
         else if (temp->get_below() != nullptr)
         {
            temp = temp->get_below();
         }
      }
      test_emp = nullptr;
      return false;
   }

   void update(int id, int salary, int department) // sadece tek nodu update etmek yeterli çünkü tüm nodelar aynı işçiyi gösteriyor
   {
      DSL_Node *current_node = nullptr;
      if (search_for_update(id, current_node))
      {
         Employee *myemp = current_node->get_data();
         myemp->set_salary(salary);
         myemp->set_department(department);
      }
      else
      {
         //cout << "ERROR: invalid ID to update\n";
      }
   }

   bool is_empty()
   {
      DSL_Node *current_node = start;
      while (current_node->get_below() != nullptr)
      {
         current_node = current_node->get_below();
      }

      if (current_node->get_next()->get_data()->get_id() == 9999999)
      {
         return true;
      }
      return false;
   }

   bool search_for_delete(int search_id, DSL_Node *root)
   {
      DSL_Node *temp = root;
      for (int i = 0; i < this->height; i++)
      {
         while ((temp->get_next()->get_data()->get_id() < search_id))
         {
            temp = temp->get_next();
         }

         if (temp->get_next()->get_data()->get_id() == search_id)
         {
            DSL_Node *for_delete = temp->get_next();
            temp->set_next(temp->get_next()->get_next());
            search_for_delete(search_id, temp);
            delete for_delete;
            return true;
         }
         else if (temp->get_below() != nullptr)
         {
            temp = temp->get_below();
         }
      }
      return false;
   }

   void remove(int remove_id)
   {
      if (is_empty())
      {
         //cout << "ERROR: There is no Employee\n";
         return;
      }
      if (search_for_delete(remove_id, this->start))
      {
         return;
      }
      else
      {
         //cout << "ERROR: invalid ID to delete\n";
      };
   }
   void dumpToFile(ofstream &dosya)
   {
      DSL_Node *temp = start;
      for (int i = 0; i < this->height - 1; i++)
      {
         temp = temp->get_below();
      }
      dosya << "Employee_ID;Salary;Department\n";
      temp = temp->get_next();
      while (temp->get_data()->get_id() != 9999999)
      {
         dosya << temp->get_data()->get_id() << ";" << temp->get_data()->get_salary() << ";" << temp->get_data()->get_department() << "\n";
         temp = temp->get_next();
      }
   };
};