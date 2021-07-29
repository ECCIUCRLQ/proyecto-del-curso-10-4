load("@rules_cc//cc:defs.bzl", "cc_library")

#
# TARGETS
#

# Base Client
cc_library(
  name = "Client",
  srcs = ["Client.cpp"],
  hdrs = ["Client.hpp"],
  deps = ["//Network:Socket"],
)

# File System Client
cc_library(
  name = "FSClient",
  srcs = ["FSClient.cpp"],
  hdrs = ["FSClient.hpp"],
  deps = [
    ":Client",
    "//FileSystem:FileSystem",
    "//Network:TcpClient",
  ],
)

# Padron Client
cc_library(
  name = "PadronClient",
  srcs = ["PadronClient.cpp"],
  hdrs = ["PadronClient.hpp"],
  deps = [
    ":Client",
    "//Network:TcpClient",
  ],
  visibility = [":friends"],
)

# Vote Client
cc_library(
  name = "VoteClient",
  srcs = ["VoteClient.cpp"],
  hdrs = ["VoteClient.hpp"],
  deps = [
    ":FSClient",
    "//FileSystem:FileSystem",
    "//Network:Socket",
    "//Network:TcpClient",
  ],
  visibility = [":friends",],
)


#
# FRIEND PACKAGES
#

package_group(
  name = "friends",
  packages = [
    "//Shells",
    "//Servers",
    "//Executables",
    "//GUI",
  ]
)
