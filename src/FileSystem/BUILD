load("@rules_cc//cc:defs.bzl", "cc_library")

# Bitmap
cc_library(
  name = "Bitmap",
  srcs = ["Bitmap.cpp"],
  hdrs = ["Bitmap.hpp"],
)

# Directory
cc_library(
  name = "Directory",
  srcs = ["Directory.cpp"],
  hdrs = ["Directory.hpp"],
  deps = [
    "//FileSystem:File",
    "//Utils:Parser"
  ],
)

# File
cc_library(
  name = "File",
  srcs = ["File.cpp"],
  hdrs = ["File.hpp"],
)

# File System
cc_library(
  name = "FileSystem",
  srcs = ["FileSystem.cpp"],
  hdrs = ["FileSystem.hpp"],
  deps = [
    ":Bitmap",
    ":Directory",
    ":File",
    ":HardDrive",
    "//Utils:Parser"
  ],
  visibility = [
    ":friends",
  ],
)

# Hard Drive
cc_library(
  name = "HardDrive",
  srcs = ["HardDrive.cpp"],
  hdrs = ["HardDrive.hpp"],
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
    "//Clients",
    "//Servers",
    "//Shells",
    "//Executables",
  ],
)
