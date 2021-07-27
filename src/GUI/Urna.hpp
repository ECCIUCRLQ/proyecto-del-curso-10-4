#ifndef URNA_GUI_HPP
#define URNA_GUI_HPP

#include <gtkmm.h>
#include <gtkmm/entry.h>
#include <iostream>
#include <map>
#include <string.h>

// FILE SYSTEM
#include "FileSystem/HardDrive.hpp"
#include "FileSystem/FileSystem.hpp"

// CLIENTS
#include "Clients/PadronClient.hpp"
#include "Clients/VoteClient.hpp"

#define GLADE_PATH "interfazUrna.glade"
#define HD_SIZE 51200

class Urna {
 private:
  HardDrive* hd;
  FileSystem* fs;

 private:
  PadronClient* padronClient = nullptr;
  VoteClient* voteClient = nullptr;

 private:
  std::map<std::string, Gtk::Window*> windows;
  std::map<std::string, Gtk::Button*> buttons;
  std::map<std::string, Gtk::Label*> labels;
  std::map<std::string, Gtk::Entry*> entries;
  std::map<std::string, Gtk::CheckButton*> checkButtons;
  Glib::RefPtr<Gtk::Application> app;

 private:
  std::string activeCarnet;

 public:
  Urna() = delete;
  Urna(const std::string& serverIp, const std::string& serverPort);
  ~Urna();

 public:
  int run(int argc, char** argv);

 private:
  void buildUI();
  void buildLoginUI();
  void buildVoteUI();
  void buildConnections();

 private:
  void login();
  void updateVote();
  void finishVote();
};


#endif
