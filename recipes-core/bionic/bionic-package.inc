INHIBIT_SYSROOT_STRIP = "1"

PACKAGES = "${PN}-dbg ${PN} ${PN}-dev ${PN}-staticdev ${PN}-doc ${PN}-src"

libc_baselibs = "${libdir}/libc.so ${libdir}/libm.so ${libdir}/libdl.so"

FILES_${PN} = "${libc_baselibs}"
FILES_SOLIBSDEV = ""
FILES_${PN}-dev += "${libdir}/*.o"
RDEPENDS_${PN}-dev = "linux-libc-headers-dev"
FILES_${PN}-staticdev += "${libdir}/libc.a  ${libdir}/libcompiler_rt-extras.a  ${libdir}/libdl.a  ${libdir}/libm.a"
RPROVIDES_${PN}-dev += "libc-dev"
RPROVIDES_${PN}-staticdev += "libc-staticdev"
