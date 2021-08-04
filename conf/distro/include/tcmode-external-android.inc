require conf/distro/include/tcmode-external.inc

TCMODEOVERRIDES .= ":tcmode-external-android"
TCLIBC = "bionic"

ANDROID_NDK_PLATFORM_LEVEL ?= "30"

ELT_TARGET_SYS_arm = "armv7a-linux-androideabi"
ELT_TARGET_SYS_aarch64 = "aarch64-linux-android"
ELT_TARGET_SYS_x86 = "i686-linux-android"
ELT_TARGET_SYS_x86-64 = "x86_64-linux-android"

EXTERNAL_TARGET_SYS ?= "${ELT_TARGET_SYS}${ANDROID_NDK_PLATFORM_LEVEL}"
EXTERNAL_SDK_SYS ?= "${SDK_SYS}"

EXTERNAL_MULTIMACH_TARGET_SYS_arm = "arm-linux-androideabi"
EXTERNAL_MULTIMACH_TARGET_SYS_aarch64 = "aarch64-linux-android"
EXTERNAL_MULTIMACH_TARGET_SYS_x86 = "i686-linux-android"
EXTERNAL_MULTIMACH_TARGET_SYS_x86-64 = "x86_64-linux-android"
EXTERNAL_TOOLCHAIN_SYSROOT = "${EXTERNAL_TOOLCHAIN}/llvm/prebuilt/linux-x86_64/sysroot"

EXTERNAL_CC = "clang \
               -resource-dir ${EXTERNAL_TOOLCHAIN_SYSROOT}/usr/lib/${EXTERNAL_MULTIMACH_TARGET_SYS}/${ANDROID_NDK_PLATFORM_LEVEL} \
              "

RANLIB_toolchain-clang_forcevariable = "llvm-ranlib"
AR_toolchain-clang_forcevariable = "llvm-ar"
NM_toolchain-clang_forcevariable = "llvm-nm"
LD_toolchain-clang = "ld.lld"

HOST_SYS_toolchain-clang = "${EXTERNAL_TARGET_SYS}"

CC_toolchain-clang_forcevariable = "${CCACHE}clang ${HOST_CC_ARCH}${TOOLCHAIN_OPTIONS}"
CXX_toolchain-clang_forcevariable = "${CCACHE}clang++ ${HOST_CC_ARCH}${TOOLCHAIN_OPTIONS}"
CPP_toolchain-clang_forcevariable = "${CCACHE}clang ${HOST_CC_ARCH}${TOOLCHAIN_OPTIONS} -E"
CCLD_toolchain-clang_forcevariable = "${CCACHE}clang ${HOST_CC_ARCH}${TOOLCHAIN_OPTIONS}"

TARGET_PREFIX = "${EXTERNAL_MULTIMACH_TARGET_SYS}-"
TARGET_OS = "linux-androideabi"

HOST_PREFIX = "${EXTERNAL_MULTIMACH_TARGET_SYS}-"
HOST_CC_ARCH_remove = "--no-sysroot-suffix"

PREFERRED_PROVIDER_virtual/libc = "bionic-external"
PREFERRED_PROVIDER_virtual/libiconv = "bionic-external"
PREFERRED_PROVIDER_virtual/libintl = "gettext"
PREFERRED_PROVIDER_zlib = "zlib-external"

# This is defined in default-providers.inc, which is parsed before the tcmode,
# so we can't use ?=
PREFERRED_PROVIDER_linux-libc-headers = "linux-libc-headers-external"
PNBLACKLIST[linux-libc-headers] = "not building with an external toolchain"
PNBLACKLIST[linux-libc-headers-yocto] = "not building with an external toolchain"

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
LLVM_VERSION = "${@external_run(d, d.getVar('EXTERNAL_CC'), '-dumpversion').rstrip()}"

BUILDCFG_VARS += "${@'ANDROID_NDK_TOOLCHAIN_VERSION' if d.getVar('ANDROID_NDK_VERSION') != 'UNKNOWN' else ''}"

INHERIT_remove = "sanity-external-toolchain"
INHERIT += "sanity-external-toolchain-clang"
