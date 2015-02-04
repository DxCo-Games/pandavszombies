package com.dxco.pandavszombies;

import android.app.Activity;
import android.content.ActivityNotFoundException;
import android.content.Intent;
import android.net.Uri;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Toast;

public class SocialUtil {

	public static void addRateAppListener(final Activity activity, View view, final String appID, final String gameURL) {
		view.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				startRateAppIntent(activity, appID, gameURL);
			}
		});
	}
	
	private static void startRateAppIntent(Activity activity, String appID, String appURL) {
		Intent intent = new Intent(Intent.ACTION_VIEW);
		intent.setData(Uri.parse("market://details?id=" + appID));

		if (!tryToStartActivity(activity, intent)) {
			// Google play app is not installed, let's try to open a web browser
			intent.setData(Uri.parse(appURL));

			if (!tryToStartActivity(activity, intent)) {
				// Everything failed, inform the user.
				Toast.makeText(activity, "Could not open Android market, please install the market app.", Toast.LENGTH_SHORT).show();
			}
		}
	}
	
	private static boolean tryToStartActivity(Activity activity, Intent intent) {
		try {
			activity.startActivity(intent);
			return true;
		} catch (ActivityNotFoundException e) {
			return false;
		}
	}
}
