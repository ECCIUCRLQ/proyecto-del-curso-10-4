#ifndef PADRON_CLIENT_HPP
#define PADRON_CLIENT_H

#include "FileSystem.hpp"
#include "FSClient.hpp"
#include "Socket.hpp"
#define MAX_ATTEMPTS 3
#define RANDOM_FILENAME_LEN 5
#define UPDATE_CODE_UPCODE 'h'
#define UPDATE_CARNET_UPCODE 'i'
#define VERIFY_CODE_UPCODE 'j'
#define VERIFY_CARNET_UPCODE 'k'
class PadronClient : public FSClient {

private:
  std::string clientClass = "";
  std::string clientID = "";

 public:
  PadronClient() = delete;
  PadronClient(FileSystem& fs, const std::string& parentIp, const std::string& parentPort);
  virtual ~VoteClient();

 private:
  bool getClassAndID();

 private:
  bool createFileLocal(const std::string& filepath);
  bool writeFileLocal(const std::string& filepath, const std::string& data);

 public:
  bool updateCode(const std::string& filepath, std::string codigo);
  bool verifyCode(const std::string& filepath, std::string codigo);
  bool verifyCarnet(const std::string& filepath);
  bool updateVote(const std::string& filepath);

}
