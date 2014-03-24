package com.venky;

public class Color {
	private int color;
	public Color(String rColor) {
		super();
		color = android.graphics.Color.parseColor(rColor);
	}
	
	@Override
	public String toString() {
		return String.format("#%06X", color);
	}

}
