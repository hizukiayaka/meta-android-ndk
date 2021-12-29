PREFERRED_PROVIDER_virtual/egl = "android-gl"
PREFERRED_PROVIDER_virtual/libgles1 = "android-gl"
PREFERRED_PROVIDER_virtual/libgles2 = "android-gl"
PREFERRED_PROVIDER_virtual/libgles3 = "android-gl"

MACHINE_FEATURES_BACKFILL_CONSIDERED = "qemu-usermode"

export base_libdir = "${exec_prefix}/${baselib}"
export nonarch_base_libdir = "${exec_prefix}/${baselib}"
