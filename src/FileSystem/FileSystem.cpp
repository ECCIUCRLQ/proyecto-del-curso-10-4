#include "FileSystem.hpp"

#include <iostream>

FileSystem::FileSystem(const size_t& size, HardDrive* drive) : size(size),
  hardDrive(drive) {
  // Creates the Bitmap for free/used space in storage
  this->spaceBitmap = new Bitmap(this->size / BLOCK_SIZE);

  // Creates the root directory
  this->rootDirectory = new Directory("/");
}

FileSystem::~FileSystem() {
}

/*
 * FILE MANAGEMENT METHODS
*/

bool FileSystem::createFile(std::string fileName, int user, int group) {
  bool created = false;

  // TODO (any): Add a method to verify if path is relative or absolute
  std::string filePath = fileName;
  std::vector<std::string> splitPath = Parser::split(filePath, '/');

  File* found = this->search(filePath);
  if (found == nullptr) {
    // Verifies if the parent Directory exists
    std::string parentPath = Parser::parentDirectory(filePath, '/');
    Directory* parent;
    if (parentPath.length() == 0) {
      parent = rootDirectory;
    } else {
      parent = dynamic_cast<Directory*>(this->search(parentPath));
    }
    if (parent != nullptr) {
      // Verifies if a free block can be found for the new File
      size_t freeBlock = this->spaceBitmap->firstFreeBlock();
      if (freeBlock > 0) {
        // Creates a new File
        File* newFile = new File(fileName, freeBlock);

        // Adds the new File to the parent Directory
        parent->addFile(newFile);

        // Sets the block for the file as used
        this->spaceBitmap->setBlockAs(freeBlock, BITMAP_USED_BLOCK);

        // The File was created
        created = true;

        parent->list();
      }
    }
  }

  return created;
}

bool FileSystem::writeFile(std::string filepath, char* data, int user, int group) {
  // Busca el archivo
  // Abre el archivo
  // Medir el largo de data
  // Calcular cuántos bloques necesita para almacenar data
  // Se va a la última porción del archivo
  // Busca el primer byte disponible [calculado a partir de size]
  // Empieza a escribir bytes hasta llegar al final del bloque

  // Cuando llega al final del bloque:
  // Pregunta si el siguiente bloque está disponible:
    // Si el siguiente está disponible, lo agrega al "portion" actual

  // Si el siguiente bloque no está disponible:
    // Empieza a escribir en el próximo bloque vacío
    // Agregar un nuevo "portion" al archivo
  return true;
}

File* FileSystem::search(const std::string& filePath) {
  File* ret = nullptr;

  // Split the filePath
  std::vector<std::string> splitPath = Parser::split(filePath, '/');

  ret = this->search(&splitPath, 0, rootDirectory);

  return ret;
}

File* FileSystem::search(std::vector<std::string>* splitPath, size_t pos, Directory* directory) {
  File* ret = nullptr;

  // Stop condition
  if (pos == splitPath->size() - 1) {
    std::cout << "Elements in final dir: " << std::endl;
    directory->list();
    std::cout << "Searching for: " << splitPath->at(pos) << std::endl;
    ret = directory->search(splitPath->at(pos));
  } else {
    // Continues searching
    File* nextFile = directory->search(splitPath->at(pos));
    Directory* nextDir = dynamic_cast<Directory*>(nextFile);
    if (nextDir != nullptr) {
      ret = search(splitPath, pos + 1, nextDir);
    }
  }

  return ret;
}

bool FileSystem::deleteFile(const std::string& filePath, int user, int group) {
  bool ret = false;
  File* file = this->search(filePath);

  if (file != nullptr) {
    // Get the parent of the File/Directory
    File* parentFile = file->getParent();
    Directory* parent = dynamic_cast<Directory*>(parentFile);

    // Delete the File from the parent
    if (parent != nullptr) {
      parent->deleteFile(file);
    }

    // Get all the portions of the File
    auto portions = file->getAllPortions();

    // Set all the blocks of the portions to Free
    for (auto portion : portions) {
      for (size_t i = portion.first; i <= portion.second; ++i) {
        this->spaceBitmap->setBlockAs(i, BITMAP_FREE_BLOCK);
      }
    }
    
    // Delete the File
    delete file;
  }

  return ret;
}


bool FileSystem::openFile(std::string filepath, int user, int group){
	bool opened = false;
	if(search(filepath) != nullptr){
		search(filepath)->open();
		opened = true;
	}
	
	return opened;
}

bool FileSystem::closeFile(std::string filepath, int user, int group){
	bool closed = false;
	if(search(filepath) != nullptr){
		search(filepath)->close();
		closed = true;
	}
	
	return closed;
}

bool FileSystem::isFileOpen(std::string filepath, int user, int group){
	bool fileOpen = false;
	if(search(filepath) != nullptr){
		fileOpen = search(filepath)->isOpen();
	}
	return fileOpen;
}

