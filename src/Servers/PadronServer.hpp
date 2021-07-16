#ifndef SERVER_PADRON_HPP
#define SERVER_PADRON_HPP

#include <string>

// NETWORK
#include "Network/Socket.hpp"

// SERVERS
#include "Server.hpp"

// UTILS
#include "Utils/Parser.hpp"

// VOTACION
#include "Votacion/PadronManager.hpp"

#define UPDATE_CODE_OPCODE    'h'
#define UPDATE_VOTE_OPCODE    'i'
#define VERIFY_CODE_OPCODE    'j'
#define VERIFY_CARNET_OPCODE  'k'
#define GET_CENTRO_OPCODE     'l'
#define GET_NOMBRE_OPCODE     'm'
#define VERIFY_VOTE_OPCODE    'n'

class PadronServer : public Server {
 protected:
  PadronManager* padron;

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
  std::string setCodigo(const std::string& carnet, const std::string& codigo);
  std::string setHaVotado(const std::string& carnet);

 protected:
  virtual void handleClientConnection(Socket& socket);
};


#endif
