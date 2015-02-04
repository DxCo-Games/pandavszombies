package com.dxco.pandavszombies;

import android.app.Activity;
import android.content.SharedPreferences;

public class ConfigurationUtil {
	
	private static String PREFERENCES_NAME = "configuration";

	public static boolean getConfiguration(Activity activity, String configurationName, boolean defaultValue) {
		SharedPreferences settings = activity.getSharedPreferences(PREFERENCES_NAME, 0);
	    return settings.getBoolean(configurationName, true);
	}
	
	public static void editConfiguration(Activity activity, String configurationName, boolean value) {
		SharedPreferences settings = activity.getSharedPreferences(PREFERENCES_NAME, 0);
		SharedPreferences.Editor editor = settings.edit();
		editor.putBoolean(configurationName, value);
		editor.commit();
	}
}
