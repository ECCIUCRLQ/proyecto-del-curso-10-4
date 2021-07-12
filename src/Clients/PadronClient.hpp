#ifndef PADRON_CLIENT_HPP
#define PADRON_CLIENT_HPP

#include "FileSystem.hpp"
#include "FSClient.hpp"
#include "Socket.hpp"
#define MAX_ATTEMPTS 3
#define RANDOM_FILENAME_LEN 5
#define UPDATE_CODE_OPCODE 'h'
#define UPDATE_VOTE_OPCODE 'i'
#define VERIFY_CODE_OPCODE 'j'
#define VERIFY_CARNET_OPCODE 'k'
#define PRINT_DISK 'z'
class PadronShell;
class PadronClient : public FSClient {
 friend class PadronShell;

 public:
  PadronClient() = delete;
  PadronClient(FileSystem& fs, const std::string& parentIp, const std::string& parentPort);
  virtual ~PadronClient();


 public:
  bool updateCode(const std::string& filepath, std::string codigo);
  bool verifyCode(const std::string& filepath, std::string codigo);
  bool verifyCarnet(const std::string& filepath);
  bool updateVote(const std::string& filepath);
  bool printDisk();

};

#endif
