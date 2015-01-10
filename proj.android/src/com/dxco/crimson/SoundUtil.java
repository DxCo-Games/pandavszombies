package com.dxco.crimson;

import android.app.Activity;

public class SoundUtil {

	public static Activity activity;

	public static boolean isMusicOn() {
		return ConfigurationUtil.getConfiguration(activity, "isMusicOn", true);
	}
	
	public static boolean isSoundEffectsOn() {
		return ConfigurationUtil.getConfiguration(activity, "isSoundEffectsOn", true);
	}
	
	public static void enableMusic() {
		ConfigurationUtil.editConfiguration(activity, "isMusicOn", true);
	}
	
	public static void disableMusic() {
		ConfigurationUtil.editConfiguration(activity, "isMusicOn", false);
	}
	
	public static void enableSoundEffects() {
		ConfigurationUtil.editConfiguration(activity, "isSoundEffectsOn", true);
	}
	
	public static void disableMusicEffects() {
		ConfigurationUtil.editConfiguration(activity, "isSoundEffectsOn", false);
	}

	public static int isSoundEffectsCpp() {
		return isSoundEffectsOn() ? 1 : 0;
	}
	
	public static int isMusicOnCpp() {
		return isMusicOn() ? 1 : 0;
	}
}
