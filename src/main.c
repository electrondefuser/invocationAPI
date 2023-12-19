#include <jni.h>
#include <stdlib.h>
#include <assert.h>

#include "include/jnienv.h"

JavaCTX ctx;
extern jstring Java_com_example_hellojni_HelloJni_stringFromJNI (JNIEnv*, jobject);

int initialize_caller(JavaCTX ctx) {

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

    return 0;
}

int main (int argc, char** argv) {

    JavaVMOption options[5];
    
    options[0].optionString = "-Djava.class.path=/data/local/tmp/JNIhelper/base.apk";
    int status = initialize_java_environment(&ctx, options);

    if (status == 0) {
        initialize_caller(ctx);
        cleanup(&ctx);
    }

    return 0;
}