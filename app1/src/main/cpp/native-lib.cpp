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
JNIEXPORT jlong JNICALL getStringFromJni__(JNIEnv *env, jobject instance) {

    char *p = "Hello from Jni!";

    return (jlong) p;
}

JNIEXPORT jstring JNICALL getStringFromJni__J(JNIEnv *env, jobject instance, jlong in) {

    char *p = (char *) in;

    return env->NewStringUTF(p);
}

JNIEXPORT jstring JNICALL getPackagenameFromJni(JNIEnv *env, jclass type, jobject context) {

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

/**
 * 声明映射本地方法和java层方法的映射关系
 */
static JNINativeMethod methods[]{
        {"getStringFromJni",      "()J",                                           (void *) getStringFromJni__},
        {"getStringFromJni",      "(J)Ljava/lang/String;",                         (void *) getStringFromJni__J},
        {"getPackagenameFromJni", "(Landroid/content/Context;)Ljava/lang/String;", (void *) getPackagenameFromJni}
};

/**
 * 注册本地方法
 *
 * @param env
 * @param class_name
 * @param methods
 * @param num_methods
 * @return
 */
jint registerNativeMethods(JNIEnv *env, const char *class_name, JNINativeMethod *methods,
                           int num_methods) {
    jclass clazz = env->FindClass(class_name);
    int result = env->RegisterNatives(clazz, methods, num_methods);
    return result;
}

/**
 * 与对应java类关联
 *
 * @param env
 * @return
 */
int registerNative(JNIEnv *env) {
    const char *className = "com/xiaozhi/jni1/JniTest";
    return registerNativeMethods(env, className, methods,
                                 ((int) sizeof(methods) / sizeof(methods[0])));
}

//当动态库被加载时这个函数被系统调用
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }
    // register native methods
    if (registerNative(env)) {
        return JNI_ERR;
    }
    // return jni version
    return JNI_VERSION_1_6;
}

//当动态库被卸载时这个函数被系统调用
JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *vm, void *reserved) {
}
}
