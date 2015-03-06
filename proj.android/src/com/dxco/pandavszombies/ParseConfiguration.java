package com.dxco.pandavszombies;

import android.app.Activity;

public class ParseConfiguration {
	
	public static Activity activity;

	public static int getAdMinLevel() {
		return ConfigurationUtil.getConfiguration(activity, "showAdMinLevel", 15);
	}
	
	public static int getShowAdRateStory() {
		return ConfigurationUtil.getConfiguration(activity, "showAdRateStory", 34);
	}
	
	public static int getShowAdRateSurvival() {
		return ConfigurationUtil.getConfiguration(activity, "showAdRateSurvival", 34);
	}
	
	public static int getConfigurationTimeCacheHs() {
		return ConfigurationUtil.getConfiguration(activity, "configurationTimeCacheHs", 24);
	}
}
