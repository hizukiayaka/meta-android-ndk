require conf/distro/include/tcmode-external.inc

TCMODEOVERRIDES .= ":tcmode-external-android"
TCLIBC = "bionic"

ANDROID_NDK_PLATFORM_LEVEL ?= "30"

ELT_TARGET_SYS:arm = "armv7a-linux-androideabi"
ELT_TARGET_SYS:aarch64 = "aarch64-linux-android"
ELT_TARGET_SYS:x86 = "i686-linux-android"
ELT_TARGET_SYS:x86-64 = "x86_64-linux-android"

EXTERNAL_TARGET_SYS ?= "${ELT_TARGET_SYS}${ANDROID_NDK_PLATFORM_LEVEL}"
EXTERNAL_SDK_SYS ?= "${SDK_SYS}"

EXTERNAL_MULTIMACH_TARGET_SYS:arm = "arm-linux-androideabi"
EXTERNAL_MULTIMACH_TARGET_SYS:aarch64 = "aarch64-linux-android"
EXTERNAL_MULTIMACH_TARGET_SYS:x86 = "i686-linux-android"
EXTERNAL_MULTIMACH_TARGET_SYS:x86-64 = "x86_64-linux-android"
EXTERNAL_TOOLCHAIN_SYSROOT = "${EXTERNAL_TOOLCHAIN}/llvm/prebuilt/linux-x86_64/sysroot"

EXTERNAL_CC = "clang \
               -resource-dir ${EXTERNAL_TOOLCHAIN_SYSROOT}/usr/lib/${EXTERNAL_MULTIMACH_TARGET_SYS}/${ANDROID_NDK_PLATFORM_LEVEL} \
              "

RANLIB:toolchain-clang:forcevariable = "llvm-ranlib"
AR:toolchain-clang:forcevariable = "llvm-ar"
NM:toolchain-clang:forcevariable = "llvm-nm"
LD:toolchain-clang = "ld.lld"

HOST_SYS:toolchain-clang = "${EXTERNAL_TARGET_SYS}"

CC:toolchain-clang:forcevariable = "${CCACHE}clang ${HOST_CC_ARCH}${TOOLCHAIN_OPTIONS}"
CXX:toolchain-clang:forcevariable = "${CCACHE}clang++ ${HOST_CC_ARCH}${TOOLCHAIN_OPTIONS}"
CPP:toolchain-clang:forcevariable = "${CCACHE}clang ${HOST_CC_ARCH}${TOOLCHAIN_OPTIONS} -E"
CCLD:toolchain-clang:forcevariable = "${CCACHE}clang ${HOST_CC_ARCH}${TOOLCHAIN_OPTIONS}"

TARGET_SYS:toolchain-clang = "${EXTERNAL_TARGET_SYS}"
TARGET_PREFIX = "${EXTERNAL_MULTIMACH_TARGET_SYS}-"

HOST_PREFIX = "${EXTERNAL_MULTIMACH_TARGET_SYS}-"
HOST_CC_ARCH:remove = "--no-sysroot-suffix"

SOLIBS:runtime-android = ".so"
SOLIBSDEV:runtime-android = ".so.broken"

PREFERRED_PROVIDER_virtual/libc = "bionic-external"
PREFERRED_PROVIDER_virtual/${TARGET_PREFIX}compilerlibs = "libcxx-external"
# NOTE: Android only provides libiconv with API level >=28 (Pie and newer)
PREFERRED_PROVIDER_virtual/libiconv = "bionic-external"
PREFERRED_PROVIDER_virtual/libintl = "proxy-libintl"
PREFERRED_PROVIDER_libcxx = "libcxx-external"
PREFERRED_PROVIDER_zlib = "zlib-external"
PREFERRED_PROVIDER_compiler-rt = "compiler-rt-external"

# This is defined in default-providers.inc, which is parsed before the tcmode,
# so we can't use ?=
PREFERRED_PROVIDER_linux-libc-headers = "linux-libc-headers-external"
PNBLACKLIST[linux-libc-headers] = "not building with an external toolchain"
PNBLACKLIST[linux-libc-headers-yocto] = "not building with an external toolchain"

BASE_DEFAULT_DEPS:remove = "${MLPREFIX}clang-cross-${TARGET_ARCH}"
BASE_DEFAULT_DEPS:toolchain-clang:remove = "${MLPREFIX}clang-cross-${TARGET_ARCH}"
BASE_DEFAULT_DEPS:toolchain-clang:class-target:remove = "${MLPREFIX}clang-cross-${TARGET_ARCH}"

PNBLACKLIST_DYNAMIC:append = "\
    ${MLPREFIX}clang-cross-${TARGET_ARCH} \
    clang-cross-canadian-${TRANSLATED_TARGET_ARCH} \
    clang-crosssdk-${TRANSLATED_TARGET_ARCH} \
"

# Disable pseudo for these cross binaries
EXTERNAL_CROSS_NOPSEUDO = "gcc g++ cpp"

# Use tuning-defined baselib to align with multilib and external toolchain
baselib = "${@d.getVar('BASE_LIB_tune-' + (d.getVar('DEFAULTTUNE') or 'INVALID')) or d.getVar('BASELIB')}"

def android_ndk_version(d):
    import os

    path = d.getVar('EXTERNAL_TOOLCHAIN')
    while True:
        parts = os.path.split(path)
        if len(parts[1]):
            version_output = parts[1].split('.')
            if version_output[0].isnumeric():
                return parts[1]
                break
        
        if parts[0] == path and not len(parts[1]):
            break
        elif parts[1] == path:
            break
        else:
            path = parts[0]

    return 'UNKNOWN'

ANDROID_NDK_VERSION = "${@android_ndk_version(d)}"
ANDROID_NDK_VERSION_allarch = ""
ANDROID_NDK_VERSION[vardepvalue] = "${ANDROID_NDK_VERSION}"

# Add android ndk toolchain version to external recipe versions
EXTERNAL_PV_SUFFIX ?= "${@'-${ANDROID_NDK_VERSION}' if d.getVar('ANDROID_NDK_VERSION') != 'UNKNOWN' else ''}"
EXTERNAL_PV_SUFFIX[vardepvalue] = "${EXTERNAL_PV_SUFFIX}"
EXTERNAL_PV_SUFFIX_allarch = ""

# Make it clear that this version is the toolchain
ANDROID_NDK_TOOLCHAIN_VERSION = "${ANDROID_NDK_VERSION}"
LLVMVERSION = "${@external_run(d, d.getVar('EXTERNAL_CC'), '-dumpversion').rstrip()}"

BUILDCFG_VARS += "${@'ANDROID_NDK_TOOLCHAIN_VERSION' if d.getVar('ANDROID_NDK_VERSION') != 'UNKNOWN' else ''}"

INHERIT:remove = "sanity-external-toolchain"
INHERIT:append = " sanity-external-toolchain-clang"

BUILDCFG_VARS:remove = "GCC_VERSION"
BUILDCFG_VARS:append = "LLVMVERSION"
