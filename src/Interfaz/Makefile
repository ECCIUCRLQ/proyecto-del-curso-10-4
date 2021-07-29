exePadronClient: MainUI.cpp
	g++ -o interfazUrna ../Network/NetworkAddress.cpp ../Network/Socket.cpp ../Network/TcpServer.cpp ../Servers/Server.cpp ../Servers/FSServer.cpp ../Network/TcpClient.cpp ../Servers/PadronServer.cpp ../Votacion/PadronManager.cpp ../FileSystem/FileSystem.cpp ../FileSystem/Bitmap.cpp ../FileSystem/Directory.cpp ../FileSystem/File.cpp ../FileSystem/HardDrive.cpp ../Utils/Parser.cpp ../Clients/PadronClient.cpp ../Clients/Client.cpp ../Clients/FSClient.cpp MainUI.cpp `pkg-config gtkmm-3.0 --cflags --libs`

clean:
	-rm serverPadron clientPadron

