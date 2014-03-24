package com.venky.exceptions;

public class NonExistingKeyException extends Exception{
	private static final long serialVersionUID = 991261286324263123L;
	public NonExistingKeyException(String detailMsg) {
		super(detailMsg);
	}
}
