#ifndef CIPHER_HPP
#define CIPHER_HPP

#include <gcrypt.h>
#include <string>
#include <vector>

#define AES256_SALT_LEN 16
#define AES256_PASS_ROUNDS 16
#define AES256_KEY_LEN 32
#define AES256_IV_LEN 16

class Cipher {
 public:
  Cipher();
  ~Cipher();

 private:
  char* encryptAES256(std::string pass, const char* data, size_t dataSize, size_t* outSize);
  char* decryptAES256(std::string pass, const char* data, size_t dataSize, size_t* outSize);

 public:
  std::string encryptAES256(const std::string& pass, const std::string& data, bool base64 = true);
  std::string decryptAES256(const std::string& pass, std::string& data, bool base64 = true);

 public:
  bool encryptFileAES256(const std::string& pass, const std::string& filepath);
  bool decryptFileAES256(const std::string& pass, const std::string& filepath);
};


#endif
