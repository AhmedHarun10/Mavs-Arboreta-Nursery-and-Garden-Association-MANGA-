#include "store.h"
#include <iostream>
#include "tool.h"
#include "customer.h"
#include <string>
Store::Store(std::string name) : _name{name} {}

void Store::save(std::ostream &ost)
{
    ost << _name << std::endl;
    ost << _products.size() << std::endl;
    for (auto P : _products)
    {
        P->save(ost);
    }
    ost << _customers.size() << std::endl;
    for (auto C : _customers)
    {
        C->save(ost);
    }
    ost<<store.size()<<std::endl;
    for(auto o: store)
    {
        o->save(ost);
    }
}
Store::Store(std::istream &ist)
{
    int length, length2;
    int num;
    std::string store_name;
    std::string type;
    std::getline(ist, _name);
    ist >> length;
    ist.ignore(32767, '\n');
    for (int i = 0; i < length; i++)
    {
        std::getline(ist, type);
        if (type == "tool")
        {
            _products.push_back(new Tool(ist));
        }
        else if (type == "mulch")
        {
            _products.push_back(new Mulch(ist));
        }
        else
        {
            _products.push_back(new Plant(ist));
        }
    }
    ist >> length2;
    ist.ignore(32767, '\n');
    for (int i = 0; i < length2; i++)
    {
        _customers.push_back(new Customer{ist});
    }
    ist>>length2;
    ist.ignore(32767, '\n');
    for (int i = 0; i < length2; i++){
        store.push_back(new Order{ist});
    }
}
void Store::add_product(const Tool &product) { _products.push_back(new Tool{product}); }
void Store::add_product(const Plant &product) { _products.push_back(new Plant{product}); }
void Store::add_product(const Mulch &product) { _products.push_back(new Mulch{product}); }
int Store::products() { return _products.size(); }
Product &Store::product(int index) { return *_products.at(index); }
void Store::add_customer(Customer &customer) { 
_customers.push_back(new Customer{customer}); 
std::sort((_customers.begin()), (_customers.end()), [](Customer *lfh, Customer *rhs) { return lfh->get_name() < rhs->get_name(); });
}
int Store::add_order(const Customer &customer){
   store.push_back(new Order{customer});
    return store.size()-1;
}
void Store::add_item(int order, Product &product, int quantity){

    store[order]->add_item(Item{product,quantity});
}
const Customer &Store::customer(int index) { return *_customers.at(index); }
int Store::customers() { return _customers.size(); }


void Store::replace_product(std::string type,int index){

    {
    Gtk::Dialog dialog{"Enter Plant Product Info"};
    Gtk::Grid grid;

    std::ostringstream oss;
    oss<<*(_products[index])<<std::endl;
    std::string s=oss.str();
    std::string name , price ,description,temp,temp_species,temp_expo,species,exp;
    name=s.substr(0, s.find("("));
    price=s.substr(s.find("$")+1,9);

    std::stringstream iss{s};
    std::string SingleLine;
	getline(iss, SingleLine, '\n');
	temp = SingleLine;

	getline(iss, SingleLine, '\n');
	description = SingleLine;
	getline(iss, SingleLine, '\n');
	temp_species = SingleLine;
    if(type!="Tool"){
        try{
            getline(iss, SingleLine, '\n');
	        temp_expo = SingleLine;
            species=temp_species.substr(temp_species.find(":")+2,temp_species.size()-1);
            exp=temp_expo.substr(temp_expo.find(":")+2,temp_expo.size()-1);
              }
        catch(std::exception& ex)
            {
                
            }
    }

    Gtk::Label l_name{"Name"};
    Gtk::Entry e_name;
    e_name.set_placeholder_text(name);
    grid.attach(l_name, 0, 0, 1, 1);
    grid.attach(e_name, 1, 0, 2, 1);

    Gtk::Label l_description{"Description"};
    Gtk::Entry e_description;
    e_description.set_placeholder_text(description);
    grid.attach(l_description, 0, 1, 1, 1);
    grid.attach(e_description, 1, 1, 2, 1);

    Gtk::Label l_price{"Price"};
    Gtk::Entry e_price;
    e_price.set_placeholder_text(price);
    grid.attach(l_price, 0, 2, 1, 1);
    grid.attach(e_price, 1, 2, 2, 1);
    

    dialog.get_content_area()->add(grid);

    dialog.add_button("Enter", Gtk::RESPONSE_OK);
    dialog.add_button("Cancel", Gtk::RESPONSE_CANCEL);
    dialog.show_all();
    int response;
    int exposure;
    response = dialog.run();
      if (response == Gtk::RESPONSE_OK)
          {
                std::string check1,check2,check3;
                check1=e_name.get_text();
                check2=e_description.get_text();
                check3=e_price.get_text();

                if(!check1.empty()){
                    _products[index]->set_name(e_name.get_text());
                }
                    

                 if(!check2.empty()){
                _products[index]->set_description(e_description.get_text());
                }

                if(!check3.empty()){
                       double new_price=std::stod(e_price.get_text());
                    _products[index]->set_price(new_price);
                }   
      
          }
    }
}

