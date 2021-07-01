#include "Base64.hpp"
#include "Cipher.hpp"
#include "Hash.hpp"

#include <iostream>

void testSHA256(const std::string& data) {
  std::cout << "Testing SHA256..." << std::endl;
  std::cout << "SHA256: ";
  std::string hash = Hash::SHA256(data);
  std::cout << hash << std::endl << std::endl;
}

void testSHA512(const std::string& data) {
  std::cout << "Testing SHA512..." << std::endl;
  std::cout << "SHA512: ";
  std::string hash = Hash::SHA512(data);
  std::cout << hash << std::endl << std::endl;
}

void testAES(const std::string& data, const std::string& password) {
  std::cout << "Testing AES..." << std::endl;
  Cipher cipher;
  std::vector<unsigned char> ret;
  cipher.encryptWithAES256(data, password, ret);
}

int main(int argc, char const* argv[]) {
  Hash hasher;

  std::string data = "Pruebas";
  std::string tmp;
  //while (std::getline(std::cin, tmp)) {
  //  data += tmp;
  //}

  // TEST SHA256
  testSHA256(data);

  // TEST SHA512
  testSHA512(data);

  // TEST AES
  std::string password = "password";
  testAES(data, password);

  return 0;
}
