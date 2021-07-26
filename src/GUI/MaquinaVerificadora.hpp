#ifndef MAQUINA_VERIFICADORA_HPP
#define MAQUINA_VERIFICADORA_HPP

#include <map>
#include <string>

#include <gtk/gtk.h>

class MaquinaVerificadora {
 private:
  GtkApplication* app;
  GtkBuilder* builder;
  std::map<std::string, GtkWidget*> windows;
  std::map<std::string, GtkWidget*> widgets;

 public:
  MaquinaVerificadora();
  ~MaquinaVerificadora();

 private:
  void init(int argc, char *argv[]);

 private:
  void mainWindow(GtkApplication* app, gpointer userData);
  void errorWindow(GtkApplication* app, gpointer userData);
  void successWindow(GtkApplication* app, gpointer userData);

 public:
  void run();
};


#endif
