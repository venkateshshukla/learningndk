#ifndef _STORE_H
#define _STORE_H

#include "jni.h"
#include <stdint.h>

#define STORE_MAX_CAPACITY 10

typedef enum {
	StoreType_Int, StoreType_String, StoreType_Color,
	StoreType_IntArray, StoreType_ColorArray
} StoreType;

typedef union {
	int32_t intValue;
	char* stringValue;
	jobject colorValue;
	int32_t *intArrayValues;
	jobject *colorArrayValues;
} StoreValue;

typedef struct {
	char* nKey;
	StoreType nType;
	StoreValue nValue;
	int32_t length;
} StoreEntry;

typedef struct {
	StoreEntry allentries[STORE_MAX_CAPACITY];
	int numentries;
} Store;

int32_t isEntryValid(JNIEnv* env,StoreEntry* rEntry, StoreType rType);
StoreEntry* allocateEntry(JNIEnv* env, Store* rStore, jstring rKey);
StoreEntry* findEntry(JNIEnv* env, Store* rStore, jstring rKey, int32_t* rError);
void freeEntry(JNIEnv* env,StoreEntry* rEntry);

void throwInvalidTypeException(JNIEnv* pEnv);
void throwNonExistingKeyException(JNIEnv* pEnv);
void throwStoreFullException(JNIEnv* pEnv);

#endif
