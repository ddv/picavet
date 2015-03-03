package org.psystems.picavet;

import android.app.Activity;
import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class MainScreenActivity extends Activity implements SensorEventListener {

	EditText editText1;
	Button buttonSend;
	EditText editText2;
	
	 SensorManager sensorManager;
	    float[] mGravs = new float[3];
	    float[] mGeoMags = new float[3];
	    float[] mRotationM = new float[16];
	    float[] mInclinationM = new float[16];
	    float[] mOrientation = new float[3];
	    float[] mOldOreintation = new float[3];
	    String[] mAccelerometer =  new String[3];
	    String[] mMagnetic =  new String[3];    
	    String[] mRotation =  new String[16];
	    String[] mInclination =  new String[16];
	    String[] mOrientationString =  new String[3];
	    String[] mOldOreintationString =  new String[3];
	    
	private TextView xyView;
	private TextView xzView;
	private TextView zyView;

	private TextView mxView;
	private TextView myView;
	private TextView mzView;

	//private SensorManager msensorManager;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		// StrictMode.ThreadPolicy policy = new
		// StrictMode.ThreadPolicy.Builder().permitAll().build();
		// StrictMode.setThreadPolicy(policy);

		setContentView(R.layout.activity_main_screen);

		// найдем View-элементы
		editText1 = (EditText) findViewById(R.id.editText1);
		editText2 = (EditText) findViewById(R.id.editText2);
		buttonSend = (Button) findViewById(R.id.buttonSend);

		Log.i("DDV", "buttonSend=" + buttonSend);
		Log.i("DDV", "editText1=" + editText1);
		Log.i("DDV", "editText2=" + editText2);

		buttonSend.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {

				new InternetRequestTask(MainScreenActivity.this)
						.execute("http://10.130.1.100");

				// HttpClient httpclient = new DefaultHttpClient();
				// HttpResponse response = httpclient.execute(new HttpGet(URL));
				// StatusLine statusLine = response.getStatusLine();
				// if(statusLine.getStatusCode() == HttpStatus.SC_OK){
				// ByteArrayOutputStream out = new ByteArrayOutputStream();
				// response.getEntity().writeTo(out);
				// String responseString = out.toString();
				// out.close();
				// //..more logic
				// } else{
				// //Closes the connection.
				// response.getEntity().getContent().close();
				// throw new IOException(statusLine.getReasonPhrase());
				// }

				editText1.setText("OK!!!!");
				// editText2.setText("OK!\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\n");
			}

		});

//		msensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
//
		sensorManager = (SensorManager)getSystemService(SENSOR_SERVICE);
//		
//		rotationMatrix = new float[16];
//		accelData = new float[3];
//		magnetData = new float[3];
//		OrientationData = new float[3];
//
//		xyView = (TextView) findViewById(R.id.xyValue); //
//		xzView = (TextView) findViewById(R.id.xzValue); // Наши текстовые поля
//														// для вывода показаний
//		zyView = (TextView) findViewById(R.id.zyValue); //
//
//		mxView = (TextView) findViewById(R.id.mxValue); //
//		myView = (TextView) findViewById(R.id.myValue); // Наши текстовые поля
//														// для вывода показаний
//		mzView = (TextView) findViewById(R.id.mzValue); //
	}

	public EditText getEditText1() {
		return editText1;
	}
	
	private SensorEventListener sensorEventListener = new SensorEventListener() {

        public void onAccuracyChanged(Sensor sensor, int accuracy) {

        }


        /* Get the Sensors */
        public void onSensorChanged(SensorEvent event) {

              switch (event.sensor.getType()) {
                     case Sensor.TYPE_ACCELEROMETER:
                              System.arraycopy(event.values, 0, mGravs, 0, 3);
                              break;
                     case Sensor.TYPE_MAGNETIC_FIELD:
                              System.arraycopy(event.values, 0, mGeoMags, 0, 3);
                              break;
                     case Sensor.TYPE_ORIENTATION:
                            System.arraycopy(event.values, 0, mOldOreintation, 0, 3);
                      break;

                     default:
                              return;
            }

                // If mGravs and mGeoMags have values then find rotation matrix
                if (mGravs != null && mGeoMags != null) {

                    // checks that the rotation matrix is found
                    boolean success = SensorManager.getRotationMatrix(mRotationM, mInclinationM, mGravs, mGeoMags);
                    if (success) {
                        /* getOrientation Values */   
                        SensorManager.getOrientation(mRotationM, mOrientation);

                          for(int i=0; i<2; i++){
                              mAccelerometer[i] = Float.toString(mGravs[i]);
                              mMagnetic[i] = Float.toString(mGeoMags[i]);
                              mOrientationString[i] = Float.toString(mOrientation[i]);
                              mOldOreintationString[i] = Float.toString(mOldOreintation[i]);
                          }

                          /* Make everything text to show on device */
                          TextView xaxisAccelerometerText = (TextView)findViewById(R.id.xaxisAccelerometer);
                          xaxisAccelerometerText.setText(mAccelerometer[0]);      
                          TextView yaxisAccelerometerText = (TextView)findViewById(R.id.yaxisAccelerometer);
                          yaxisAccelerometerText.setText(mAccelerometer[1]);
                          TextView zaxisAccelerometerText = (TextView)findViewById(R.id.zaxisAccelerometer);
                          zaxisAccelerometerText.setText(mAccelerometer[2]);    
                          TextView xaxisMagneticText = (TextView)findViewById(R.id.xaxisMagnetic);
                          xaxisMagneticText.setText(mMagnetic[0]);    
                          TextView yaxisMagneticText = (TextView)findViewById(R.id.yaxisMagnetic);
                          yaxisMagneticText.setText(mMagnetic[1]);
                          TextView zaxisMagneticText = (TextView)findViewById(R.id.zaxisMagnetic);
                          zaxisMagneticText.setText(mMagnetic[2]);
                          TextView xaxisOrientationText = (TextView)findViewById(R.id.xaxisOrientation);
                          xaxisOrientationText.setText(mOrientationString[0]);    
                          TextView yaxisOrientationText = (TextView)findViewById(R.id.yaxisOrientation);
                          yaxisOrientationText.setText(mOrientationString[1]);
                          TextView zaxisOrientationText = (TextView)findViewById(R.id.zaxisOrientation);
                          zaxisOrientationText.setText(mOrientationString[2]);
                          TextView xaxisOldOrientationText = (TextView)findViewById(R.id.xaxisOldOrientation);
                          xaxisOldOrientationText.setText(mOldOreintationString[0]);      
                          TextView yaxisOldOrientationText = (TextView)findViewById(R.id.yaxisOldOrientation);
                          yaxisOldOrientationText.setText(mOldOreintationString[1]);
                          TextView zaxisOldOrientationText = (TextView)findViewById(R.id.zaxisOldOrientation);
                          zaxisOldOrientationText.setText(mOldOreintationString[2]);

                    }else{

                         /* Make everything text to show on device even if getRotationMatrix fails*/
                          String matrixFailed = "Rotation Matrix Failed";
                          TextView xaxisAccelerometerText = (TextView)findViewById(R.id.xaxisAccelerometer);
                          xaxisAccelerometerText.setText(mAccelerometer[0]);      
                          TextView yaxisAccelerometerText = (TextView)findViewById(R.id.yaxisAccelerometer);
                          yaxisAccelerometerText.setText(mAccelerometer[1]);
                          TextView zaxisAccelerometerText = (TextView)findViewById(R.id.zaxisAccelerometer);
                          zaxisAccelerometerText.setText(mAccelerometer[2]);    
                          TextView xaxisMagneticText = (TextView)findViewById(R.id.xaxisMagnetic);
                          xaxisMagneticText.setText(mMagnetic[0]);    
                          TextView yaxisMagneticText = (TextView)findViewById(R.id.yaxisMagnetic);
                          yaxisMagneticText.setText(mMagnetic[1]);
                          TextView zaxisMagneticText = (TextView)findViewById(R.id.zaxisMagnetic);
                          zaxisMagneticText.setText(mMagnetic[2]);
                          TextView xaxisOrientationText = (TextView)findViewById(R.id.xaxisOrientation);
                          xaxisOrientationText.setText(matrixFailed);     
                          TextView yaxisOrientationText = (TextView)findViewById(R.id.yaxisOrientation);
                          yaxisOrientationText.setText(matrixFailed);
                          TextView zaxisOrientationText = (TextView)findViewById(R.id.zaxisOrientation);
                          zaxisOrientationText.setText(matrixFailed);
                          TextView xaxisOldOrientationText = (TextView)findViewById(R.id.xaxisOldOrientation);
                          xaxisOldOrientationText.setText(mOldOreintationString[0]);      
                          TextView yaxisOldOrientationText = (TextView)findViewById(R.id.yaxisOldOrientation);
                          yaxisOldOrientationText.setText(mOldOreintationString[1]);
                          TextView zaxisOldOrientationText = (TextView)findViewById(R.id.zaxisOldOrientation);
                          zaxisOldOrientationText.setText(mOldOreintationString[2]);





                    }
                }


        }
    };

//	private void loadNewSensorData(SensorEvent event) {
//		final int type = event.sensor.getType(); // Определяем тип датчика
//		if (type == Sensor.TYPE_ACCELEROMETER) { // Если акселерометр
//			accelData = event.values.clone();
//		}
//
//		if (type == Sensor.TYPE_MAGNETIC_FIELD) { // Если геомагнитный датчик
//			magnetData = event.values.clone();
//		}
//	}

	@Override
	protected void onResume() {
		super.onResume();
		 super.onResume();
	        sensorManager.registerListener(sensorEventListener, sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER), SensorManager.SENSOR_DELAY_NORMAL);
	        sensorManager.registerListener(sensorEventListener, sensorManager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD), SensorManager.SENSOR_DELAY_NORMAL);
	        sensorManager.registerListener(sensorEventListener, sensorManager.getDefaultSensor(Sensor.TYPE_ORIENTATION), SensorManager.SENSOR_DELAY_NORMAL);
	}

	@Override
	protected void onPause() {
		 super.onPause();
	        sensorManager.unregisterListener(sensorEventListener);
	}

	@Override
	public void onSensorChanged(SensorEvent event) {

//		// Log.i("DDV", "onSensorChanged Sensor: " + event);
//
//		loadNewSensorData(event); // Получаем данные с датчика
//		SensorManager.getRotationMatrix(rotationMatrix, null, accelData,
//				magnetData); // Получаем матрицу поворота
//		SensorManager.getOrientation(rotationMatrix, OrientationData); // Получаем
//																		// данные
//																		// ориентации
//																		// устройства
//																		// в
//																		// пространстве
//
//		if ((xyView == null) || (xzView == null) || (zyView == null)) { // Без
//																		// этого
//																		// работать
//																		// отказалось.
//			xyView = (TextView) findViewById(R.id.xyValue);
//			xzView = (TextView) findViewById(R.id.xzValue);
//			zyView = (TextView) findViewById(R.id.zyValue);
//		}
//
//		// Выводим результат
//		xyView.setText(String.valueOf(Math.round(Math
//				.toDegrees(OrientationData[0]))));
//		xzView.setText(String.valueOf(Math.round(Math
//				.toDegrees(OrientationData[1]))));
//		zyView.setText(String.valueOf(Math.round(Math
//				.toDegrees(OrientationData[2]))));
//
////		if (magnetData.length == 3) {
////			mxView.setText("" + magnetData[0]);
////			myView.setText("" + magnetData[1]);
////			mzView.setText("" + magnetData[2]);
////		}
//		
//		mxView.setText("" + event.values[0]); //Плоскость XY
//		myView.setText("" + event.values[1]); //Плоскость XZ
//		mzView.setText("" + event.values[2]); //Плоскость ZY
		
	    

	}

	@Override
	public void onAccuracyChanged(Sensor sensor, int accuracy) {

	}

}
