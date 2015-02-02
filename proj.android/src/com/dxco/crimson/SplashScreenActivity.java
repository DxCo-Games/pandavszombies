package com.dxco.crimson;

import java.util.Timer;
import java.util.TimerTask;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;

public class SplashScreenActivity extends Activity {

	private static final long SPLASH_SCREEN_DELAY = 3000;
	
	 @Override
	    protected void onCreate(Bundle savedInstanceState) {
	        super.onCreate(savedInstanceState);
	        
	        setContentView(R.layout.splash_screen_activity);
	 
	        TimerTask task = new TimerTask() {
	            @Override
	            public void run() {
	 
	                Intent mainIntent = new Intent().setClass(SplashScreenActivity.this, MainMenuActivity.class);
	                startActivity(mainIntent);
	 
	                // Close the activity so the user won't able to go back this activity pressing Back button
	                finish();
	            }
	        };
	 
	        // Simulate a long loading process on application startup.
	        Timer timer = new Timer();
	        timer.schedule(task, SPLASH_SCREEN_DELAY);
	    }
}
