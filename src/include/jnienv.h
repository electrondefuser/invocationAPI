#include <jni.h>

typedef struct JniInvocation {
    const char* jni_provider_library_name;
    void* jni_provider_library;
    jint (*JNI_GetDefaultJavaVMInitArgs)(void*);
    jint (*JNI_CreateJavaVM)(JavaVM**, JNIEnv**, void*);
    jint (*JNI_GetCreatedJavaVMs)(JavaVM**, jsize, jsize*);
} JniInvocationImpl;

typedef struct JavaContext {
  JavaVM* vm;
  JNIEnv* env;
  JniInvocationImpl* invoc;
} JavaCTX;

int initialize_java_environment(JavaCTX *ctx, JavaVMOption* options);
int cleanup(JavaCTX*);

