package com.venky.exceptions;

public class InvalidTypeException extends Exception {
	private static final long serialVersionUID = 992384254281371123L;
	public InvalidTypeException(String detailMsg) {
		super(detailMsg);
	}
}