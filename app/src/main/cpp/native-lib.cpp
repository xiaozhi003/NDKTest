#include <jni.h>
#include <string.h>
#include <android/log.h>

#define TAG "JniTest"

#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG  , TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO   , TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN   , TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR  , TAG, __VA_ARGS__)

extern "C" {

JNIEXPORT jlong JNICALL
Java_com_xiaozhi_jni_JniTest_getStringFromJni__(JNIEnv *env, jobject instance) {

    char *p = "Hello from Jni!";

    return (jlong) p;
}

JNIEXPORT jstring JNICALL
Java_com_xiaozhi_jni_JniTest_getStringFromJni__J(JNIEnv *env, jobject instance, jlong in) {

    char *p = (char *) in;

    return env->NewStringUTF(p);
}

JNIEXPORT jstring JNICALL
Java_com_xiaozhi_jni_JniTest_getPackagenameFromJni(JNIEnv *env, jclass type, jobject context) {

    //Get Context Class descriptor
    jclass contextClass = env->FindClass("android/content/Context");
    //Get methodId from Context class
    jmethodID getPackageNameMethodId = env->GetMethodID(contextClass, "getPackageName",
                                                        "()Ljava/lang/String;");

    //Call the method using fileObject
    jstring stringObject = (jstring) env->CallObjectMethod(context, getPackageNameMethodId);
    // TODO

    const char *packageName = env->GetStringUTFChars(stringObject, 0);

    int isOk = strcmp(packageName, "com.xiaozhi.jni");

    LOGI("包名 isOK:%d", isOk);

    return stringObject;
}
}
