#ifndef MAQUINA_VERIFICADORA_GUI_HPP
#define MAQUINA_VERIFICADORA_GUI_HPP

#include <gtkmm.h>
#include <gtkmm/entry.h>
#include <iostream>
#include <map>
#include <string.h>

// CLIENTS
#include "Clients/PadronClient.hpp"

#define GLADE_PATH "interfazMaquinaVerificadora.glade"

class MaquinaVerificadora {
 private:
  PadronClient* padronClient = nullptr;

 private:
  std::map<std::string, Gtk::Window*> windows;
  std::map<std::string, Gtk::Button*> buttons;
  std::map<std::string, Gtk::Label*> labels;
  std::map<std::string, Gtk::Entry*> entries;
  Glib::RefPtr<Gtk::Application> app;

 public:
  MaquinaVerificadora() = delete;
  MaquinaVerificadora(const std::string& serverIp, const std::string& serverPort);
  ~MaquinaVerificadora();

 public:
  int run();

 private:
  void buildUI();
  void buildMainUI();
  void buildSuccessUI();
  void buildErrorUI();
  void buildConnections();

 private:
  void verify();
  void exitError();
  void exitSuccess();
};


#endif
