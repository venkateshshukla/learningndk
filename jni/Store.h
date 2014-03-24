#ifndef _STORE_H
#define _STORE_H
#endif

#include "jni.h"
#include <stdint.h>

#define STORE_MAX_CAPACITY 20

typedef enum {
	StoreType_Int, StoreType_String, StoreType_Color
} StoreType;

typedef union {
	int32_t intValue;
	char* stringValue;
	jobject colorValue;
} StoreValue;

typedef struct {
	char* nKey;
	StoreType nType;
	StoreValue nValue;
} StoreEntry;

typedef struct {
	StoreEntry allentries[STORE_MAX_CAPACITY];
	int numentries;
} Store;

int32_t isEntryValid(JNIEnv* env,StoreEntry* rEntry, StoreType rType);
StoreEntry* allocateEntry(JNIEnv* env, Store* rStore, jstring rKey);
StoreEntry* findEntry(JNIEnv* env, Store* rStore, jstring rKey, int32_t* rError);
void freeEntry(JNIEnv* env,StoreEntry* rEntry);
