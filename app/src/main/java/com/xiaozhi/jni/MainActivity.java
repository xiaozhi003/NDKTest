package com.xiaozhi.jni;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

  // Used to load the 'native-lib' library on application startup.
  static {
    System.loadLibrary("native-lib");
  }

  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_main);

    // Example of a call to a native method
    TextView tv = (TextView) findViewById(R.id.sample_text);

    long p = JniTest.getStringFromJni();

    tv.setText(JniTest.getStringFromJni(p) + "\n");

    // 获取包名
    tv.append(JniTest.getPackagenameFromJni(this) + "\n");
  }
}
