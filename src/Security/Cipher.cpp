#include "Cipher.hpp"

#include <cinttypes>
#include <fstream>
#include <iostream>

Cipher::Cipher() {
}

Cipher::~Cipher() {
}

std::string Cipher::encryptAES256(const std::string& pass, const std::string& data, bool base64) {
  std::string ret;
  size_t encLen;
  char* encData = this->encryptAES256(pass, data.c_str(), data.length(), &encLen);
  if (base64) {
    ret = base64_encode(encData);
  } else {
    ret = std::string(encData, encLen);
  }
  delete encData;
  return ret;
}

std::string Cipher::decryptAES256(const std::string& pass, std::string& data, bool base64) {
  std::string ret;
  size_t decLen;
  if (base64) {
    data = base64_decode(data);
  }
  char* decData = this->decryptAES256(pass, data.c_str(), data.length(), &decLen);
  ret.assign(decData, decLen);
  delete decData;
  return ret;
}

bool Cipher::encryptFileAES256(const std::string& pass, const std::string& filepath) {
  bool ret = false;
  std::ifstream input;
  input.open(filepath);
  if (input.is_open()) {
    // Read the file
    std::string fileContent = "";
    std::string line;
    while (std::getline(input, line)) {
      fileContent += line;
    }

    // Encrypt the file
    fileContent = this->encryptAES256(pass, fileContent, false);

    // Write the encrypted content into a new file
    std::ofstream output;
    output.open(filepath + ".enc");
    if (output.is_open()) {
      output << fileContent;
      output.close();
      ret = true;
    }

    input.close();
  }
  return ret;
}

bool Cipher::decryptFileAES256(const std::string& pass, const std::string& filepath) {
  bool ret = false;
  std::ifstream input;
  input.open(filepath);
  if (input.is_open()) {
    // Read the file
    std::string fileContent = "";
    std::string line;
    while (std::getline(input, line)) {
      fileContent += line;
    }

    // Decrypt the file
    fileContent = this->decryptAES256(pass, fileContent, false);

    // Write the decrypted content into a new file
    std::ofstream output;
    output.open(filepath + ".dec");
    if (output.is_open()) {
      output << fileContent;
      output.close();
      ret = true;
    }

    input.close();
  }
  return ret;
}

char* Cipher::encryptAES256(std::string pass, const char* data, size_t dataSize, size_t* outSize) {
  // Generate SALT
  char salt[AES256_SALT_LEN];
  ::gcry_randomize(salt, AES256_SALT_LEN, GCRY_VERY_STRONG_RANDOM);

  // Array for the key
  char key[AES256_KEY_LEN];

  // Derive the key from the password and salt
  gcry_error_t error = ::gcry_kdf_derive(pass.c_str(), pass.length(), GCRY_KDF_PBKDF2,
  GCRY_MD_SHA512, salt, AES256_SALT_LEN, AES256_PASS_ROUNDS, AES256_KEY_LEN,
  key);
  if (error) {
    std::cout << "Error: " << ::gcry_strsource(error) << ::gcry_strerror(error) << std::endl;
  }

  // Variables for encription handles
  size_t blockSize = ::gcry_cipher_get_algo_blklen(GCRY_CIPHER_AES256);
  size_t blocksRequired = dataSize / blockSize;
  if (dataSize % blockSize) {
    ++blocksRequired;
  }
  *outSize = blockSize * blocksRequired;

  // Initialize encription handles
  gcry_cipher_hd_t hd;
  error = ::gcry_cipher_open(&hd, GCRY_CIPHER_AES256, GCRY_CIPHER_MODE_CBC, GCRY_CIPHER_CBC_CTS);
  if (error) {
    std::cout << "Error: " << ::gcry_strsource(error) << ::gcry_strerror(error) << std::endl;
  }
  error = ::gcry_cipher_setkey(hd, key, AES256_KEY_LEN);
  if (error) {
    std::cout << "Error: " << ::gcry_strsource(error) << ::gcry_strerror(error) << std::endl;
  }
  error = ::gcry_cipher_setiv(hd, salt, AES256_IV_LEN);
  if (error) {
    std::cout << "Error: " << ::gcry_strsource(error) << ::gcry_strerror(error) << std::endl;
  }

  // Cipher buffer
  char* encryptBuffer = new char[*outSize];
  ::memset(encryptBuffer, 0, *outSize);
  // Copy the data
  ::memcpy(encryptBuffer, data, dataSize);

  // Encrypt the output data
  error = gcry_cipher_encrypt(hd, encryptBuffer,
    *outSize, NULL, 0);
  if (error) {
    std::cout << "Error: " << ::gcry_strsource(error) << " " << ::gcry_strerror(error) << std::endl;
  }

  // Create the out array
  char* out = new char[AES256_SALT_LEN + *outSize];

  // Copy the salt and the data to the output
  ::memcpy(out, salt, AES256_SALT_LEN);
  ::memcpy(out + AES256_SALT_LEN, encryptBuffer, *outSize);
  *outSize += AES256_SALT_LEN;

  // Clean the Salt/IV and close the cipher
  gcry_cipher_close(hd);
  delete[] encryptBuffer;

  return out;
}

char* Cipher::decryptAES256(std::string pass, const char* data, size_t dataSize, size_t* outSize) {
  // Array for the key
  char key[AES256_KEY_LEN];

  // Read the salt from the input
  char salt[AES256_SALT_LEN];
  ::memcpy(salt, data, AES256_SALT_LEN);
  // char salt[AES256_SALT_LEN] = {'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'};

  // Derive the key from the password and salt
  gcry_error_t error = ::gcry_kdf_derive(pass.c_str(), pass.length(), GCRY_KDF_PBKDF2,
  GCRY_MD_SHA512, salt, AES256_SALT_LEN, AES256_PASS_ROUNDS, AES256_KEY_LEN,
  key);
  if (error) {
    std::cout << "Error: " << ::gcry_strsource(error) << ::gcry_strerror(error) << std::endl;
  }
  
  // Initialize encription handles
  gcry_cipher_hd_t hd;
  error = ::gcry_cipher_open(&hd, GCRY_CIPHER_AES256, GCRY_CIPHER_MODE_CBC, GCRY_CIPHER_CBC_CTS);
  if (error) {
    std::cout << "Error: " << ::gcry_strsource(error) << ::gcry_strerror(error) << std::endl;
  }
  error = ::gcry_cipher_setkey(hd, key, AES256_KEY_LEN);
  if (error) {
    std::cout << "Error: " << ::gcry_strsource(error) << ::gcry_strerror(error) << std::endl;
  }
  error = ::gcry_cipher_setiv(hd, salt, AES256_IV_LEN);
  if (error) {
    std::cout << "Error: " << ::gcry_strsource(error) << ::gcry_strerror(error) << std::endl;
  }

  // Initialize the decrypt buffer
  data = data + AES256_SALT_LEN;
  dataSize = dataSize - AES256_SALT_LEN;
  char* decryptBuff = new char[dataSize];
  ::memcpy(decryptBuff, data, dataSize);

  // Decrypt the output data
  error = gcry_cipher_decrypt(hd, decryptBuff, dataSize, NULL, 0);
  if (error) {
    std::cout << "Error: " << ::gcry_strsource(error) << ::gcry_strerror(error) << std::endl;
  }

  // Initialize output memory
  *outSize = dataSize;
  char* out = new char[*outSize];

  // Copy the decrypted data to the output
  ::memcpy(out, decryptBuff, dataSize);

  // Cleanup
  gcry_cipher_close(hd);
  delete[] decryptBuff;

  // Return the amount of bytes used
  return out;
}
