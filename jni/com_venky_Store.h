/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_venky_Store */

#ifndef _Included_com_venky_Store
#define _Included_com_venky_Store
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_venky_Store
 * Method:    getInt
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_venky_Store_getInt
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_venky_Store
 * Method:    setInt
 * Signature: (Ljava/lang/String;I)V
 */
JNIEXPORT void JNICALL Java_com_venky_Store_setInt
  (JNIEnv *, jobject, jstring, jint);

/*
 * Class:     com_venky_Store
 * Method:    getString
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_venky_Store_getString
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_venky_Store
 * Method:    setString
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_venky_Store_setString
  (JNIEnv *, jobject, jstring, jstring);

/*
 * Class:     com_venky_Store
 * Method:    getColor
 * Signature: (Ljava/lang/String;)Lcom/venky/Color;
 */
JNIEXPORT jobject JNICALL Java_com_venky_Store_getColor
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_venky_Store
 * Method:    setColor
 * Signature: (Ljava/lang/String;Lcom/venky/Color;)V
 */
JNIEXPORT void JNICALL Java_com_venky_Store_setColor
  (JNIEnv *, jobject, jstring, jobject);

#ifdef __cplusplus
}
#endif
#endif
