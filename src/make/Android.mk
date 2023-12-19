# Enable native helper calls
LOCAL_SHARED_LIBRARIES += libnativehelper

# Include all of the Android's libsigchain symbols
LOCAL_WHOLE_STATIC_LIBRARIES += libsigchain

# Export only libsigchain symbols to global symbol table.
LOCAL_LDFLAGS += \
    -Wl,--export-dynamic \
    -Wl,--version-script,art/sigchainlib/version-script.txt