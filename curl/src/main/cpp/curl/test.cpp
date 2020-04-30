//
// Created by Administrator on 2020/4/29.
//

#include <jni.h>
#include <cstdio>
#include <memory.h>
#include <curl/curl.h>
#include <cmath>
#include <cstdlib>
#include "utils/log.hpp"

using adx::Logger;

jobject gTestObj;

JNIEnv *gEnv;

void *data;

void *header;

jmethodID gIdOnWriteCallback;

jmethodID gIdOnHeaderCallback;

jobject gDataObj;

jobject gHeaderObj;

static void callOnWriteCallback();

static void callOnHeaderCallback();

static size_t write_callback(void *ptr, size_t size, size_t nmemb, void *stream) {

    size_t len = size * nmemb;

    memccpy(stream, ptr, size, nmemb);

    Logger::d("---->callOnWriteCallback");

    callOnWriteCallback();

    return len;
}

static size_t header_callback(void *ptr, size_t size, size_t nmemb, void *stream) {

    size_t len = size * nmemb;

    memccpy(stream, ptr, size, nmemb);

    Logger::d("---->callOnHeaderCallback");

    callOnHeaderCallback();

    return len;
}


void test() {

    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://www.baidu.com");
        /* example.com is redirected, so we tell libcurl to follow redirection */
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, data);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, header);
        curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if (res != CURLE_OK)
            Logger::d("curl_easy_perform() failed: %s\n",
                      curl_easy_strerror(res));
        /* always cleanup */
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

}


JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {

    Logger::d("------------------------------------------------------------》");

    vm->GetEnv(reinterpret_cast<void **>(&gEnv), JNI_VERSION_1_6);

    return JNI_VERSION_1_6;
}


JNIEXPORT void JNI_OnUnload(JavaVM *vm, void *reserved) {

    Logger::d("《------------------------------------------------------------");
}


static void _callOnWriteCallback(JNIEnv *__env, jobject __obj, jobject __buff) {

    __env->CallVoidMethod(__obj, gIdOnWriteCallback, __buff);

}

static void _callOnHeaderCallback(JNIEnv *__env, jobject __obj, jobject __buff) {

    __env->CallVoidMethod(__obj, gIdOnHeaderCallback, __buff);

}

static void callOnWriteCallback() {

    _callOnWriteCallback(gEnv, gTestObj, gDataObj);
}

static void callOnHeaderCallback() {

    _callOnHeaderCallback(gEnv, gTestObj, gHeaderObj);
}


extern "C"
JNIEXPORT void JNICALL
Java_org_oz_curl_Test_native_1init(JNIEnv *env, jobject obj) {

    gTestObj = env->NewGlobalRef(obj);


    gDataObj = env->NewGlobalRef(
            env->GetObjectField(obj, env->GetFieldID(env->GetObjectClass(obj), "data",
                                                     "Ljava/nio/ByteBuffer;")));
    gHeaderObj = env->NewGlobalRef(
            env->GetObjectField(obj, env->GetFieldID(env->GetObjectClass(obj), "header",
                                                     "Ljava/nio/ByteBuffer;")));

    data = env->GetDirectBufferAddress(gDataObj);
    header = env->GetDirectBufferAddress(gHeaderObj);

    gIdOnWriteCallback = env->GetMethodID(env->GetObjectClass(gTestObj),
                                          "onWriteCallback",
                                          "(Ljava/nio/ByteBuffer;)V");
    gIdOnHeaderCallback = env->GetMethodID(env->GetObjectClass(gTestObj),
                                           "onHeaderCallback",
                                           "(Ljava/nio/ByteBuffer;)V");

}

extern "C"
JNIEXPORT void JNICALL
Java_org_oz_curl_Test_native_1test(JNIEnv *env, jobject obj) {

    test();
}

extern "C"
JNIEXPORT void JNICALL
Java_org_oz_curl_Test_native_1destroy(JNIEnv *env, jobject obj) {

    env->DeleteGlobalRef(gTestObj);
    env->DeleteGlobalRef(gDataObj);
    env->DeleteGlobalRef(gHeaderObj);
    gIdOnWriteCallback = NULL;
    gIdOnHeaderCallback = NULL;
    gTestObj = NULL;
    gDataObj = NULL;
    gHeaderObj = NULL;
    gEnv = NULL;

}