#include "Store.h"
#include <string.h>
#include <android/log.h>
#define LOG_TAG "Store.c"
#define LOGV(logmsg) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, logmsg)

int32_t isEntryValid(JNIEnv* env, StoreEntry* rEntry, StoreType rType)
{
	LOGV("isEntryValid is called");
	if(rEntry == NULL)
	{
		throwNonExistingKeyException(env);
		LOGV("No key present with that type");
		return 0;
	}
	else if(rEntry->nType != rType)
	{
		throwInvalidTypeException(env);
		LOGV("EntryType is invalid");
		return 0;
	}
	LOGV("Entry is valid");
	return 1;
}

StoreEntry* findEntry(JNIEnv* env, Store* rStore, jstring rKey, int32_t* rError)
{
	LOGV("findEntry is called");
	StoreEntry* fEntry = rStore->allentries;
	StoreEntry* lEntry = rStore->allentries + rStore->numentries;

	const char* tmpKeyString = (*env)->GetStringUTFChars(env, rKey, NULL);

	if(tmpKeyString == NULL)
	{
		LOGV("Key is NULL");
		if(rError != NULL)
		{
			*rError = 1;
		}
		return NULL;
	}

	while(fEntry < lEntry && (strcmp(tmpKeyString, fEntry->nKey) != 0))
		fEntry++;

	(*env)->ReleaseStringUTFChars(env, rKey, tmpKeyString);

	return (fEntry == lEntry) ? NULL:  fEntry;
}

StoreEntry* allocateEntry(JNIEnv* env, Store* rStore, jstring rKey)
{
	LOGV("allocateEntry is called");
	int32_t error = 0;
	StoreEntry* rEntry = findEntry(env, rStore, rKey, &error);

	if(rEntry != NULL) freeEntry(env, rEntry);

	else if(!error)
	{
		LOGV("No error while allocation");
		if(rStore->numentries >= STORE_MAX_CAPACITY)
		{
			LOGV("Store is full");
			throwStoreFullException(env);
			return NULL;
		}
		rEntry = rStore->allentries + rStore->numentries;

		const char* tmpKeyString = (*env)->GetStringUTFChars(env, rKey, NULL);
		if(tmpKeyString == NULL) return NULL;

		rEntry->nKey = (char*) malloc(strlen(tmpKeyString));
		strcpy(rEntry->nKey, tmpKeyString);

		(*env)->ReleaseStringUTFChars(env, rKey, tmpKeyString);

		rStore->numentries++;
	}

	return rEntry;
}

void freeEntry(JNIEnv* env, StoreEntry* rEntry)
{
	int i;
	LOGV("freeEntry is called");
	switch(rEntry->nType)
	{
		case StoreType_String:
			free(rEntry->nValue.stringValue);
			break;
		case StoreType_Color:
			(*env)->DeleteGlobalRef(env, rEntry->nKey);
			break;
		case StoreType_IntArray:
			free(rEntry->nValue.intArrayValues);
			break;
		case StoreType_ColorArray:

			for(i = 0; i < rEntry->length; i++)
				(*env)->DeleteGlobalRef(env,
						rEntry->nValue.colorArrayValues[i]);
			free(rEntry->nValue.colorArrayValues);
			break;
	}
	LOGV("Entry is freed");
}

void throwNonExistingKeyException(JNIEnv* pEnv)
{
	jclass fClass = (*pEnv)->FindClass(pEnv,
			"com/venky/exceptions/NonExistingKeyException");
	if (fClass != NULL)
	{
		(*pEnv)->ThrowNew(pEnv, fClass, "Key does not exist.");
	}
	(*pEnv)->DeleteLocalRef(pEnv, fClass);
}

void throwInvalidTypeException(JNIEnv* env)
{
	jclass fClass = (*env)->FindClass(env,
			"com/venky/exceptions/InvalidTypeException");
	if(fClass != NULL)
		(*env)->DeleteLocalRef(env, fClass);
	else
		(*env)->ThrowNew(env, fClass, "Incorrect Type");
}

void throwStoreFullException(JNIEnv* env)
{
	jclass fClass = (*env)->FindClass(env,
			"com/venky/exceptions/StoreFullException");
	if(fClass == NULL)
		(*env)->DeleteLocalRef(env, fClass);
	else
		(*env)->ThrowNew(env, fClass, "Store is Full");
}
