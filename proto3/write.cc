#include <iostream>
#include <fstream>
#include "contacts.pb.h"

using namespace std;

void AddPeopleInfo(contacts2::PeopleInfo* people)
{
    cout << "-------------新增联系⼈-------------" << endl;
    cout << "请输入联系人姓名：" << endl;
    string name;
    getline(cin,name);
    people->set_name(name);

    cout << "请输入联系人年龄：" << endl;
    int age;
    cin >> age;
    people->set_age(age);
    cin.ignore(256,'\n');

    for(int i = 0;;i++)
    {
        cout << "请输入联系人电话：" << i + 1 << "(只输入回车完成电话新增):";
        string number;
        getline(cin,number);
        if(number.empty()){
            break;
        }
        contacts2::PeopleInfo_Phone* phone = people->add_phone();
        phone->set_number(number);

        cout << "请输入电话类型(1、固定电话 2、移动电话)：";
        int type;
        cin >> type;
        cin.ignore(256,'\n');
        switch (type)
        {
        case 1:
            phone->set_type(contacts2::PeopleInfo_Phone_PhoneType::PeopleInfo_Phone_PhoneType_MP);
            break;
        case 2:
            phone->set_type(contacts2::PeopleInfo_Phone_PhoneType::PeopleInfo_Phone_PhoneType_TEL);
        default:
            cout << "select error!" << endl;
            break;
        }
    }
    cout << "-----------添加联系⼈成功-----------" << endl;
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

    // 向通讯录中添加一个联系人信息
    AddPeopleInfo(contacts.add_contacts());

    // 将通讯录写入本地文件中
    fstream output("contacts.bin",ios::out | ios::binary | ios::trunc);
    if(!contacts.SerializeToOstream(&output)){
        cerr << "write error!" << endl;
        input.close();
        output.close();
        return -1;
    }
    cout << "write success!" << endl;
    input.close();
    output.close();
    return 0;
}