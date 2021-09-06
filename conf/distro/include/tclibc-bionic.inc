#
# Android bionic configuration
#

# It looks like nobody call it bionic environment
LIBCEXTENSION = "-android"
LIBCOVERRIDE = ":libc-bionic"

PREFERRED_PROVIDER_virtual/libc ??= "bionic"
PREFERRED_PROVIDER_virtual/libiconv ??= "bionic"
PREFERRED_PROVIDER_virtual/libintl ?= "gettext"
PREFERRED_PROVIDER_virtual/nativesdk-libintl ?= "nativesdk-glibc"
PREFERRED_PROVIDER_virtual/nativesdk-libiconv ?= "nativesdk-glibc"

DISTRO_FEATURES_BACKFILL_CONSIDERED += "ldconfig"

USE_NLS ?= "no"
IMAGE_LINGUAS = ""

LIBC_DEPENDENCIES = ""

ASSUME_PROVIDED += "virtual/crypt"

TOOLCHAIN_HOST_TASK ?= "packagegroup-cross-canadian-${MACHINE} nativesdk-qemu"
TOOLCHAIN_TARGET_TASK ?= "${LIBC_DEPENDENCIES}"
TOOLCHAIN_NEED_CONFIGSITE_CACHE:remove = "zlib ncurses"

# Android requests pie security flags
GCCPIE = ""
SECURITY_CFLAGS_libc-bionic = "${SECURITY_PIE_CFLAGS}"
SECURITY_LDFLAGS_libc-bionic = "-Wl,-z,relro,-z,now"
