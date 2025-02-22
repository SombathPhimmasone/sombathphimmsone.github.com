#include "jniutil.h"

CJavaWrapper::CJavaWrapper(JNIEnv *env, jobject activity)
{
    this->activity = env->NewGlobalRef(activity);

    jclass clas = env->GetObjectClass(activity);
    this->s_SetUseFullScreen = env->GetMethodID(clas, "setUseFullscreen", "(I)V");
    this->s_ShowClientSettings = env->GetMethodID(clas, "showClientSettings", "()V");
    this->s_ShowInputLayout = env->GetMethodID(clas, "showInputLayout", "()V");
    this->s_HideInputLayout = env->GetMethodID(clas, "hideInputLayout", "()V");
    this->s_GetKeyboardString = env->GetMethodID(clas, "getClipboardText", "()[B");
    env->DeleteLocalRef((jobject)clas);
    Log("nvEventClass null");
}

void CJavaWrapper::SetUseFullScreen(int b)
{
    JNIEnv* p;
    CMain::javaVM->GetEnv((void**)&p, JNI_VERSION_1_6);
    p->CallVoidMethod(this->activity, this->s_SetUseFullScreen, b);
}

void CJavaWrapper::ShowClientSettings()
{
    JNIEnv* p;
    CMain::javaVM->GetEnv((void**)&p, JNI_VERSION_1_6);
    p->CallVoidMethod(this->activity, this->s_ShowClientSettings);
}

void CJavaWrapper::ShowInputLayout()
{
    JNIEnv* p;
    CMain::javaVM->GetEnv((void**)&p, JNI_VERSION_1_6);
    p->CallVoidMethod(this->activity, this->s_ShowInputLayout);
}

void CJavaWrapper::HideInputLayout()
{
    JNIEnv* p;
    CMain::javaVM->GetEnv((void**)&p, JNI_VERSION_1_6);
    p->CallVoidMethod(this->activity, this->s_HideInputLayout);
}

const char* CJavaWrapper::GetClipboardString()
{
    JNIEnv* p;
    CMain::javaVM->GetEnv((void**)&p, JNI_VERSION_1_6);
    jstring res =  static_cast<jstring>(p->CallObjectMethod(this->activity, this->s_GetKeyboardString));
    jboolean iscopy;
    const char *tempString = p->GetStringUTFChars(res, &iscopy);
    if(iscopy == JNI_TRUE) p->ReleaseStringUTFChars(res, tempString);
    p->DeleteLocalRef(res);

    return tempString;
}