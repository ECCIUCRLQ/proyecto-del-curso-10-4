# Compile
CXX = g++
INCLUDES = -I$(shell pwd)
CXXFLAGS = `pkg-config --cflags gtkmm-3.0` -Wall
LIBS = `pkg-config --libs gtkmm-3.0` -lgcrypt -lgpg-error

# Objects
CLIENTS = Client.o FSClient.o PadronClient.o VoteClient.o
FILE_SYSTEM = Bitmap.o Directory.o File.o FileSystem.o HardDrive.o
GUIS = Urna.o MaquinaVerificadora.o
NETWORK = NetworkAddress.o Socket.o TcpClient.o TcpServer.o
SECURITY = Base64.o Cipher.o Hash.o
SERVERS = FSServer.o PadronServer.o Server.o VoteServer.o
SHELLS = PadronShell.o VoteShell.o
UTILS = Parser.o
VOTACION = Padron.o PadronManager.o

ALL_OBJECTS = $(CLIENTS) $(FILE_SYSTEM) $(GUIS) $(NETWORK) $(SECURITY) $(SERVERS) $(SHELLS) $(UTILS) $(VOTACION)

# Executables
EXECUTABLE = PadronServerExe PadronShellExe VoteClientExe VoteServerExe

# Client Objects Compile
Client.o: Clients/Client.hpp Clients/Client.hpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) Clients/Client.cpp -o Build/Client.o $(LIBS)

FSClient.o: Clients/FSClient.hpp Clients/FSClient.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) Clients/FSClient.cpp -o Build/FSClient.o $(LIBS)

PadronClient.o: Clients/PadronClient.hpp Clients/PadronClient.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) Clients/PadronClient.cpp -o Build/PadronClient.o $(LIBS)

VoteClient.o: Clients/VoteClient.hpp Clients/VoteClient.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) Clients/VoteClient.cpp -o Build/VoteClient.o $(LIBS)


# File System Objects Compile
Bitmap.o: FileSystem/Bitmap.hpp FileSystem/Bitmap.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) FileSystem/Bitmap.cpp -o Build/Bitmap.o $(LIBS)

Directory.o: FileSystem/Directory.hpp FileSystem/Directory.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) FileSystem/Directory.cpp -o Build/Directory.o $(LIBS)

File.o: FileSystem/File.hpp FileSystem/File.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) FileSystem/File.cpp -o Build/File.o $(LIBS)

FileSystem.o: FileSystem/FileSystem.hpp FileSystem/FileSystem.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) FileSystem/FileSystem.cpp -o Build/FileSystem.o $(LIBS)

HardDrive.o: FileSystem/HardDrive.hpp FileSystem/HardDrive.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) FileSystem/HardDrive.cpp -o Build/HardDrive.o $(LIBS)


# Network Objects Compile
NetworkAddress.o: Network/NetworkAddress.hpp Network/NetworkAddress.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) Network/NetworkAddress.cpp -o Build/NetworkAddress.o $(LIBS)

Socket.o: Network/Socket.hpp Network/Socket.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) Network/Socket.cpp -o Build/Socket.o $(LIBS)

TcpClient.o: Network/TcpClient.hpp Network/TcpClient.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) Network/TcpClient.cpp -o Build/TcpClient.o $(LIBS)

TcpServer.o: Network/TcpServer.hpp Network/TcpServer.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) Network/TcpServer.cpp -o Build/TcpServer.o $(LIBS)


# Security Objects Compile
Base64.o: Security/Base64.hpp Security/Base64.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) Security/Base64.cpp -o Build/Base64.o $(LIBS)

Cipher.o: Security/Cipher.hpp Security/Cipher.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) Security/Cipher.cpp -o Build/Cipher.o $(LIBS)

Hash.o: Security/Hash.hpp Security/Hash.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) Security/Hash.cpp -o Build/Hash.o $(LIBS)


# Server Objects Compile
FSServer.o: Servers/FSServer.hpp Servers/FSServer.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) Servers/FSServer.cpp -o Build/FSServer.o $(LIBS)

PadronServer.o: Servers/PadronServer.hpp Servers/PadronServer.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) Servers/PadronServer.cpp -o Build/PadronServer.o $(LIBS)

Server.o: Servers/Server.hpp Servers/Server.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) Servers/Server.cpp -o Build/Server.o $(LIBS)

VoteServer.o: Servers/VoteServer.hpp Servers/VoteServer.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) Servers/VoteServer.cpp -o Build/VoteServer.o $(LIBS)


# Shell Objects Compile
PadronShell.o: Shells/PadronShell.hpp Shells/PadronShell.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) Shells/PadronShell.cpp -o Build/PadronShell.o $(LIBS)

VoteShell.o: Shells/VoteShell.hpp Shells/VoteShell.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) Shells/VoteShell.cpp -o Build/VoteShell.o $(LIBS)


# Util Objects Compile
Parser.o: Utils/Parser.hpp Utils/Parser.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) Utils/Parser.cpp -o Build/Parser.o $(LIBS)


# Votacion Objects Compile
Padron.o: Votacion/Padron.hpp Votacion/Padron.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) Votacion/Padron.cpp -o Build/Padron.o $(LIBS)

PadronManager.o: Votacion/PadronManager.hpp Votacion/PadronManager.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) Votacion/PadronManager.cpp -o Build/PadronManager.o $(LIBS)


# GUIs
Urna.o: GUI/Urna.hpp GUI/Urna.hpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) GUI/Urna.cpp -o Build/Urna.o $(LIBS)

MaquinaVerificadora.o: GUI/MaquinaVerificadora.hpp GUI/MaquinaVerificadora.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) GUI/MaquinaVerificadora.cpp -o Build/MaquinaVerificadora.o $(LIBS)

# Executables
PadronServer: makeDirs $(ALL_OBJECTS) Executables/PadronServer.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) Build/*.o Executables/PadronServer.cpp -o Bin/PadronServer.out $(LIBS)

PadronShell: makeDirs $(ALL_OBJECTS) Executables/PadronShell.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) Build/*.o Executables/PadronShell.cpp -o Bin/PadronShell.out $(LIBS)

VoteClient: makeDirs $(ALL_OBJECTS) Executables/VoteClient.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) Build/*.o Executables/VoteClient.cpp -o Bin/VoteClient.out $(LIBS)

VoteServer: makeDirs $(ALL_OBJECTS) Executables/VoteServer.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) Build/*.o Executables/VoteServer.cpp -o Bin/VoteServer.out $(LIBS)

Urna: makeDirs $(ALL_OBJECTS) Executables/Urna.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) Build/*.o Executables/Urna.cpp -o Bin/Urna.out $(LIBS)

MaquinaVerificadora: makeDirs $(ALL_OBJECTS) Executables/MaquinaVerificadora.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) Build/*.o Executables/MaquinaVerificadora.cpp -o Bin/MaquinaVerificadora.out $(LIBS)

all: makeDirs PadronServer PadronShell VoteClient VoteServer Urna MaquinaVerificadora

# Phonies
.PHONY: makeDirs
makeDirs:
	mkdir -p Build
	mkdir -p Bin

.PHONY: clean
clean:
	rm -rf Build/*
	rm -rf Bin/*.out
