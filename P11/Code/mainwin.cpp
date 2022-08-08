#include "mainwin.h"
#include "store.h"
#include "entrydialog.h"
#include "customer.h"
#include <iostream>
#include "product.h"
#include <fstream>
#include "item.h"
#include <unistd.h>
//git add about.png box.png cloud-computing2.png cloud-computing.png customer.h customer.png entrydialog.cpp entrydialog.h garden-tool.png item.cpp box.png item.h main.cpp mainwin.cpp mainwin.h Makefile mulch.cpp mulch.h order.cpp ordered.png order.h plant.cpp plant.h plant-with-leaves.png potting-soil.png product.h ///Scrum_MANGA.ods shopping-bag.png store.cpp store.h tool.cpp tool.h

Mainwin::Mainwin() : store{nullptr}, filename{"untitled.MANGA"}
{
    //Window set-up
    set_default_size(400, 200);
    set_title("MANGA Magic");

    //create and add a vertical box to the window
    
    Gtk::ScrolledWindow *scroll=Gtk::manage(new Gtk::ScrolledWindow);
    add(*scroll);
    Gtk::Box *vbox = Gtk::manage(new Gtk::VBox);
    scroll->add(*vbox);

    //create a menu bar and add it to the verical box
    Gtk::MenuBar *menubar = Gtk::manage(new Gtk::MenuBar);
    vbox->pack_start(*menubar, Gtk::PACK_SHRINK, 0);

    Gtk::Toolbar *toolbar = Gtk::manage(new Gtk::Toolbar);
    vbox->pack_start(*toolbar, Gtk::PACK_SHRINK, 0);

    //create a menu item, add it to the menu bar and create a submenu for file
    Gtk::MenuItem *menuitem_file = Gtk::manage(new Gtk::MenuItem("_File", true));
    menubar->append(*menuitem_file);
    Gtk::Menu *filemenu = Gtk::manage(new Gtk::Menu());
    menuitem_file->set_submenu(*filemenu);

    //create a new store drop down option
    Gtk::MenuItem *menuitem_new = Gtk::manage(new Gtk::MenuItem("_New Store", true));
    menuitem_new->signal_activate().connect([this] { this->on_new_store_click(); });
    filemenu->append(*menuitem_new);

    Gtk::ToolButton *new_store_button = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::NEW));
    new_store_button->set_tooltip_markup("Open a new store");
    new_store_button->signal_clicked().connect([this] { this->on_new_store_click(); });
    toolbar->append(*new_store_button);

    Gtk::MenuItem *menuitem_save = Gtk::manage(new Gtk::MenuItem("_Save", true));
    menuitem_save->signal_activate().connect([this] { this->on_save_click(); });
    filemenu->append(*menuitem_save);

    Gtk::ToolButton *save_store_button = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::SAVE));
    save_store_button->set_tooltip_markup("Save store");
    save_store_button->signal_clicked().connect([this] { this->on_save_click(); });
    toolbar->append(*save_store_button);

    Gtk::MenuItem *menuitem_save_as = Gtk::manage(new Gtk::MenuItem("_Save As", true));
    menuitem_save_as->signal_activate().connect([this] { this->on_save_as_click(); });
    filemenu->append(*menuitem_save_as);

    Gtk::ToolButton *save_as_store_button = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::SAVE_AS));
    save_as_store_button->set_tooltip_markup("Save Store As");
    save_as_store_button->signal_clicked().connect([this] { this->on_save_as_click(); });
    toolbar->append(*save_as_store_button);

    Gtk::MenuItem *menuitem_open = Gtk::manage(new Gtk::MenuItem("_Open", true));
    menuitem_open->signal_activate().connect([this] { this->on_open_click(); });
    filemenu->append(*menuitem_open);

    Gtk::ToolButton *open_store_button = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::OPEN));
    open_store_button->set_tooltip_markup("Open Store");
    open_store_button->signal_clicked().connect([this] { this->on_open_click(); });
    toolbar->append(*open_store_button);

    //create quit as a a menu item of file and add to file menu also connect to observer via lambda function
    Gtk::MenuItem *menuitem_quit = Gtk::manage(new Gtk::MenuItem("_Quit", true));
    menuitem_quit->signal_activate().connect([this] { this->on_quit_click(); });
    filemenu->append(*menuitem_quit);

    //create an insert item and add to the menu bar and also a drop down menu for insert
    Gtk::MenuItem *menuitem_insert = Gtk::manage(new Gtk::MenuItem("_insert", true));
    menubar->append(*menuitem_insert);
    Gtk::Menu *insertmenu = Gtk::manage(new Gtk::Menu());

    menuitem_insert->set_submenu(*insertmenu);

    //insert a drop down menu item of customer into the insert menu
    Gtk::MenuItem *menuitem_customer = Gtk::manage(new Gtk::MenuItem("Customer", true));
    menuitem_customer->signal_activate().connect([this] { this->on_new_customer_click(); });
    insertmenu->append(*menuitem_customer);

    Gtk::Image *add_customer_image = Gtk::manage(new Gtk::Image{"add_customer.png"});
    Gtk::ToolButton *insert_customer_button = Gtk::manage(new Gtk::ToolButton(*add_customer_image));
    insert_customer_button->set_tooltip_markup("Insert Customer");
    insert_customer_button->signal_clicked().connect([this] { this->on_new_customer_click(); });
    toolbar->append(*insert_customer_button);

    Gtk::MenuItem *menuitem_order = Gtk::manage(new Gtk::MenuItem("Order", true));
    menuitem_order->signal_activate().connect([this] { this->on_new_order_click(); });
    insertmenu->append(*menuitem_order);

    Gtk::Image *add_order_image = Gtk::manage(new Gtk::Image{"order.png"});
    Gtk::ToolButton *insert_order_button = Gtk::manage(new Gtk::ToolButton(*add_order_image));
    insert_order_button->set_tooltip_markup("Insert Order");
    insert_order_button->signal_clicked().connect([this] { this->on_new_order_click(); });
    toolbar->append(*insert_order_button);

    //insert a drop down menu item of tool into the insert menu
    Gtk::MenuItem *menuitem_tool = Gtk::manage(new Gtk::MenuItem("_Tool", true));
    menuitem_tool->signal_activate().connect([this] { this->on_new_tool_click(); });
    insertmenu->append(*menuitem_tool);

    Gtk::Image *add_tool_image = Gtk::manage(new Gtk::Image{"tool.png"});
    Gtk::ToolButton *insert_tool_button = Gtk::manage(new Gtk::ToolButton(*add_tool_image));
    insert_tool_button->set_tooltip_markup("Insert Tool");
    insert_tool_button->signal_clicked().connect([this] { this->on_new_tool_click(); });
    toolbar->append(*insert_tool_button);

    //insert a drop down menu item of plant into the insert menu
    Gtk::MenuItem *menuitem_plant = Gtk::manage(new Gtk::MenuItem("_Plant", true));
    menuitem_plant->signal_activate().connect([this] { this->on_new_plant_click(); });
    insertmenu->append(*menuitem_plant);

    Gtk::Image *add_plant_image = Gtk::manage(new Gtk::Image{"plant.png"});
    Gtk::ToolButton *insert_plant_button = Gtk::manage(new Gtk::ToolButton(*add_plant_image));
    insert_plant_button->set_tooltip_markup("Insert Plant");
    insert_plant_button->signal_clicked().connect([this] { this->on_new_plant_click(); });
    toolbar->append(*insert_plant_button);

    //insert a drop down menu item of plant into the insert menu
    Gtk::MenuItem *menuitem_mulch = Gtk::manage(new Gtk::MenuItem("_Mulch", true));
    menuitem_mulch->signal_activate().connect([this] { this->on_new_mulch_click(); });
    insertmenu->append(*menuitem_mulch);

    Gtk::Image *add_mulch_image = Gtk::manage(new Gtk::Image{"mulch.png"});
    Gtk::ToolButton *insert_mulch_button = Gtk::manage(new Gtk::ToolButton(*add_mulch_image));
    insert_mulch_button->set_tooltip_markup("Insert Mulch");
    insert_mulch_button->signal_clicked().connect([this] { this->on_new_mulch_click(); });
    toolbar->append(*insert_mulch_button);

    Gtk::MenuItem *menuitem_view = Gtk::manage(new Gtk::MenuItem("_View", true));
    menubar->append(*menuitem_view);
    Gtk::Menu *viewmenu = Gtk::manage(new Gtk::Menu());
    menuitem_view->set_submenu(*viewmenu);

    Gtk::MenuItem *viewitem_customer = Gtk::manage(new Gtk::MenuItem("_Customer", true));
    viewitem_customer->signal_activate().connect([this] { this->on_view_customer_click(); });
    viewmenu->append(*viewitem_customer);

    Gtk::Image *view_customers_image = Gtk::manage(new Gtk::Image{"customers.png"});
    Gtk::ToolButton *view_customers_button = Gtk::manage(new Gtk::ToolButton(*view_customers_image));
    view_customers_button->set_tooltip_markup("View Customers");
    view_customers_button->signal_clicked().connect([this] { this->on_view_customer_click(); });
    toolbar->append(*view_customers_button);

    Gtk::MenuItem *viewitem_order = Gtk::manage(new Gtk::MenuItem("_Order", true));
    viewitem_order->signal_activate().connect([this] { this->on_view_order_click(); });
    viewmenu->append(*viewitem_order);

    void on_view_order_click();

    Gtk::Image *viewitem_order_image = Gtk::manage(new Gtk::Image{"order_view.png"});
    Gtk::ToolButton *viewitem_order_button = Gtk::manage(new Gtk::ToolButton(*viewitem_order_image));
    viewitem_order_button->set_tooltip_markup("View order");
    viewitem_order_button->signal_clicked().connect([this] { this->on_view_order_click(); });
    toolbar->append(*viewitem_order_button);

    Gtk::MenuItem *viewitem_product = Gtk::manage(new Gtk::MenuItem("_Product", true));
    viewitem_product->signal_activate().connect([this] { this->on_view_products_click(); });
    viewmenu->append(*viewitem_product);

    Gtk::Image *view_box_image = Gtk::manage(new Gtk::Image{"product.png"});
    Gtk::ToolButton *view_products_button = Gtk::manage(new Gtk::ToolButton(*view_box_image));
    view_products_button->set_tooltip_markup("View Product");
    view_products_button->signal_clicked().connect([this] { this->on_view_products_click(); });
    toolbar->append(*view_products_button);

    
    Gtk::MenuItem *menuitem_edit = Gtk::manage(new Gtk::MenuItem("_Edit", true));
    menubar->append(*menuitem_edit);
    Gtk::Menu *editmenu = Gtk::manage(new Gtk::Menu());
    menuitem_edit->set_submenu(*editmenu);


    Gtk::MenuItem *edit_product=Gtk::manage(new Gtk::MenuItem("_Edit Product",true));
    edit_product->signal_activate().connect([this] { this->on_edit_product_click(); });
    editmenu->append(*edit_product);

    Gtk::Image *edit_product_image = Gtk::manage(new Gtk::Image{"edit.png"});
    Gtk::ToolButton *edit_product_button = Gtk::manage(new Gtk::ToolButton(*edit_product_image));
    edit_product_button->set_tooltip_markup("Edit");
    edit_product_button->signal_clicked().connect([this] { this->on_edit_product_click(); });
    toolbar->append(*edit_product_button);

    

    Gtk::MenuItem *menuitem_help = Gtk::manage(new Gtk::MenuItem("_help", true));
    menubar->append(*menuitem_help);
    Gtk::Menu *helpmenu = Gtk::manage(new Gtk::Menu());
    menuitem_help->set_submenu(*helpmenu);

    Gtk::MenuItem *menuitem_about = Gtk::manage(new Gtk::MenuItem("_about", true));
    menuitem_about->signal_activate().connect([this] { this->on_about_click(); });
    helpmenu->append(*menuitem_about);


    scroll->show_all();

    display = Gtk::manage(new Gtk::Label());
    display->set_hexpand(true);
    display->set_vexpand(true);
    vbox->add(*display);
    msg = Gtk::manage(new Gtk::Label());
    msg->set_hexpand(true);
    msg->set_vexpand(true);
    vbox->pack_start(*msg, Gtk::POS_BOTTOM, 0);
    statusbar = Gtk::manage(new Gtk::Statusbar);
    ID = statusbar->get_context_id("MANGA MAGIC");
    vbox->pack_start(*statusbar, Gtk::POS_BOTTOM, 0);
    scroll->show_all();
    statusbar->push("Manga Magic", ID);
    store = new Store{"Manga Magic"};
    std::ostringstream oss;
    oss << "Current products" << std::endl;
    oss << "________________" << std::endl;
    display->set_text(oss.str());
    msg->set_alignment(0.5, 0);
    //msg->set_text("Manga Magic");
   // set_status("MANGA MAGIC");
}

Mainwin::~Mainwin() {}



void Mainwin::on_edit_product_click(){
    Gtk::Dialog dialog{"Choose a Product", *this};
    // store->customer(2)
    Gtk::ComboBoxText p_type{true}; // Drop down with an Entry (true)
    std::ostringstream oss;
    Gtk::Grid grid;
    
    std::vector<std::string> types{"Tool","Plant","Mulch"};
    std::string s;
    for(int i=0;i<types.size();i++){
       oss<<types[i]<<std::endl;
         s = oss.str();
         p_type.append(s);
         oss.str("");
    }
        
    std::ostringstream oss2;
    std::string s2;
    Gtk::ComboBoxText productlist{true};
    for (int i = 0; i < store->products(); ++i)
    {
        oss2 << store->product(i) << std::endl; // do this for product
        s2 = oss2.str();
        productlist.append(s2);
        oss2.str("");
    }
    Gtk::Label l_type{"Product Type"};
    Gtk::Label l_product{"Product"};
    grid.attach(l_type,   0, 0, 1, 1);
    grid.attach(l_product,0, 1, 1, 1);
    grid.attach(p_type,  1, 0, 2, 1);
    grid.attach(productlist,1, 1, 2, 1);
    dialog.get_content_area()->add(grid);
    dialog.add_button("Selct", Gtk::RESPONSE_OK);
    dialog.add_button("Cancel", Gtk::RESPONSE_CANCEL);
    dialog.show_all();
    int result = dialog.run();
    int o_index;
    if (result == Gtk::RESPONSE_OK)
    {
        store->replace_product(types[p_type.get_active_row_number()],productlist.get_active_row_number());
        statusbar->push("Successfully Edited", ID);
    }   
      on_view_products_click();
}


void Mainwin::get_plant()
{
    Gtk::Dialog dialog{"Enter Plant Product Info", *this};
    Gtk::Grid grid;

    Gtk::Label l_name{"Name"};
    Gtk::Entry e_name;
    e_name.set_placeholder_text("Name");
    grid.attach(l_name, 0, 0, 1, 1);
    grid.attach(e_name, 1, 0, 2, 1);

    Gtk::Label l_description{"Description"};
    Gtk::Entry e_description;
    e_description.set_placeholder_text("Description");
    grid.attach(l_description, 0, 1, 1, 1);
    grid.attach(e_description, 1, 1, 2, 1);

    Gtk::Label l_price{"Price"};
    Gtk::Entry e_price;
    e_price.set_placeholder_text("Price");
    grid.attach(l_price, 0, 2, 1, 1);
    grid.attach(e_price, 1, 2, 2, 1);

    Gtk::Label l_species{"Species"};
    Gtk::Entry e_species;
    e_species.set_placeholder_text("Species");
    grid.attach(l_species, 0, 3, 1, 1);
    grid.attach(e_species, 1, 3, 2, 1);

    Gtk::Label l_exposure{"Exposure"};
    Gtk::Entry e_exposure;
    e_exposure.set_placeholder_text("Must be Sun or Shade or Part Sun");
    grid.attach(l_exposure, 0, 4, 1, 1);
    grid.attach(e_exposure, 1, 4, 2, 1);

    dialog.get_content_area()->add(grid);

    dialog.add_button("Enter", Gtk::RESPONSE_OK);
    dialog.add_button("Cancel", Gtk::RESPONSE_CANCEL);
    dialog.show_all();
    int response;
    int exposure;
    response = dialog.run();
    if (response == Gtk::RESPONSE_OK)
    {
        std::string s = e_exposure.get_text();
        std::transform(s.begin(), s.end(), s.begin(),
                       [](unsigned char c) -> unsigned char { return std::tolower(c); });
        //std::cout << s << std::endl;
        if (s == "shade")
            exposure = 0;
        else if (s == "part sun")
            exposure = 1;
        else
            exposure = 2;
        Plant new_plant{e_name.get_text(), std::stod(e_price.get_text()), e_description.get_text(), e_species.get_text(), (Exposure)exposure};
       // store->add_product(*(new Plant{e_name.get_text(), std::stod(e_price.get_text()), e_description.get_text(), e_species.get_text(), (Exposure)exposure}));
        store->add_product(new_plant);
        statusbar->push("Plant added successfully", ID);
       // set_status("Plant added successfully");
    }
}
void Mainwin::set_status(std::string status)
{
    msg->set_text(status);
}
void Mainwin::get_tool()
{
    Gtk::Dialog dialog{"Enter Tool Product Info", *this};
    Gtk::Grid grid;

    Gtk::Label l_name{"Name"};
    Gtk::Entry e_name;
    e_name.set_placeholder_text("Name");
    grid.attach(l_name, 0, 0, 1, 1);
    grid.attach(e_name, 1, 0, 2, 1);

    Gtk::Label l_description{"Description"};
    Gtk::Entry e_description;
    e_description.set_placeholder_text("Description");
    grid.attach(l_description, 0, 1, 1, 1);
    grid.attach(e_description, 1, 1, 2, 1);

    Gtk::Label l_price{"Price"};
    Gtk::Entry e_price;
    e_price.set_placeholder_text("Price");
    grid.attach(l_price, 0, 2, 1, 1);
    grid.attach(e_price, 1, 2, 2, 1);

    dialog.get_content_area()->add(grid);

    dialog.add_button("Enter", Gtk::RESPONSE_OK);
    dialog.add_button("Cancel", Gtk::RESPONSE_CANCEL);
    dialog.show_all();
    int response;
    response = dialog.run();
    if (response == Gtk::RESPONSE_OK)
    {
        Tool new_tool{e_name.get_text(), std::stod(e_price.get_text()), e_description.get_text()};
        //store->add_product((Tool{e_name.get_text(), std::stod(e_price.get_text()), e_description.get_text()}));
        store->add_product(new_tool);
        statusbar->push("Tool added successfully", ID);
        //set_status("Tool added successfully");
    }
}
void Mainwin::get_mulch()
{
    Gtk::Dialog dialog{"Enter Mulch Product Info", *this};
    Gtk::Grid grid;

    Gtk::Label l_name{"Name"};
    Gtk::Entry e_name;
    e_name.set_placeholder_text("Name");
    grid.attach(l_name, 0, 0, 1, 1);
    grid.attach(e_name, 1, 0, 2, 1);

    Gtk::Label l_description{"Description"};
    Gtk::Entry e_description;
    e_description.set_placeholder_text("Description");
    grid.attach(l_description, 0, 1, 1, 1);
    grid.attach(e_description, 1, 1, 2, 1);

    Gtk::Label l_price{"Price"};
    Gtk::Entry e_price;
    e_price.set_placeholder_text("Price");
    grid.attach(l_price, 0, 2, 1, 1);
    grid.attach(e_price, 1, 2, 2, 1);

    Gtk::Label l_volume{"Volume"};
    Gtk::Entry e_volume;
    e_volume.set_placeholder_text("Volume");
    grid.attach(l_volume, 0, 3, 1, 1);
    grid.attach(e_volume, 1, 3, 2, 1);

    Gtk::Label l_material{"Material"};
    Gtk::Entry e_material;
    e_material.set_placeholder_text("Must be Rubber or Pine etc..");
    grid.attach(l_material, 0, 4, 1, 1);
    grid.attach(e_material, 1, 4, 2, 1);

    dialog.get_content_area()->add(grid);

    dialog.add_button("Enter", Gtk::RESPONSE_OK);
    dialog.add_button("Cancel", Gtk::RESPONSE_CANCEL);
    dialog.show_all();
    int response;
    int material;
    response = dialog.run();
    if (response == Gtk::RESPONSE_OK)
    {
        std::string s = e_material.get_text();
        std::transform(s.begin(), s.end(), s.begin(),
                       [](unsigned char c) -> unsigned char { return std::tolower(c); });
        //std::cout << s << std::endl;
        if (s == "rubber")
            material = 0;
        else if (s == "pine")
            material = 1;
        else if (s == "cedar")
            material = 2;
        else
            material = 3;
        Mulch new_mulch{e_name.get_text(), std::stod(e_price.get_text()), e_description.get_text(), std::stoi(e_volume.get_text()), (Material)material};
        //store->add_product(*(new Mulch{e_name.get_text(), std::stod(e_price.get_text()), e_description.get_text(), std::stoi(e_volume.get_text()), (Material)material}));
          store->add_product(new_mulch);
        statusbar->push("Mulch added successfully", ID);
      //  set_status("Mulch added successfully");
    }
}

void Mainwin::on_quit_click()
{
    close();
}

void Mainwin::on_new_customer_click()
{
    Gtk::Dialog dialog{"Enter Info", *this};
    Gtk::Grid grid;

    Gtk::Label l_name{"Name"};
    Gtk::Entry e_name;
    e_name.set_placeholder_text("Name");
    grid.attach(l_name, 0, 0, 1, 1);
    grid.attach(e_name, 1, 0, 2, 1);

    Gtk::Label l_phone{"Phone"};
    Gtk::Entry e_phone;
    e_phone.set_placeholder_text("xxx-xxx-xxxx");
    grid.attach(l_phone, 0, 1, 1, 1);
    grid.attach(e_phone, 1, 1, 2, 1);

    Gtk::Label l_email{"Email"};
    Gtk::Entry e_email;
    e_email.set_placeholder_text("xxx@email.com");
    grid.attach(l_email, 0, 2, 1, 1);
    grid.attach(e_email, 1, 2, 2, 1);

    dialog.get_content_area()->add(grid);

    dialog.add_button("Enter", Gtk::RESPONSE_OK);
    dialog.add_button("Cancel", Gtk::RESPONSE_CANCEL);
    dialog.show_all();
    int response;
    response = dialog.run();
    if (response == Gtk::RESPONSE_OK)
    {
        Customer new_customer{e_name.get_text(), e_phone.get_text(), e_email.get_text()};
        store->add_customer(new_customer);
        statusbar->push("customer added successfully", ID);
        //set_status("customer added successfully");
    }
    on_view_customer_click();
}

void Mainwin::on_view_customer_click()
{

    std::ostringstream oss;
    oss << "Current Customers" << std::endl;
    oss << "________________" << std::endl;
    for (int i = 0; i < store->customers(); ++i)
    {
        oss << store->customer(i) << std::endl;
    }
    display->set_text(oss.str());
    statusbar->push("Viewing Customers", ID);
    //set_status("Viewing Customers");
}

void Mainwin::on_new_order_click()
{
    Gtk::Dialog dialog{"Choose a Customer", *this};
    Gtk::Grid grid;
    // store->customer(2)
    Gtk::ComboBoxText c_type{true}; // Drop down with an Entry (true)
    std::ostringstream oss;
    std::string s;
    for (int i = 0; i < store->customers(); ++i)
    {
        oss << store->customer(i) << std::endl; // do this for product
        s = oss.str();
        c_type.append(s);
        oss.str("");
    }
    grid.attach(c_type, 0, 0, 1, 1);
    dialog.get_content_area()->add(grid);
    dialog.add_button("Selct", Gtk::RESPONSE_OK);
    dialog.add_button("Cancel", Gtk::RESPONSE_CANCEL);
    dialog.show_all();
    int result = dialog.run();
    int o_index;
    if (result == Gtk::RESPONSE_OK)
    {
        o_index = store->add_order(store->customer(c_type.get_active_row_number()));
    
    Gtk::MessageDialog dialog2{*this, "Place an order" + std::to_string(o_index)};
    Gtk::VBox *order_info=Gtk::manage(new Gtk::VBox);
    Gtk::Label l_quantity{"Quantity"};
    order_info->add(l_quantity);
    Gtk::SpinButton quantity;
    quantity.set_increments(1.0, 20.0);
    quantity.set_range(1.0, 1000.0);
    order_info->add(quantity);
    dialog2.get_content_area()->add(*order_info);
    std::ostringstream oss2;
    std::string s2;
    Gtk::ComboBoxText product_options;
    for (int i = 0; i < store->products(); ++i)
    {
        oss2 << store->product(i) << std::endl; // do this for product
        s2 = oss2.str();
        product_options.append(s2);
        oss2.str("");
    }
    dialog2.get_content_area()->add(product_options);
    dialog2.add_button("Add to Order", 1);
    dialog2.add_button("Order Complete", 0);
    std::ostringstream os;
    std::ostringstream os2;
    std::string s3;
    while(true){
        dialog2.show_all();
        int result2 = dialog2.run();
        if (result2 == 1)
        {
           store->add_item(o_index, store->product(product_options.get_active_row_number()), quantity.get_value());
           Store &store1 = *(this->store);
            for (auto &n : store1) {
                   os << *(n) << std::endl;
                   s3=os.str();
                   os.str("");
            }
          dialog2.set_secondary_text(s3);
          statusbar->push("Order Added", ID);
        }
       else{break;} 
    }
}
    on_view_order_click();

}

void Mainwin::on_view_order_click()
{
    std::ostringstream oss;
    oss << "Current Orders" << std::endl;
    oss << "________________" << std::endl;
    Store &store1 = *(this->store); //store->get_object();
    //this->store;
    for (auto &s : store1)
    {
        oss << *s << std::endl;
        
    }
    display->set_text(oss.str());
    statusbar->push("Viewing Orders", ID);
   // set_status("Viewing Orders");
}

void Mainwin::on_new_tool_click()
{
    get_tool();
    on_view_products_click();
}

void Mainwin::on_new_plant_click()
{
    get_plant();
    on_view_products_click();
}

void Mainwin::on_new_mulch_click()
{
    get_mulch();
    on_view_products_click();
}

void Mainwin::on_view_products_click()
{
    std::ostringstream oss;
    oss << "Current products" << std::endl;
    oss << "________________" << std::endl;
    for (int i = 0; i < store->products(); ++i)
    {
        oss << store->product(i) << std::endl;
    }
    display->set_text(oss.str());
   statusbar->push("Viewing Products", ID);
    //set_status("Viewing Products");
}

void Mainwin::on_new_store_click()
{
   
    delete store;
    EntryDialog edialog{*this, "<big>New Store</big>", true};
    edialog.set_secondary_text("name?", true);
    edialog.run();
    store = new Store{edialog.get_text()};
    //store->reset_stock();
    on_view_products_click();
    //msg->set_text(edialog.get_text());
    statusbar->push(edialog.get_text(), ID);
    //set_status(edialog.get_text());
}

void Mainwin::on_about_click()
{
    Gtk::AboutDialog dialog;
    dialog.set_transient_for(*this);
    dialog.set_program_name("Manga Magic");
    auto logo = Gdk::Pixbuf::create_from_file("about.png");
    dialog.set_logo(logo);
    dialog.set_version("Version 1.0");
    dialog.set_copyright("Copyright 2017-2020");
    dialog.set_license_type(Gtk::License::LICENSE_GPL_3_0);
    std::vector<Glib::ustring> authors = {"Ahmed Harun"};
    dialog.set_authors(authors);
    std::vector<Glib::ustring> artists = {
        "Logo by M0tty, licensed under CC BY-SA 3.0 https://commons.wikimedia.org/wiki/File:Pyramidal_matches.svg",
        "Robot by IMGBIN.com, licensed for personal and commercial purposes with attribution https://imgbin.com/",
        "User by JeraOcean from the Noun Project",
        "add to order by Aldric Rodríguez from the Noun Project",
        "Plant by iconcheese from the Noun Project",
        "tools by Roberto Chiaveri from the Noun Project",
        "mulch by Vectors Point from the Noun Project" ,
        "products by Prettycons from the Noun Project",
        "Customers View by icongeek from the Noun Project",
        "Magic Wand by arejoenah from the Noun Project",
         "eye device by David Carrero from the Noun Project"   } ;
    dialog.set_artists(artists);
    dialog.run();
}

void Mainwin::on_save_click()
{
    //std::cout<<filename<<std::endl;
    std::ofstream ofs{filename};
    statusbar->push("Successfully Saved ", ID);
    on_view_products_click();
    store->save(ofs);
}

void Mainwin::on_save_as_click()
{
    Gtk::FileChooserDialog dialog("Please choose a file",
                                  Gtk::FileChooserAction::FILE_CHOOSER_ACTION_SAVE);
    dialog.set_transient_for(*this);

    auto filter_manga = Gtk::FileFilter::create();
    filter_manga->set_name("Manga files");
    filter_manga->add_pattern("*.MANGA");
    dialog.add_filter(filter_manga);

    auto filter_any = Gtk::FileFilter::create();
    filter_any->set_name("Any files");
    filter_any->add_pattern("*");
    dialog.add_filter(filter_any);

    dialog.set_filename("untitled.MANGA");

    //Add response buttons the the dialog:
    dialog.add_button("_Cancel", 0);
    dialog.add_button("_Save", 1);

    int result = dialog.run();

    if (result == 1)
    {
        try
        {
            std::ofstream ofs{dialog.get_filename()};
            filename = dialog.get_filename();
            store->save(ofs);
            statusbar->push("Successfully Saved ", ID);
                on_view_products_click();
            if (!ofs)
                throw std::runtime_error{"Error writing file"};
        }
        catch (std::exception &e)
        {
            Gtk::MessageDialog{*this, "Unable to save file"}.run();
        }
    }
}
void Mainwin::on_open_click()
{
    Gtk::FileChooserDialog dialog("Please choose a file",
                                  Gtk::FileChooserAction::FILE_CHOOSER_ACTION_OPEN);
    dialog.set_transient_for(*this);

    auto filter_manga = Gtk::FileFilter::create();
    filter_manga->set_name("MANGA files");
    filter_manga->add_pattern("*.MANGA");
    dialog.add_filter(filter_manga);

    auto filter_any = Gtk::FileFilter::create();
    filter_any->set_name("Any files");
    filter_any->add_pattern("*");
    dialog.add_filter(filter_any);

    dialog.set_filename("untitled.MANGA");

    //Add response buttons the the dialog:
    dialog.add_button("_Cancel", 0);
    dialog.add_button("_Open", 1);
    int result = dialog.run();

    if (result == 1)
    {
        try
        {
            delete store;
            std::ifstream ifs{dialog.get_filename()};
            filename = dialog.get_filename();
            store = new Store{ifs};
            statusbar->push("Successfully opened ", ID);
           // set_status("Successfully opened");
            if (!ifs)
                throw std::runtime_error{"File contents bad"};
            on_view_products_click();
        }
        catch (std::exception &e)
        {
            Gtk::MessageDialog{*this, "Unable to open file"}.run();
        }
    }
}
