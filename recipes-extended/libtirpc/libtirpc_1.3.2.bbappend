FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI:append = " \
    file://0001-rpc-types.h-fix-android-build.patch \
    file://0002-_rpc_dtablesize-use-portable-system-call.patch \
    file://0003-build-use-autoconf-archive-to-link-pthread.patch \
"

DEPENDS:append = " autoconf-archive-native"
DEPENDS:append:class-target = " virtual/libintl"
