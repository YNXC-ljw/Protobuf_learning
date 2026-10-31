#include <iostream>
#include <fstream>
#include "contacts.pb.h"

using namespace std;


void PrintContacks(contacts2::Contacts& contact)
{
    for(int i = 0;i < contact.contacts_size();i++)
    {
        cout << "----------------联系人" << i + 1 << "---------------" << endl;
        const contacts2::PeopleInfo& people = contact.contacts(i);
        cout << "联系人姓名：" << people.name() << endl;
        cout << "联系人年龄：" << people.age() << endl;
        for(int j = 0;j < people.phone_size();j++)
        {
            const contacts2::PeopleInfo_Phone& phone = people.phone(j);
            cout << "联系人电话" << j+1 << ":" << phone.number() ;
            cout << "   (" << phone.PhoneType_Name(phone.type()) << ")    " << endl;
        }
        if(people.has_data() && people.data().Is<contacts2::Address>()){
            contacts2::Address address;
            people.data().UnpackTo(&address);
            if(!address.home_address().empty()){
                cout << "联系人家庭地址：" << address.home_address() << endl;
            }
            if(!address.unit_address().empty()){
                cout << "联系人单位地址：" << address.unit_address() << endl;
            }
        }
    }
}
int main()
{
    contacts2::Contacts contacts;

    // 读取本地已存在的通讯录文件
    fstream input("contacts.bin",ios::in | ios::binary);
    if(!input){
        cerr << "contacts.bin file not find! create new file" << endl;
    }else if(!contacts.ParseFromIstream(&input)){
        cerr << "parse error" << endl;
        input.close();
        return -1;
    }

    // 打印通讯录列表
    PrintContacks(contacts);
    return 0;
}