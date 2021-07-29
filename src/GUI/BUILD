load("@rules_cc//cc:defs.bzl", "cc_library")

#
# TARGETS
#

cc_library(
  name = "MaquinaVerificadora",
  srcs = ["MaquinaVerificadora.cpp"],
  hdrs = ["MaquinaVerificadora.hpp"],
  deps = [
    # Targets
    "//Clients:PadronClient",

    # GTK Inc
    "@Gtk-3.0-inc//:gtk-3.0",
    "@Gtk-3.0-inc//:pango-1.0",
    "@Gtk-3.0-inc//:glib-2.0",
    "@Gtk-3.0-inc//:harfbuzz",
    "@Gtk-3.0-inc//:freetype2",
    "@Gtk-3.0-inc//:libpng16",
    "@Gtk-3.0-inc//:libmount",
    "@Gtk-3.0-inc//:blkid",
    "@Gtk-3.0-inc//:fribidi",
    "@Gtk-3.0-inc//:cairo",
    "@Gtk-3.0-inc//:lzo",
    "@Gtk-3.0-inc//:pixman-1",
    "@Gtk-3.0-inc//:gdk-pixbuf-2.0",
    "@Gtk-3.0-inc//:gio-unix-2.0",
    "@Gtk-3.0-inc//:cloudproviders",
    "@Gtk-3.0-inc//:atk-1.0",
    "@Gtk-3.0-inc//:at-spi2-atk",
    "@Gtk-3.0-inc//:dbus-1.0",
    "@Gtk-3.0-inc//:at-spi-2.0",
    "@Gtk-3.0-inc//:glib-2.0-lib",
    "@Gtk-3.0-inc//:dbus-1.0-lib",
  ],
  visibility = [
    ":friends",
  ],
  copts = [
    "-I/usr/include/gtk-3.0",
    "-I/usr/include/pango-1.0",
    "-I/usr/include/glib-2.0",
    "-I/usr/include/glib-2.0-lib",
    "-I/usr/include/harfbuzz",
    "-I/usr/include/freetype2",
    "-I/usr/include/libpng16",
    "-I/usr/include/libmount",
    "-I/usr/include/blkid",
    "-I/usr/include/fribidi",
    "-I/usr/include/cairo",
    "-I/usr/include/lzo",
    "-I/usr/include/pixman-1",
    "-I/usr/include/gdk-pixbuf-2.0",
    "-I/usr/include/gio-unix-2.0",
    "-I/usr/include/cloudproviders",
    "-I/usr/include/atk-1.0",
    "-I/usr/include/at-spi2-atk/2.0",
    "-I/usr/include/dbus-1.0",
    "-I/usr/include/dbus-1.0-lib",
    "-I/usr/include/at-spi-2.0",
  ],
  linkopts = [
    "-pthread",
    "-lgtk-3",
    "-lgdk-3",
    "-lz",
    "-lpangocairo-1.0",
    "-lpango-1.0",
    "-lharfbuzz",
    "-latk-1.0",
    "-lcairo-gobject",
    "-lcairo",
    "-lgdk_pixbuf-2.0",
    "-lgio-2.0",
    "-lgobject-2.0",
    "-lglib-2.0",
  ]
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
