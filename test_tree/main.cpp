#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Employee // class tanımlıyoruz
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

Employee::Employee(int id = 0, int salary = 0, int department = 0) // constructer
{
    this->id = id;
    this->salary = salary;
    this->department = department;
}
Employee::~Employee()
{
}

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

void Employee::set_id(int id) // for set id
{
    this->id = id;
}

void Employee::set_salary(int salary) // for set salary
{
    this->salary = salary;
}

void Employee::set_department(int department) // for set department
{
    this->department = department;
}

class Node
{
private:
    Employee *data;
    Node* left;
    Node* right;

public:
    Node(Employee *emp) : data(emp), left(nullptr), right(nullptr){};

    Employee *get_data()
    {
        return this->data;
    }

    Node *get_left()
    {
        return this->left;
    }
    Node *get_right()
    {
        return this->right;
    }
    void set_left(Node *emp)
    {
        this->left = emp;
    }
    void set_right(Node *emp)
    {
        this->right = emp;
    }
};

class BinaryTree
{
private:
    Node *root;

public:
    BinaryTree() : root(nullptr){};
    ~BinaryTree(){};

    void printToFile(ofstream &dosya){

        dosya<<"Employee_ID;Salary;Department\n";
        BinaryTree::inOrderToFile(dosya,this->root);
    };

void inOrderToFile(ofstream &dosya, Node* key)
    {
        if (key != nullptr)
        {
            inOrderToFile(dosya, key->get_left());
            dosya << key->get_data()->get_id()<<";"<<key->get_data()->get_salary()<<";"<<key->get_data()->get_department()<<endl;
            inOrderToFile(dosya,key->get_right());
        }
        else
        {
            return;
        }
    }

    void printToConsole()
    {
        BinaryTree::preOrder(this->root);
    }

    int getHeight(Node *key)
    {
        if (key == nullptr)
        {
            return 0;
        }
        else
        {
            int height = 1;
            int leftHeight = BinaryTree::getHeight(key->get_left());
            int rightHeight = BinaryTree::getHeight(key->get_right());

            if (leftHeight > rightHeight)
            {
                return height + leftHeight;
            }
            else
            {
                return height + rightHeight;
            }
        }
    };

    void preOrder(Node *key)
    {
        if (key != nullptr)
        {
            cout << key->get_data()->get_id() << endl;
            preOrder(key->get_left());
            preOrder(key->get_right());
        }
        else
        {
            return;
        }
    };

    void inOrder(Node *key)
    {
        if (key != nullptr)
        {
            inOrder(key->get_left());
            cout << key->get_data()->get_id()<<endl;
            inOrder(key->get_right());
        }
        else
        {
            return;
        }
    }

    Node *get_root()
    {
        return this->root;
    }

    void insert(Employee *data)
    {
        Node *newNode = new Node(data);

        if (this->root == nullptr)
        {
            this->root = newNode;
            return;
        }

        Node *current_node = root;
        while (current_node != nullptr)
        {
            if (current_node->get_data()->get_id() > data->get_id())
            {
                if (current_node->get_left() == nullptr)
                {
                    current_node->set_left(newNode);
                    return;
                }

                current_node = current_node->get_left();
            }
            else if (current_node->get_data()->get_id() < data->get_id())
            {
                if (current_node->get_right() == nullptr)
                {
                    current_node->set_right(newNode);
                    return;
                }

                current_node = current_node->get_right();
            }
            else
            {
                delete newNode;
                return;
            }
        }
    }

    bool contains(int id)
    {
        if (this->root == nullptr)
        {
            return false;
        }

        Node *current_node = root;
        while (current_node != nullptr)
        {
            if (current_node->get_data()->get_id() > id)
            {

                current_node = current_node->get_left();
            }
            else if (current_node->get_data()->get_id() < id)
            {

                current_node = current_node->get_right();
            }
            else
            {
                return true;
            }
        }
        return false;
    }

    void update(int id, int salary, int department)
    {
        if (!BinaryTree::contains(id))
        {
            cout << "ERROR: invalid ID to update";
        }
        else
        {
            Node *current_node = this->root;
            while (current_node != nullptr)
            {
                if (current_node->get_data()->get_id() > id)
                {
                    current_node = current_node->get_left();
                }
                else if (current_node->get_data()->get_id() < id)
                {
                    current_node = current_node->get_right();
                }
                else
                {
                    current_node->get_data()->set_salary(salary);
                    current_node->get_data()->set_department(department);
                    return;
                }
            }
        }
    }

    void remove(int id)
    {
        if (this->root == nullptr)
        {
            cout << "ERROR: There is no Employee";
        }
        if (!BinaryTree::contains(id))
        {
            cout << "ERROR: invalid ID to delete";
        }
        else
        {
            if (this->root->get_data()->get_id() == id)
            {
                if (this->root->get_left() != nullptr)
                {
                    Node *temp = this->root;
                    this->root = this->root->get_left();
                    Node *temp2 = this->root;

                    while (temp2->get_right() != nullptr)
                    {
                        temp2 = temp2->get_right();
                    }
                    temp2->set_right(temp->get_right());
                }
                else
                {
                    Node *temp = this->root;
                    this->root = this->root->get_right();
                    delete temp;
                }
            }
            else
            {
                Node *current_node = root;
                while (current_node != nullptr)
                {
                    if (current_node->get_data()->get_id() > id)
                    {
                        if (current_node->get_left()->get_data()->get_id() == id)
                        {
                            Node *temp = current_node;              // silinecek olanın parent
                            Node *temp2 = current_node->get_left(); // silinecek olan
                            Node *left_child = temp2->get_left();
                            Node *right_child = temp2->get_right();

                            if (left_child == nullptr)
                            {
                                temp->set_left(right_child);
                                delete temp2;
                                return;
                            }
                            else
                            {
                                temp->set_left(left_child);
                                delete temp2;
                                Node* last = left_child;
                                while (last->get_right() != nullptr)
                                {
                                    last = last->get_right();
                                }
                                last->set_right(right_child);
                                return;
                            }
                        }
                        else
                        {
                            current_node = current_node->get_left();
                        }
                    }
                    else if (current_node->get_data()->get_id() < id)
                    {
                        if (current_node->get_right()->get_data()->get_id() == id)
                        {
                            Node *temp = current_node;               // silinecek olanın parent
                            Node *temp2 = current_node->get_right(); // silinecek olan
                            Node *left_child = temp2->get_left();
                            Node *right_child = temp2->get_right();

                            if (temp2->get_left() == nullptr)
                            {
                                temp->set_right(right_child);
                                delete temp2;
                                return;
                            }
                            else
                            {
                                temp->set_right(left_child);
                                delete temp2;
                                Node* last = left_child;
                                while (last->get_right() != nullptr)
                                {
                                    last = last->get_right();
                                }
                                last->set_right(right_child);
                                return;
                            }
                        }
                        else
                        {
                            current_node = current_node->get_right();
                        }
                    }
                }
            }
        }
    }

    void add(int salary, int department,int &value){
        value++;
        Employee *myemp = new Employee(value, salary, department);
        BinaryTree::insert(myemp);
    }
};

int main(int argc, char const *argv[])
{
    BinaryTree tree;
    fstream dosya_oku(argv[1]);
    string satir = "";
    int global_max_id=0;
    

    if (dosya_oku.is_open())
    {
        getline(dosya_oku, satir);
        while (getline(dosya_oku, satir))
        {
            char employee_id[10]; // dosya okumak için tanımlama yapıyoruz string de olurdu ama başta böyle yaptım
            char employee_salary[10];
            char employee_department[10];
            int counter = 0; // her satırda id salary department kısmını hesaplamak için
            int y = 0;
            int integer_employee_id, integer_employee_salary, integer_employee_department; // id salary department
            int length = satir.length();
            for (int i = 0; i < length; i++)
            {
                if (counter == 0)
                {
                    if (satir[i] != ';')
                    {
                        employee_id[y] = satir[i]; // satırdan id okuma
                        y++;
                    }
                    else
                    {
                        counter += 1;
                        y = 0;
                        integer_employee_id = stoi(employee_id); // okunan idyi karşılaştırma için integer yapma
                    }
                }
                else if (counter == 1)
                {
                    if (satir[i] != ';')
                    {
                        employee_salary[y] = satir[i]; // satırdan salary okuma
                        y++;
                    }
                    else
                    {
                        counter += 1;
                        y = 0;
                        integer_employee_salary = stoi(employee_salary); // okunan salaryi karşılaştırma için integera çevirme
                    }
                }
                else if (counter == 2)
                {
                    if (satir[i] != '\n' || satir[i] != '\0') // department sonra ya null ya da kaçış satır gelebilir o yüzden böyle
                    {

                        employee_department[y] = satir[i]; // satırdan department okuma
                        y++;
                        integer_employee_department = stoi(employee_department); // departmenti karşılaştırma için integera çevirme
                    }
                }
            }
            Employee *myemp = new Employee(integer_employee_id, integer_employee_salary, integer_employee_department); // classa ekliyoruz
            global_max_id++;
            tree.insert(myemp);
            
        }
    }
    else
    {
        cout << "dosya açılamadı" << endl; // dosya açılmazsa diye uyarı
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
            tree.add(add_salary, add_department,global_max_id);
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
            tree.update(update_id, update_salary, update_department);
        }
        else if (operation == "DELETE")
        {
            string delete_id_str;
            getline(operations, delete_id_str);
            int delete_id = stoi(delete_id_str);
            tree.remove(delete_id);
        }
        else if (operation == "PRINT")
        {

            cout<< "P\n";
            tree.printToConsole();
        }
        else if (operation == "HEIGHT")
        {

            cout<< "H "<< tree.getHeight(tree.get_root())<<"\n";
        }
    }
    operations.close();

    
    return 0;
}
