#ifndef PADRON_SHELL_HPP
#define PADRON_SHELL_HPP

#include "PadronClient.hpp"

#include <string>



#define PRINT_COMMAND   "print"
#define UPDATECODE_COMMAND  "code"
#define VERIFYCODE_COMMAND  "verifycode"
#define VERIFYCARNET_COMMAND "verifycarnet"
#define UPDATEVOTE_COMMAND "vote"

class PadronShell {
 private:
  PadronClient& padronClient;


 public:
  PadronShell(PadronClient& padronClient);
  ~PadronShell();

 private:

  // code created successfully (actualizar padron)
  void updateCode(const std::string& filepath, std::string codigo);
  // code associated with carnet verified against padron (verificar contra padron)
  void verifyCode(const std::string& filepath, std::string codigo);
  // voter carnet verified against padron (verificar carnet para crear codigo)
  void verifyCarnet(const std::string& filepath);
  // voter vote updated in padron (actualizar padron)
  void updateVote(const std::string& filepath);
    void printDisk();

 private:
  void parse(const std::string& input);

 public:
  void shell();
};


#endif
