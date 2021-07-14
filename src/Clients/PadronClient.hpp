#ifndef PADRON_CLIENT_HPP
#define PADRON_CLIENT_HPP

// CLIENTS
#include "Clients/FSClient.hpp"

// FILE SYSTEM
#include "FileSystem/FileSystem.hpp"

// NETWORK
#include "Network/Socket.hpp"

#define MAX_ATTEMPTS 3
#define RANDOM_FILENAME_LEN 5
#define UPDATE_CODE_OPCODE 'h'
#define UPDATE_VOTE_OPCODE 'i'
#define VERIFY_CODE_OPCODE 'j'
#define VERIFY_CARNET_OPCODE 'k'
#define PRINT_DISK 'z'

class PadronClient : public Client {
 public:
  PadronClient() = delete;
  PadronClient(const std::string& parentIp, const std::string& parentPort);
  virtual ~PadronClient();

 public:
  bool updateCode(const std::string& filepath, std::string codigo);
  bool verifyCode(const std::string& filepath, std::string codigo);
  bool verifyCarnet(const std::string& filepath);
  bool updateVote(const std::string& filepath);
  bool printDisk();
};

#endif
