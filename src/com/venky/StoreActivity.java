package com.venky;

import java.util.ArrayList;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.Toast;

public class StoreActivity extends Activity {
	
	private EditText etKey, etValue;
	private Spinner spinType;
	private Store store;
	private static final String TAG = "StoreActivity"; 
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_store);
		initializeUi();
		store = new Store();
	}

	private void initializeUi() {
		etKey = (EditText) findViewById(R.id.etKey);
		etValue = (EditText) findViewById(R.id.etValue);
		spinType = (Spinner) findViewById(R.id.spinType);
		ArrayList<StoreType> spinnerArray = new ArrayList<StoreType>();
		spinnerArray.add(StoreType.Int);
		spinnerArray.add(StoreType.String);
		spinnerArray.add(StoreType.Color);
		ArrayAdapter<StoreType> spinnerArrayAdapter = new ArrayAdapter<StoreType>
		(this, android.R.layout.simple_spinner_dropdown_item, spinnerArray);
		spinType.setAdapter(spinnerArrayAdapter);
	}
	
	public void pressGet(View v) {
		String key = etKey.getText().toString();
		StoreType type = (StoreType) spinType.getSelectedItem();
		String value; 
		Log.v(TAG, key);
		Log.v(TAG, String.valueOf(type));
		switch(type) {
		case Int:
			value = String.valueOf(store.getInt(key));
			Log.v(TAG, value);
			etValue.setText(value);
			break;
		case String:
			value = store.getString(key);
			Log.v(TAG, value);
			etValue.setText(value);
			break;
		case Color:
			value = store.getColor(key).toString();
			Log.v(TAG, value);
			etValue.setText(value);
			break;
		}
	}
	
	public void pressSet(View v) {
		String key = etKey.getText().toString();
		String value = etValue.getText().toString();
		StoreType type = (StoreType) spinType.getSelectedItem();
		Log.v(TAG, key);
		Log.v(TAG, value);
		Log.v(TAG, String.valueOf(type));
		try {
			switch(type) {
				case Int:
					store.setInt(key, Integer.valueOf(value));
					break;
				case String:
					store.setString(key, value);
					break;
				case Color:
					store.setColor(key, new Color(value));
					break;
			}
		} catch(Exception e) {
			Toast.makeText(this, e.toString(), Toast.LENGTH_LONG).show();
		}
	}
}
