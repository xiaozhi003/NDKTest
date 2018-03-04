package com.xiaozhi.jni1;

import android.content.Context;

/**
 * Created by wangzhi on 2017/9/2.
 */
public class JniTest {

  public static native long getStringFromJni();

  public static native String getStringFromJni(long p);

  public static native String getPackagenameFromJni(Context context);
}
