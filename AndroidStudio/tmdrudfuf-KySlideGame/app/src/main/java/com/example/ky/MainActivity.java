package com.example.ky;

import android.os.Bundle;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;
public class MainActivity extends AppCompatActivity {

    private KyView ky;

    @Override
    protected void onCreate(Bundle b) {
        super.onCreate(b);
        ky = new KyView(this);
        setContentView(ky); // Replace "activity_main" with your actual layout file name

    }
}