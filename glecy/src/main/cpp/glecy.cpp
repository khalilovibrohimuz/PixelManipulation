#include <jni.h>
#include <android/bitmap.h>


// create global variables
static jobject bitmap;
static void *pixels;
static AndroidBitmapInfo info;


// create global functions
void lockBitmap(JNIEnv *env, jobject bmp) {
    bitmap = env->NewGlobalRef(bmp);
    AndroidBitmap_getInfo(env, bitmap, &info);
    AndroidBitmap_lockPixels(env, bitmap, &pixels);
}

void unlockBitmap(JNIEnv *env) {
    AndroidBitmap_unlockPixels(env, bitmap);
    env->DeleteGlobalRef(bitmap);
}

void pixel(__attribute__((unused)) JNIEnv *env, jint x, jint y, jint r, jint g, jint b) {
    auto* pixelData = (uint32_t*) pixels;
    uint32_t pixel = 255 << 24 | b << 16 | g << 8 | r;
    pixelData[y * info.stride / 4 + x] = pixel;
}


void gradient(__attribute__((unused)) JNIEnv *env) {
    auto* pixelData = (uint32_t*) pixels;
    for (int y = 0; y < info.height; y++) {
        for (int x = 0; x < info.width; x++) {
            uint32_t pixel = (0xFF << 24) | (255 << 16) | (y * 255 / info.height << 8) | x * 255 / info.width;
            pixelData[y * info.stride / 4 + x] = pixel;
        }
    }
}


// create JNI functions
extern "C" JNIEXPORT void JNICALL
Java_uz_alien_glecy_NativeLib_lockBitmap(JNIEnv *env, jobject /* this */, jobject bmp) {
    lockBitmap(env, bmp);
}

extern "C" JNIEXPORT void JNICALL
Java_uz_alien_glecy_NativeLib_unlockBitmap(JNIEnv *env, jobject /* this */) {
    unlockBitmap(env);
}

extern "C" JNIEXPORT void JNICALL
Java_uz_alien_glecy_NativeLib_pixel(JNIEnv *env, jobject /* this */, jint x, jint y, jint r, jint g, jint b) {
    pixel(env, x, y, r, g, b);
}

extern "C" JNIEXPORT void JNICALL
Java_uz_alien_glecy_NativeLib_gradient(JNIEnv *env, jobject /* this */) {
    gradient(env);
}