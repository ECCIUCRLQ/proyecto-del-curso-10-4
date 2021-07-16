load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
  name = "Padron",
  srcs = ["Padron.cpp"],
  hdrs = ["Padron.hpp"],
  visibility = [
    ":friends",
  ],
)

cc_library(
  name = "PadronManager",
  srcs = ["PadronManager.cpp"],
  hdrs = ["PadronManager.hpp"],
  deps = [
    "//FileSystem:FileSystem",
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
    "//Servers",
  ],
)
