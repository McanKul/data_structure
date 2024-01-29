/* @Author
StudentN ame :< mehmetcan kul >
StudentID :< 150210076 >
Date :< 04/01/2024 > */

// buradaki çoğu ödevin diğer kısmında yatpım o yüzden burada pek açıklama yapmadım
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
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

class QSL_Node
{
private:
    Employee *data;
    QSL_Node *next;
    QSL_Node *prev;
    QSL_Node *below;
    QSL_Node *above;

public:
    QSL_Node(Employee *data) : data(data), next(nullptr), prev(nullptr), below(nullptr), above(nullptr){};
    ~QSL_Node(){

    };

    QSL_Node *get_next()
    {
        return this->next;
    };
    QSL_Node *get_prev()
    {
        return this->prev;
    };
    QSL_Node *get_below()
    {
        return this->below;
    };
    QSL_Node *get_above()
    {
        return this->above;
    };
    Employee *get_data()
    {
        return this->data;
    };

    void set_next(QSL_Node *value)
    {
        this->next = value;
    };
    void set_prev(QSL_Node *value)
    {
        this->prev = value;
    };
    void set_below(QSL_Node *value)
    {
        this->below = value;
    };
    void set_above(QSL_Node *value)
    {
        this->above = value;
    };
    void set_data(Employee *value)
    {
        this->data = value;
    };
};

class QSL
{
private:
    QSL_Node *start;
    QSL_Node *end;
    int height;
    int height_for_random;

public:
    srand(static_cast<unsigned int>(time(nullptr)));
    QSL(int height_in)
    {
        this->height_for_random = 1;
        this->start = nullptr;
        this->end = nullptr;
        this->height = height_in;
        Employee *sentinal1 = new Employee(-1, 0, 0);
        Employee *sentinal2 = new Employee(9999999, 0, 0);
        for (int i = 0; i < height_in; i++)
        {
            QSL_Node *start_node = new QSL_Node(sentinal1);
            QSL_Node *end_node = new QSL_Node(sentinal2);
            if (start == nullptr)
            {

                start = start_node;
                end = end_node;
            }
            else
            {
                start_node->set_below(this->start);
                this->start->set_above(start_node);
                end_node->set_below(this->end);
                this->end->set_above(end_node);
                start = start_node;
                end = end_node;
            }
            start->set_next(end);
            end->set_prev(start);
        }
    };
    ~QSL(){

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
        else if ((random == 1) && (this->height_for_random = this->height))
        {
            this->height_for_random = 1;
        }

        QSL_Node *temp = start;
        QSL_Node *temp_header = nullptr;
        int height_for_add = this->height;
        for (int i = 0; i < (this->height); i++)
        {
            
            while (temp->get_next()->get_data()->get_id() < data->get_id())
            {
                temp = temp->get_next();
            }
            if (height_for_add <= (this->height - (this->height - this->height_for_random)))
            {
                QSL_Node *new_node = new QSL_Node(data);
                if (temp_header == nullptr)
                {
                    new_node->set_next(temp->get_next());
                    temp->get_next()->set_prev(new_node);
                    temp->set_next(new_node);
                    new_node->set_prev(temp);
                    temp_header = new_node;
                }
                else
                {
                    new_node->set_next(temp->get_next());
                    temp->get_next()->set_prev(new_node);
                    temp->set_next(new_node);
                    new_node->set_prev(temp);
                    temp_header->set_below(new_node);
                    new_node->set_above(temp_header);
                    temp_header = new_node;
                }
                temp = temp->get_below();
                height_for_add--;
            }
        };
    }

    bool search(int search_id, QSL_Node *(&test_emp))//search node döndürüyor ve gerekli yerlerde bu nodu kullanarak update veya delete yapıyorum 4 lü olmasının avantajı sayesinde aranılan nodun tepesini bulsak yetio
    {
        QSL_Node *temp = this->start;
        for (int i = 0; i < this->height; i++)
        {
            while ((temp->get_next()->get_data()->get_id() < search_id) && (temp->get_next()->get_data()->get_id() != 9999999))
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

    void update(int id, int salary, int department)
    {
        QSL_Node *current_node = nullptr;
        if (search(id, current_node))
        {
            Employee *myemp = current_node->get_data();
            myemp->set_salary(salary);
            myemp->set_department(department);
        }
        else
        {
            cout << "ERROR: invalid ID to update\n";
        }
    }

    bool is_empty()
    {
        QSL_Node *current_node = start;
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

    void remove(int remove_id)
    {
        if (is_empty())
        {
            cout << "ERROR: There is no Employee\n";
            return;
        }
        QSL_Node *current_node = nullptr;
        if (search(remove_id, current_node))
        {
            delete current_node->get_data();
            while (current_node != nullptr)
            {
                QSL_Node *for_prev = current_node->get_prev();
                QSL_Node *for_next = current_node->get_next();
                for_prev->set_next(for_next);
                for_next->set_prev(for_prev);
                QSL_Node *for_delete = current_node;
                current_node = current_node->get_below();
                delete for_delete;
            }
        }
        else
        {
            cout << "ERROR: invalid ID to delete\n";
        };
    }
    void dumpToFile(ofstream &dosya)
    {
        QSL_Node *temp = start;
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