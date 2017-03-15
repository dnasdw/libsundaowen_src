#ifndef LIBSUNDAOWEN_SDW_PLATFORM_H_
#define LIBSUNDAOWEN_SDW_PLATFORM_H_

#define SDW_COMPILER_MSC   1
#define SDW_COMPILER_GNUC  2
#define SDW_COMPILER_CLANG 3

#if defined(_MSC_VER)
#define SDW_COMPILER SDW_COMPILER_MSC
#define SDW_COMPILER_VERSION _MSC_VER
#elif defined(__clang__)
#define SDW_COMPILER SDW_COMPILER_CLANG
#define SDW_COMPILER_VERSION (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)
#elif defined(__GNUC__)
#define SDW_COMPILER SDW_COMPILER_GNUC
#define SDW_COMPILER_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#else
#error "compiler no support"
#endif

#define SDW_PLATFORM_WINDOWS 1
#define SDW_PLATFORM_LINUX   2
#define SDW_PLATFORM_MACOS   3
#define SDW_PLATFORM_CYGWIN  4

#if defined(_WIN32)
#define SDW_PLATFORM SDW_PLATFORM_WINDOWS
#elif defined(__APPLE__)
#define SDW_PLATFORM SDW_PLATFORM_MACOS
#elif defined(__linux__)
#define SDW_PLATFORM SDW_PLATFORM_LINUX
#elif defined(__CYGWIN__)
#define SDW_PLATFORM SDW_PLATFORM_CYGWIN
#else
#error "platform no support"
#endif

#if SDW_COMPILER == SDW_COMPILER_MSC
#define SDW_MSC_PUSH_PACKED <pshpack1.h>
#define SDW_MSC_POP_PACKED <poppack.h>
#define SDW_GNUC_PACKED
#else
#define SDW_MSC_PUSH_PACKED <cstdlib>
#define SDW_MSC_POP_PACKED <cstdlib>
#define SDW_GNUC_PACKED __attribute__((packed))
#endif

#endif	// LIBSUNDAOWEN_SDW_PLATFORM_H_
