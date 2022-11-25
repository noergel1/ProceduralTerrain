#pragma once

#ifdef VUSE_PLATFORM_WINDOWS

#else
	#error Vuse only supports Windows
#endif

#if VUSE_DEBUG
	#define VUSE_ENABLE_ASSERTS
#endif

#ifdef VUSE_ENABLE_ASSERTS
	#define	VUSE_ASSERT(x, ...) { if(!(x)) { VUSE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define	VUSE_CORE_ASSERT(x, ...) { if(!(x)) { VUSE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define VUSE_ASSERT(x, ...)
	#define VUSE_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)