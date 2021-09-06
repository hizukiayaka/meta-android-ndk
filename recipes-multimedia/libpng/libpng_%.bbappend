do_configure:prepend:runtime-android() {
    sed -i -e "/install-exec-hook: install-library-links/d" ${S}/Makefile.am
}
