#pragma once

#include "main.h"

class CJavaWrapper
{
public:
    CJavaWrapper(JNIEnv *env, jobject activity);
    ~CJavaWrapper() {};

    void SetUseFullScreen(int b);
    void ShowClientSettings();
    void ShowInputLayout();
    void HideInputLayout();
    const char* GetClipboardString();

    jobject activity;
    jmethodID s_SetUseFullScreen;
    jmethodID s_ShowClientSettings;
    jmethodID s_ShowInputLayout;
    jmethodID s_HideInputLayout;
    jmethodID s_GetKeyboardString;
};