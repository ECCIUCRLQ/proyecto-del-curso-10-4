load("@rules_cc//cc:defs.bzl", "cc_library")

#
# PACKAGES
#

cc_library(
  name = "PadronShell",
  srcs = ["PadronShell.cpp"],
  hdrs = ["PadronShell.hpp"],
  deps = ["//Clients:PadronClient"],
  visibility = [
    ":friends",
  ],
)

cc_library(
  name = "VoteShell",
  srcs = ["VoteShell.cpp"],
  hdrs = ["VoteShell.hpp"],
  deps = ["//Clients:VoteClient"],
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
