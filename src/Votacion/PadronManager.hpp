#ifndef PADRON_MANAGER_HPP
#define PADRON_MANAGER_HPP

#include <map>
#include <string>

// FILE SYSTEM
#include "FileSystem/FileSystem.hpp"

// UTILS
#include "Utils/Parser.hpp"

// Largo de datos de votante en bytes, para serializar
#define LARGO_CARNET 10
#define LARGO_NOMBRE 30
#define LARGO_APELLIDO 30
#define LARGO_CENTRO 30
#define LARGO_CODIGO 64

#define POS_CARNET 0
#define POS_NOMBRE 9
#define POS_APELLIDO1 39
#define POS_APELLIDO2 69
#define POS_CENTRO 99
#define POS_CODIGO 129
#define POS_HA_VOTADO 193

class PadronManager {
 private:
  typedef struct {
    std::string carnet = "";
    std::string nombre = "";
    std::string apellido1 = "";
    std::string apellido2 = "";
    std::string centroVotacion = "";
    std::string codigo = "";
    bool haVotado = false;
  } datosVotante;

 private:
  FileSystem* fs;
  std::string rutaPadron = "";
  std::map<std::string, datosVotante> padron;

 public:
  PadronManager(const std::string& filepath, FileSystem& fs);
  ~PadronManager();

 private:
  bool initPadron();
  bool serialize(const std::string& carnet, const datosVotante& data);
  bool deserialize(const std::string& carnet, datosVotante& data);
 
 public:
  bool votanteExiste(const std::string& carnet);
  std::string getNombreCompleto(const std::string& carnet);
  std::string getCentroVotacion(const std::string& carnet);
  std::string getCodigo(const std::string& carnet);
  bool getHaVotado(const std::string& carnet);

 public:
  bool setCodigo(const std::string& carnet, const std::string& codigo);
  bool setHaVotado(const std::string& carnet);
};


#endif
