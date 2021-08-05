DESCRIPTION = "Proxy libintl"
HOMEPAGE = "https://github.com/frida/proxy-libintl"
SECTION = "libs"
LICENSE = "LGPL"

PR = "r8"
PROVIDES = "virtual/libintl"

BBCLASSEXTEND = "native"
NATIVE_INSTALL_WORKS = "1"

SRC_URI = "git://github.com/frida/proxy-libintl.git"
SRCREV = "ef9fe6dc15bb0a4962606658ce23d81f3352e58d"

LIC_FILES_CHKSUM = "file://COPYING;md5=3bf50002aefd002f49e7bb854063f7e7"
LICENSE = "LGPLv2.1"

S = "${WORKDIR}/git"

inherit meson
