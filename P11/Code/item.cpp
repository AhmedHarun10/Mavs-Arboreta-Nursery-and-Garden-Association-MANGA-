#include "item.h"
#include "tool.h"
#include "mulch.h"
#include "plant.h"

Item::Item(Product &product, int quantity):_product{&product},_quantity{quantity}{
}
Item::Item(std::istream &ist){
    std::string type;
    ist>>_quantity;
    ist.ignore(32767,'\n');
    std::getline(ist,type);
    if(type=="tool"){
        _product=new Tool{ist};    
    }
    else if (type=="plant"){
        _product=new Plant{ist};    
    }
    else if (type=="mulch"){
        _product=new Mulch{ist};    
    }
}

void Item::save(std::ostream &ost){
    ost<<_quantity<<std::endl;
    _product->save(ost);
}
double Item::subtotal(){
    return _product->price()*_quantity;
}
std::ostream &operator<<(std::ostream &ost, const Item &item){
    ost<<item._quantity<<" "<<*item._product<<std::endl;
    return ost;
}
