#include <jni.h>
#include <string>
#include <fcntl.h>
#include <pthread.h>
#include "xhook/xhook.h"
#include "xh_log.h"


void *(*old_pthread_create)(pthread_t *__pthread_ptr, pthread_attr_t const *__attr,
                            void *(*__start_routine)(void *), void *);

void *my_pthread_create(pthread_t *__pthread_ptr, pthread_attr_t const *__attr,
                        void *(*__start_routine)(void *), void *name) {
    __android_log_print(ANDROID_LOG_ERROR, "rzm", "my_pthread_create");
    void *re = old_pthread_create(__pthread_ptr, __attr, __start_routine, name);
    __android_log_print(ANDROID_LOG_ERROR, "rzm", "my_pthread_create2");
    return re;
}

void *(*old_pthread_setname_np)(pthread_t __pthread, const char *__name);

void *my_pthread_setname_np(pthread_t __pthread, const char *__name) {
    __android_log_print(ANDROID_LOG_ERROR, "rzm", "my_pthread_setname_np");
    void *re = old_pthread_setname_np(__pthread, __name);
    __android_log_print(ANDROID_LOG_ERROR, "rzm", "my_pthread_setname_np2");
    return re;
}

void *(*old_pthread_detach)(pthread_t __pthread);


void *my_pthread_detach(pthread_t __pthread) {
    __android_log_print(ANDROID_LOG_ERROR, "rzm", "my_pthread_detach");
    void *re = old_pthread_detach(__pthread);
    __android_log_print(ANDROID_LOG_ERROR, "rzm", "my_pthread_detach2");
    return re;
}

void *(*old_pthread_join)(pthread_t __pthread, void **__return_value_ptr);

void *my_pthread_join(pthread_t __pthread, void **__return_value_ptr) {
    __android_log_print(ANDROID_LOG_ERROR, "rzm", "my_pthread_join");
    void *re = old_pthread_join(__pthread, __return_value_ptr);
    __android_log_print(ANDROID_LOG_ERROR, "rzm", "my_pthread_join2");
    return re;
}


int ProxyOpen(const char *path, int flags, mode_t mode) {
    __android_log_print(ANDROID_LOG_ERROR, "rzm", "监听到文件打开：%s", path);

    int fd = open(path, flags, mode);

    return fd;
}

void *(*old_malloc)(size_t __byte_count);

void *my_malloc(size_t __byte_count) {
    __android_log_print(ANDROID_LOG_ERROR, "rzm", "this is test hook my_malloc : %x", __byte_count);
    void *addr = old_malloc(__byte_count);
    __android_log_print(ANDROID_LOG_ERROR, "rzm", "real hook my_malloc : %x", addr);
    return addr;
}

void *(*old_free)(void *__ptr);

void *my_free(void *__ptr) {
    if (__ptr != NULL) {
        __android_log_print(ANDROID_LOG_ERROR, "rzm", "this is test hook my_free ");
        void *addr = old_free(__ptr);
        __android_log_print(ANDROID_LOG_ERROR, "rzm", "real hook my_free : %x", addr);
        return addr;
    }
    return NULL;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_myxhook_Hook_hook(JNIEnv *env, jobject thiz) {
    xhook_register("libopenjdkjvm.so", "open", (void *) ProxyOpen, NULL);
    xhook_register("libjavacore.so", "open", (void *) ProxyOpen, NULL);
    xhook_register("libopenjdk.so", "open", (void *) ProxyOpen, NULL);

    xhook_register("libopenjdkjvm.so", "open64", (void *) ProxyOpen, NULL);
    xhook_register("libjavacore.so", "open64", (void *) ProxyOpen, NULL);
    xhook_register("libopenjdk.so", "open64", (void *) ProxyOpen, NULL);


    xhook_register(".*\\.so$", "malloc", (void *) my_malloc, (void **) &old_malloc);
    xhook_register(".*\\.so$", "free", (void *) my_free, (void **) &old_free);

    xhook_register(".*\\.so$", "pthread_create", (void *) my_pthread_create,
                   (void **) &old_pthread_create);
    xhook_register(".*\\.so$", "pthread_setname_np", (void *) my_pthread_setname_np,
                   (void **) &old_pthread_setname_np);
    xhook_register(".*\\.so$", "pthread_detach", (void *) my_pthread_detach,
                   (void **) &old_pthread_detach);
    xhook_register(".*\\.so$", "pthread_join", (void *) my_pthread_join,
                   (void **) &old_pthread_join);
    // 执行真正的 hook 操作
    xhook_refresh(1);
}

