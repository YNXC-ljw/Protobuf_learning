#include <iostream>
#include "contacts.pb.hpp"

int main()
{
    std::string people_str;
    {
        // 对联系人的信息使用 PB 进行序列化，并将结果打印出来
        contacts::PeopleInfo people;
        people.set_name("张三");
        people.set_age(20);
        if(!people.SerializeToString(&people_str))
        {
            std::cerr << "序列化失败!" << std::endl;
            return -1;
        }
        std::cout << "序列化成功，结果：" << people_str << std::endl;
    }
    {
        // 对序列化后的结果使用 PB 进行反序列化，并将结果打印出来
        contacts::PeopleInfo people;
        if(!people.ParseFromString(people_str))
        {
            std::cout << "反序列化失败！" << std::endl;
            return -1;
        }
        std::cout << "反序列化成功！" << std::endl
                    << "年龄：" << people.age() << std::endl
                    << "名字：" << people.name() << std::endl;
    }

    return 0;
}