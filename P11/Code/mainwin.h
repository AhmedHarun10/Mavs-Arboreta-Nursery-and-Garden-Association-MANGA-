#ifndef _MAINWIN_H
#define _MAINWIN_H
#include <iostream>
#include "store.h"
#include <gtkmm.h>
#include <vector>
class Mainwin : public Gtk::Window
{
public:
    Mainwin();
    virtual ~Mainwin();
    friend std::ostream &operator<<(std::ostream &oss, Store &Store);

protected:
    void on_new_store_click();
    void on_save_click();
    void on_save_as_click();
    void on_open_click();
    void on_new_tool_click();
    void on_new_plant_click();
    void on_new_mulch_click();
    void on_view_products_click();
    void on_view_customer_click();
    void on_view_order_click();
    void on_new_customer_click();
    void on_new_order_click();
    void on_about_click();
    void on_edit_product_click();
    void on_quit_click();

private:
    void set_status(std::string status = " ");
    void get_tool();
    void get_plant();
    void get_mulch();
    Gtk::Statusbar *statusbar;
    unsigned ID;
    Store *store;
    Gtk::Label *display;
    Gtk::Label *msg;
    std::string filename;
};

#endif
