#include "order.h"

Order::Order(Customer customer):_customer{customer}
{
}
Order::Order(std::istream &ist):_customer{ist}
{

    int items;
    ist>>items;
    ist.ignore(32767,'\n');
    for (int i = 0; i < items; i++){
        _items.push_back(new Item{ist});
    }
}
void Order::save(std::ostream &ost){

    _customer.save(ost);
    ost<<_items.size()<<std::endl;
    for(auto i: _items){
        i->save(ost);
    }
}
void Order::add_item(Item item){
      _items.push_back(new Item{item});
}
double Order::total() const{
    double total;
    for(auto i : _items){
        total+=i->subtotal();
    }
    return total;
}

std::ostream &operator<<(std::ostream &ost,const Order &order){
    ost<<"For customer "<<order._customer<<" $"<<order.total()<<std::endl;
    for(int i=0;i<order._items.size();i++){
        ost<<*(order._items[i])<<std::endl;
      }
    return ost;
}
