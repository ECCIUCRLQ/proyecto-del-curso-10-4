#include "MaquinaVerificadora.hpp"

#include <cstdlib>
#include <ctime>
#include <stdexcept>

#include "Security/Hash.hpp"

MaquinaVerificadora::MaquinaVerificadora(const std::string& serverIp, const std::string& serverPort) {
  this->padronClient = new PadronClient(serverIp, serverPort);
  if (padronClient == nullptr) {
    throw std::runtime_error("Error: could not initialize the PadronClient");
  }
}

MaquinaVerificadora::~MaquinaVerificadora() {
  delete this->padronClient;
}

int MaquinaVerificadora::run() {
  this->app = Gtk::Application::create("org.tronaditas.maquinaverificadora");
  this->app->signal_activate().connect(sigc::mem_fun(*this, &MaquinaVerificadora::buildUI));
  return this->app->run();
}

void MaquinaVerificadora::buildUI() {
  // Build Windows
  this->buildMainUI();
  this->buildSuccessUI();
  this->buildErrorUI();

  // Connections
  this->buildConnections();

  // Add the windows to the app
  this->app->add_window(*this->windows["main"]);
  this->app->add_window(*this->windows["success"]);
  this->app->add_window(*this->windows["error"]);

  // Show the login window
  this->windows["main"]->show();
}

void MaquinaVerificadora::buildMainUI() {
  // Create a builder
  auto builder = Gtk::Builder::create();
  builder->add_from_file(GLADE_PATH);

  // Main Window
  this->windows["main"] = nullptr;
  builder->get_widget("MainWindow", this->windows["main"]);
  this->windows["main"]->set_position(Gtk::WIN_POS_CENTER);

  // Carnet Entry
  this->entries["carnet"] = nullptr;
  builder->get_widget("carnetEntry", this->entries["carnet"]);

  // Verify Button
  this->buttons["verify"] = nullptr;
  builder->get_widget("carnetButton", this->buttons["verify"]);
}

void MaquinaVerificadora::buildErrorUI() {
  // Create a builder
  auto builder = Gtk::Builder::create();
  builder->add_from_file(GLADE_PATH);

  // Error Window
  this->windows["error"] = nullptr;
  builder->get_widget("ErrorWindow", this->windows["error"]);
  this->windows["error"]->set_position(Gtk::WIN_POS_CENTER);

  // Error Label
  this->labels["errorMsg"] = nullptr;
  builder->get_widget("errorLabel", this->labels["errorMsg"]);

  // Go back Button
  this->buttons["errorButton"] = nullptr;
  builder->get_widget("errorButton", this->buttons["errorButton"]);
}

void MaquinaVerificadora::buildSuccessUI() {
  // Create a builder
  auto builder = Gtk::Builder::create();
  builder->add_from_file(GLADE_PATH);

  // Success Window
  this->windows["success"] = nullptr;
  builder->get_widget("SuccessWindow", this->windows["success"]);
  this->windows["success"]->set_position(Gtk::WIN_POS_CENTER);

  // Carnet Entry
  this->labels["successMsg"] = nullptr;
  builder->get_widget("successLabel", this->labels["successMsg"]);

  // Go back Button
  this->buttons["successButton"] = nullptr;
  builder->get_widget("successButton", this->buttons["successButton"]);
}

void MaquinaVerificadora::buildConnections() {
  // Login Button
  this->buttons["verify"]->signal_clicked().connect(
    sigc::mem_fun(*this, &MaquinaVerificadora::verify)
  );

  // Vote updated
  this->buttons["errorButton"]->signal_clicked().connect(
    sigc::mem_fun(*this, &MaquinaVerificadora::exitError)
  );

  // Finish
  this->buttons["successButton"]->signal_clicked().connect(
    sigc::mem_fun(*this, &MaquinaVerificadora::exitSuccess)
  );
}

void MaquinaVerificadora::verify() {
  std::string carnet = this->entries["carnet"]->get_text().c_str();
  std::string error = "";

  if (this->padronClient->verifyCarnet(carnet)) {
    if (!this->padronClient->verifyVote(carnet)) {
      // Generate a random code
      std::string code = "";
      ::srand(::time(NULL));
      int c = ::rand() % 126 + 33;
      code += (char)c;
      code = Hash::SHA256(code);

      // Set the code
      this->padronClient->updateCode(carnet, code);

      // Go to Success Window
      this->entries["carnet"]->set_text("");
      this->labels["successMsg"]->set_label("Su código de verificación es: " + code);
      this->windows["success"]->show();
    } else {
      error = "Usted ya ha registrado su voto";
    }
  } else {
    error = "El número de carnet no está registrado en el padrón";
  }

  if (error.length() > 0) {
    // Error Window
    this->labels["errorMsg"]->set_label(error);
    this->windows["error"]->show();
  }
}

void MaquinaVerificadora::exitError() {
  this->labels["errorMsg"]->set_label("");
  this->windows["error"]->hide();
}

void MaquinaVerificadora::exitSuccess() {
  this->labels["successMsg"]->set_label("");
  this->windows["success"]->hide();
}
