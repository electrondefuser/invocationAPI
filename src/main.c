#include <jni.h>
#include <stdlib.h>
#include <assert.h>

#include "include/jnienv.h"

JavaCTX ctx;

/*
    Declare any JNI methods to used in the caller code here in the following way
    to avoid compiler errors

    extern return_value jni_function_name_here (JNIEnv*, jobject, any_other_parameters)
    The first two parameters will always be same.
*/
extern jstring Java_com_example_hellojni_HelloJni_stringFromJNI (JNIEnv*, jobject);

int initialize_caller(JavaCTX ctx) {

    /*
        This is the caller function. This is the main hooking/execution code that will
        be changed depending upon the reverse engineer's needs.
        
        This code is specific to the application given in the resources/base.apk which is a
        simple HelloWorld application found the ndk_sample repository in github.

        https://github.com/android/ndk-samples/tree/main/hello-jni
    */

    jclass mainClass = (*ctx.env)->FindClass(ctx.env, "com/example/hellojni/HelloJni");
    assert(mainClass != NULL && "mainClass class not found");

    jmethodID callJniMethod = (*ctx.env)->GetMethodID(ctx.env, mainClass, "callJni", "(Ljava/lang/String;)Ljava/lang/String;");
    assert(callJniMethod != NULL && "callJni method not found");

    jstring val = (*ctx.env)->CallObjectMethod(ctx.env, mainClass, callJniMethod, Java_com_example_hellojni_HelloJni_stringFromJNI(ctx.env, mainClass));
    const char *descr = (*ctx.env)->GetStringUTFChars(ctx.env, val, NULL);

    if (descr != NULL) {
        printf("%s",descr);
        printf("\n");
    }

    (*ctx.env)->ReleaseStringUTFChars(ctx.env, val, descr);
    return 0;
}

int main (int argc, char** argv) {

    /*
        Java Virtual Machine initialization options used for creating the
        VM via the JNI Loader. 
    */

    JavaVMOption options[5];
    
    /* application APK package path, change it depending on your needs */
    
    options[0].optionString = "-Djava.class.path=/data/local/tmp/app_base/base.apk"; 
    int status = initialize_java_environment(&ctx, options);

    if (status == 0) {
        initialize_caller(ctx);
        cleanup(&ctx);
    }

    return 0;
}