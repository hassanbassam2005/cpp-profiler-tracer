#pragma once
#include "config.hpp"
#include "scope.hpp"

#if PROFILER_ENABLED

#define PROFILER_JOIN_IMPL(a,b) a##b
#define PROFILER_JOIN(a,b) PROFILER_JOIN_IMPL(a,b)

/**
 * @brief Profiles a named scope.
 */
#define PROFILE_SCOPE(name) ::profiler::Scope PROFILER_JOIN(_prof_scope_, __LINE__)(name)

 /**
  * @brief Profiles the current function scope.
  */
#if defined(_MSC_VER)
#define PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCSIG__)
#else
#define PROFILE_FUNCTION() PROFILE_SCOPE(__PRETTY_FUNCTION__)
#endif

#else

#define PROFILE_SCOPE(name)    ((void)0)
#define PROFILE_FUNCTION()     ((void)0)

#endif
