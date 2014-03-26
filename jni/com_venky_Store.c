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

JNIEXPORT jintArray JNICALL Java_com_venky_Store_getIntArray
  (JNIEnv *env, jobject obj, jstring rKey)
{
	LOGV("getIntArray is called");
	StoreEntry *fEntry = findEntry(env, &nStore, rKey, NULL);
	if(isEntryValid(env, fEntry, StoreType_IntArray))
	{
		jintArray nJavaIntArray = (*env)->NewIntArray(env, fEntry->length);
		if(nJavaIntArray == NULL) {
			return NULL;
		}
		(*env)->SetIntArrayRegion(env, nJavaIntArray, 0, fEntry->length,
				fEntry->nValue.intArrayValues);
		return nJavaIntArray;
	}
	return NULL;
}
JNIEXPORT void JNICALL Java_com_venky_Store_setIntArray
  (JNIEnv *env, jobject obj, jstring rKey, jintArray jIntArray)
{
	jsize arraylen = (*env)->GetArrayLength(env, jIntArray);
	int32_t* nIntArray = (int32_t *) malloc(arraylen * sizeof(int32_t));
	(*env)->GetIntArrayRegion(env, jIntArray, 0, arraylen, nIntArray);
	if((*env)->ExceptionCheck(env))
	{
		free(nIntArray);
		return;
	}
	StoreEntry *nEntry = allocateEntry(env, &nStore, rKey);
	if(nEntry != NULL)
	{
		nEntry->length = arraylen;
		nEntry->nType = StoreType_IntArray;
		nEntry->nValue.intArrayValues = nIntArray;
	}
	else
	{
		free(nIntArray);
		return;
	}

}
JNIEXPORT jobjectArray JNICALL Java_com_venky_Store_getColorArray
  (JNIEnv *env, jobject obj, jstring rKey)
{
	StoreEntry *fEntry = findEntry(env, &nStore, rKey, NULL);
	if(fEntry == NULL)
		return NULL;
	if(isEntryValid(env, fEntry, StoreType_ColorArray))
	{
		jclass jColorClass = (*env)->FindClass(env, "com/venky/Color");
		if(jColorClass == NULL)
			return NULL;

		jobjectArray jColorArray = (*env)->NewObjectArray(env, fEntry->length,
				jColorClass, NULL);
		(*env)->DeleteLocalRef(env, jColorClass);
		if(jColorArray == NULL)
			return NULL;

		int32_t i;
		for(i = 0; i < fEntry->length; i++)
		{
			(*env)->SetObjectArrayElement(env, jColorArray, i,
					fEntry->nValue.colorArrayValues[i]);
			if((*env)->ExceptionCheck(env))
				return NULL;
		}
		return jColorArray;
	}
	else
		return NULL;

}
JNIEXPORT void JNICALL Java_com_venky_Store_setColorArray
  (JNIEnv *env, jobject obj, jstring rKey, jobjectArray jColorArray)
{
	jsize arraylen = (*env)->GetArrayLength(env, jColorArray);
	jobject *nColorArray = (jobject *) malloc(arraylen* sizeof(jobject));
	int32_t i, j ;
	for(i = 0; i < arraylen; i++)
	{
		jobject nLocalColor = (*env)->GetObjectArrayElement(env, jColorArray, i);
		if(nLocalColor == NULL)
			for(j = 0; j < arraylen; j++)
				(*env)->DeleteGlobalRef(env, nColorArray[j]);
		nColorArray[i] = (*env)->NewGlobalRef(env, nLocalColor);
		if(nColorArray[i] == NULL)
			for(j = 0; j < arraylen; j++)
				(*env)->DeleteGlobalRef(env, nColorArray[j]);
		(*env)->DeleteLocalRef(env, nLocalColor);
	}
	StoreEntry *nEntry = allocateEntry(env, &nStore, rKey);
	if(nEntry == NULL)
	{
		for(j = 0; j < i; j++)
			(*env)->DeleteGlobalRef(env, nColorArray[j]);
		free(nColorArray);
		return;
	}
	else
	{
		nEntry->length = arraylen;
		nEntry->nType = StoreType_ColorArray;
		nEntry->nValue.colorArrayValues = nColorArray;
	}
}
