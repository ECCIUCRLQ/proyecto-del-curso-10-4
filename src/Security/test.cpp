#include "Base64.hpp"
#include "Cipher.hpp"
#include "Hash.hpp"

#include <fstream>
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

void testStringAES(const std::string& data, const std::string& password) {
  std::cout << "Testing AES for strings..." << std::endl;
  Cipher cipher;

  std::cout << "Encrypting data..." << std::endl;
  std::string encData = cipher.encryptAES256(password, data);
  std::cout << "Encrypted data: " << encData << std::endl << std::endl;

  std::cout << "Decrypting data..." << std::endl;
  std::string decData = cipher.decryptAES256(password, encData);
  std::cout << "Decrypted data: " << decData << std::endl;
}

void testFileAES(const std::string& data, const std::string& password) {
  std::cout << std::endl << "Testing AES for files..." << std::endl;
  Cipher cipher;

  std::ofstream newFile;
  newFile.open("encTest.txt");
  if (newFile.is_open()) {
    newFile << data;
    newFile.close();
    if (cipher.encryptFileAES256(password, "encTest.txt")) {
      std::cout << "encTest.txt.enc created successfully" << std::endl;
    }

    if (cipher.decryptFileAES256(password, "encTest.txt.enc")) {
      std::cout << "encTest.txt.enc.dec created successfully" << std::endl;
    }
  }
}

int main(int argc, char const* argv[]) {
  Hash hasher;

  std::string data = "";
  std::string tmp;
  std::cout << "Ingrese un texto para pruebas: ";
  std::getline(std::cin, data);
  std::cout << std::endl;

  // TEST SHA256
  testSHA256(data);

  // TEST SHA512
  testSHA512(data);

  // TEST AES STRING
  std::cout << "Ingrese una clave para AES: ";
  std::string password = "";
  std::getline(std::cin, password);
  std::cout << std::endl;
  testStringAES(data, password);

  // TEST AES FILE
  testFileAES(data, password);

  return 0;
}
