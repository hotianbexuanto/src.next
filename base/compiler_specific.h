// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_COMPILER_SPECIFIC_H_
#define BASE_COMPILER_SPECIFIC_H_

#include "build/build_config.h"

#if defined(COMPILER_MSVC) && !defined(__clang__)
#error "Only clang-cl is supported on Windows, see https://crbug.com/988071"
#endif

// This is a wrapper around `__has_cpp_attribute`, which can be used to test for
// the presence of an attribute. In case the compiler does not support this
// macro it will simply evaluate to 0.
//
// References:
// https://wg21.link/sd6#testing-for-the-presence-of-an-attribute-__has_cpp_attribute
// https://wg21.link/cpp.cond#:__has_cpp_attribute
#if defined(__has_cpp_attribute)
#define HAS_CPP_ATTRIBUTE(x) __has_cpp_attribute(x)
#else
#define HAS_CPP_ATTRIBUTE(x) 0
#endif

// A wrapper around `__has_builtin`, similar to HAS_CPP_ATTRIBUTE.
#if defined(__has_builtin)
#define HAS_BUILTIN(x) __has_builtin(x)
#else
#define HAS_BUILTIN(x) 0
#endif

// Annotate a variable indicating it's ok if the variable is not used.
// (Typically used to silence a compiler warning when the assignment
// is important for some other reason.)
// Use like:
//   int x = ...;
//   ALLOW_UNUSED_LOCAL(x);
#define ALLOW_UNUSED_LOCAL(x) (void)x

// Annotate a typedef or function indicating it's ok if it's not used.
// Use like:
//   typedef Foo Bar ALLOW_UNUSED_TYPE;
#if defined(COMPILER_GCC) || defined(__clang__)
#define ALLOW_UNUSED_TYPE __attribute__((unused))
#else
#define ALLOW_UNUSED_TYPE
#endif

// Annotate a function indicating it should not be inlined.
// Use like:
//   NOINLINE void DoStuff() { ... }
#if defined(COMPILER_GCC)
#define NOINLINE __attribute__((noinline))
#elif defined(COMPILER_MSVC)
#define NOINLINE __declspec(noinline)
#else
#define NOINLINE
#endif

#if defined(COMPILER_GCC) && defined(NDEBUG)
#define ALWAYS_INLINE inline __attribute__((__always_inline__))
#elif defined(COMPILER_MSVC) && defined(NDEBUG)
#define ALWAYS_INLINE __forceinline
#else
#define ALWAYS_INLINE inline
#endif

// Annotate a function indicating it should never be tail called. Useful to make
// sure callers of the annotated function are never omitted from call-stacks.
// To provide the complementary behavior (prevent the annotated function from
// being omitted) look at NOINLINE. Also note that this doesn't prevent code
// folding of multiple identical caller functions into a single signature. To
// prevent code folding, see NO_CODE_FOLDING() in base/debug/alias.h.
// Use like:
//   void NOT_TAIL_CALLED FooBar();
#if defined(__clang__) && __has_attribute(not_tail_called)
#define NOT_TAIL_CALLED __attribute__((not_tail_called))
#else
#define NOT_TAIL_CALLED
#endif

// Specify memory alignment for structs, classes, etc.
// Use like:
//   class ALIGNAS(16) MyClass { ... }
//   ALIGNAS(16) int array[4];
//
// In most places you can use the C++11 keyword "alignas", which is preferred.
//
// But compilers have trouble mixing __attribute__((...)) syntax with
// alignas(...) syntax.
//
// Doesn't work in clang or gcc:
//   struct alignas(16) __attribute__((packed)) S { char c; };
// Works in clang but not gcc:
//   struct __attribute__((packed)) alignas(16) S2 { char c; };
// Works in clang and gcc:
//   struct alignas(16) S3 { char c; } __attribute__((packed));
//
// There are also some attributes that must be specified *before* a class
// definition: visibility (used for exporting functions/classes) is one of
// these attributes. This means that it is not possible to use alignas() with a
// class that is marked as exported.
#if defined(COMPILER_MSVC)
#define ALIGNAS(byte_alignment) __declspec(align(byte_alignment))
#elif defined(COMPILER_GCC)
#define ALIGNAS(byte_alignment) __attribute__((aligned(byte_alignment)))
#endif

// Annotate a function indicating the caller must examine the return value.
// Use like:
//   int foo() WARN_UNUSED_RESULT;
// To explicitly ignore a result, see |ignore_result()| in base/macros.h.
#undef WARN_UNUSED_RESULT
#if defined(COMPILER_GCC) || defined(__clang__)
#define WARN_UNUSED_RESULT __attribute__((warn_unused_result))
#else
#define WARN_UNUSED_RESULT
#endif

// In case the compiler supports it NO_UNIQUE_ADDRESS evaluates to the C++20
// attribute [[no_unique_address]]. This allows annotating data members so that
// they need not have an address distinct from all other non-static data members
// of its class.
//
// References:
// * https://en.cppreference.com/w/cpp/language/attributes/no_unique_address
// * https://wg21.link/dcl.attr.nouniqueaddr
#if HAS_CPP_ATTRIBUTE(no_unique_address)
#define NO_UNIQUE_ADDRESS [[no_unique_address]]
#else
#define NO_UNIQUE_ADDRESS
#endif

// Tell the compiler a function is using a printf-style format string.
// |format_param| is the one-based index of the format string parameter;
// |dots_param| is the one-based index of the "..." parameter.
// For v*printf functions (which take a va_list), pass 0 for dots_param.
// (This is undocumented but matches what the system C headers do.)
// For member functions, the implicit this parameter counts as index 1.
#if defined(COMPILER_GCC) || defined(__clang__)
#define PRINTF_FORMAT(format_param, dots_param) \
  __attribute__((format(printf, format_param, dots_param)))
#else
#define PRINTF_FORMAT(format_param, dots_param)
#endif

// WPRINTF_FORMAT is the same, but for wide format strings.
// This doesn't appear to yet be implemented in any compiler.
// See http://gcc.gnu.org/bugzilla/show_bug.cgi?id=38308 .
#define WPRINTF_FORMAT(format_param, dots_param)
// If available, it would look like:
//   __attribute__((format(wprintf, format_param, dots_param)))

// Sanitizers annotations.
#if defined(__has_attribute)
#if __has_attribute(no_sanitize)
#define NO_SANITIZE(what) __attribute__((no_sanitize(what)))
#endif
#endif
#if !defined(NO_SANITIZE)
#define NO_SANITIZE(what)
#endif

// MemorySanitizer annotations.
#if defined(MEMORY_SANITIZER) && !defined(OS_NACL)
#include <sanitizer/msan_interface.h>

// Mark a memory region fully initialized.
// Use this to annotate code that deliberately reads uninitialized data, for
// example a GC scavenging root set pointers from the stack.
#define MSAN_UNPOISON(p, size) __msan_unpoison(p, size)

// Check a memory region for initializedness, as if it was being used here.
// If any bits are uninitialized, crash with an MSan report.
// Use this to sanitize data which MSan won't be able to track, e.g. before
// passing data to another process via shared memory.
#define MSAN_CHECK_MEM_IS_INITIALIZED(p, size) \
  __msan_check_mem_is_initialized(p, size)
#else  // MEMORY_SANITIZER
#define MSAN_UNPOISON(p, size)
#define MSAN_CHECK_MEM_IS_INITIALIZED(p, size)
#endif  // MEMORY_SANITIZER

// DISABLE_CFI_PERF -- Disable Control Flow Integrity for perf reasons.
#if !defined(DISABLE_CFI_PERF)
#if defined(__clang__) && defined(OFFICIAL_BUILD)
#define DISABLE_CFI_PERF __attribute__((no_sanitize("cfi")))
#else
#define DISABLE_CFI_PERF
#endif
#endif

// DISABLE_CFI_ICALL -- Disable Control Flow Integrity indirect call checks.
#if !defined(DISABLE_CFI_ICALL)
#if defined(OS_WIN)
// Windows also needs __declspec(guard(nocf)).
#define DISABLE_CFI_ICALL NO_SANITIZE("cfi-icall") __declspec(guard(nocf))
#else
#define DISABLE_CFI_ICALL NO_SANITIZE("cfi-icall")
#endif
#endif
#if !defined(DISABLE_CFI_ICALL)
#define DISABLE_CFI_ICALL
#endif

// Macro useful for writing cross-platform function pointers.
#if !defined(CDECL)
#if defined(OS_WIN)
#define CDECL __cdecl
#else  // defined(OS_WIN)
#define CDECL
#endif  // defined(OS_WIN)
#endif  // !defined(CDECL)

// Macro for hinting that an expression is likely to be false.
#if !defined(UNLIKELY)
#if defined(COMPILER_GCC) || defined(__clang__)
#define UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
#define UNLIKELY(x) (x)
#endif  // defined(COMPILER_GCC)
#endif  // !defined(UNLIKELY)

#if !defined(LIKELY)
#if defined(COMPILER_GCC) || defined(__clang__)
#define LIKELY(x) __builtin_expect(!!(x), 1)
#else
#define LIKELY(x) (x)
#endif  // defined(COMPILER_GCC)
#endif  // !defined(LIKELY)

// Compiler feature-detection.
// clang.llvm.org/docs/LanguageExtensions.html#has-feature-and-has-extension
#if defined(__has_feature)
#define HAS_FEATURE(FEATURE) __has_feature(FEATURE)
#else
#define HAS_FEATURE(FEATURE) 0
#endif

<<<<<<< HEAD
// Annotates a function indicating it should not be inlined.
//
// You may also want `NOOPT` if your goal is to preserve a function call even
// for the most trivial cases; see
// https://stackoverflow.com/questions/54481855/clang-ignoring-attribute-noinline/54482070#54482070.
//
// See also:
//   https://clang.llvm.org/docs/AttributeReference.html#noinline
//
// Usage:
// ```
//   NOINLINE void Func() {
//     // This body will not be inlined into callers.
//   }
// ```
#if __has_cpp_attribute(clang::noinline)
#define NOINLINE [[clang::noinline]]
#elif __has_cpp_attribute(gnu::noinline)
#define NOINLINE [[gnu::noinline]]
#elif __has_cpp_attribute(msvc::noinline)
#define NOINLINE [[msvc::noinline]]
=======
// Macro for telling -Wimplicit-fallthrough that a fallthrough is intentional.
#if defined(__clang__)
#define FALLTHROUGH [[clang::fallthrough]]
>>>>>>> chromium
#else
#define FALLTHROUGH
#endif

<<<<<<< HEAD
// Annotates a call site indicating that the callee should not be inlined.
//
// See also:
//   https://clang.llvm.org/docs/AttributeReference.html#noinline
//
// Usage:
// ```
//   void Func() {
//      // This specific call to `DoSomething` should not be inlined.
//      NOINLINE_CALL DoSomething();
//   }
// ```
#if __has_cpp_attribute(clang::noinline)
#define NOINLINE_CALL [[clang::noinline]]
#else
#define NOINLINE_CALL
#endif

// Annotates a function indicating it should not be optimized.
//
// See also:
//   https://clang.llvm.org/docs/AttributeReference.html#optnone
//   https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#index-optimize-function-attribute
//
// Usage:
// ```
//   NOOPT void Func() {
//     // This body will not be optimized.
//   }
// ```
#if __has_cpp_attribute(clang::optnone)
#define NOOPT [[clang::optnone]]
#elif __has_cpp_attribute(gnu::optimize)
#define NOOPT [[gnu::optimize(0)]]
#else
#define NOOPT
#endif

// Annotates a function indicating it should always be inlined.
//
// See also:
//   https://clang.llvm.org/docs/AttributeReference.html#always-inline-force-inline
//
// Usage:
// ```
//   ALWAYS_INLINE void Func() {
//     // This body will be inlined into callers whenever possible.
//   }
// ```
//
// Since `ALWAYS_INLINE` is performance-oriented but can hamper debugging,
// ignore it in debug mode.
#if defined(NDEBUG)
#if __has_cpp_attribute(clang::always_inline)
#define ALWAYS_INLINE [[clang::always_inline]] inline
#elif __has_cpp_attribute(gnu::always_inline)
#define ALWAYS_INLINE [[gnu::always_inline]] inline
#elif defined(COMPILER_MSVC)
#define ALWAYS_INLINE __forceinline
#endif
#endif
#if !defined(ALWAYS_INLINE)
#define ALWAYS_INLINE inline
#endif

// Annotates a call site indicating the calee should always be inlined.
//
// See also:
//   https://clang.llvm.org/docs/AttributeReference.html#always-inline-force-inline
//
// Usage:
// ```
//   void Func() {
//     // This specific call will be inlined if possible.
//     ALWAYS_INLINE_CALL DoSomething();
//   }
// ```
//
// Since `ALWAYS_INLINE_CALL` is performance-oriented but can hamper debugging,
// ignore it in debug mode.
#if defined(NDEBUG)
#if __has_cpp_attribute(clang::always_inline)
#define ALWAYS_INLINE_CALL [[clang::always_inline]]
#endif
#endif
#if !defined(ALWAYS_INLINE_CALL)
#define ALWAYS_INLINE_CALL
#endif

// Annotates a function indicating it should never be tail called. Useful to
// make sure callers of the annotated function are never omitted from call
// stacks. Often useful with `NOINLINE` to make sure the function itself is also
// not omitted from call stacks. Note: this does not prevent code folding of
// multiple identical callers into a single signature; to do that, see
// `NO_CODE_FOLDING()` in base/debug/alias.h.
//
// For a caller-side version of this, see `DISABLE_TAIL_CALLS`.
//
// See also:
//   https://clang.llvm.org/docs/AttributeReference.html#not-tail-called
//
// Usage:
// ```
//   // Calls to this function will not be tail calls.
//   NOT_TAIL_CALLED void Func();
// ```
#if __has_cpp_attribute(clang::not_tail_called)
#define NOT_TAIL_CALLED [[clang::not_tail_called]]
#else
#define NOT_TAIL_CALLED
#endif

// Annotates a return statement indicating the compiler must convert it to a
// tail call. Can be used only on return statements, even for functions
// returning void. Caller and callee must have the same number of arguments and
// the argument types must be "similar". While the compiler may automatically
// convert compatible calls to tail calls when optimizing, this annotation
// requires it to occur if doing so is valid, and will not compile otherwise.
//
// See also:
//   https://clang.llvm.org/docs/AttributeReference.html#musttail
//
// Usage:
// ```
//   int Func1(double);
//   int Func2(double d) {
//     MUSTTAIL return Func1(d + 1);  // `Func1()` will be tail-called.
//   }
// ```
#if __has_cpp_attribute(clang::musttail)
#define MUSTTAIL [[clang::musttail]]
#else
#define MUSTTAIL
#endif

// Annotates a data member indicating it need not have an address distinct from
// all other non-static data members of the class, and its tail padding may be
// used for other objects' storage. This can have subtle and dangerous effects,
// including on containing objects; use with caution.
//
// See also:
//   https://en.cppreference.com/w/cpp/language/attributes/no_unique_address
//   https://wg21.link/dcl.attr.nouniqueaddr
// Usage:
// ```
//   // In the following struct, `t` might not have a unique address from `i`,
//   // and `t`'s tail padding (if any) may be reused by subsequent objects.
//   struct S {
//     int i;
//     NO_UNIQUE_ADDRESS T t;
//   };
// ```
//
// Unfortunately MSVC ignores [[no_unique_address]] (see
// https://devblogs.microsoft.com/cppblog/msvc-cpp20-and-the-std-cpp20-switch/#msvc-extensions-and-abi),
// and clang-cl matches it for ABI compatibility reasons. We need to prefer
// [[msvc::no_unique_address]] when available if we actually want any effect.
#if __has_cpp_attribute(msvc::no_unique_address)
#define NO_UNIQUE_ADDRESS [[msvc::no_unique_address]]
#elif __has_cpp_attribute(no_unique_address)
#define NO_UNIQUE_ADDRESS [[no_unique_address]]
#else
#define NO_UNIQUE_ADDRESS
#endif

// Annotates a function indicating it takes a `printf()`-style format string.
// The compiler will check that the provided arguments match the type specifiers
// in the format string. Useful to detect mismatched format strings/args.
//
// `format_param` is the one-based index of the format string parameter;
// `dots_param` is the one-based index of the "..." parameter.
// For `v*printf()` functions (which take a `va_list`), `dots_param` should be
// 0. For member functions, the implicit `this` parameter is at index 1.
//
// See also:
//   https://clang.llvm.org/docs/AttributeReference.html#format
//   https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#index-format-function-attribute
//
// Usage:
// ```
//   PRINTF_FORMAT(1, 2)
//   void Print(const char* format, ...);
//   void Func() {
//     // The following call will not compile; diagnosed as format and argument
//     // types mismatching.
//     Print("%s", 1);
//   }
// ```
#if __has_cpp_attribute(gnu::format)
#define PRINTF_FORMAT(format_param, dots_param) \
  [[gnu::format(printf, format_param, dots_param)]]
#else
#define PRINTF_FORMAT(format_param, dots_param)
#endif

// Annotates a function disabling the named sanitizer within its body.
//
// See also:
//   https://clang.llvm.org/docs/AttributeReference.html#no-sanitize
//   https://clang.llvm.org/docs/UsersManual.html#controlling-code-generation
//
// Usage:
// ```
//   NO_SANITIZE("cfi-icall") void Func() {
//     // CFI indirect call checks will not be performed in this body.
//   }
// ```
#if __has_cpp_attribute(clang::no_sanitize)
#define NO_SANITIZE(sanitizer) [[clang::no_sanitize(sanitizer)]]
#else
#define NO_SANITIZE(sanitizer)
#endif

// Annotates a pointer and size directing MSAN to treat that memory region as
// fully initialized. Useful for e.g. code that deliberately reads uninitialized
// data, such as a GC scavenging root set pointers from the stack.
//
// See also:
//   https://github.com/google/sanitizers/wiki/MemorySanitizer
//
// Usage:
// ```
//   T* ptr = ...;
//   // After the next statement, MSAN will assume `ptr` points to an
//   // initialized `T`.
//   MSAN_UNPOISON(ptr, sizeof(T));
// ```
#if defined(MEMORY_SANITIZER) && !BUILDFLAG(IS_NACL)
#include <sanitizer/msan_interface.h>
#define MSAN_UNPOISON(p, size) __msan_unpoison(p, size)
#else
#define MSAN_UNPOISON(p, size)
#endif

// Annotates a pointer and size directing MSAN to check whether that memory
// region is initialized, as if it was being read from. If any bits are
// uninitialized, crashes with an MSAN report. Useful for e.g. sanitizing data
// MSAN won't be able to track, such as data that is about to be passed to
// another process via shared memory.
//
// See also:
//   https://www.chromium.org/developers/testing/memorysanitizer/#debugging-msan-reports
//
// Usage:
// ```
//   T* ptr = ...;
//   // The following line will crash at runtime in MSAN builds if `ptr` does
//   // not point to an initialized `T`.
//   MSAN_CHECK_MEM_IS_INITIALIZED(ptr, sizeof(T));
// ```
#if defined(MEMORY_SANITIZER) && !BUILDFLAG(IS_NACL)
#define MSAN_CHECK_MEM_IS_INITIALIZED(p, size) \
  __msan_check_mem_is_initialized(p, size)
#else
#define MSAN_CHECK_MEM_IS_INITIALIZED(p, size)
#endif

// Annotates a function disabling Control Flow Integrity checks due to perf
// impact.
//
// See also:
//   https://clang.llvm.org/docs/ControlFlowIntegrity.html#performance
//   https://www.chromium.org/developers/testing/control-flow-integrity/#overhead-only-tested-on-x64
//
// Usage:
// ```
//   DISABLE_CFI_PERF void Func() {
//     // CFI checks will not be performed in this body, due to perf reasons.
//   }
// ```
#if !defined(DISABLE_CFI_PERF)
#if defined(__clang__) && defined(OFFICIAL_BUILD)
#define DISABLE_CFI_PERF NO_SANITIZE("cfi")
#else
#define DISABLE_CFI_PERF
#endif
#endif

// Annotates a function disabling Control Flow Integrity indirect call checks.
// NOTE: Prefer `DISABLE_CFI_DLSYM()` if you just need to allow calling of dlsym
// functions.
//
// See also:
//   https://clang.llvm.org/docs/ControlFlowIntegrity.html#available-schemes
//   https://www.chromium.org/developers/testing/control-flow-integrity/#indirect-call-failures
//
// Usage:
// ```
//   DISABLE_CFI_ICALL void Func() {
//     // CFI indirect call checks will not be performed in this body.
//   }
// ```
#if !defined(DISABLE_CFI_ICALL)
#if BUILDFLAG(IS_WIN)
#define DISABLE_CFI_ICALL NO_SANITIZE("cfi-icall") __declspec(guard(nocf))
#else
#define DISABLE_CFI_ICALL NO_SANITIZE("cfi-icall")
#endif
#endif

// Annotates a function disabling Control Flow Integrity indirect call checks if
// doing so is necessary to call dlsym functions. The checks are retained on
// platforms where loaded modules participate in CFI (viz. Windows).
//
// See also:
//   https://www.chromium.org/developers/testing/control-flow-integrity/#indirect-call-failures
//
// Usage:
// ```
//   DISABLE_CFI_DLSYM void Func() {
//     // On non-Windows platforms, CFI indirect call checks will not be
//     // performed in this body.
//   }
// ```
#if !defined(DISABLE_CFI_DLSYM)
#if BUILDFLAG(IS_WIN)
#define DISABLE_CFI_DLSYM
#else
#define DISABLE_CFI_DLSYM DISABLE_CFI_ICALL
#endif
#endif

// Evaluates to a string constant containing the function signature.
//
// See also:
//   https://clang.llvm.org/docs/LanguageExtensions.html#source-location-builtins
//   https://en.cppreference.com/w/c/language/function_definition#func
//
// Usage:
// ```
//   void Func(int arg) {
//     std::cout << PRETTY_FUNCTION;  // Prints `void Func(int)` or similar.
//   }
// ```
=======
>>>>>>> chromium
#if defined(COMPILER_GCC)
#define PRETTY_FUNCTION __PRETTY_FUNCTION__
#elif defined(COMPILER_MSVC)
#define PRETTY_FUNCTION __FUNCSIG__
#else
// See https://en.cppreference.com/w/c/language/function_definition#func
#define PRETTY_FUNCTION __func__
#endif

#if !defined(CPU_ARM_NEON)
#if defined(__arm__)
#if !defined(__ARMEB__) && !defined(__ARM_EABI__) && !defined(__EABI__) && \
    !defined(__VFP_FP__) && !defined(_WIN32_WCE) && !defined(ANDROID)
#error Chromium does not support middle endian architecture
#endif
#if defined(__ARM_NEON__)
#define CPU_ARM_NEON 1
#endif
#endif  // defined(__arm__)
#endif  // !defined(CPU_ARM_NEON)

#if !defined(HAVE_MIPS_MSA_INTRINSICS)
#if defined(__mips_msa) && defined(__mips_isa_rev) && (__mips_isa_rev >= 5)
#define HAVE_MIPS_MSA_INTRINSICS 1
#endif
#endif

#if defined(__clang__) && __has_attribute(uninitialized)
// Attribute "uninitialized" disables -ftrivial-auto-var-init=pattern for
// the specified variable.
// Library-wide alternative is
// 'configs -= [ "//build/config/compiler:default_init_stack_vars" ]' in .gn
// file.
//
// See "init_stack_vars" in build/config/compiler/BUILD.gn and
// http://crbug.com/977230
// "init_stack_vars" is enabled for non-official builds and we hope to enable it
// in official build in 2020 as well. The flag writes fixed pattern into
// uninitialized parts of all local variables. In rare cases such initialization
// is undesirable and attribute can be used:
//   1. Degraded performance
// In most cases compiler is able to remove additional stores. E.g. if memory is
// never accessed or properly initialized later. Preserved stores mostly will
// not affect program performance. However if compiler failed on some
// performance critical code we can get a visible regression in a benchmark.
//   2. memset, memcpy calls
// Compiler may replaces some memory writes with memset or memcpy calls. This is
// not -ftrivial-auto-var-init specific, but it can happen more likely with the
// flag. It can be a problem if code is not linked with C run-time library.
//
// Note: The flag is security risk mitigation feature. So in future the
// attribute uses should be avoided when possible. However to enable this
// mitigation on the most of the code we need to be less strict now and minimize
// number of exceptions later. So if in doubt feel free to use attribute, but
// please document the problem for someone who is going to cleanup it later.
// E.g. platform, bot, benchmark or test name in patch description or next to
// the attribute.
#define STACK_UNINITIALIZED __attribute__((uninitialized))
#else
#define STACK_UNINITIALIZED
#endif

// The ANALYZER_ASSUME_TRUE(bool arg) macro adds compiler-specific hints
// to Clang which control what code paths are statically analyzed,
// and is meant to be used in conjunction with assert & assert-like functions.
// The expression is passed straight through if analysis isn't enabled.
//
// ANALYZER_SKIP_THIS_PATH() suppresses static analysis for the current
// codepath and any other branching codepaths that might follow.
#if defined(__clang_analyzer__)

inline constexpr bool AnalyzerNoReturn() __attribute__((analyzer_noreturn)) {
  return false;
}

inline constexpr bool AnalyzerAssumeTrue(bool arg) {
  // AnalyzerNoReturn() is invoked and analysis is terminated if |arg| is
  // false.
  return arg || AnalyzerNoReturn();
}

#define ANALYZER_ASSUME_TRUE(arg) ::AnalyzerAssumeTrue(!!(arg))
#define ANALYZER_SKIP_THIS_PATH() static_cast<void>(::AnalyzerNoReturn())
#define ANALYZER_ALLOW_UNUSED(var) static_cast<void>(var);

#else  // !defined(__clang_analyzer__)

#define ANALYZER_ASSUME_TRUE(arg) (arg)
#define ANALYZER_SKIP_THIS_PATH()
#define ANALYZER_ALLOW_UNUSED(var) static_cast<void>(var);

#endif  // defined(__clang_analyzer__)

// Use nomerge attribute to disable optimization of merging multiple same calls.
#if defined(__clang__) && __has_attribute(nomerge)
#define NOMERGE [[clang::nomerge]]
#else
#define NOMERGE
#endif

// Marks a type as being eligible for the "trivial" ABI despite having a
// non-trivial destructor or copy/move constructor. Such types can be relocated
// after construction by simply copying their memory, which makes them eligible
// to be passed in registers. The canonical example is std::unique_ptr.
//
// Use with caution; this has some subtle effects on constructor/destructor
// ordering and will be very incorrect if the type relies on its address
// remaining constant. When used as a function argument (by value), the value
// may be constructed in the caller's stack frame, passed in a register, and
// then used and destructed in the callee's stack frame. A similar thing can
// occur when values are returned.
//
// TRIVIAL_ABI is not needed for types which have a trivial destructor and
// copy/move constructors, such as base::TimeTicks and other POD.
//
// It is also not likely to be effective on types too large to be passed in one
// or two registers on typical target ABIs.
//
// See also:
//   https://clang.llvm.org/docs/AttributeReference.html#trivial-abi
//   https://libcxx.llvm.org/docs/DesignDocs/UniquePtrTrivialAbi.html
#if defined(__clang__) && __has_attribute(trivial_abi)
#define TRIVIAL_ABI [[clang::trivial_abi]]
#else
#define TRIVIAL_ABI
#endif

// Marks a member function as reinitializing a moved-from variable.
// See also
// https://clang.llvm.org/extra/clang-tidy/checks/bugprone-use-after-move.html#reinitialization
#if defined(__clang__) && __has_attribute(reinitializes)
#define REINITIALIZES_AFTER_MOVE [[clang::reinitializes]]
#else
#define REINITIALIZES_AFTER_MOVE
#endif

// Requires constant initialization. See constinit in C++20. Allows to rely on a
// variable being initialized before execution, and not requiring a global
// constructor.
#if defined(__has_attribute)
#if __has_attribute(require_constant_initialization)
#define CONSTINIT __attribute__((require_constant_initialization))
#endif
#endif
#if !defined(CONSTINIT)
#define CONSTINIT
#endif

#endif  // BASE_COMPILER_SPECIFIC_H_
