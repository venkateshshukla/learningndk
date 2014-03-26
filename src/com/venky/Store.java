package com.venky;

import com.venky.exceptions.InvalidTypeException;
import com.venky.exceptions.NonExistingKeyException;

public class Store {
	static {
		System.loadLibrary("store");
	}
	public native int getInt(String key) throws NonExistingKeyException,
		InvalidTypeException;
	public native void setInt(String key, int value);

	public native String getString(String key) throws NonExistingKeyException,
		InvalidTypeException;
	public native void setString(String key, String value);

	public native Color getColor(String key) throws NonExistingKeyException,
		InvalidTypeException;
	public native void setColor(String key, Color value);

	public native int[] getIntArray(String key) throws NonExistingKeyException,
	InvalidTypeException;
	public native void setIntArray(String key, int[] value);

	public native Color[] getColorArray(String key) throws NonExistingKeyException,
	InvalidTypeException;
	public native void setColorArray(String key, Color[] value);
}
