load("@rules_cc//cc:defs.bzl", "cc_library")

# Network Address
cc_library(
  name = "NetworkAddress",
  srcs = ["NetworkAddress.cpp"],
  hdrs = ["common.hpp", "NetworkAddress.hpp"],
)

# Socket
cc_library(
  name = "Socket",
  srcs = ["Socket.cpp"],
  hdrs = ["common.hpp", "Socket.hpp"],
  deps = [":NetworkAddress"],
  visibility = [
    ":friends",
  ],
)

# TCP Client
cc_library(
  name = "TcpClient",
  srcs = ["TcpClient.cpp"],
  hdrs = ["common.hpp", "TcpClient.hpp"],
  deps = [
    ":NetworkAddress",
    ":Socket",
  ],
  visibility = [
    ":friends"
  ],
)

# TCP Server
cc_library(
  name = "TcpServer",
  srcs = ["TcpServer.cpp"],
  hdrs = ["common.hpp", "TcpServer.hpp"],
  deps = [
    ":NetworkAddress",
    ":Socket"
  ],
  visibility = [
    ":friends"
  ]
)

#
# FRIEND PACKAGES
#

package_group(
  name = "friends",
  packages = [
    "//Clients",
    "//Servers",
  ],
)
