# Released under the MIT license (see COPYING.MIT for the terms)

DESCRIPTION = "LLVM based C/C++ compiler Runtime"
HOMEPAGE = "http://compiler-rt.llvm.org/"
SECTION = "base"

inherit external-toolchain

PROVIDES += "compiler-rt"
PV = "${LLVMVERSION}"

MAJOR_VER = "${@str.split('${LLVMVERSION}', '.')[0]}"
MINOR_VER = "${@str.split('${LLVMVERSION}', '.')[1]}"
PATCH_VER = "${@str.split('${LLVMVERSION}', '.')[2]}"

DEPENDS:append:class-target = " virtual/${MLPREFIX}libc"

FILES_MIRRORS =. "\
    ${nonarch_libdir}/|/lib64/ \n\
"

FILES_SOLIBSDEV = ""
FILES:${PN} += "${nonarch_libdir}/clang/${MAJOR_VER}.${MINOR_VER}.${PATCH_VER}/lib/linux/lib*${SOLIBSDEV} \
                ${nonarch_libdir}/clang/${MAJOR_VER}.${MINOR_VER}.${PATCH_VER}/*.txt \
                ${nonarch_libdir}/clang/${MAJOR_VER}.${MINOR_VER}.${PATCH_VER}/share/*.txt"
FILES:${PN}-staticdev += "${nonarch_libdir}/clang/${MAJOR_VER}.${MINOR_VER}.${PATCH_VER}/lib/linux/libclang_rt.*-${TARGET_ARCH}-android.a"
FILES:${PN}-dev += "${nonarch_libdir}/clang/${MAJOR_VER}.${MINOR_VER}.${PATCH_VER}/lib/linux/*.syms \
                    ${nonarch_libdir}/clang/${MAJOR_VER}.${MINOR_VER}.${PATCH_VER}/include \
                    ${nonarch_libdir}/clang/${MAJOR_VER}.${MINOR_VER}.${PATCH_VER}/lib/linux/clang_rt.crt*.o \
                    ${nonarch_libdir}/clang/${MAJOR_VER}.${MINOR_VER}.${PATCH_VER}/lib/linux/libclang_rt.asan-preinit*-${TARGET_ARCH}-android.a \
                   "
INSANE_SKIP:${PN} = "dev-so libdir"
INSANE_SKIP:${PN}-dev = "staticdev"
INSANE_SKIP:${PN}-dbg = "libdir"

RDEPENDS:${PN}-dev += "${PN}-staticdev"

libc_rdep = "${@'${PREFERRED_PROVIDER_virtual/libc}' if '${PREFERRED_PROVIDER_virtual/libc}' else '${TCLIBC}'}"
RDEPENDS_${PN} += "${libc_rdep}"

INHIBIT_DEFAULT_DEPS = "1"

ALLOW_EMPTY_${PN} = "1"

SYSROOT_DIRS:append:class-target = " ${nonarch_libdir}"
