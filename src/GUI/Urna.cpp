#include "Urna.hpp"

#include <stdexcept>
#include <thread>

Urna::Urna(const std::string& padronIp, const std::string& padronPort,
          const std::string& voteIp, const std::string& votePort,
          const std::string& serverPort) {
  // File System
  this->hd = new HardDrive(HD_SIZE);
  this->fs = new FileSystem(HD_SIZE, this->hd);

  // Clients
  this->padronClient = new PadronClient(padronIp, padronPort);
  this->voteClient = new VoteClient(*this->fs, voteIp, votePort);
  if (padronClient == nullptr) {
    throw std::runtime_error("Error: could not initialize the PadronClient");
  }
  if (voteClient == nullptr) {
    throw std::runtime_error("Error: could not initialize the VoteClient");
  }

  // Init server in a separate thread
  std::thread server(Urna::initServer, this->fs, serverPort);
}

Urna::~Urna() {
  delete this->padronClient;
  //delete this->voteClient;
}

void Urna::initServer(FileSystem* fs, std::string port) {
  VoteServer vs(*fs, "URNA");
  vs.listenForever(port.c_str());
}

int Urna::run(int argc, char** argv) {
  this->app = Gtk::Application::create("org.tronaditas.urna");
  this->app->signal_activate().connect(sigc::mem_fun(*this, &Urna::buildUI));
  return this->app->run();
}

void Urna::buildUI() {
  // Build both Windows
  this->buildLoginUI();
  this->buildVoteUI();

  // Connections
  this->buildConnections();

  // Add the windows to the app
  this->app->add_window(*this->windows["login"]);
  this->app->add_window(*this->windows["vote"]);

  // Show the login window
  this->windows["login"]->show();
}

void Urna::buildLoginUI() {
  // Create a builder
  auto builder = Gtk::Builder::create();
  builder->add_from_file(GLADE_PATH);

  // Login Window
  this->windows["login"] = nullptr;
  builder->get_widget("loginWindow", this->windows["login"]);
  this->windows["login"]->set_position(Gtk::WIN_POS_CENTER);

  // Window Title
  this->labels["loginTitle"] = nullptr;
  builder->get_widget("loginTitle", this->labels["loginTitle"]);

  // Info Label
  this->labels["loginInfo"] = nullptr;
  builder->get_widget("loginInfo", this->labels["loginInfo"]);

  // Carnet Entry
  this->entries["carnet"] = nullptr;
  builder->get_widget("carnetEntry", this->entries["carnet"]);

  // Codigo Entry
  this->entries["codigo"] = nullptr;
  builder->get_widget("codigoEntry", this->entries["codigo"]);

  // Login Button
  this->buttons["login"] = nullptr;
  builder->get_widget("loginButton", this->buttons["login"]);
}

void Urna::buildVoteUI() {
  // Create a builder
  auto builder = Gtk::Builder::create();
  builder->add_from_file(GLADE_PATH);

  // Voto Window
  this->windows["vote"] = nullptr;
  builder->get_widget("voteWindow", this->windows["vote"]);
  this->windows["vote"]->set_position(Gtk::WIN_POS_CENTER);

  // Window Title
  this->labels["voteTitle"] = nullptr;
  builder->get_widget("loginTitle", this->labels["voteTitle"]);

  // Candidato 1
  this->checkButtons["candidato1"] = nullptr;
  builder->get_widget("candidato1", this->checkButtons["candidato1"]);

  // Candidato 2
  this->checkButtons["candidato2"] = nullptr;
  builder->get_widget("candidato2", this->checkButtons["candidato2"]);

  // Candidato 3
  this->checkButtons["candidato3"] = nullptr;
  builder->get_widget("candidato3", this->checkButtons["candidato3"]);

  // Vote Label
  this->labels["vote"] = nullptr;
  builder->get_widget("voteLabel", this->labels["vote"]);

  // Confirm Vote
  this->checkButtons["confirmVote"] = nullptr;
  builder->get_widget("confirmVoteBox", this->checkButtons["confirmVote"]);
  this->checkButtons["confirmVote"]->hide();

  // Vote Button
  this->buttons["vote"] = nullptr;
  builder->get_widget("voteButton", this->buttons["vote"]);

  // Exit Button
  this->buttons["exit"] = nullptr;
  builder->get_widget("exitButton", this->buttons["exit"]);
  this->buttons["exit"]->hide();
}

void Urna::buildConnections() {
  // Login Button
  this->buttons["login"]->signal_clicked().connect(
    sigc::mem_fun(*this, &Urna::login)
  );

  // Vote updated
  this->buttons["vote"]->signal_clicked().connect(
    sigc::mem_fun(*this, &Urna::updateVote)
  );

  // Finish
  this->buttons["exit"]->signal_clicked().connect(
    sigc::mem_fun(*this, &Urna::finishVote)
  );
}

void Urna::login() {
  std::string carnet = this->entries["carnet"]->get_text().c_str();
  std::string codigo = this->entries["codigo"]->get_text().c_str();
  std::string error = "Ingrese número de Carnet y Código de verificación";

  // Authentication and authorization
  if (padronClient->verifyCarnet(carnet)) {
    if (padronClient->verifyCode(carnet, codigo)) {
      if (!padronClient->verifyVote(carnet)) {
        this->activeCarnet = carnet;
        //this->windows["login"]->hide();
        this->windows["vote"]->show();
      } else {
        error = "Usted ya ha registrado su voto";
      }
    } else {
      error = "Número de carnet o código de verificación erroneo. Por favor, intentelo de nuevo";
    }
  } else {
    error = "Usted no se encuentra registrado en el padrón";
  }

  // Update the label value
  this->labels["loginInfo"]->set_label(error);
}

void Urna::updateVote() {
  auto confirm = this->checkButtons["confirmVote"];
  confirm->show();
  int c1 = this->checkButtons["candidato1"]->property_active();
  int c2 = this->checkButtons["candidato2"]->property_active();
  int c3 = this->checkButtons["candidato3"]->property_active();
  int cantidadEscogidos = c1 + c2 + c3;
  std::string eleccion;
  auto voto = this->labels["vote"];

  if (c1) {
    voto->set_label("Usted seleccionó al candidato 1");
    eleccion = "candidato1";
  }

  if (c2) {
    voto->set_label("Usted seleccionó al candidato 2");
    eleccion = "candidato2";
  }

  if (c3) {
    voto->set_label("Usted seleccionó al candidato 3");
    eleccion = "candidato3";
  }

  if(cantidadEscogidos > 1 || cantidadEscogidos == 0){
    eleccion = "nulo";
    voto->set_label("Su voto es nulo");
  }

  if (confirm->property_active()) {
    voto->set_label("Voto registrado. Gracias por participar.");
    this->checkButtons["candidato1"]->property_active() = 0;
    this->checkButtons["candidato2"]->property_active() = 0;
    this->checkButtons["candidato3"]->property_active() = 0;
    this->buttons["vote"]->hide();
    confirm->hide();
    confirm->property_active() = 0;
    this->buttons["exit"]->show();

    // Send Vote TODO!! SUPER IMPORTANT

    // Update Padron
    this->padronClient->updateVote(this->activeCarnet);
  }
}

void Urna::finishVote() {
  this->windows["vote"]->hide();
  this->buttons["vote"]->show();
  this->buttons["exit"]->hide();
  this->checkButtons["confirmVote"]->show();
  this->labels["vote"]->set_label("Voto:");
  this->entries["carnet"]->set_text("");
  this->entries["codigo"]->set_text("");
}
