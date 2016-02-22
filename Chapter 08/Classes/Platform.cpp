#include "Platform.h"
#include "platform/android/jni/JniHelper.h"

#define CLASS_NAME "org/cocos2dx/cpp/AppActivity"

USING_NS_CC;

const char* Platform::getAppVersion()
{
    JniMethodInfo t;
    const char* ret = NULL;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getAppVersionInJava", "()Ljava/lang/String;")) {
        jstring jstr = (jstring)t.env->CallStaticObjectMethod(t.classID,t.methodID);
        std::string sstr = JniHelper::jstring2string(jstr);
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(jstr);
        ret = sstr.c_str();
    }
    return ret;
}