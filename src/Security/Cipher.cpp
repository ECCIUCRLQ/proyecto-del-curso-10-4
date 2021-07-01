#include "Cipher.hpp"

#include "Base64.hpp"

#include <stdexcept>

#include <cinttypes>
#include <iostream>

Cipher::Cipher() {
}

Cipher::~Cipher() {
}

bool Cipher::prepareAES256(AESConf& conf, gcry_cipher_hd_t* hd) {
  bool ret = true;

  gcry_error_t error = gcry_cipher_open(hd, GCRY_CIPHER_AES256, GCRY_CIPHER_MODE_CBC, 0);
  if (error) {
    ret = false;
  }

  error = gcry_cipher_setkey(*hd, conf.key, conf.keyLen);
  if (error) {
    ret = false;
  }

  error = gcry_cipher_setiv(*hd, conf.iv, conf.ivLen);
  
  uint64_t params[3];
  params[0] = conf.messageLen;
  params[1] = 0;
  params[2] = conf.authTagLen;

  error = gcry_cipher_ctl(*hd, GCRYCTL_SET_CCM_LENGTHS, params, sizeof(params));
  if (error) {
    ret = false;
  }

  return ret;
}

bool Cipher::encryptWithAES256(const std::string& data, const std::string& pass,
    std::vector<unsigned char> res) {
  bool ret = true;

  // Config
  AESConf conf;
  conf.key = "12345678901234567890123456789012";
  conf.keyLen = 32;
  conf.iv = "1234567890123456";
  conf.ivLen = 16;
  conf.messageLen = data.length();
  conf.authTagLen = 8;

  // Create the hd
  gcry_cipher_hd_t hd;
  if (this->prepareAES256(conf, &hd)) {
    throw std::runtime_error("Error intializing enc");
  }

  void* encData = reinterpret_cast<void*>(new char[conf.messageLen]);
  
  gcry_error_t error = gcry_cipher_encrypt(hd, encData, conf.messageLen, reinterpret_cast<const void*>(data.c_str()), data.length());
  if (error) {
    //throw std::runtime_error("Erro 2");
  }

  char* cEncData = reinterpret_cast<char*>(encData);
  std::string e = std::string(cEncData, data.length());

  std::cout << base64_encode(e) << std::endl;

  delete cEncData;

  return ret;
}

bool Cipher::decryptWithAES256(const std::string& data, const std::string& pass,
    std::vector<unsigned char> res) {
  bool ret = true;

  return ret;
}

