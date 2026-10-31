#include <iostream>
#include <fstream>
#include "contacts.pb.h"

using namespace std;

void AddPeopleInfo(contacts2::PeopleInfo* people)
{
    // 1.添加联系人姓名
    cout << "-------------新增联系⼈-------------" << endl;
    cout << "请输入联系人姓名：" << endl;
    string name;
    getline(cin,name);
    people->set_name(name);

    // 2.添加联系人年龄
    cout << "请输入联系人年龄：" << endl;
    int age;
    cin >> age;
    people->set_age(age);
    cin.ignore(256,'\n');

    for(int i = 0;;i++)
    {
        // 3.添加联系人电话
        cout << "请输入联系人电话：" << i + 1 << "(只输入回车完成电话新增):";
        string number;
        getline(cin,number);
        if(number.empty()){
            break;
        }
        contacts2::PeopleInfo_Phone* phone = people->add_phone();
        phone->set_number(number);

        // 4.设置电话类别
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
            break;
        default:
            cout << "select error!" << endl;
            break;
        }
    }
    // 5.添加联系人地址
    contacts2::Address address;
    cout << "请输入联系人家庭住址:";
    string home_address;
    getline(cin,home_address);
    address.set_home_address(home_address);
    cout << "请输入联系人单位地址:";
    string unit_address;
    getline(cin,unit_address);
    address.set_unit_address(unit_address);
    // Address->Any
    people->mutable_data()->PackFrom(address);

    // 6.添加其他联系方式
    cout << "请选择要添加的其他联系方式: (1、qq    2.微信)";
    int other_contact;
    cin >> other_contact;
    cin.ignore(256,'\n');
    if(1 == other_contact){
        cout << "请输入联系人qq号:" << endl;
        string qq;
        getline(cin,qq);
        people->set_qq(qq);
    }else if(2 == other_contact){
        cout << "请输入联系人微信号:" << endl;
        string wechat;
        getline(cin,wechat);
        people->set_wechat(wechat);
    }else{
        cout << "选择有误，未设置联系人其他联系方式!" << endl;
    }

    // 7.添加联系人备注
    for(int i = 0;;i++)
    {
        cout << "请输入备注" << i + 1 << "标题(只输入回车完成备注新增): ";
        string remark_key;
        getline(cin,remark_key);
        if(remark_key.empty()){
            break;
        }
        cout << "请输入备注" << i + 1 << "内容：";
        string remark_value;
        getline(cin,remark_value);
        people->mutable_remark()->insert({remark_key,remark_value});
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