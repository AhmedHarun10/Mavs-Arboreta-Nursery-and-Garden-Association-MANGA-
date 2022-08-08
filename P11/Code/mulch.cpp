#include "mulch.h"
#include <vector>
Mulch::Mulch(std::string name, double price, std::string description, int volume, Material material)
    : Product(name, price, description), _volume{volume}, _material{material} { }
std::string Mulch::to_string() const {
    return Product::to_string() + "\n  Volume: " + std::to_string(_volume) + " ft³\n  Material: " + ::to_string(_material);
}
std::ostream& operator<<(std::ostream& ost, const Material& material) {
    ost << to_string(material);
    return ost;
}
std::string to_string(Material material) {
    if(material == Material::RUBBER) return "rubber";
    else if(material == Material::PINE) return "pine";
    else if(material == Material::CEDAR) return "cedar";
    else if(material == Material::HARDWOOD) return "hardwood";
    else throw std::out_of_range("Invalid Material value");
}

std::string to_string(int material) {
    if(material ==0) return "rubber";
    else if(material == 1) return "pine";
    else if(material == 2) return "cedar";
    else if(material == 3) return "hardwood";
    else throw std::out_of_range("Invalid Material value");
}

Material from_string_mat(std::string material) {
    if(material == "rubber") return Material::RUBBER;
    else if(material == "pine") return Material::PINE;
    else if(material == "cedar") return Material::CEDAR;
    return Material::HARDWOOD;
}


void Mulch::save(std::ostream &ost){
    ost<<"mulch"<<std::endl;
    Product::save(ost);
    ost<<_volume<<std::endl;
    ost<<::to_string(_material)<<std::endl;
}
Mulch::Mulch(std::istream &ist)
:Product(ist){
    std::string mat;
    ist>>_volume;
    ist.ignore(32767,'\n');
    std::getline(ist,mat);
   // std::cout<<mat<<std::endl;
   _material=from_string_mat(mat);
   // std::cout<<"mulch complete"<<std::endl;
}

