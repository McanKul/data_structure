#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Employee
{
private:
    int id;
    int salary;
    int department;

public:
    Employee() {}
    ~Employee() {}
    void setSalary(int salary) { this->salary = salary; }
    void setId(int id) { this->id = id; }
    void setDepartment(int department) { this->department = department; }
    int getId() { return this->id; }
    int getSalary() { return this->salary; }
    int getDepartment() { return this->department; }
};

void addEmployee(Employee* &array, int &employeeCount, int newSalary, int newDepartment, int &maxId);
void deleteEmployee(Employee* &array, int &employeeCount, int deletedId);
void updateEmployee(Employee* array, int employeeCount, int updatedId, int newSalary, int newDepartment);
void printArray(Employee* array, int employeeCount);

int main(int argc, char **argv)
{
    fstream line_counter(argv[1], ios::in);
    int initialSize = 0;
    int maxId;
    string temp;
    getline(line_counter, temp);
    while (getline(line_counter, temp))
    {
        initialSize++;
    }
    maxId = initialSize;
    line_counter.close();

    fstream employeeFile(argv[1]);
    employeeFile.seekg(0);
    Employee* array = new Employee[initialSize];

    string line;
    string empId, empSalary, empDepartment;
    int intId, intSalary, intDepartment;
    int employeeCount = 0;

    getline(employeeFile, line);
    while(getline(employeeFile, line))
    {

        
        Employee emp;
        stringstream ss(line);

        getline(ss, empId, ';');
        getline(ss, empSalary, ';');
        getline(ss, empDepartment);

        intId = stoi(empId);
        intSalary = stoi(empSalary);
        intDepartment = stoi(empDepartment);

        emp.setId(intId);
        emp.setSalary(intSalary);
        emp.setDepartment(intDepartment);

        array[employeeCount] = emp;

        employeeCount++;
    }

    employeeFile.close();

    fstream operationFile;
    operationFile.open(argv[2], ios::in);

    string line2 = "";

    while (getline(operationFile, line2))
    {
        stringstream ss2(line2);

        string operation, num1="", num2="", num3="";

        getline(ss2, operation, ';');

        if (operation == "ADD")
        {
            getline(ss2, num1, ';');
            getline(ss2, num2);
            addEmployee(array, employeeCount, stoi(num1), stoi(num2), maxId);
        }
        else if (operation == "UPDATE")
        {
            getline(ss2, num1, ';');
            getline(ss2, num2, ';');
            getline(ss2, num3);

            updateEmployee(array, employeeCount, stoi(num1), stoi(num2), stoi(num3));
        }
        else if (operation == "DELETE")
        {
            getline(ss2, num1);
            deleteEmployee(array, employeeCount, stoi(num1));
        }
    }

    operationFile.close();

    printArray(array, employeeCount);

    ofstream finalCsv;
    finalCsv.open("array_solution.csv");
    finalCsv << "Employee_ID;Salary;Department" << endl;

    for (int i = 0; i < employeeCount-1; i++)
    {
        finalCsv << array[i].getId() << ";" << array[i].getSalary() << ";" << array[i].getDepartment() << endl;
    }

    delete[] array;
    finalCsv.close();

    return 0;
}

void printArray(Employee* array, int employeeCount)
{
    for (int i = 0; i < employeeCount; i++)
    {
        cout << array[i].getId() << " " << array[i].getSalary() << " " << array[i].getDepartment() << endl;
    }
}

void addEmployee(Employee* &arr, int &employeeCount, int newSalary, int newDepartment, int &maxId)
{
    maxId++;
    employeeCount++;


    Employee* newArr = new Employee[employeeCount];
    for (int i = 0; i < employeeCount-1; i++)
    {
        newArr[i] = arr[i];
    }
    Employee newEmployee;
     newEmployee.setId(maxId);
    newEmployee.setSalary(newSalary);
    newEmployee.setDepartment(newDepartment);
    newArr[employeeCount-1] = newEmployee;
    delete[] arr;
    arr = newArr;

}


void updateEmployee(Employee* arr, int employeeCount, int updatedId, int newSalary, int newDepartment)
{
    bool isWorked = false;
    for (int i = 0; i < employeeCount; i++)
    {
        if (arr[i].getId() == updatedId)
        {
            arr[i].setSalary(newSalary);
            arr[i].setDepartment(newDepartment);
            isWorked = true;
        }
    }

    if (!isWorked)
    {
        cout << "ERROR: Geçersiz bir ID güncelleme işlemi" << endl;
    }
}

void deleteEmployee(Employee* &arr, int &employeeCount, int deletedId)
{
    bool isFound = false;
    if (employeeCount == 0)
    {
        cout << "HATA: Silinecek bir çalişan yok!" << endl;
    }
    else
    {
        for (int i = 0; i < employeeCount; i++)
        {
            if (arr[i].getId() == deletedId)
            {
                isFound = true;
                break;
            }
        }

        if (isFound)
        {
            employeeCount--;
            Employee* newArr = new Employee[employeeCount];
            int k = 0;
            for (int i = 0; i <= employeeCount; i++)
            {
                if (arr[i].getId() != deletedId)
                {
                    newArr[k] = arr[i];
                    k++;
                }else{
                  
                }
            }

            delete[] arr;
            arr = newArr;
            
        }
        else
        {
            cout << "HATA: Belirtilen ID'ye sahip bir çalişan bulunamadi" << endl;
        }
    }
}
