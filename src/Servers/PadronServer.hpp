/* COPYRIGHT Equipo Tronaditas 2021 */
// Clase principal-Servidor del padron
#ifndef SERVER_PADRON_HPP
#define SERVER_PADRON_HPP

#include <string>

// NETWORK
#include "Network/Socket.hpp"

// SERVERS
#include "Server.hpp"

// UTILS
#include "Utils/Parser.hpp"

// LOGGER
#include "Logger/Logger.hpp"
// VOTACION
#include "Votacion/PadronManager.hpp"

#define UPDATE_CODE_OPCODE    'h'
#define UPDATE_VOTE_OPCODE    'i'
#define VERIFY_CODE_OPCODE    'j'
#define VERIFY_CARNET_OPCODE  'k'
#define GET_CENTRO_OPCODE     'l'
#define GET_NOMBRE_OPCODE     'm'
#define VERIFY_VOTE_OPCODE    'n'
#define PRINT_OPCODE          'p'

class PadronServer : public Server {
 protected:
  PadronManager* padron;
  Logger* logger;

 public:
  PadronServer() = delete;
  PadronServer(PadronManager& padron);
  ~PadronServer();

 protected:
 
  std::string carnetValido(const std::string& carnet);
  std::string codigoValido(const std::string& carnet, const std::string& data);
  std::string getNombreCompleto(const std::string& carnet);
  std::string getCentroVotacion(const std::string& carnet);
  std::string getHaVotado(const std::string& carnet);

 protected:
  /*
  *Funcion setCodigo- cambia el codigo de verificacion de un votante
  * datos de la funcion setCodigo
  * @param carnet-carnet del votante
  * @param codigo-codigo de verificacion hasheado
  */
  std::string setCodigo(const std::string& carnet, const std::string& codigo);
  std::string setHaVotado(const std::string& carnet);

 protected:
  void printPadron();

 protected:
 /*
  *Funcion handleClientConnection determina que solicitud se esta realizando basandose en el datagrama recibido que fue enviado por el cliente
  * datos de la funcion handleClientConnection
  * @param socket- socket del cliente conectandose con el padron
  */
  virtual void handleClientConnection(Socket& socket);
};


#endif
