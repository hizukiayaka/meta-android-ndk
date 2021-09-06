SUMMARY="Android platform NDK modules"

SECTION = "libs"

inherit external-toolchain

FILES_MIRRORS =. "\
    ${libdir}/|/usr/lib/${EXTERNAL_MULTIMACH_TARGET_SYS}/${ANDROID_NDK_PLATFORM_LEVEL}/ \n\
"

android_ndk_modules = " \
    libaaudio.so libamidi.so libandroid.so libbinder_ndk.so \
    libcamera2ndk.so libjnigraphics.so liblog.so \
    libmediandk.so libneuralnetworks.so libsync.so \
"

ndk_headers_file = "${@bb.utils.which('${FILESPATH}', 'ndk.headers')}"

FILES:${PN}-dev = " \
    ${@' '.join('${libdir}/%s' % d for d in '${android_ndk_modules}'.split())} \
    ${@' '.join('${includedir}/' + f.rstrip() for f in oe.utils.read_file('${ndk_headers_file}').splitlines())} \
    ${includedir}/aaudio \
    ${includedir}/amidi \
    ${includedir}/camera \
    ${includedir}/jni.h \
"
