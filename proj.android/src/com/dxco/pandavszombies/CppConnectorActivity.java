/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 ****************************************************************************/
package com.dxco.pandavszombies;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;

import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdView;
import com.google.android.gms.ads.InterstitialAd;
import com.kskkbys.rate.RateThisApp;

public class CppConnectorActivity extends Cocos2dxActivity {

	private static CppConnectorActivity _appActiviy;
	private AdView adView;
	private static InterstitialAd interstitial;
	private static final String AD_UNIT_ID = "ca-app-pub-5892109117152956/3638174425";

	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		interstitial = new InterstitialAd(this);
		interstitial.setAdUnitId(AD_UNIT_ID);

		// Create ad request.
		AdRequest adRequest = new AdRequest.Builder().addTestDevice("381853A2F9EC0A98").build();

		// Begin loading your interstitial.
		interstitial.loadAd(adRequest);

		_appActiviy = this;

	}
	
//	public String takeScreenshot() {
//		View rootView = this.getCurrentFocus();
//		rootView.setVisibility(View.VISIBLE);
//		rootView.setDrawingCacheEnabled(true);
//		Bitmap bitmap = rootView.getDrawingCache();
//		
//		File imagePath = new File(Environment.getExternalStorageDirectory() + "/screenshot.png");
//		FileOutputStream fos;
//
//		try {
//			fos = new FileOutputStream(imagePath);
//			bitmap.compress(CompressFormat.PNG, 100, fos);
//			fos.flush();
//			fos.close();
//		} catch (FileNotFoundException e) {
//			Log.e("GREC", e.getMessage(), e);
//		} catch (IOException e) {
//			Log.e("GREC", e.getMessage(), e);
//		}
//
//		return imagePath.getAbsolutePath();
//	}
	
	public static void share(String path, String msg) {
		Uri screenshotUri = Uri.parse(path); 
		
		Intent intent = new Intent(Intent.ACTION_SEND);
		intent.setType("image/png"); 
		intent.putExtra(Intent.EXTRA_STREAM, screenshotUri);
		intent.putExtra(Intent.EXTRA_TEXT, msg);
		
		_appActiviy.startActivity(Intent.createChooser(intent, "Share"));
	}
	
	public static Integer rateDialog() {
		boolean should = RateThisApp.shouldShowRateDialog();
		
		_appActiviy.runOnUiThread(new Runnable() {
			
			@Override
			public void run() {
				RateThisApp.showRateDialogIfNeeded(_appActiviy);
			}
		});
		
		//stupid java
		int ret = 0;
		if (should) {
			ret = 1;
		}
		
		return ret;
	}
	
	public static void loadAdmob() {
		_appActiviy.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				if (interstitial.isLoaded()) {
					interstitial.show();
					
					interstitial = new InterstitialAd(_appActiviy);
					interstitial.setAdUnitId(AD_UNIT_ID);

					// Create ad request.
					AdRequest adRequest = new AdRequest.Builder().addTestDevice("381853A2F9EC0A98").build();

					// Begin loading your interstitial.
					interstitial.loadAd(adRequest);

				}
			}
		});
	}


	static {
		System.loadLibrary("hellocpp");
	}
}
