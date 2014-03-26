package com.venky;

import java.util.ArrayList;

import com.venky.exceptions.InvalidTypeException;
import com.venky.exceptions.NonExistingKeyException;
import com.venky.exceptions.StoreFullException;

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
		spinnerArray.add(StoreType.IntArray);
		spinnerArray.add(StoreType.ColorArray);
		ArrayAdapter<StoreType> spinnerArrayAdapter = new ArrayAdapter<StoreType>
		(this, android.R.layout.simple_spinner_dropdown_item, spinnerArray);
		spinType.setAdapter(spinnerArrayAdapter);
	}

	public void pressGet(View v) {
		String key = etKey.getText().toString();
		StoreType type = (StoreType) spinType.getSelectedItem();
		String value = "";
		Log.v(TAG, key);
		Log.v(TAG, String.valueOf(type));
		try {
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
			case IntArray:
				int[] intvalues = store.getIntArray(key);
				for(int x: intvalues)
					value += (String.valueOf(x) + ";");
				Log.v(TAG, value);
				etValue.setText(value);
				break;
			case ColorArray:
				Color[] colorvalues = store.getColorArray(key);
				for(Color x:colorvalues)
					value += (x.toString() + ";");
				Log.v(TAG, value);
				etValue.setText(value);
			}
		} catch (NonExistingKeyException e) {
			displayErrorMsg(e.getMessage());
		} catch (InvalidTypeException e) {
			displayErrorMsg(e.getMessage());
		}

	}

	public void pressSet(View v) {
		String key = etKey.getText().toString();
		String value = etValue.getText().toString();
		StoreType type = (StoreType) spinType.getSelectedItem();
		String[] stringvalues;
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
				case IntArray:
					stringvalues = value.split(";");
					int[] intvalues = new int[stringvalues.length];
					for(int i = 0; i < stringvalues.length; i++)
						intvalues[i] = Integer.parseInt(stringvalues[i]);
					store.setIntArray(key, intvalues);
					break;
				case ColorArray:
					stringvalues = value.split(";");
					Color[] colorvalues = new Color[stringvalues.length];
					for(int i = 0; i < stringvalues.length; i++)
						colorvalues[i] = new Color(stringvalues[i]);
					store.setColorArray(key, colorvalues);
					break;
			}
		}
		catch (NumberFormatException e)
		{
			displayErrorMsg("Incorrect Value");
		}
		catch (IllegalArgumentException e)
		{
			displayErrorMsg("Incorrect Value");
		}
		catch (StoreFullException e)
		{
			displayErrorMsg(e.getMessage());
		}
	}

	private void displayErrorMsg(String errorMsg) {
		Toast.makeText(this, errorMsg, Toast.LENGTH_LONG).show();
	}
}

