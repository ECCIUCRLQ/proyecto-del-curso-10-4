#include "PadronManager.hpp"

#include <fstream>
#include <sstream>
#include <vector>

PadronManager::PadronManager(const std::string& filepath, FileSystem& fs) : fs(&fs), rutaPadron(filepath) {
  this->initPadron();
}

PadronManager::~PadronManager() {
}

bool PadronManager::initPadron() {
  bool ret = false;

  std::ifstream padronFile;
  padronFile.open(this->rutaPadron);
  if (padronFile.is_open()) {
    // Skip the first line
    std::string linea;
    std::getline(padronFile, linea);

    // Parse each line
    while (std::getline(padronFile, linea)) {
      datosVotante votante;
      std::stringstream ss(linea);
      // Extraer todos los valores de esa fila- todos estos valores se cambian segun los datos que se necesitan para el padron
      std::vector<std::string> fields = Parser::split(linea, ',');
      votante.carnet = fields[0];
      votante.apellido1 = fields[1];
      votante.apellido2 = fields[2];
      votante.nombre = fields[3];
      if (fields[4].compare("No") == 0) {
        votante.haVotado = false;
      } else {
        votante.haVotado = true;
      }
      votante.codigo = fields[5];
      votante.centroVotacion = fields[6];

      // Add the dummy to the map
      this->padron.insert(std::pair<std::string, datosVotante>(votante.carnet, votante));

      // Serialize the new voter into the file system
      this->serialize(votante.carnet, votante);
    }

    ret = true;
  }

  return ret;
}

bool PadronManager::serialize(const std::string& carnet, const datosVotante& data) {
  bool ret = false;

  if (!this->fs->fileExists("/" + carnet + ".votante")) {
    // Create the file for the user
    if (!this->fs->createFile(carnet + ".votante", 0, 0, uReadWrite)) {
    }

    // Char array for the data
    char serializedData[BLOCK_SIZE] = {0};

    // Copy the data into the serialized data
    data.carnet.copy(&serializedData[POS_CARNET], data.carnet.length());
    data.nombre.copy(&serializedData[POS_NOMBRE], data.nombre.length());
    data.apellido1.copy(&serializedData[POS_APELLIDO1], data.apellido1.length());
    data.apellido2.copy(&serializedData[POS_APELLIDO2], data.apellido2.length());
    data.centroVotacion.copy(&serializedData[POS_CENTRO], data.centroVotacion.length());
    data.codigo.copy(&serializedData[POS_CODIGO], data.codigo.length());
    serializedData[POS_HA_VOTADO] = (char)data.haVotado;

    // Write the data into the file system
    this->fs->writeFile("/" + carnet + ".votante", serializedData, BLOCK_SIZE, 0, 0);
    ret = true;
  }

  return ret;
}

bool PadronManager::deserialize(const std::string& carnet, datosVotante& data) {
  bool ret = false;

  if (this->fs->fileExists("/" + carnet + ".votante")) {
    char votanteSerializado[BLOCK_SIZE];
    this->fs->readFile("/" + carnet + ".votante", votanteSerializado, BLOCK_SIZE, 0, 0);

    // Read the data from the serialized data
    std::string carnet(votanteSerializado[POS_CARNET], LARGO_CARNET);
    std::string nombre(votanteSerializado[POS_NOMBRE], LARGO_NOMBRE);
    std::string apellido1(votanteSerializado[POS_APELLIDO1], LARGO_APELLIDO);
    std::string apellido2(votanteSerializado[POS_APELLIDO2], LARGO_APELLIDO);
    std::string centro(votanteSerializado[POS_CENTRO], LARGO_CENTRO);
    std::string codigo(votanteSerializado[POS_CODIGO], LARGO_CODIGO);
    char haVotado = votanteSerializado[POS_HA_VOTADO];
    bool yaVoto = true;
    if (haVotado == 0) {
      yaVoto = false;
    }

    // Copy the data into the struct
    data.carnet = carnet;
    data.nombre = nombre;
    data.apellido1 = apellido1;
    data.apellido2 = apellido2;
    data.centroVotacion = centro;
    data.codigo = codigo;
    data.haVotado = yaVoto;

    ret = true;
  }

  return ret;
}

bool PadronManager::votanteExiste(const std::string& carnet) {
  bool ret = false;

  if (this->padron.find(carnet) != this->padron.end()) {
    ret = true;
  }

  return ret;
}

std::string PadronManager::getNombreCompleto(const std::string& carnet) {
  std::string ret = "";

  if (this->votanteExiste(carnet)) {
    auto votante = this->padron.find(carnet);
    ret += votante->second.nombre;
    ret += " " + votante->second.apellido1;
    ret += " " + votante->second.apellido2;
  }

  return ret;
}

std::string PadronManager::getCentroVotacion(const std::string& carnet) {
  std::string ret = "";

  if (this->votanteExiste(carnet)) {
    auto votante = this->padron.find(carnet);
    ret += votante->second.centroVotacion;
  }

  return ret;
}

std::string PadronManager::getCodigo(const std::string& carnet) {
  std::string ret = "";

  if (this->votanteExiste(carnet)) {
    auto votante = this->padron.find(carnet);
    ret += votante->second.codigo;
  }

  return ret;
}

bool PadronManager::getHaVotado(const std::string& carnet) {
  bool ret = false;

  if (this->votanteExiste(carnet)) {
    auto votante = this->padron.find(carnet);
    ret = votante->second.haVotado;
  }

  return ret;
}

bool PadronManager::setCodigo(const std::string& carnet, const std::string& codigo) {
  bool ret = false;

  if (this->votanteExiste(carnet)) {
    auto votante = this->padron.find(carnet);
    votante->second.codigo = codigo;
    this->serialize(carnet, votante->second);
    ret = true;
  }

  return ret;
}

bool PadronManager::setHaVotado(const std::string& carnet) {
  bool ret = false;

  if (this->votanteExiste(carnet)) {
    auto votante = this->padron.find(carnet);
    votante->second.haVotado = true;
    this->serialize(carnet, votante->second);
    ret = true;
  }

  return ret;
}

void PadronManager::printPadron() {
  for(auto i = padron.cbegin(); i != myMap.cend(); ++i)
{
    std::cout<<"Nombre: " << i->second.nombre << " " << i->second.apellido1 << " " << it->second.apellido2 << "Si ha votado: "<<i->second.haVotado <<"Código: " << i->second.codigo << "Centro de votación: "<< second.centroVotacion "\n";
}

