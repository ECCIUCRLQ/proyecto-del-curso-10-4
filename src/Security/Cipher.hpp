#ifndef CIPHER_HPP
#define CIPHER_HPP

#include <gcrypt.h>
#include <string>
#include <vector>

class Cipher {
 public:
  Cipher();
  ~Cipher();

 private:
  typedef struct {
    const void* key = nullptr;
    const void* iv = nullptr;
    size_t messageLen = 0;
    size_t keyLen = 0;
    size_t ivLen = 0;
    int authTagLen = 0;
  } AESConf;

 private:
  bool generateAESConf();
  bool prepareAES256(AESConf& conf, gcry_cipher_hd_t* h);

 public:
  bool encryptWithAES256(const std::string& data, const std::string& pass,
    std::vector<unsigned char> res);
  bool decryptWithAES256(const std::string& data, const std::string& pass,
    std::vector<unsigned char> res);
};


#endif
