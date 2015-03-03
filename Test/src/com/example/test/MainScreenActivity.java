package com.example.test;

import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

public class MainScreenActivity extends ActionBarActivity {

	TextView editTextInput;
	Button buttonSend;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main_screen);
		
		// найдем View-элементы
				editTextInput = (TextView) findViewById(R.id.editTextInput);
				buttonSend = (Button) findViewById(R.id.buttonSend);
				
				Log.i("DDV", "editTextInput="+editTextInput);
				Log.i("DDV", "buttonSend="+buttonSend);
				
				OnClickListener list = new OnClickListener() {

					@Override
					public void onClick(View v) {
						editTextInput.setText("Нажата кнопка ОК");

					}
				};
				
//				buttonSend.setOnClickListener(list);

//				buttonSend.setOnClickListener(new OnClickListener() {
		//
//					@Override
//					public void onClick(View v) {
//						editTextInput.setText("Нажата кнопка ОК");
		//
//					}
//				});
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main_screen, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		int id = item.getItemId();
		if (id == R.id.action_settings) {
			return true;
		}
		return super.onOptionsItemSelected(item);
	}
}
