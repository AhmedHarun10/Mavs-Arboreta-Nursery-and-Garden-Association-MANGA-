#ifndef _CUSTOMER_H
#define _CUSTOMER_H
#include <iostream>

class Customer
{
public:
    Customer(std::string name, std::string phone, std::string email);
    Customer(std::istream &ist);
    void save(std::ostream &ost);
    friend std::ostream &operator<<(std::ostream &ost, const Customer &customer);
     std::string get_name();

private:
    std::string _name;
    std::string _phone;
    std::string _email;
};
#endif
