#include "Platform.h"

const char* Platform::getAppVersion()
{
    NSDictionary* info = [[NSBundle mainBundle] infoDictionary];
    NSString* version = [info objectForKey:(NSString*)kCFBundleVersionKey];
    if (version) {
        return [version UTF8String];
    }
    return nullptr;
}