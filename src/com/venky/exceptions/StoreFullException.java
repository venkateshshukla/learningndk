package com.venky.exceptions;

public class StoreFullException extends RuntimeException{
	private static final long serialVersionUID = 991212353545589123L;
	public StoreFullException(String detailMsg) {
		super(detailMsg);
	}
}
