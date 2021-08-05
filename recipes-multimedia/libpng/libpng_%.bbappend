do_configure_prepend_runtime-android() {
    sed -i -e "/install-exec-hook: install-library-links/d" ${S}/Makefile.am
}
