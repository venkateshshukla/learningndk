package com.venky;

public class Store {
	static {
		System.loadLibrary("store");
	}
	public native int getInt(String key);
	public native void setInt(String key, int value);
	
	public native String getString(String key);
	public native void setString(String key, String value);
	
	public native Color getColor(String key);
	public native void setColor(String key, Color value);
}
