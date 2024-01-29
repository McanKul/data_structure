#include <iostream>
#include <fstream>
using namespace std;
int employee_counter = 0; // kaç tane işçi var
int max_id;               // en son giren işçinin id_si
fstream file;        // file i global tanımlıyoruz
string satir = "";   // okuma işlemleri için satırı da global

void ADD(int salary, int department)
{
    file.clear(); // her fonksiyonun başında temizleme yapıp cursorı olması gerekn yere alıyoruz
    file.seekg(0, ios::end);
    file << max_id << ";" << salary << ";" << department << "\n"; //add fonksiyonun için yazma kısmı
    max_id++; //id ve işçi sayısını arttır
    employee_counter++;
}

void UPDATE(int id, int salary, int department)
{
    bool unfound = true; //işçi bulunamazsa if condition çalışması için 
    file.clear();
    file.seekg(0);
    getline(file, satir);//satır okuma işlemi bir kez yaparak baştaki gereksiz kısmı atlıyoruz
    while (getline(file, satir))//satır okuyarak idyi bulma
    {
        string employee_id = "";
        for (int i = 0; i < satir.length(); i++) //id satrın tamamını kaplayamayacağı iççin loopa fazladan değer vervemk için tüm satır uzunluğu max değer
        {
            if (satir[i] != ';')//noktalı vrigüle kadar id kısmını buluyoruz
            {
                employee_id += satir[i];
            }
            else
            {
                break;
            }
        }
        int intid = stoi(employee_id);//okunan idyi integera çeviriyoruz
        if (intid == id)//eğer id istenilen id ise burası çalışır
        {
            file.seekp(-(satir.length() + 1), ios::cur);//cursorı satırın başına atıyoruz en son kaçış satırı okunduğu için +1 değeri veriyoruz
            file << id << ";" << salary << ";" << department;
            unfound = false;//işçi bulunamadı false a çeviireke işçi bulunamadı kısmından kaçıyrouz
            break;
        }
    }
    if (unfound) //işçi bulunamazsa çalışır
    {
        cout << "ERROR: An invalid ID to update" << endl;
    }
}

void DELETE(int id, char **argv)
{
    if (employee_counter == 0)//eğer işçi yoksa çalışır
    {
        cout << "ERROR: There is no Employee" << endl;
        file.clear();
        fstream dosya(argv[1], ios::out | ios::trunc);//dosyayı bu modda açık kapatarak içindeki tüm veriyi siliyoruz overwrite yaptığımız için veriyi silmemiz gerekiyor
        dosya.close();
        file.seekp(0);
        file << "Employee_ID;Salary;Department\n";//dosya tamamen boş olduğu için en baş değerleri tekrar yazdırıyoruz
    }
    else
    {
        bool unfound = true;//işçi yoksa if condition çalıştırmak için
        string yeni_sayfa = "";//silinecek id hariç kalan satırları string ifadeye eklemek için boş string
        file.clear();
        file.seekg(0);
        getline(file, satir);
        yeni_sayfa = satir;
        yeni_sayfa += "\n";
        while (getline(file, satir))
        {
            string employee_id = "";
            for (int i = 0; i < satir.length(); i++)
            {
                if (satir[i] != ';')
                {
                    employee_id += satir[i];//id buluyoruz
                }
                else
                {
                    break;
                }
            }
            int intid = stoi(employee_id);
            if (intid == id)//silinecek id ise işçi sayısını azaltıp işçi bulunamadı çalıştırmamak için değerini değiştiriyoruz
            {
                unfound = false;
            }
            else
            {
                yeni_sayfa += satir;//okunan satır silinecek satır değilse stringe ekliyoruz 
                yeni_sayfa += "\n";
            }
        }

        file.clear();
        fstream dosya(argv[1], ios::out | ios::trunc);//dosyayı bu modda açıp kapatarak overwrite yerine silinmiş boş dosyaya yazıyoruz
        dosya.close();

        file.seekp(0);
        file << yeni_sayfa;//dosyaya yazma işini tamamlıyoruz

        if (unfound)
        {
            cout << "ERROR: An invalid ID to delete" << endl;
        }
        else
        {
            employee_counter--;//eğer işçi bulunduysa işçiyi toplam işçiden azaltıyoruz
        }
    }
}

int main(int argc, char **argv)
{
    file.open(argv[1], ios::out | ios::in);
    fstream operations(argv[2]);
    string operation = "";
    while (getline(file, satir))
    {
        employee_counter++;
    }
    max_id = employee_counter;//satır sayısından işçi sayısını buluyoruz ve max_id ona göre düzenliyoruz
    file.clear();

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
            DELETE(delete_id,argv);//gerekli fonksiyon çağrıldı
        }
    }
    operations.close();//doaya kapatma

    file.close();//dosya kapatma
    return 0;
}
