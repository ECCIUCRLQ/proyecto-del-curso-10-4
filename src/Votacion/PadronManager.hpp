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
 /**
  * @brief objeto de sistema de archivo propio del padron manager
  */
  FileSystem* fs;
  /**
  * @brief ruta de donde se encuentra el archivo que carga y contiene el padron
  */
  std::string rutaPadron = "";
  /**
  * @brief mapa asociativo entre el numero de carnet del votante y sus datos en el padron.
  */
  std::map<std::string, datosVotante> padron;

 public:
 /**
   * @brief Constructor del padron manager
   * @param filepath ruta de donde se encuentra el archivo que se carga y que contiene el padron
   * @param fs sistema de archivos propio del padron manager
   */
  PadronManager(const std::string& filepath, FileSystem& fs);
  ~PadronManager();

 private:
 /**
   * @brief Constructor del padron manager
   * @param filepath ruta de donde se encuentra el archivo que se carga y que contiene el padron
   * @param fs sistema de archivos propio del padron manager
   * @return True on success, false if the File could not be created
   */
  bool initPadron();
 /**
   * @brief serializa el sistema archivos propio del padron manager
   * @param carnet nuevo del votante agregado al padron manager
   * @param data datos del votane que esta siendo agregado al padron manager
   * @return True si hubo exito, false si no se pudo completar la serializacion
   */
  bool serialize(const std::string& carnet, const datosVotante& data);
 /**
   * @brief deserializa el sistema archivos propio del padron manager
   * @param carnet nuevo del votante agregado al padron manager
   * @param data datos del votane que esta siendo agregado al padron manager
   * @return True si hubo exito, false si no se pudo completar la deserializacion
   */
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
  void printPadron();
};


#endif
