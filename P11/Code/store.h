
#ifndef __STORE_H
#define __STORE_H

#include "tool.h"
#include "plant.h"
#include "mulch.h"
#include "customer.h"
#include "order.h"
#include <vector>
#include <gtkmm.h>
#include <algorithm>
class Store
{

private:
    std::string _name;
    Product *_product;
    std::vector<Product *> _products;
    std::vector<Customer *> _customers;
    typedef std::vector<Order*> Stores;
    Stores store;

public:
    Store(std::string name);
    Store(std::istream &ist);
    void save(std::ostream &ost);
    void add_product(const Tool &product);
    void add_product(const Plant &product);
    void add_product(const Mulch &product);
    std::string name();
    void add_customer(Customer &customer);
    int products();
    Product &product(int index);
    int customers();
    const Customer &customer(int index);

    int add_order(const Customer &customer);
    void add_item(int order, Product &product, int quantity);
    
    void replace_product(std::string type,int index);

    typedef Stores::iterator iterator;
    typedef Stores::const_iterator const_iterator;
    iterator begin() { return store.begin(); }
    iterator end() { return store.end(); }
};
#endif

