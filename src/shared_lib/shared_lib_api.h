#ifndef _SHARED_LIB_API_H_
#define _SHARED_LIB_API_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifndef _VISIBILITY_DEFAULT_
#ifdef _MSC_VER
#define _VISIBILITY_DEFAULT_
#else
#define _VISIBILITY_DEFAULT_ __attribute__((visibility("default")))
#endif // !_MSC_VER
#endif // !_VISIBILITY_DEFAULT_

    void _VISIBILITY_DEFAULT_ shared_library_say(const char* what);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !_SHARED_LIB_API_H_