#ifndef PADRON_SHELL_HPP
#define PADRON_SHELL_HPP

#include <string>

// CLIENTS
#include "Clients/PadronClient.hpp"

// UTILS
#include "Utils/Parser.hpp"

#define VERIFYCARNET_COMMAND  "verifyCarnet"
#define UPDATECODE_COMMAND    "updateCode"
#define VERIFYCODE_COMMAND    "verifyCode"
#define UPDATEVOTE_COMMAND    "updateVote"
#define VERIFYVOTE_COMMAND    "verifyVote"
#define GETCENTRO_COMMAND     "centro"
#define GETNAME_COMMAND       "name"

class PadronShell {
 private:
  PadronClient& padronClient;

 public:
  PadronShell(PadronClient& padronClient);
  ~PadronShell();

 private:
  // voter carnet verified against padron (verificar carnet para crear codigo)
  void verifyCarnet(const std::string& carnet);
  // code created successfully (actualizar padron)
  void updateCode(const std::string& carnet, std::string codigo);
  // code associated with carnet verified against padron (verificar contra padron)
  void verifyCode(const std::string& carnet, std::string codigo);
  // verify if the voter has already voted
  void verifyVote(const std::string& carnet);
  // voter vote updated in padron (actualizar padron)
  void updateVote(const std::string& carnet);
  // Get the vote centre for the voter
  void getCentro(const std::string& carnet);
  // Get the voter's full name
  void getName(const std::string& carnet);

 private:
  void parse(const std::string& input);

 public:
  void shell();
};


#endif
