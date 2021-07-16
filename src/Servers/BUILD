load("@rules_cc//cc:defs.bzl", "cc_library")

#
# PACKAGES
#

# File System Server
cc_library(
  name = "FSServer",
  srcs = ["FSServer.cpp"],
  hdrs = ["FSServer.hpp"],
  deps = [
    "//FileSystem:FileSystem",
    "//Network:Socket",
    "//Servers:Server",
  ],
)

# Padron Server
cc_library(
  name = "PadronServer",
  srcs = ["PadronServer.cpp"],
  hdrs = ["PadronServer.hpp"],
  deps = [
    ":Server",
    "//Network:Socket",
    "//Utils:Parser",
    "//Votacion:PadronManager",
  ],
  visibility = [
    ":friends",
  ],
)

# Base Server
cc_library(
  name = "Server",
  srcs = ["Server.cpp"],
  hdrs = ["Server.hpp"],
  deps = [
    "//Network:TcpServer",
  ],
)

# Vote Server
cc_library(
  name = "VoteServer",
  srcs = ["VoteServer.cpp"],
  hdrs = ["VoteServer.hpp"],
  deps = [
    "//Clients:VoteClient",
    "//FileSystem:FileSystem",
    "//Network:Socket",
    "//Servers:FSServer",
  ],
  visibility = [
    ":friends",
  ],
)


#
# FRIEND PACKAGES
#

package_group(
  name = "friends",
  packages = [
    "//Executables",
  ],
)
