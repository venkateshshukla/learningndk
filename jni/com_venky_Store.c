#include "com_venky_Store.h"
#include "Store.h"
#include <stdint.h>
#include <string.h>
#include <android/log.h>
#define LOG_TAG "com_venky_Store.c"
#define LOGV(logmsg) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, logmsg)

static Store nStore = {{},0};

JNIEXPORT jint JNICALL Java_com_venky_Store_getInt
	(JNIEnv* env, jobject obj, jstring rKey)
{
	LOGV("getInt is called");
	StoreEntry* fEntry = findEntry(env, &nStore, rKey, NULL);
	if(isEntryValid(env, fEntry, StoreType_Int))
		return fEntry->nValue.intValue;
	else
		return 0;
}

JNIEXPORT void JNICALL Java_com_venky_Store_setInt
	(JNIEnv* env, jobject obj, jstring rKey, jint rInt)
{
	LOGV("setInt is called");
	StoreEntry* nEntry = allocateEntry(env, &nStore, rKey);
	if(nEntry != NULL)
	{
		nEntry->nType = StoreType_Int;
		nEntry->nValue.intValue = rInt;
	}
}

JNIEXPORT jstring JNICALL Java_com_venky_Store_getString
  (JNIEnv* env, jobject obj, jstring rKey)
{
	LOGV("getString is called");
	StoreEntry* fEntry = findEntry(env, &nStore, rKey, NULL);
	if(isEntryValid(env, fEntry, StoreType_String))
	{
		return (*env)->NewStringUTF(env, fEntry->nValue.stringValue);
	}
	else
		return NULL;
}

JNIEXPORT void JNICALL Java_com_venky_Store_setString
  (JNIEnv* env, jobject obj, jstring rKey, jstring rString)
{
	LOGV("setString is called");
	const char* tmpValue = (*env)->GetStringUTFChars(env, rString, NULL);
	if(tmpValue == NULL) return;
	StoreEntry* nEntry = allocateEntry(env, &nStore, rKey);
	if(nEntry != NULL)
	{
		nEntry->nType = StoreType_String;
		jsize nValueSize = (*env)->GetStringUTFLength(env, rString);
		nEntry->nValue.stringValue = (char*) malloc(sizeof(char) * nValueSize);
		strcpy(nEntry->nValue.stringValue, tmpValue);
	}
	(*env)->ReleaseStringUTFChars(env, rString, tmpValue);
}

JNIEXPORT jobject JNICALL Java_com_venky_Store_getColor
  (JNIEnv* env, jobject obj, jstring rKey)
{
	int32_t error = 0;
	LOGV("getColor is called");
	StoreEntry* fEntry = findEntry(env, &nStore, rKey, &error);
	if(isEntryValid(env, fEntry, StoreType_Color))
		return fEntry->nValue.colorValue;
	else
		return NULL;
}

JNIEXPORT void JNICALL Java_com_venky_Store_setColor
  (JNIEnv *env , jobject obj, jstring rKey, jobject rColor)
{
	LOGV("setColor is called");
	jobject nColor = (*env)->NewGlobalRef(env, rColor);
	if(nColor == NULL) return;
	StoreEntry* nEntry = allocateEntry(env, &nStore, rKey);
	if(nEntry == NULL)
		(*env)->DeleteGlobalRef(env,nColor);
	else
	{
		nEntry->nType = StoreType_Color;
		nEntry->nValue.colorValue = nColor;
	}
}


