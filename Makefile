CXX = g++
INCLUDES =  -Isrc/Network -Isrc/FileSystem -Isrc/Utils -Isrc/Servers -Isrc/Clients

all: ServerMain ClientMain prueba

ServerMain:
	$(CXX) $(INCLUDES) src/Network/*.cpp src/FileSystem/*.cpp src/Utils/*.cpp src/Servers/*.cpp src/ServerMain.cpp -o ServerMain.out
	
ClientMain:
	$(CXX) $(INCLUDES) src/Network/*.cpp src/FileSystem/*.cpp src/Utils/*.cpp src/Clients/*.cpp src/ClientMain.cpp -o ClientMain.out

prueba:
	$(CXX) $(INCLUDES) src/Network/*.cpp src/FileSystem/*.cpp src/Utils/*.cpp src/Clients/*.cpp src/prueba.cpp -o prueba.out
