package com.dxco.pandavszombies;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Calendar;
import java.util.Date;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.content.pm.Signature;
import android.os.Bundle;
import android.util.Base64;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.ImageButton;
import android.widget.Toast;

import com.facebook.Session;
import com.facebook.Session.OpenRequest;
import com.facebook.SessionState;
import com.parse.ConfigCallback;
import com.parse.Parse;
import com.parse.ParseConfig;
import com.parse.ParseException;


public class MainMenuActivity extends Activity {

	private ImageButton botonLoginFacebook;
	//private ImageButton botonLogoutFacebook;
	
	private ImageButton botonMusicOn;
	private ImageButton botonMusicOff;
	private ImageButton botonSoundEffectsOn;
	private ImageButton botonSoundEffectsOff;
	
	private static final String APP_ID = "com.dxco.pandavszombies";
	private static final String GAME_URL = "https://play.google.com/store/apps/details?id=" + APP_ID;
	
	static {
		System.loadLibrary("hellocpp");
	}

	private Session.StatusCallback statusCallback = new SessionStatusCallback();

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
	 
		Parse.initialize(this, "IJw4teqCfajXsuurrzbokGmsmjE1i86gbuYNO6my", "dUoVH3BLMqFijaiVZN31VTw6Gr2chR52MuQ6yc8l");
		
		SoundUtil.activity = this;
		ParseConfiguration.activity = this;
		
		getConfigFromParse();
		
		setContentView(R.layout.main_menu_activity);

		this.botonMusicOn = (ImageButton) findViewById(R.id.botonMusicOn);
		this.botonMusicOff = (ImageButton) findViewById(R.id.botonMusicOff);
		this.botonSoundEffectsOn = (ImageButton) findViewById(R.id.botonSoundEffectsOn);
		this.botonSoundEffectsOff = (ImageButton) findViewById(R.id.botonSoundEffectsOff);
		
		if (SoundUtil.isMusicOn()) {
			this.botonMusicOff.setVisibility(ImageButton.GONE);
		} else {
			this.botonMusicOn.setVisibility(ImageButton.GONE);
		}
		
		if (SoundUtil.isSoundEffectsOn()) {
			this.botonSoundEffectsOff.setVisibility(ImageButton.GONE);
		} else {
			this.botonSoundEffectsOn.setVisibility(ImageButton.GONE);
		}
		
		this.botonMusicOn.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				SoundUtil.disableMusic();
				botonMusicOff.setVisibility(ImageButton.VISIBLE);
				botonMusicOn.setVisibility(ImageButton.GONE);
			}
		});
		
		this.botonMusicOff.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				SoundUtil.enableMusic();
				botonMusicOn.setVisibility(ImageButton.VISIBLE);
				botonMusicOff.setVisibility(ImageButton.GONE);
			}
		});
		
		this.botonSoundEffectsOn.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				SoundUtil.disableMusicEffects();
				botonSoundEffectsOff.setVisibility(ImageButton.VISIBLE);
				botonSoundEffectsOn.setVisibility(ImageButton.GONE);
			}
		});
		
		this.botonSoundEffectsOff.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				SoundUtil.enableSoundEffects();
				botonSoundEffectsOn.setVisibility(ImageButton.VISIBLE);
				botonSoundEffectsOff.setVisibility(ImageButton.GONE);
			}
		});
		
		ImageButton botonPlay = (ImageButton) findViewById(R.id.botonPlay);

		botonPlay.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				Intent intent = new Intent(MainMenuActivity.this, CppConnectorActivity.class);
		        startActivity(intent);
			}
		});

		
		
		SocialUtil.addRateAppListener(this, findViewById(R.id.botonRate), APP_ID, GAME_URL);

		/*this.botonLoginFacebook.setOnClickListener(new OnClickListener() {
			public void onClick(View view) {
				onClickLogin();
			}
		});
		
		
		
		this.botonLoginFacebook = (ImageButton) findViewById(R.id.botonLoginFacebook);
		
		this.botonLogoutFacebook = (ImageButton) findViewById(R.id.botonLogoutFacebook);
		this.botonLogoutFacebook.setOnClickListener(new OnClickListener() {
			public void onClick(View view) {
				onClickLogout();
			}
		});*/

		/* Facebook Configuration */
		Session session = Session.getActiveSession();

		if (session == null) {
			if (savedInstanceState != null) {
				session = Session.restoreSession(this, null, statusCallback, savedInstanceState);
			}
			if (session == null) {
				session = new Session(this);
			}
			
			Session.setActiveSession(session);
			
			if (session.getState().equals(SessionState.CREATED_TOKEN_LOADED)) {
				session.openForRead(new Session.OpenRequest(this).setCallback(statusCallback));
			}
		}

		updateView();
	}
	
private void getConfigFromParse() {
		
		final Activity context = this;
		
		Date configurationLastUpdate = ConfigurationUtil.getConfiguration(context, "configurationLastUpdate");
		int configurationTimeCacheHs = ParseConfiguration.getConfigurationTimeCacheHs();
		
		Calendar cal = Calendar.getInstance();
		cal.setTime(configurationLastUpdate);
		cal.add(Calendar.HOUR_OF_DAY, configurationTimeCacheHs);
		
		Date newUpdateTime = cal.getTime();
		
		if (new Date().after(newUpdateTime)) {
			ParseConfig.getInBackground(new ConfigCallback() {
				
				@Override
				public void done(ParseConfig config, ParseException e) {
					if (e != null) {
						return;
					}
					
					int showAdMinLevel = config.getInt("showAdMinLevel");
					int showAdRateStory = config.getInt("showAdRateStory");
					int showAdRateSurvival = config.getInt("showAdRateSurvival");
					int configurationTimeCacheHs = config.getInt("configurationTimeCacheHs");

					ConfigurationUtil.editConfiguration(context, "showAdMinLevel", showAdMinLevel);
					ConfigurationUtil.editConfiguration(context, "showAdRateStory", showAdRateStory);
					ConfigurationUtil.editConfiguration(context, "showAdRateSurvival", showAdRateSurvival);
					ConfigurationUtil.editConfiguration(context, "configurationTimeCacheHs", configurationTimeCacheHs);
					
					ConfigurationUtil.editConfiguration(context, "configurationLastUpdate", new Date());
				}
			});
		}
	}

	private void onClickLogin() {
		Session session = Session.getActiveSession();

		if (!session.isOpened() && !session.isClosed()) {
			OpenRequest openRequest = new Session.OpenRequest(this);
			session.openForRead(openRequest.setCallback(statusCallback));
		} else {
			Session.openActiveSession(this, true, statusCallback);
		}
	}

	private void onClickLogout() {
		Session session = Session.getActiveSession();
		if (!session.isClosed()) {
			session.closeAndClearTokenInformation();
			Toast.makeText(this, "Logged out from Facebook", Toast.LENGTH_SHORT).show();
		}
		
		this.botonLoginFacebook.setVisibility(ImageButton.VISIBLE);
	}
	
	private void updateView() {
		Session session = Session.getActiveSession();
		if (session.isOpened()) {
			this.botonLoginFacebook.setVisibility(ImageButton.GONE);
		} else {
			//this.botonLogoutFacebook.setVisibility(ImageButton.GONE);
		}
	}
	
	@Override
    public void onStart() {
        super.onStart();
        Session.getActiveSession().addCallback(statusCallback);
    }

    @Override
    public void onStop() {
        super.onStop();
        Session.getActiveSession().removeCallback(statusCallback);
    }

	@Override
	public void onBackPressed() {
	    new AlertDialog.Builder(this)
	    	.setMessage("Are you sure you want to exit?")
	        .setPositiveButton("Yes", new DialogInterface.OnClickListener() {
	        
	        @Override
	        public void onClick(DialogInterface dialog, int which) {
	            finish();
	        }
	    })
	    .setNegativeButton("No", null)
	    .show();
	}
	
	private class SessionStatusCallback implements Session.StatusCallback {

		@Override
		public void call(Session session, SessionState state, Exception exception) {
			updateView();

			if (session != null && session.getAccessToken() != null && !session.getAccessToken().equals("")) {
				// TODO: User logged in
			}
		}
	}
	
	private void printKeyHash() {
		try {
			PackageInfo info = getPackageManager().getPackageInfo("com.dxco.pandavszombies", PackageManager.GET_SIGNATURES);
			for (Signature signature : info.signatures) {
				MessageDigest md = MessageDigest.getInstance("SHA");
				md.update(signature.toByteArray());
				Log.d("KeyHash:", Base64.encodeToString(md.digest(), Base64.DEFAULT));
			}
		} catch (NameNotFoundException e) {
			e.printStackTrace();
		} catch (NoSuchAlgorithmException e) {
			e.printStackTrace();
		}
	}
}