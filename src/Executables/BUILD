load("@rules_cc//cc:defs.bzl", "cc_binary")


#
# EXECUTABLE BINARIES
#

# Padron Client
cc_binary(
  name = "PadronShell",
  srcs = ["PadronShell.cpp"],
  deps = [
    "//FileSystem:HardDrive",
    "//FileSystem:FileSystem",
    "//Servers:PadronServer",
    "//Shells:PadronShell",
  ]
)

# Padron Server
cc_binary(
  name = "PadronServer",
  srcs = ["PadronServer.cpp"],
  deps = [
    "//FileSystem:HardDrive",
    "//FileSystem:FileSystem",
    "//Servers:PadronServer",
  ],
)

# Vote Client
cc_binary(
  name = "VoteClient",
  srcs = ["VoteClient.cpp"],
  deps = [
    "//Clients:VoteClient",
    "//FileSystem:FileSystem",
    "//FileSystem:HardDrive",
    "//Servers:VoteServer",
    "//Shells:VoteShell",
  ],
  linkopts = ["-pthread"],
)

# Vote Server
cc_binary(
  name = "VoteServer",
  srcs = ["VoteServer.cpp"],
  deps = [
    "//FileSystem:FileSystem",
    "//FileSystem:HardDrive",
    "//Servers:VoteServer",
  ],
)
