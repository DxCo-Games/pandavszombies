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

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.annotation.TargetApi;
import android.graphics.Color;
import android.graphics.Point;
import android.os.Build;
import android.os.Bundle;
import android.view.Display;
import android.view.View;
import android.view.WindowManager;
import android.widget.LinearLayout;

import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdView;
import com.google.android.gms.ads.InterstitialAd;
import com.revmob.cocos2dx.RevMobWrapper;

public class CppConnectorActivity extends Cocos2dxActivity {

	private static CppConnectorActivity _appActiviy;
	private AdView adView;
	private static InterstitialAd interstitial;
	private static final String AD_UNIT_ID = "ca-app-pub-5892109117152956/3638174425";

	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		RevMobWrapper.setActivity(this);

		interstitial = new InterstitialAd(this);
		interstitial.setAdUnitId(AD_UNIT_ID);

		// Create ad request.
		AdRequest adRequest = new AdRequest.Builder().addTestDevice("381853A2F9EC0A98").build();

		// Begin loading your interstitial.
		interstitial.loadAd(adRequest);

		_appActiviy = this;

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
