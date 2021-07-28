#ifndef PADRON_CLIENT_HPP
#define PADRON_CLIENT_HPP

#include <string>

// CLIENTS
#include "Client.hpp"

// NETWORK
#include "Network/Socket.hpp"
#include "Network/TcpClient.hpp"

#define MAX_ATTEMPTS 3
#define RANDOM_FILENAME_LEN 5

#define UPDATE_CODE_OPCODE    "h"
#define UPDATE_VOTE_OPCODE    "i"
#define VERIFY_CODE_OPCODE    "j"
#define VERIFY_CARNET_OPCODE  "k"
#define GET_CENTRO_OPCODE     "l"
#define GET_NOMBRE_OPCODE     "m"
#define VERIFY_VOTE_OPCODE    "n"

class PadronClient : public Client {
 public:
  PadronClient() = delete;
  PadronClient(const std::string& parentIp, const std::string& parentPort);
  virtual ~PadronClient();

 private:
  std::string sendReceiveDatagram(std::string opCode, const std::string& carnet, const std::string& other = "");

 public:
  bool verifyCarnet(const std::string& carnet);
  bool updateCode(const std::string& carnet, std::string codigo);
  bool verifyCode(const std::string& carnet, std::string codigo);
  bool verifyVote(const std::string& carnet);
  bool updateVote(const std::string& carnet);
  bool verifyCentroVotacion(const std::string& carnet, const std::string& centro);
  std::string getCentroVotacion(const std::string& carnet);
  std::string getNombreCompleto(const std::string& carnet);
  void printPadron();
};

#endif
