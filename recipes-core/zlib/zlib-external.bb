SUMMARY = "Zlib Compression Library"
DESCRIPTION = "Zlib is a general-purpose, patent-free, lossless data compression \
library which is used by many different programs."
HOMEPAGE = "http://zlib.net/"
SECTION = "libs"
LICENSE = "Zlib"

inherit external-toolchain

PROVIDES += "zlib"

FILES_MIRRORS =. "\
    ${libdir}/|/usr/lib/${EXTERNAL_MULTIMACH_TARGET_SYS}/${ANDROID_NDK_PLATFORM_LEVEL}/ \n\
"

EXTERNAL_PROVIDE_PATTERN = "${libdir}/libz.*"

libc_rdep = "${@'${PREFERRED_PROVIDER_virtual/libc}' if '${PREFERRED_PROVIDER_virtual/libc}' else '${TCLIBC}'}"
RDEPENDS_${PN} += "${libc_rdep}"

FILES:${PN} = "${libdir}/libz.so"
FILES:${PN}-staticdev = "${libdir}/libz.a"
FILES:${PN}-dev = "\
    ${includedir}/zconf.h \
    ${includedir}/zlib.h \
"
