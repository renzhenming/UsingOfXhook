package com.rzm.myxhook;

public class Hook {

    static {
        System.loadLibrary("xhook");
    }

    public native void hook();
}
