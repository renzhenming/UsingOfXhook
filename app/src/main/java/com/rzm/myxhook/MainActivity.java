package com.rzm.myxhook;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;

public class MainActivity extends AppCompatActivity {


    private Hook threadHook;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        threadHook = new Hook();
        threadHook.hook();
    }

    public void create(View view) {
        for (int i = 0; i < 10; i++) {
            Thread thread = new Thread();
            thread.start();
        }
    }

    public void open(View view) {
        File file = new File("/sdcard/audio.pcm");
        try {
            FileInputStream fis = new FileInputStream(file);
            int read = fis.read();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
        System.out.println("file is open");
    }
}