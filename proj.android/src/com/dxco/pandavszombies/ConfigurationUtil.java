package com.dxco.pandavszombies;

import java.util.Date;

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
	
	public static int getConfiguration(Activity activity, String configurationName, int defaultValue) {
		SharedPreferences settings = activity.getSharedPreferences(PREFERENCES_NAME, 0);
	    return settings.getInt(configurationName, defaultValue);
	}
	
	public static void editConfiguration(Activity activity, String configurationName, int value) {
		SharedPreferences settings = activity.getSharedPreferences(PREFERENCES_NAME, 0);
		SharedPreferences.Editor editor = settings.edit();
		editor.putInt(configurationName, value);
		editor.commit();
	}
	
	public static void editConfiguration(Activity activity, String configurationName, Date value) {
		SharedPreferences settings = activity.getSharedPreferences(PREFERENCES_NAME, 0);
		SharedPreferences.Editor editor = settings.edit();
		editor.putLong(configurationName, value.getTime());
		editor.commit();
	}
	
	public static Date getConfiguration(Activity activity, String configurationName) {
		SharedPreferences settings = activity.getSharedPreferences(PREFERENCES_NAME, 0);
	    return new Date(settings.getLong(configurationName, 0));
	}
}
