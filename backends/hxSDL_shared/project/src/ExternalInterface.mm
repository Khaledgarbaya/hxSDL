#ifndef STATIC_LINK
#define IMPLEMENT_API
#endif

#include <hx/CFFI.h>
#include <Foundation/Foundation.h>


static value do_one_thing_native(value hxString)
{
    NSString *string = [NSString stringWithCString:val_get_string(hxString) encoding:NSUTF8StringEncoding];

    string = [NSString stringWithFormat:@"do one thing in %@", string];

    const char* cStr = (const char *)[string UTF8String];
    value haxeString = alloc_string_len(cStr, strlen(cStr));

	return haxeString;
}

DEFINE_PRIM(do_one_thing_native, 1);


extern "C" int sample_ios_register_prims() { return 0; }
