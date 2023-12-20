#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <jni.h>
#include <assert.h>

#include "include/jnienv.h"
#include "include/defs.h"
#include "include/macros.h"

#define LIB_NATIVE_HELPER "libnativehelper.so"
/* 
    Function typedef to the JNI_CreateJavaVM function present in the
    libart library.
*/
typedef jint (*JNI_CreateJavaVM_t)(JavaVM **p_vm, JNIEnv **p_env, void *vm_args);

int initialize_java_environment(JavaCTX *ctx, JavaVMOption* jopts)
{
    JNI_CreateJavaVM_t JNI_CreateJVM;

    void *lib_native_helper;
    /* 
        Function pointer to JniInvocationCreate present in libnative helper 
        JniInvocationImpl* JniInvocationCreate () {}
    */
    JniInvocationImpl *(*JniInvocationCreate)();
    /* 
        Function pointer to JniInvocationInit present in libnative helper 
        bool JniInvocationInit (JniInvocationImpl *, const char *) {}
    */
    bool (*JniInvocationInit)(JniInvocationImpl *, const char *);

    /*
        Load the libnativehelper.so via dlopen to call it's methods via dlsym function.
        JNI_CreateJavaVM, JniInvocationCreate, JniInvocationInit are
        loaded via dlsym.
    */

    lib_native_helper = dlopen(LIB_NATIVE_HELPER, RTLD_NOW);
    assert(lib_native_helper != NULL);

    JNI_CreateJVM = (JNI_CreateJavaVM_t) dlsym(lib_native_helper, "JNI_CreateJavaVM");
    assert(JNI_CreateJVM != NULL);

    JniInvocationCreate = dlsym(lib_native_helper, "JniInvocationCreate");
    assert(JniInvocationCreate != NULL);
    
    JniInvocationInit = dlsym(lib_native_helper, "JniInvocationInit");
    assert(JniInvocationInit != NULL);

    /*
        Create the invocation struct JniInvocationImpl via the method and store it
        to the ctx->invoc struct variable.
    */
    ctx->invoc = JniInvocationCreate();

    /*
        Call the JniInvocationInit with ctx->invoc (JniInvocationImpl struct) and 
        use the libart.so library to load it.
    */

    bool invocation_response = JniInvocationInit(ctx->invoc, "libart.so");
    assert(JniInvocationInit != NULL);
    
    JavaVMInitArgs args;
    args.version  = GLOBAL_JNI_VERSION;
    args.nOptions = 1;
    args.options  = jopts;
    args.ignoreUnrecognized = JNI_FALSE;

    /*
        Create the Java Virtual Machine using the acquired data like ctx->vm,
        ctx->env and the VMInitArgs declared above.
    */

    jint status = JNI_CreateJVM(&ctx->vm, &ctx->env, &args);

    if (status == JNI_ERR) {
        printf("[!] Can't create java vm/env \n");
        return JNI_ERR;
    }

    printf("%s", "[*] VM Initialized");

    printf("%s%p", "\n[*] JVM addr: ", ctx->vm);
    printf("%s%p", "\n[*] ENV addr: ", ctx->env);

    printf("%s", "\n---------------------------\n");

    return JNI_OK;
}


int cleanup(JavaCTX *ctx)
{
    void (*JniInvocationDestroy)(JniInvocationImpl *);
    void *lib_native_helper;

    printf("%s", "---------------------------\n");
    printf("[*] Initiating Cleanup...\n");

    if (ctx == NULL || ctx->vm == NULL)
        return JNI_ERR;

    lib_native_helper = dlopen(LIB_NATIVE_HELPER, RTLD_NOW);
    JniInvocationDestroy = dlsym(lib_native_helper, "JniInvocationDestroy");

    (*ctx->vm)->DetachCurrentThread(ctx->vm);
    (*ctx->vm)->DestroyJavaVM(ctx->vm);

    JniInvocationDestroy(ctx->invoc);
    return JNI_OK;
}

/* Signal chain library (libsigchain.so) exports */
/* Art or Dalvik will load libsigchain.so, which is a stub and abort()s every time any of its methods are being called. */

JNIEXPORT void RemoveSpecialSignalHandlerFn() {}
JNIEXPORT void AddSpecialSignalHandlerFn() {}
JNIEXPORT void InvokeUserSignalHandler() {}
JNIEXPORT void InitializeSignalChain() {}

JNIEXPORT void UnclaimSignalChain() {}
JNIEXPORT void EnsureFrontOfChain() {}
JNIEXPORT void ClaimSignalChain() {}
