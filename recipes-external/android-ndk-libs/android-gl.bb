SUMMARY="Android platform NDK Graphics OpenGL ES/EGL/Vulkan libraries"

SECTION = "libs"

PROVIDES = "virtual/libgles1 virtual/libgles2 virtual/libgles3 virtual/egl"
PACKAGES += "libegl-android libegl-android-dev \
             libgles1-android libgles1-android-dev \
             libgles2-android libgles2-android-dev \
             libgles3-android libgles3-android-dev \
             android-vulkan android-vulkan-dev \
            "
            

inherit external-toolchain

FILES_MIRRORS =. "\
    ${libdir}/|/usr/lib/${EXTERNAL_MULTIMACH_TARGET_SYS}/${ANDROID_NDK_PLATFORM_LEVEL}/ \n\
"

FILES_libegl-android = "${libdir}/libEGL.so"
FILES_libgles1-android = "${libdir}/libGLESv1_CM.so"
FILES_libgles2-android = "${libdir}/libGLESv2.so"
FILES_libgles3-android = "${libdir}/libGLESv3.so"
FILES_android-vulkan = "${libdir}/libvulkan.so"

FILES_libegl-android-dev = "${includedir}/EGL"
FILES_libgles1-android-dev = "${includedir}/GLES"
FILES_libgles2-android-dev = "${includedir}/GLES2"
FILES_libgles3-android-dev = "${includedir}/GLES3"
FILES_android-vulkan-dev = "${includedir}/vulkan"
