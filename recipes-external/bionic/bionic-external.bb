SRC_URI = ""
inherit external-toolchain


DEPENDS = "virtual/${TARGET_PREFIX}binutils"
PROVIDES += "bionic \
             virtual/libc \
             virtual/libiconv \
             linux-libc-headers \
             linux-libc-headers-dev"

def get_external_libc_license(d):
    if (d.getVar('TCMODE', True).startswith('external') and
            d.getVar('EXTERNAL_TOOLCHAIN', True)):
        errnosearch = os.path.join(d.getVar('includedir', True), 'errno.h')
        found = oe.external.find_sysroot_files([errnosearch], d)
        if found:
            errno_paths = found[0]
            if errno_paths:
                with open(errno_paths[0], 'rU') as f:
                    text = f.read()
                lictext = """Copyright (C) 2008 The Android Open Source Project"""
                if lictext in text:
                    return 'Apache-2.0'

    return 'UNKNOWN'
                
LICENSE_tcmode-external := "${@get_external_libc_license(d)}"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta/files/common-licenses/Apache-2.0;md5=89aea4e17d99a7cacdbeed46a0096b10"

python do_install () {
    bb.build.exec_func('external_toolchain_do_install', d)
    # sentinel
}

bberror_task-install () {
    # Silence any errors from oe_multilib_header, as we don't care about
    # missing multilib headers, as the oe-core glibc version isn't necessarily
    # the same as our own.
    :
}

require recipes-core/bionic/bionic-package.inc

FILES_MIRRORS =. "\
    ${libdir}/|/usr/lib/${EXTERNAL_MULTIMACH_TARGET_SYS}/${ANDROID_NDK_PLATFORM_LEVEL}/ \n\
"

FILES_${PN}-dbg = ""

linux_include_subdirs = "asm asm-generic bits drm linux mtd rdma sound sys video"
FILES_${PN}-dev += "${@' '.join('${includedir}/%s' % d for d in '${linux_include_subdirs}'.split())}"

libc_headers_file = "${@bb.utils.which('${FILESPATH}', 'libc.headers')}"
FILES_${PN}-dev += "\
    ${@' '.join('${includedir}/' + f.rstrip() for f in oe.utils.read_file('${libc_headers_file}').splitlines())} \
    ${includedir}/${EXTERNAL_MULTIMACH_TARGET_SYS} \
"
FILES_${PN}-dev[file-checksums] += "${libc_headers_file}:True"

# We don't need linux-libc-headers
LINUX_LIBC_RDEP_REMOVE ?= "linux-libc-headers-dev"
RDEPENDS_${PN}-dev_remove = "${LINUX_LIBC_RDEP_REMOVE}"
