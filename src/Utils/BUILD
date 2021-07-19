load("@rules_cc//cc:defs.bzl", "cc_library")

#
# TARGETS
#

cc_library(
  name = "Parser",
  srcs = ["Parser.cpp"],
  hdrs = ["Parser.hpp"],
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
    "//FileSystem",
    "//Servers",
    "//Shells",
    "//Votacion",
  ],
)