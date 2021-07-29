load("@rules_cc//cc:defs.bzl", "cc_library")

#
# TARGETS
#

# Base64
cc_library(
  name = "Base64",
  srcs = ["Base64.cpp"],
  hdrs = ["Base64.hpp"],
)

# Cipher
cc_library(
  name = "Cipher",
  srcs = ["Cipher.cpp"],
  hdrs = ["Cipher.hpp"],
  deps = ["//Security:Base64"],
  visibility = [
    ":friends",
  ],
  linkopts = ["-lgcrypt -lgpg-error"],
)

# Hash
cc_library(
  name = "Hash",
  srcs = ["Hash.cpp"],
  hdrs = ["Hash.hpp"],
  visibility = [
    ":friends",
  ],
  linkopts = ["-lgcrypt -lgpg-error"],
)


#
# FRIEND PACKAGES
#

package_group(
  name = "friends",
  packages = [
    "//Clients",
    "//Servers",
  ]
)
