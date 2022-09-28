/*
 * plasma_attr - portability macros for compiler-specific code attributes
 *
 * Copyright (c) 2010, Glue Logic LLC. All rights reserved. code()gluelogic.com
 *
 *  This file is part of plasma.
 *
 *  plasma is free software: you can redistribute it and/or modify it under
 *  the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 2.1 of the License, or
 *  (at your option) any later version.
 *
 *  plasma is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with plasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef INCLUDED_PLASMA_ATTR_H
#define INCLUDED_PLASMA_ATTR_H

#include "plasma_feature.h"

#if __STDC_VERSION__-0 < 199901L \
 && !defined(__STDC_C99) && !defined(__C99_RESTRICT)
/*(__C99_RESTRICT defined in xlc/xlC -qkeyword=restrict or some -qlanglevel= )*/
/* msvc: http://msdn.microsoft.com/en-us/library/5ft82fed.aspx */
#ifndef restrict
#if defined(__GNUC__) || defined(__clang__) || defined(_MSC_VER)
#define restrict __restrict
#elif defined(__SUNPRO_C)
#define restrict _Restrict
#else
#define restrict
#endif
#endif
#endif

/* Sun Studio C/C++ might not recognize __asm, __asm__, and __volatile__ */
#if defined(__SUNPRO_C) ||  defined(__SUNPRO_CC)
#if (defined(__SUNPRO_C)  && __SUNPRO_C  < 0x5100)   /* Sun Studio C < 12.1 */ \
 ||  defined(__SUNPRO_CC)
#ifndef __asm__
#if defined(__SUNPRO_C)
#define __asm__ __asm
#else
#define __asm__ asm
#endif
#if defined(__SUNPRO_CC) && !defined(__asm)
#define __asm   asm
#endif
#endif
#endif
#ifndef __volatile__
#define __volatile__ volatile
#endif
#endif

/*
 * C inline functions defined in header
 * Discussion of nuances of "extern inline" and inline functions in C headers:
 *   http://www.greenend.org.uk/rjk/2003/03/inline.html
 *   http://gcc.gnu.org/onlinedocs/gcc/Inline.html#Inline
 */
#ifdef NO_C99INLINE
#define C99INLINE
#else
#ifndef C99INLINE
#ifdef __cplusplus
#  define C99INLINE inline
#elif !defined(__GNUC__) || defined(__GNUC_STDC_INLINE__) || defined(__clang__)
#  ifdef _MSC_VER
#  define C99INLINE __inline
#  else
#  define C99INLINE inline
#  endif
#else /* (GCC extern inline was prior to C99 standard; gcc 4.3+ supports C99) */
#  define C99INLINE extern inline
#endif
#endif
#endif


/*
 * http://gcc.gnu.org/onlinedocs/gcc/Function-Attributes.html
 * http://gcc.gnu.org/onlinedocs/gcc/Variable-Attributes.html
 * http://gcc.gnu.org/onlinedocs/gcc/Attribute-Syntax.html
 * http://gcc.gnu.org/onlinedocs/ (manuals for different gcc versions)
 * /usr/include/sys/cdefs.h (GNU/Linux systems)
 * http://ohse.de/uwe/articles/gcc-attributes.html
 *
 * Note: below is not an exhaustive list of attributes
 * Attributes exist at above URLs that are not listed below
 *
 * http://clang.llvm.org/docs/LanguageExtensions.html
 *
 * Oracle Solaris Studio support for __attributes__
 * Sun Studio 12: C Compiler 5.9 Readme 
 * http://docs.oracle.com/cd/E19205-01/820-4155/c.html
 * Oracle Solaris Studio 12.2: C User's Guide 
 * 2.9 Supported Attributes
 * http://docs.oracle.com/cd/E18659_01/html/821-1384/gjzke.html
 * Oracle Solaris Studio 12.2: C++ User's Guide
 * 4.11 Supported Attributes
 * http://docs.oracle.com/cd/E18659_01/html/821-1383/gjzmh.html
 *
 * IBM Visual Age support for __attributes__
 * http://publib.boulder.ibm.com/infocenter/comphelp/v7v91/index.jsp?topic=/com.ibm.vacpp7a.doc/getstart/overview/port_gcc.htm
 * http://publib.boulder.ibm.com/infocenter/comphelp/v8v101/index.jsp?topic=%2Fcom.ibm.xlcpp8a.doc%2Flanguage%2Fref%2Fgcc_cext.htm
 * http://pic.dhe.ibm.com/infocenter/comphelp/v111v131/index.jsp?topic=%2Fcom.ibm.xlcpp111.aix.doc%2Fcompiler_ref%2Fopt_info.html
 * http://pic.dhe.ibm.com/infocenter/comphelp/v111v131/index.jsp?topic=%2Fcom.ibm.xlc111.aix.doc%2Flanguage_ref%2Fvariable_attrib.html
 *
 * HP aCC
 * http://h21007.www2.hp.com/portal/download/files/unprot/aCxx/Online_Help/pragmas.htm#Attributes
 *
 * MS Visual Studio __declspec()
 * http://msdn.microsoft.com/en-us/library/dabb5z75%28v=vs.90%29.aspx
 *
 * discussion of __attribute__() and __declspec() syntax
 * http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2008/n2761.pdf
 */

#ifndef __has_attribute       /* clang */
#define __has_attribute(x) 0
#endif

#ifndef __has_builtin         /* clang */
#define __has_builtin(x) 0
#endif

#ifndef __has_feature         /* clang */
#define __has_feature(x) 0
#endif
#ifndef __has_extension       /* clang */
#define __has_extension(x)  __has_feature(x)
#endif

#ifndef __GNUC_PREREQ
#  ifdef __GNUC_PREREQ__
#    define __GNUC_PREREQ __GNUC_PREREQ__
#  elif defined __GNUC__ && defined __GNUC_MINOR__
#    define __GNUC_PREREQ(maj, min) \
       ((__GNUC__ << 16) + __GNUC_MINOR__ >= ((maj) << 16) + (min))
#  else
#    define __GNUC_PREREQ(maj, min) 0
#  endif
#endif

#if defined(__GNUC__) && !__GNUC_PREREQ(2,7)
#define __attribute__(x)
#endif

#if !__GNUC_PREREQ(2,8) && !defined(__clang__) \
 && !defined(__xlc__) && !defined(__xlC__) /* IBM AIX xlC */
#define __extension__
#endif

/* __inline__ available when: defined(__GNUC__) && __GNUC_PREREQ(2,7) */
/* __restrict available when: defined(__GNUC__) && __GNUC_PREREQ(2,92) */

#ifndef __attribute_noinline__
#if __has_attribute(noinline) \
 || __GNUC_PREREQ(3,1) \
 || defined(__xlc__) || defined(__xlC__) /* IBM AIX xlC */ \
 || (defined(__SUNPRO_C)  && __SUNPRO_C  >= 0x590)  /* Sun Studio 12   C   */ \
 || (defined(__SUNPRO_CC) && __SUNPRO_CC >= 0x5110) /* Sun Studio 12.2 C++ */
#define __attribute_noinline__  __attribute__((__noinline__))
#elif defined(_MSC_VER)
#define __attribute_noinline__  __declspec(noinline)
#else
#define __attribute_noinline__
#endif
#endif

#ifndef __attribute_always_inline__
#if __has_attribute(always_inline) \
 || __GNUC_PREREQ(3,1) \
 || defined(__xlc__) || defined(__xlC__) /* IBM AIX xlC */ \
 || (defined(__SUNPRO_C)  && __SUNPRO_C  >= 0x590)  /* Sun Studio 12   C   */ \
 || (defined(__SUNPRO_CC) && __SUNPRO_CC >= 0x5110) /* Sun Studio 12.2 C++ */
#define __attribute_always_inline__  __attribute__((__always_inline__))
#elif defined(_MSC_VER)
/* http://msdn.microsoft.com/en-us/library/z8y1yy88.aspx */
#define __attribute_always_inline__  __forceinline
#else
#define __attribute_always_inline__  C99INLINE
#endif
#endif

/* C11 _Noreturn <stdnoreturn.h> (not included; __attribute_noreturn__ provided)
 * http://www.gnu.org/software/gnulib/manual/html_node/stdnoreturn_002eh.html
 * ISO C11 section 7.23
 * (latest free draft http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf)
 */
#ifndef __attribute_noreturn__
#if __has_attribute(noreturn) \
 || __GNUC_PREREQ(2,5) \
 || defined(__xlc__) || defined(__xlC__) /* IBM AIX xlC */ \
 || (defined(__SUNPRO_C)  && __SUNPRO_C  >= 0x590)  /* Sun Studio 12   C   */ \
 || (defined(__SUNPRO_CC) && __SUNPRO_CC >= 0x5110) /* Sun Studio 12.2 C++ */ \
 || defined(__HP_cc) || defined(__HP_aCC)
#define __attribute_noreturn__  __attribute__((__noreturn__))
#elif defined(_MSC_VER)
#define __attribute_noreturn__  __declspec(noreturn)
#else
#define __attribute_noreturn__
#endif
#endif

#ifndef __attribute_nonnull__
#if __has_attribute(nonnull) \
 || __GNUC_PREREQ(3,3)
#define __attribute_nonnull__(params)  __attribute__((__nonnull__ params))
#else
#define __attribute_nonnull__(params)
#endif
#endif

/*(deprecated; compat with older plasma macro)*/
#ifndef __attribute_nonnull_x__
#define __attribute_nonnull_x__(x)  __attribute_nonnull__(x)
#endif

#ifndef __attribute_returns_nonnull__
#if __has_attribute(returns_nonnull) \
 || __GNUC_PREREQ(4,9)
#define __attribute_returns_nonnull__  __attribute__((__returns_nonnull__))
#else
#define __attribute_returns_nonnull__
#endif
#endif

#ifndef __attribute_malloc__
#if __has_attribute(malloc) \
 || __GNUC_PREREQ(2,96) \
 || (defined(__SUNPRO_C)  && __SUNPRO_C  >= 0x590)  /* Sun Studio 12   C   */ \
 || (defined(__SUNPRO_CC) && __SUNPRO_CC >= 0x5110) /* Sun Studio 12.2 C++ */ \
 || defined(__HP_cc) || defined(__HP_aCC)
#define __attribute_malloc__  __attribute__((__malloc__))
#elif defined(_MSC_VER)
#undef  restrict
#define __attribute_malloc__  __declspec(restrict)
#define restrict __restrict
#else
#define __attribute_malloc__
#endif
#endif

#ifndef __attribute_alloc_align__
#if __has_attribute(alloc_align) \
 || __GNUC_PREREQ(4,9)
#define __attribute_alloc_align__(pos)  __attribute__((__alloc_align__ pos))
#else
#define __attribute_alloc_align__(pos)
#endif
#endif

#ifndef __attribute_alloc_size__
#if __has_attribute(alloc_size) \
 || __GNUC_PREREQ(4,3)
#define __attribute_alloc_size__(pos)  __attribute__((__alloc_size__ pos))
#else
#define __attribute_alloc_size__(pos)
#endif
#endif

#ifndef __attribute_assume_aligned__
#if __has_attribute(assume_aligned) \
 || __GNUC_PREREQ(4,9)
#define __attribute_assume_aligned__(x)  __attribute__((__assume_aligned__ x))
#else
#define __attribute_assume_aligned__(x)
#endif
#endif

#ifndef __attribute_pure__
#if __has_attribute(pure) \
 || __GNUC_PREREQ(2,96) \
 || defined(__xlc__) || defined(__xlC__) /* IBM AIX xlC */ \
 || (defined(__SUNPRO_C)  && __SUNPRO_C  >= 0x590)  /* Sun Studio 12   C   */ \
 || (defined(__SUNPRO_CC) && __SUNPRO_CC >= 0x5110) /* Sun Studio 12.2 C++ */
#define __attribute_pure__  __attribute__((__pure__))
#elif defined(__HP_cc) || defined(__HP_aCC)
#define __attribute_pure__  __attribute__((__non_exposing__))
#else
#define __attribute_pure__
#endif
#endif

#ifndef __attribute_const__
#if defined(__clang__) /*(__has_attribute(const) might not be handled on OSX)*/\
 || __GNUC_PREREQ(2,5) \
 || defined(__xlc__) || defined(__xlC__) /* IBM AIX xlC */ \
 || (defined(__SUNPRO_C)  && __SUNPRO_C  >= 0x590)  /* Sun Studio 12   C   */ \
 || (defined(__SUNPRO_CC) && __SUNPRO_CC >= 0x5100) /* Sun Studio 12.1 C++ */
#define __attribute_const__  __attribute__((__const__))
#elif defined(_MSC_VER)
/* http://msdn.microsoft.com/en-us/library/dabb5z75%28v=vs.90%29.aspx
 * (not as strict as GNU attr const, but more strict than GNU attr pure) */
#define __attribute_const__  __declspec(noalias)
#else
#define __attribute_const__
#endif
#endif
/* gcc attribute const must not be used on functions to which pointers
 * are passed as arguments and the function dereferences the pointers.
 * (gcc attribute pure can be use when pointers passed as args are dereferenced)
 * Sun Studio #pragma no_side_effect and Visual Age xlC #pragma isolated_call
 * are more strict than gcc attribute pure, and more close match gcc attribute
 * const, though also permit dereference of pointers passed as function args,
 * so might be used in addition to portable code marked with attribute pure,
 * provided requirements are met for pragma no_side_effect or isolated_call. */

#ifndef __attribute_leaf__
#if (__has_attribute(leaf) \
 || __GNUC_PREREQ(4,6)) && !defined(_LIBC)
#define __attribute_leaf__  __attribute__((__leaf__))
#else
#define __attribute_leaf__
#endif
#endif

#ifndef __attribute_hot__
#if __has_attribute(hot) \
 || __GNUC_PREREQ(4,3)
#define __attribute_hot__  __attribute__((__hot__))
#else
#define __attribute_hot__
#endif
#endif

#ifndef __attribute_cold__
#if __has_attribute(cold) \
 || __GNUC_PREREQ(4,3)
#define __attribute_cold__  __attribute__((__cold__))
#else
#define __attribute_cold__
#endif
#endif

#ifndef __attribute_unused__
#if __has_attribute(unused) \
 || __GNUC_PREREQ(2,95)
#define __attribute_unused__  __attribute__((__unused__))
#else
#define __attribute_unused__
#endif
#endif

#ifndef __attribute_used__
#if __has_attribute(used) \
 || __GNUC_PREREQ(3,1)
#define __attribute_used__  __attribute__((__used__))
#else
#define __attribute_used__
#endif
#endif

#ifndef __attribute_may_alias__
#if __has_attribute(may_alias) \
 || __GNUC_PREREQ(3,3)
#define __attribute_may_alias__  __attribute__((__may_alias__))
#else
#define __attribute_may_alias__
#endif
#endif

#ifndef __attribute_common__
#if __has_attribute(common) \
 || __GNUC_PREREQ(3,3) \
 || defined(__HP_cc) || defined(__HP_aCC)
#define __attribute_common__  __attribute__((__common__))
#else
#define __attribute_common__
#endif
#endif

#ifndef __attribute_weak__
#if __has_attribute(weak) \
 || __GNUC_PREREQ(2,95) /*(maybe earlier gcc, too)*/ \
 || defined(__xlc__) || defined(__xlC__) /* IBM AIX xlC */ \
 || (defined(__SUNPRO_C)  && __SUNPRO_C  >= 0x590)  /* Sun Studio 12   C   */ \
 || (defined(__SUNPRO_CC) && __SUNPRO_CC >= 0x5100) /* Sun Studio 12.1 C++ */
#define __attribute_weak__  __attribute__((__weak__))
#else
#define __attribute_weak__
#endif
#endif

#ifndef __attribute_format__
#if __has_attribute(format) \
 || __GNUC_PREREQ(2,95) /*(maybe earlier gcc, too)*/ \
 || defined(__xlc__) || defined(__xlC__) /* IBM AIX xlC */ \
 || defined(__HP_cc) || defined(__HP_aCC)
#define __attribute_format__(x)  __attribute__((__format__ x))
#else
#define __attribute_format__(x)
#endif
#endif

#ifndef __attribute_format_arg__
#if __has_attribute(format_arg) \
 || __GNUC_PREREQ(2,96) \
 || defined(__xlc__) || defined(__xlC__) /* IBM AIX xlC */
#define __attribute_format_arg__(x)  __attribute__((__format_arg__(x)))
#else
#define __attribute_format_arg__(x)
#endif
#endif

#ifndef __attribute_sentinel__
#if __has_attribute(sentinel) \
 || __GNUC_PREREQ(4,0)
#define __attribute_sentinel__  __attribute__((__sentinel__))
#else
#define __attribute_sentinel__
#endif
#endif

#ifndef __attribute_sentinel_x__
#if __has_attribute(sentinel) \
 || __GNUC_PREREQ(4,0)
#define __attribute_sentinel_x__(negpos)  __attribute__((__sentinel__(negpos)))
#else
#define __attribute_sentinel_x__(negpos)
#endif
#endif

#ifndef __attribute_nothrow__
#if __has_attribute(nothrow) \
 || __GNUC_PREREQ(3,3)
#define __attribute_nothrow__  __attribute__((__nothrow__))
#elif defined(__SUNPRO_CC) /* Sun Studio C++ */
#define __attribute_nothrow__  throw()
#elif defined(_MSC_VER)
#define __attribute_nothrow__  __declspec(nothrow)
#else
#define __attribute_nothrow__
#endif
#endif

#ifndef __attribute_warn_unused_result__
#if __has_attribute(warn_unused_result) \
 || __GNUC_PREREQ(3,4) \
 || defined(__HP_cc) || defined(__HP_aCC)
#define __attribute_warn_unused_result__ __attribute__((__warn_unused_result__))
#else
#define __attribute_warn_unused_result__
#endif
#endif

#ifndef __attribute_warning__
#if __has_attribute(warning) \
 || __GNUC_PREREQ(4,3)
#define __attribute_warning__(msg)  __attribute__((__warning__(msg)))
#else
#define __attribute_warning__(msg)
#endif
#endif

#ifndef __attribute_error__
#if __has_attribute(error) \
 || __GNUC_PREREQ(4,3)
#define __attribute_error__(msg)  __attribute__((__error__(msg)))
#else
#define __attribute_error__(msg)
#endif
#endif

#ifndef __attribute_deprecated__
#if __has_attribute(deprecated) \
 || __GNUC_PREREQ(3,1)
#define __attribute_deprecated__  __attribute__((__deprecated__))
#elif defined(_MSC_VER)
#define __attribute_deprecated__  __declspec(deprecated)
#else
#define __attribute_deprecated__
#endif
#endif

#ifndef __attribute_deprecated_x__
#if __has_attribute(deprecated) \
 || __GNUC_PREREQ(3,1)
#define __attribute_deprecated_x__(msg)  __attribute__((__deprecated__(msg)))
#elif defined(_MSC_VER)
#define __attribute_deprecated_x__(msg)  __declspec(deprecated(msg))
#else
#define __attribute_deprecated_x__(msg)
#endif
#endif

#ifndef __attribute_regparm__
#if __has_attribute(regparm) \
 || (defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__)))
#define __attribute_regparm__(x)  __attribute__((__regparm__ x))
#else
#define __attribute_regparm__(x)
#endif
#endif

#if !(defined(__APPLE__) && defined(__MACH__)) /* not supported on Darwin */
#if __has_attribute(alias) \
 || __GNUC_PREREQ(3,3) \
 || defined(__xlc__) || defined(__xlC__) /* IBM AIX xlC */ \
 || (defined(__SUNPRO_C)  && __SUNPRO_C  >= 0x590)  /* Sun Studio 12   C   */
#define PLASMA_ATTR_ALIAS
#ifndef __attribute_alias__
#define __attribute_alias__(x)  __attribute__((__alias__(x)))
#endif
#endif
#endif
#ifndef __attribute_alias__
#define __attribute_alias__(x)
#endif


/*
 * Symbol visibility attributes:
 * http://gcc.gnu.org/wiki/Visibility
 * http://docs.oracle.com/cd/E19205-01/820-4155/c.html
 * http://docs.sun.com/source/820-4155/c.html
 *   (Oracle/Sun Studio 12 C compiler supports __attribute__)
 * http://wikis.sun.com/display/SunStudio/Using+Sun+Studio+for+open+source+apps
 * Note that GCC allows these at beginning or end of function declarations,
 * but Sun Studio requires them at the beginning, such as:
 * EXPORT void foo(int bar);
 */

#if __has_attribute(visibility) \
 || __GNUC_PREREQ(4,0) \
 || (defined(__SUNPRO_C)  && __SUNPRO_C  >= 0x590)  /* Sun Studio 12   C   */ \
 || (defined(__SUNPRO_CC) && __SUNPRO_CC >= 0x5110) /* Sun Studio 12.2 C++ */
# define EXPORT            __attribute__((__visibility__("default")))
# define HIDDEN            __attribute__((__visibility__("hidden")))
# define INTERNAL          __attribute__((__visibility__("internal")))
#elif defined(__SUNPRO_C) && (__SUNPRO_C >= 0x550)
# define EXPORT            __global
# define HIDDEN            __hidden
# define INTERNAL          __symbolic
#elif defined(__HP_cc) || defined(__HP_aCC)
# define EXPORT            __attribute__((__visibility__("default")))
# define HIDDEN            __attribute__((__visibility__("hidden")))
# define INTERNAL          __attribute__((__visibility__("protected")))
#else /* not gcc >= 4 and not Sun Studio >= 8 and not HP aCC */
# define EXPORT
# define HIDDEN
# define INTERNAL
#endif

#if defined(__GNUC__) \
 &&(defined(__sun) || defined(_AIX) || defined(__hpux) || defined(__CYGWIN__))
# undef  EXPORT
# undef  HIDDEN
# undef  INTERNAL
# define EXPORT
# define HIDDEN
# define INTERNAL
#endif

/* http://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html */

#if __has_builtin(__builtin_constant_p) \
 || __GNUC_PREREQ(3,1)/*(check major,minor ver; actually supported in 3.0.1)*/\
 || defined(__IBMC__) || (defined(__IBMCPP__) && __IBMCPP__ >= 1310) \
 || (defined(__SUNPRO_C)  && __SUNPRO_C  >= 0x5100) /* Sun Studio 12.1 C   */
#define plasma_attr_has_builtin_constant_p
/* IBM xlC (C++) compiler has a bug in 32-bit compilation on constant 8-byte
 * value via initialization assignment (and not simply integer literal)
 * which is fixed in XL C/C++ 12.1 March 2014 PTF and later (XL C/C++ 13.1)
 * [PMR 77049,7TD,000] IBM notes that __builtin_constant_p() is not officially
 * documented and was originally intended for compiling Linux headers with
 * XL C/C++ for Linux */
#else
#ifndef __builtin_constant_p
#define __builtin_constant_p(x) 0
#endif
#endif

/* GCC __builtin_expect() is used below to hint to compiler expected results
 * of commands executed.  Successful execution is expected and should be
 * optimally scheduled and predicted as branch taken.  Error conditions are
 * not expected and should be scheduled as the less likely branch taken.
 * (__builtin_expect() is recognized by IBM xlC compiler v9.0)
 * http://publib.boulder.ibm.com/infocenter/comphelp/v9v111/index.jsp?topic=/com.ibm.xlcpp9.aix.doc/compiler_ref/bifs_opt.htm
 * Note: avoid compound conditions (a && b) inside __builtin_expect() due to
 * bug in gcc 4.2,4.3,4.4  http://gcc.gnu.org/bugzilla/show_bug.cgi?id=42233 */

#ifndef __builtin_expect
#if !__has_builtin(__builtin_expect) \
 && !__GNUC_PREREQ(2,96) \
 && !(defined(__xlc__) || defined(__xlC__))
#define __builtin_expect(x,y) (x)
#endif
#endif

/* memory locality hint (for prefetch)
 * (avoid pulling in the large header xmmintrin.h just for simple enum _mm_hint)
 * #if defined(__clang__) || defined(INTEL_COMPILER) || defined(_MSC_VER) \
 *  ||(__GNUC_PREREQ(4,7) && defined(__SSE__))
 * #include <xmmintrin.h>
 */
enum plasma_attr_mm_hint
{
  PLASMA_ATTR_MM_HINT_T0 =  3,
  PLASMA_ATTR_MM_HINT_T1 =  2,
  PLASMA_ATTR_MM_HINT_T2 =  1,
  PLASMA_ATTR_MM_HINT_NTA = 0
};

/* GCC __builtin_prefetch() http://gcc.gnu.org/projects/prefetch.html */
#if !__has_builtin(__builtin_prefetch) && !defined(__GNUC__)
/* http://software.intel.com/sites/products/documentation/studio/composer/en-us/2011Update/compiler_c/intref_cls/common/intref_sse_cacheability.htm
 * http://msdn.microsoft.com/en-us/library/84szxsww%28v=vs.90%29.aspx
 * On non-x86 systems, MSVC provides PreFetchCacheLine() (not used here)
 *   void PreFetchCacheLine(int Level, VOID CONST *Address);
 *   #define __builtin_prefetch(addr,rw,locality) \
 *           PreFetchCacheLine((locality),(addr))
 * http://msdn.microsoft.com/en-us/library/windows/desktop/ms684826%28v=vs.85%29.aspx */
#if defined(__INTEL_COMPILER) || defined(_MSC_VER)
#ifdef _MSC_VER
#pragma intrinsic(_mm_prefetch)
#endif
#define __builtin_prefetch(addr,rw,locality) \
        _mm_prefetch((addr),(locality))
#endif
/* xlc v8.0 __dcbt (possibly earlier), xlc v9.0 (released 2007/08/15) __dcbtst
 * https://publib.boulder.ibm.com/infocenter/comphelp/v8v101/index.jsp?topic=%2Fcom.ibm.xlcpp8a.doc%2Fcompiler%2Fref%2Fbif_cache.htm
 * http://publib.boulder.ibm.com/infocenter/comphelp/v9v111/index.jsp?topic=/com.ibm.xlcpp9.aix.doc/compiler_ref/bifs_data_cache.htm
 * (on Power7, might check locality and use __dcbtt() or __dcbtstt())
 * http://pic.dhe.ibm.com/infocenter/comphelp/v121v141/index.jsp?topic=%2Fcom.ibm.xlc121.aix.doc%2Fcompiler_ref%2Fbifs_prefetch.html */
#if defined(__xlc__) || defined(__xlC__)
#ifdef __cplusplus
#include <builtins.h>
#endif
#define __builtin_prefetch(addr,rw,locality) \
        ((rw) ? __dcbtst((void *)(addr)) : __dcbt((void *)(addr)))
#endif
/* Sun Studio
 * http://blogs.oracle.com/solarisdev/entry/new_article_prefetching
 * (other prefetch options are available, but not mapped to locality here) */
#if defined(__SUNPRO_C) || defined(__SUNPRO_CC)
#include <sun_prefetch.h>
#define __builtin_prefetch(addr,rw,locality) \
        ((rw) ? sun_prefetch_write_once((void *)(addr)) \
              : sun_prefetch_read_once((void *)(addr)))
#endif
/* HP aCC for IA-64 (Itanium)
 * Search internet "Inline assembly for Itanium-based HP-UX"
 * (HP compiler expects to see string _LFHINT_* and not integral constants)*/
#if defined(__ia64) && (defined(__HP_cc) || defined(__HP_aCC))
#if defined(__cplusplus) && __cplusplus >= 201103L /* C++11 */
#include <cfenv>
#else
#include <fenv.h>
#endif
#include <machine/sys/inline.h>
#define __builtin_prefetch(addr,rw,locality)                        \
        ((rw) ? _Asm_lfetch_excl(_LFTYPE_NONE,                      \
                                   (locality) == 0 ? _LFHINT_NTA  : \
                                   (locality) == 1 ? _LFHINT_NT2  : \
                                   (locality) == 2 ? _LFHINT_NT1  : \
                                 /*(locality) == 3*/ _LFHINT_NONE,  \
                                 (void *)(addr))                    \
              : _Asm_lfetch(     _LFTYPE_NONE,                      \
                                   (locality) == 0 ? _LFHINT_NTA  : \
                                   (locality) == 1 ? _LFHINT_NT2  : \
                                   (locality) == 2 ? _LFHINT_NT1  : \
                                 /*(locality) == 3*/ _LFHINT_NONE,  \
                                 (void *)(addr)))
#endif
/* default (do-nothing macros) */
#ifndef __builtin_prefetch
#define __builtin_prefetch(addr,rw,locality)
#endif
#endif


#define retry_eintr_while(x) \
  /*@-whileempty@*/                 /* caller must #include <errno.h> */   \
  do {} while (__builtin_expect((x),0) && __builtin_expect(errno == EINTR, 1)) \
  /*@=whileempty@*/

#define retry_eintr_do_while(x,c)   /* caller must #include <errno.h> */   \
  do {(x);} while (__builtin_expect((c),0) && __builtin_expect(errno==EINTR, 1))

/* Interestingly, GNU Linux systems might provide similar macro
 * TEMP_FAILURE_RETRY(expression) in unistd.h when defined(_GNU_SOURCE) */


/* __typeof__() is non-standard, though available on many modern compilers
 * http://en.wikipedia.org/wiki/Typeof
 *
 * gcc and clang support __typeof__()
 * However, since typeof is not part of C11/C++11, a compatible definition of 
 * typeof is not provided for other platforms.  Please consider using __typeof__
 *
 * Sun Studio 12 C compiler supports __typeof__ extension
 * http://www.oracle.com/technetwork/systems/cccompare-137792.html
 * http://www.oracle.com/technetwork/server-storage/solaris10/c-type-137127.html
 * http://docs.oracle.com/cd/E19205-01/820-4155/c.html
 * http://docs.oracle.com/cd/E19205-01/820-4155/c++.html
 * https://blogs.oracle.com/sga/entry/typeof_and_alignof
 * Sun Studio C++:
 *   Keyword typeof is available under -features=gcc command line option.
 * !! NOTE: there is a bug in Sun Studio C++ 12u1 (not tested on other versions)
 *    32-bit compilation where __typeof__(x) mishandles x if x > 4 bytes large
 *    bug filed with Oracle:
 *       uint64_t x; __typeof__(x) y; assert(sizeof(y) == 8);
 *
 * xlC supports __typeof__()
 * The typeof and __typeof__ keywords are supported as follows:
 *     C only The __typeof__ keyword is recognized under compilation with the xlc invocation command or the -qlanglvl=extc89, -qlanglvl=extc99, or -qlanglvl=extended options. The typeof keyword is only recognized under compilation with -qkeyword=typeof.
 * https://publib.boulder.ibm.com/infocenter/comphelp/v8v101/index.jsp?topic=%2Fcom.ibm.xlcpp8a.doc%2Fcompiler%2Fref%2Fruoptkey.htm
 *     C++ The typeof and __typeof__ keywords are recognized by default.
 * https://publib.boulder.ibm.com/infocenter/comphelp/v8v101/index.jsp?topic=%2Fcom.ibm.xlcpp8a.doc%2Flanguage%2Fref%2Ftypeof_operator.htm
 *
 * HP-UX cc supports __typeof__ when compiled with -Agcc
 * http://h30499.www3.hp.com/t5/Languages-and-Scripting/HP-UX-IA64-and-HP-C-Is-quot-typeof-quot-keyword-supported/td-p/4529218
 *
 * MS Visual Studio 2010 decltype() can be used to implement __typeof__()
 * http://msdn.microsoft.com/en-us/library/dd537655.aspx
 * http://stackoverflow.com/questions/70013/how-to-detect-if-im-compiling-code-with-visual-studio-2008
 * http://en.wikipedia.org/wiki/Decltype
 * C++11 decltype() implemented in g++ (4.3), in clang++, and others
 */
#if defined(_MSC_VER) && _MSC_VER >= 1600
#ifndef __typeof__
#define __typeof__(x)  decltype(x)
#endif
#endif


/* __alignof__() is non-standard, though available on many modern compilers
 * (see plasma_stdtypes.h for _Alignof and alignof)
 *
 * (C11 <stdalign.h> _Alignof and C++11 <cstdalign> alignof)
 * (http://en.cppreference.com/w/cpp/language/alignof)
 *
 * http://www.wambold.com/Martin/writings/alignof.html
 * (note some subtle nuances of alignment of double inside structs on x86)
 *
 * gcc and clang support __alignof__()
 *
 * Sun Studio 12 C compiler supports __alignof__ extension
 * http://www.oracle.com/technetwork/systems/cccompare-137792.html
 * http://docs.oracle.com/cd/E19205-01/820-4155/c.html
 * http://docs.oracle.com/cd/E19205-01/820-4155/c++.html
 * https://blogs.oracle.com/sga/entry/typeof_and_alignof
 *
 * xlC supports __alignof__()
 * https://publib.boulder.ibm.com/infocenter/comphelp/v8v101/index.jsp?topic=%2Fcom.ibm.xlcpp8a.doc%2Flanguage%2Fref%2Falignof.htm
 *
 * HP-UX cc does not currently support __alignof__, but it can be emulated
 * (not done here, but see http://www.wambold.com/Martin/writings/alignof.html )
 *
 * MS Visual Studio supports __alignof()
 * http://msdn.microsoft.com/en-us/library/45t0s5f4%28v=vs.90%29.aspx
 */
#if defined(_MSC_VER)
#define __alignof__(x)  __alignof(x)
#endif


/* alignment
 * (see plasma_stdtypes.h for _Alignas and alignas)
 *
 * (C11 <stdalign.h> _Alignas and C++11 <cstdalign> alignas)
 * (http://en.cppreference.com/w/cpp/language/alignas)
 *
 * portability: __attribute__((aligned)) can be at beginning or end of statement
 * but must be after 'struct' (not before it) or else might be ignored.
 * MS __declspec() is expected early in statement, not at end. 
 * Placement requirements makes use of this attribute less portable without
 * use of redundant statements: place __declspec_align__(x) at the beginning
 * of a statement and __attribute_aligned__(x) at the end of a statement.
 *
 * Oracle Solaris Studio C++ 12.2 finally adds support for aligned attribute.
 * Earlier versions support #pragma align, but mangled names must be used when
 * #pragma align is used inside a namespace, and local, stack vars not supported
 *   http://docs.oracle.com/cd/E18659_01/html/821-1383/bkbjx.html#bkbjy
 * Solaris standard libc does provide memalign() for allocating aligned memory,
 * but only #pragma align for static or global alignment, until Sun Studio 12 C
 * and Sun Studio 12.2 C++.
 * POSIX documents posix_memalign() which some platforms support.
 * C11 provides aligned_alloc()
 *
 * Later patch releases of Sun Studio 12 update 1 C++ add attribute aligned.
 *   CC: Sun C++ 5.10 SunOS_sparc Patch 128228-23  (output from $ CC -V )
 *   https://getupdates.oracle.com/readme/README.128228-23
 *
 * Misaligned memory access -- loads and stores -- can have different penalties
 * depending on whether the access is within a cache line, crosses a cache line,
 * or crosses a memory page boundary.  Misaligned memory access on SPARC has
 * historically been much, much worse than on x86, POWER, or ARM.  Even Itanium
 * is substantially better except when misaligned access crosses memory page
 * boundaries.  Therefore, performance problems can occur if memory needs to be
 * aligned and __attribute_aligned__ is made a no-op when not supported.
 */
#ifndef __attribute_aligned__
#if __has_attribute(aligned) \
 || defined(__GNUC__) /* __GNUC_PREREQ(2,95) and possibly earlier */ \
 || defined(__xlc__) || defined(__xlC__) /* IBM AIX xlC */ \
 || (defined(__SUNPRO_C)  && __SUNPRO_C  >= 0x590)  /* Sun Studio 12   C   */ \
 || (defined(__SUNPRO_CC) && __SUNPRO_CC >= 0x5100) /* Sun Studio 12.1 C++ */ \
 || defined(__HP_cc) || defined(__HP_aCC)           /* (need Patch 128228-23)*/
#define __attribute_aligned__(x)  __attribute__((__aligned__ (x)))
#else
#define __attribute_aligned__(x)
#endif
#endif
#ifndef __declspec_align__
#if defined(_MSC_VER)
/* Windows Data Alignment on IPF, x86, and x64
 * http://msdn.microsoft.com/en-us/library/aa290049%28v=vs.71%29.aspx
 * __declspec(align(x))
 * http://msdn.microsoft.com/en-us/library/83ythb65%28v=vs.90%29.aspx */
#define __declspec_align__(x)  __declspec(align(x))
#else
#define __declspec_align__(x)
#endif
#endif


/*
 * macros grouping and wrapping compiler-specific pragmas
 *
 * xlC
 * http://publib.boulder.ibm.com/infocenter/comphelp/v8v101/index.jsp?topic=%2Fcom.ibm.xlcpp8a.doc%2Fcompiler%2Fref%2Frupragen.htm
 *
 * Sun Studio
 * http://docs.oracle.com/cd/E18659_01/html/821-1384/bjaby.html
 * http://docs.oracle.com/cd/E18659_01/html/821-1383/bkbju.html
 * Sun Studio C++ 12 adds support for _Pragma()
 *
 * HP aCC
 * HP-UX supports _Pragma() only in ANSI (-Aa) and ANSI extended (-Ae) mode.
 * http://h21007.www2.hp.com/portal/download/files/unprot/aCxx/Online_Help/pragmas.htm
 *
 * Visual Studio 2008 has __pragma() which is slightly different from _Pragma()
 * http://msdn.microsoft.com/en-us/library/d9x1s805%28v=vs.90%29.aspx
 * http://msdn.microsoft.com/en-us/library/f88y8c6c%28v=vs.90%29.aspx
 *
 *
 * xlc #pragma isolated_call and Sun Studio #pragma no_side_effect are
 * more restrictive than __attribute__((pure)), but less restrictive than
 * __attribute__((const)).  In particular, both pragmas permit dereferencing
 * and reading from a pointer passed in as an argument to a function, while
 * __attribute__((const)) does not.  There may be some benefit with xlc
 * and Sun Studio to add PLASMA_ATTR_Pragma_no_side_effect() annotation to 
 * functions marked __attribute__((pure)) in cases where the function can not
 * be marked __attribute__((const)) only due to taking a pointer argument
 * which is dereferenced by the function.
 *
 * When using strlen() with Sun Studio, might improve performance:
 *   #include <string.h>
 *   PLASMA_ATTR_Pragma_no_side_effect(strlen)
 * https://blogs.oracle.com/d/entry/the_perils_of_strlen
 */

#ifdef _MSC_VER
#define PLASMA_ATTR_Pragma(x)  __pragma(x)
#else
#define PLASMA_ATTR_Pragma(x)  _Pragma(#x)
#endif

#if (defined(__STDC_VERSION__) && __STDC_VERSION__-0 >= 199901L) /* C99 */ \
 || defined(__cplusplus)

#if defined(__xlc__) || defined(__xlC__)

#define PLASMA_ATTR_Pragma_no_side_effect(func) \
        PLASMA_ATTR_Pragma(isolated_call(func))
#define PLASMA_ATTR_Pragma_execution_frequency_very_low \
        PLASMA_ATTR_Pragma(execution_frequency(very_low))
#define PLASMA_ATTR_Pragma_execution_frequency_very_high \
        PLASMA_ATTR_Pragma(execution_frequency(very_high))

#elif defined(__SUNPRO_C) || (defined(__SUNPRO_CC) && __SUNPRO_CC >= 0x590)

#define PLASMA_ATTR_Pragma_no_side_effect(func) \
        PLASMA_ATTR_Pragma(no_side_effect(func))
#define PLASMA_ATTR_Pragma_rarely_called(func) \
        PLASMA_ATTR_Pragma(rarely_called(func))
#define PLASMA_ATTR_Pragma_execution_frequency_very_low \
        plasma_attr_sun_studio_shim_rarely_called();

/* Sun Studio compiler does not currently provide a means to statically tag
 * code paths as likely or unlikely.  However, a function (not inlined) that
 * is marked as rarely_called and no_side_effect might be effective substitute.
 * https://github.com/bloomberg/bsl/blob/master/groups/bsl/bsls/bsls_performancehint.h */
#ifdef __cplusplus
extern "C" {
#endif
void plasma_attr_sun_studio_shim_rarely_called (void);
#pragma rarely_called(plasma_attr_sun_studio_shim_rarely_called)
#pragma no_side_effect(plasma_attr_sun_studio_shim_rarely_called)
#ifdef __cplusplus
}
#endif

#endif

#endif

#ifndef PLASMA_ATTR_Pragma_no_side_effect
#define PLASMA_ATTR_Pragma_no_side_effect(func)
#endif
#ifndef PLASMA_ATTR_Pragma_rarely_called
#define PLASMA_ATTR_Pragma_rarely_called(func)
#endif
#ifndef PLASMA_ATTR_Pragma_execution_frequency_very_low
#define PLASMA_ATTR_Pragma_execution_frequency_very_low
#endif
#ifndef PLASMA_ATTR_Pragma_execution_frequency_very_high
#define PLASMA_ATTR_Pragma_execution_frequency_very_high
#endif

/* https://github.com/bloomberg/bsl/blob/master/groups/bsl/bsls/bsls_ident.h */
#if defined(__clang__) || defined(__GNUC__) \
 || (defined(_MSC_VER) && _MSC_VER >= 1020) \
 || defined(__IBMC__) || defined(__IBMCPP__) \
 || (defined(__HP_cc)  && __HP_cc-0  >= 62500) \
 || (defined(__HP_aCC) && __HP_aCC-0 >= 62500) /* HP aCC A.06.25 */
  #define PLASMA_ATTR_Pragma_once  PLASMA_ATTR_Pragma(once)
#else
  /* Sun Studio does not support #pragma once.  Instead, it natively detects if
   * the entire non-comment portion of a file is wrapped by #ifndef, and if so,
   * optimizes away reopens of the file if the #ifndef condition is false.
   * Therefore, include guards should still be used within each header,
   * in conjunction with PLASMA_ATTR_Pragma_once. */
  #define PLASMA_ATTR_Pragma_once
#endif
PLASMA_ATTR_Pragma_once


/*
 * Table of (popular) compiler support for various C++11 features
 * http://wiki.apache.org/stdcxx/C%2B%2B0xCompilerSupport
 */


#endif
