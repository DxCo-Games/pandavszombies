package com.dxco.crimson;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.ImageButton;
import android.widget.Toast;

import com.facebook.Session;
import com.facebook.Session.OpenRequest;
import com.facebook.SessionState;


public class MainMenuActivity extends Activity {

	private ImageButton botonLoginFacebook;
	private ImageButton botonLogoutFacebook;

	private Session.StatusCallback statusCallback = new SessionStatusCallback();

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		setContentView(R.layout.main_menu_activity);

		ImageButton botonPlay = (ImageButton) findViewById(R.id.botonPlay);

		botonPlay.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				Intent intent = new Intent(MainMenuActivity.this, CppConnectorActivity.class);
		        startActivity(intent);
			}
		});

		this.botonLoginFacebook = (ImageButton) findViewById(R.id.botonLoginFacebook);
		this.botonLogoutFacebook = (ImageButton) findViewById(R.id.botonLogoutFacebook);

		this.botonLoginFacebook.setOnClickListener(new OnClickListener() {
			public void onClick(View view) {
				onClickLogin();
			}
		});

		this.botonLogoutFacebook.setOnClickListener(new OnClickListener() {
			public void onClick(View view) {
				onClickLogout();
			}
		});

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
			this.botonLogoutFacebook.setVisibility(ImageButton.GONE);
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
}