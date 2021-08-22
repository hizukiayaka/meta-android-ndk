# Released under the MIT license (see COPYING.MIT for the terms)

DESCRIPTION = "libc++ is a new implementation of the C++ standard library, targeting C++11"
HOMEPAGE = "http://libcxx.llvm.org/"
SECTION = "base"

inherit external-toolchain

PROVIDES += "libcxx"

DEPENDS_append_class-target = " virtual/${MLPREFIX}libc"

FILES_MIRRORS =. "\
    ${libdir}/|/usr/lib/${EXTERNAL_MULTIMACH_TARGET_SYS}/ \n\
    ${libdir}/|/usr/lib/${EXTERNAL_MULTIMACH_TARGET_SYS}/${ANDROID_NDK_PLATFORM_LEVEL}/ \n\
"

FILES_${PN} = "${libdir}/libc++*.so"
FILES_${PN}-staticdev = "${libdir}/libc++*.a ${libdir}/libstdc++.a ${libdir}/libunwind.a"
FILES_${PN}-dev = "${libdir}/libc++.so ${includedir}/c++"

libc_rdep = "${@'${PREFERRED_PROVIDER_virtual/libc}' if '${PREFERRED_PROVIDER_virtual/libc}' else '${TCLIBC}'}"
RDEPENDS_${PN} += "${libc_rdep}"

INHIBIT_DEFAULT_DEPS = "1"

ALLOW_EMPTY_${PN} = "1"
