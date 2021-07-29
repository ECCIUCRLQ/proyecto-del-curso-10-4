CXX = g++
INCLUDES =  -Isrc/Network -Isrc/FileSystem -Isrc/Utils -Isrc/Servers -Isrc/Clients

all: vote_server vote_client vote_client2

vote_server:
	$(CXX) $(INCLUDES) src/Network/*.cpp src/FileSystem/*.cpp src/Utils/*.cpp src/Servers/*.cpp src/Clients/*.cpp src/ServerMain.cpp -o VoteServer.out
	
vote_client:
	$(CXX) $(INCLUDES) src/Network/*.cpp src/FileSystem/*.cpp src/Utils/*.cpp src/Servers/*.cpp src/Clients/*.cpp src/ClientMain.cpp -o VoteClient.out -pthread
	
vote_client2:
	$(CXX) $(INCLUDES) src/Network/*.cpp src/FileSystem/*.cpp src/Utils/*.cpp src/Servers/*.cpp src/Clients/*.cpp src/ClientMain2.cpp -o VoteClient2.out -pthread

prueba:
	$(CXX) $(INCLUDES) src/Network/*.cpp src/FileSystem/*.cpp src/Utils/*.cpp src/Clients/*.cpp src/prueba.cpp -o prueba.out
