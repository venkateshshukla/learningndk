#include "Store.h"
#include <string.h>
#include <android/log.h>
#define LOG_TAG "Store.c"
#define LOGV(logmsg) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, logmsg)

int32_t isEntryValid(JNIEnv* env, StoreEntry* rEntry, StoreType rType)
{
	LOGV("isEntryValid is called");
	if(rEntry == NULL || rEntry->nType != rType)
	{
		LOGV("Entry is invalid");
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
		if(rStore->numentries >= STORE_MAX_CAPACITY) return NULL;
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
	LOGV("freeEntry is called");
	switch(rEntry->nType)
	{
		case StoreType_String:
			free(rEntry->nValue.stringValue);
			break;
		case StoreType_Color:
			(*env)->DeleteGlobalRef(env, rEntry->nKey);
			break;
	}
	LOGV("Entry is freed");
}
