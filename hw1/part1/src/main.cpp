#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Employee   //class tanımlıyoruz
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

Employee::Employee(int id=0, int salary=0, int department=0) //constructer
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

void Employee::set_id(int id)   //for set id
{
    this->id = id;
}

void Employee::set_salary(int salary)   //for set salary
{
    this->salary = salary;
}

void Employee::set_department(int department)   //for set department
{
    this->department = department;
}

int employee_counter = 0; //işci ekleyip çıkarınca bu değişecek
Employee *employees = nullptr; //fonksiyonlarda kullanmak için global array
int max_id;

void ADD(int salary, int department)
{
    employee_counter++;
    max_id++;
    Employee *new_employees = new Employee[employee_counter]; // yeni array tanımlıyoruz 

    for (int i = 0; i < employee_counter - 1; i++)
    {
        new_employees[i] = employees[i]; //eski arrayi yenisine kopyalıyoruz
    }
    Employee myemp(max_id, salary, department);
    new_employees[employee_counter - 1] = myemp;  //yeni  arraye yeni işçi ekliyoruz
    delete[] employees; //eski arrayi siliyoruz
    employees = new_employees; //eski arraye yenisi kopyalıyoruz
}

void UPDATE(int id, int salary, int department, Employee arr[] = employees)
{
    bool unfound = true;  //işçi bulunamazsa fonksiyonu çalıştırmak için

    for (int i = 0; i < employee_counter; i++)
    {
        if (employees[i].get_id() == id)//işçilerinin idlerini verilen id ile kıyaslıyoruz
        {
            employees[i].set_salary(salary);
            employees[i].set_department(department); //id varsa salary ve department güncelleniyor
            unfound = false; //bulunamadı fonksiyonunu çalışmasını engelliyoruz
            break;
        }
    }

    if (unfound) //işçi bulunamazsa çalışacak fonksyon
    {
        cout << "ERROR: An invalid ID to update" << endl; 
    }
}

void DELETE(int id)
{
    bool unfound = true;
    if (employee_counter == 0)
    {
        cout << "ERROR: There is no Employee" << endl; //işçi sayısı sıfırsa doğrudan bu fonksiyon çalışımaz
    }
    else
    {
        for (int i = 0; i < employee_counter; i++)
        {
            if (employees[i].get_id() == id)
            {
                unfound = false;
            }
        }
    

    if (unfound)
    {
        cout << "ERROR: An invalid ID to delete" << endl;
    }
    else
    {   
   
        Employee *new_employees = new Employee[employee_counter-1];  
        //yeni array tanımlıyoruz bu kısımda yeni arrayi 1 kişi eksik tanımlıyoruz
        //çünkü arrayi önceden taradık silinen idnin var olduğunu anladık 
        int a = 0; //dışarda bir a değişkeni ile yeni arrayin indexini ayarlıyoruz for içinde de yapılabilir ama ilk yazarken hatırlamadım:((
        for (int i = 0; i < employee_counter; i++)
        {
            if(employees[i].get_id()!=id){ //eski arrayi yeni arraye kopyalıyoruz silenecek id gelirse pass geçiyoruz bu sayede
                new_employees[a] = employees[i];
                a++;
            }
        }
        employee_counter--; //içi sayısını azaltıyoruz ama max_id sabit kalmalı çünkü işçi sayısından bağımssız
        delete[] employees; // eski arrayi siliyoruz bu sayade girilen id kalıcı olarak gitti
        employees = new_employees; // eski arrayi yenisine eşitliyoruz
    }
    }
}

int main(int argc, char **argv)
{
    fstream satir_sayici(argv[1]); // işçileri önden saymak için dosyayı bir kez açıyoruz
    string gereksiz = ""; // okunan satırları saymak için fonksiyon istiyordu

    if (satir_sayici.is_open())
    {
        getline(satir_sayici, gereksiz);
        while (getline(satir_sayici, gereksiz))
        {
            employee_counter++;//işçi sayısı alıyoruz
        }
        max_id = employee_counter; // max id işçi sayısına eşit

        satir_sayici.close();
    }
    else
    {
        return 1;
    }

    employees = new Employee[employee_counter]; //arayimizi tanımlıyruz

    fstream dosya_oku(argv[1]);
    string satir = "";
    if (dosya_oku.is_open())
    {
        getline(dosya_oku, satir);
        int employee_place = 0; //employeeleri indexlerine göre koymak için 
        while (getline(dosya_oku, satir))
        {
            char employee_id[10]; // dosya okumak için tanımlama yapıyoruz string de olurdu ama başta böyle yaptım
            char employee_salary[10];
            char employee_department[10];
            int counter = 0; //her satırda id salary department kısmını hesaplamak için
            int y = 0;
            int integer_employee_id, integer_employee_salary, integer_employee_department; //id salary department  

            for (int i = 0; i < satir.length(); i++)
            {
                if (counter == 0)
                {
                    if (satir[i] != ';')
                    {
                        employee_id[y] = satir[i];// satırdan id okuma
                        y++;
                    }
                    else
                    {
                        counter += 1;
                        y = 0;
                        integer_employee_id = stoi(employee_id);//okunan idyi karşılaştırma için integer yapma
                    }
                }
                else if (counter == 1)
                {
                    if (satir[i] != ';')
                    {
                        employee_salary[y] = satir[i];//satırdan salary okuma
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
                    if (satir[i] != '\n' || satir[i] != '\0')//department sonra ya null ya da kaçış satır gelebilir o yüzden böyle
                    {
                        employee_department[y] = satir[i]; //satırdan department okuma
                        y++;
                        integer_employee_department = stoi(employee_department);//departmenti karşılaştırma için integera çevirme
                    }
                }
            }
            Employee myemp(integer_employee_id, integer_employee_salary, integer_employee_department);//classa ekliyoruz
            employees[employee_place] = myemp;//indexe göre yerine koyuyoruz
            employee_place++;//indexi arttırıyoruz
        }
    }
    else
    {
        cout << "dosya açılamadı" << endl;//dosya açılmazsa diye uyarı
    };
    dosya_oku.close();//dosya kapatma işlemi

    fstream operations(argv[2]);
    string operation = "";

    while (getline(operations, operation, ';'))
    {
        if (operation == "ADD")//ilk okunan değere göre devamındaki sayı sayısan agöre düzenlendi
        {
            string add_salary_str, add_department_str;
            getline(operations, add_salary_str, ';');
            getline(operations, add_department_str);
            int add_salary = stoi(add_salary_str);//okunan değerler integera çevrildi
            int add_department = stoi(add_department_str);//okunan değerler integera çevrildi
            ADD(add_salary, add_department);//gerekli fonksiyon çağrıldı
        }
        else if (operation == "UPDATE")
        {
            string update_id_str, update_salary_str, update_department_str;
            getline(operations, update_id_str, ';');
            getline(operations, update_salary_str, ';');
            getline(operations, update_department_str);
            int update_id = stoi(update_id_str);//okunan değerler integera çevrildi
            int update_salary = stoi(update_salary_str);//okunan değerler integera çevrildi
            int update_department = stoi(update_department_str);//okunan değerler integera çevrildi
            UPDATE(update_id, update_salary, update_department);//gerekli fonksiyon çağrıldı
        }
        else if (operation == "DELETE")
        {
            string delete_id_str;
            getline(operations, delete_id_str);
            int delete_id = stoi(delete_id_str);//okunan değerler integera çevrildi
            DELETE(delete_id);//gerekli fonksiyon çağrıldı
        }
    }
    operations.close();//dosya kapatma işlemi

    ofstream printer("array_solution.csv");//yazılcak dosya açıldı
    printer << "Employee_ID;Salary;Department\n";
    for (int i = 0; i < employee_counter; i++)//yeni dosyaya yazma işlemi
    {
        printer << employees[i].get_id() << ";" << employees[i].get_salary() << ";" << employees[i].get_department() << '\n';
    }
    printer.close();//dosya kapatma
    return 0;
}
