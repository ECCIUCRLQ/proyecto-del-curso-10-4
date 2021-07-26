#include "MaquinaVerificadora.hpp"

MaquinaVerificadora::MaquinaVerificadora() {
}

MaquinaVerificadora::~MaquinaVerificadora() {
}

void MaquinaVerificadora::init(int argc, char *argv[]) {
  // Init App
  this->app = gtk_application_new("org.tronaditas.mv", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(this->app, "activate", G_CALLBACK(), NULL);

  // Builder
  this->builder = gtk_builder_new_from_file("Glade/MaquinaVerificadora.glade");
}

void MaquinaVerificadora::mainWindow(GtkApplication* app, gpointer userData) {
  GtkWindow* mainWindow = GTK_WIGET(gtk_builder_get_object(this->builder, "MainWindow"));
  this->windows["MainWindow"] = mainWindow;
  gtl_application_add_window(this->app, GTK_WINDOW(mainWindow));
}

void MaquinaVerificadora::run() {
}
