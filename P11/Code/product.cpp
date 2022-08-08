#include "product.h"
#include <cmath>
#include <string>
#include "tool.h"
Product::Product(std::string name, double price, std::string description)
    : _name{name}, _price{price}, _description{description}, _stocknum{++_nextsn} { }
std::string Product::to_string() const {
    return _name + " (Stock# " + std::to_string(_stocknum)
                 + ", $" + std::to_string(round(_price*100)/100) + ")\n  "
                 + _description;
}
std::ostream& operator<<(std::ostream& ost, const Product& product) {
    ost << product.to_string();
    return ost;
}
int Product::_nextsn = 0;
void Product::save(std::ostream &ost){
    ost<<_name<<'\n'<<_nextsn<<'\n'<<_stocknum<<'\n'<<_price<<'\n'<<_description<<std::endl;
}

Product::Product(std::istream &ist){
   std::getline(ist,_name);
   //std::cout<<_name<<std::endl;
   ist>>_nextsn;
  //std::cout<<_nextsn<<std::endl;
   ist.ignore(32767,'\n');
   ist>>_stocknum;
  //std::cout<<_stocknum<<std::endl;
   ist.ignore(32767,'\n');
   ist>>_price;
  //std::cout<<_price<<std::endl;
   ist.ignore(32767,'\n');
   std::getline(ist,_description);
  //std::cout<<_description<<std::endl;
  // std::cout<<"product"<<std::endl;
}
double Product::price(){
    return _price;
}

void Product::set_name(std::string name){
    std::string description= _description;
    _description=description;
    double price=_price;
    _price=price;
    _name=name;
}
void Product::set_description(std::string description){
     double price=_price;
    _price=price;
    std::string name=_name;
    _name=name;
    _description=description;

}
void Product::set_price(double price){
     std::string name=_name;
    _name=name;
    _price=price;
    std::string description= _description;
    _description=description;

}

