INHIBIT_SYSROOT_STRIP = "1"

PACKAGES = "${PN}-dbg ${PN} ${PN}-dev ${PN}-staticdev ${PN}-doc ${PN}-src"

libc_baselibs = "${libdir}/libc.so ${libdir}/libm.so ${libdir}/libdl.so"

FILES:${PN} = "${libc_baselibs}"
FILES:SOLIBSDEV = ""
FILES:${PN}-dev += "${libdir}/*.o"
RDEPENDS_${PN}-dev = "linux-libc-headers-dev"
FILES:${PN}-staticdev += "${libdir}/libc.a  ${libdir}/libcompiler_rt-extras.a  ${libdir}/libdl.a  ${libdir}/libm.a"
RPROVIDES_${PN}-dev += "libc-dev"
RPROVIDES_${PN}-staticdev += "libc-staticdev"
