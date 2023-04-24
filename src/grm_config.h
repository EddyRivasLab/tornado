/* src/grm_config.h.  Generated from grm_config.h.in by configure.  */
/* tornado_config.h.in  [input to configure]
 * 
 * System-dependent configuration of Easel, by autoconf.
 * 
 * This file should be included in all Easel .c files before
 * anything else, because it may set #define's that control
 * behaviour of system includes and system libraries. An example
 * is large file support.
 * 
 */
#ifndef tornadoCONFIG_INCLUDED
#define tornadoCONFIG_INCLUDED

/* Version info.
 */
#define TORNADO_VERSION "0.6.0"
#define TORNADO_DATE "May 2023"
#define TORNADO_COPYRIGHT "Copyright (C) 2016 Howard Hughes Medical Institute."
#define TORNADO_LICENSE "Freely distributed under the GNU General Public License (GPLv3)."
#define TORNADO_HOME "/Users/erivas/src/Mysrc/tornado"
#define TORNADO_BIN "/Users/erivas/src/Mysrc/tornado/bin"
#define TORNADO_SHARE "/Users/erivas/src/Mysrc/tornado/share"

/* Large file support
 * Must precede any header file inclusion.
 */
/* #undef _FILE_OFFSET_BITS */
/* #undef _LARGE_FILES */
/* #undef _LARGEFILE_SOURCE */

/* Debugging verbosity (0=none;3=most verbose)
 */
/* #undef tornadoDEBUGLEVEL */

/* In Inside algorithm implementations, we use a table lookup in
 * grm_FLogsum() to calculate summed probabilities in log
 * space. grm_INTSCALE defines the precision of the calculation; the
 * default of 1000.0 means rounding differences to the nearest 0.001
 * nat. grm_LOGSUM_TBL defines the size of the lookup table; the
 * default of 16000 means entries are calculated for differences of 0
 * to 16.000 nats (when grm_INTSCALE is 1000.0).  e^{-grm_LOGSUM_TBL /
 * p7_INTSCALE} should be on the order of the machine FLT_EPSILON,
 * typically 1.2e-7.
 */
#define grm_INTSCALE     1000.0f
#define grm_LOGSUM_TBL   16000

/* System headers
 */
/* #undef HAVE_ENDIAN_H */
#define HAVE_INTTYPES_H 1
#define HAVE_STDINT_H 1
#define HAVE_UNISTD_H 1
#define HAVE_SYS_TYPES_H 1
#define HAVE_STRINGS_H 1

/* #undef HAVE_SYS_PARAM_H */
#define HAVE_SYS_SYSCTL_H 1

/* #undef HAVE_EMMINTRIN_H */
/* #undef HAVE_PMMINTRIN_H */
/* #undef HAVE_XMMINTRIN_H */

/* #undef HAVE_ALTIVEC_H */

/* Types
 */
/* #undef WORDS_BIGENDIAN */
/* #undef int8_t */
/* #undef int16_t */
/* #undef int32_t */
/* #undef int64_t */
/* #undef uint8_t */
/* #undef uint16_t */
/* #undef uint32_t */
/* #undef uint64_t */
/* #undef off_t */

/* Optional packages
 */
/* #undef HAVE_LIBGSL */

/* Optional parallel implementation support
 */
/* #undef HAVE_SSE2 */
/* #undef HAVE_VMX */
/* #undef HAVE_MPI */
#define HAVE_PTHREAD 1

/* #undef HAVE_SSE2_CAST */

/* Programs */
#define HAVE_GZIP 1

/* Functions */
/* #undef HAVE_CHMOD */
#define HAVE_FSEEKO 1
#define HAVE_FSTAT 1
#define HAVE_GETCWD 1
#define HAVE_GETPID 1
#define HAVE_MKSTEMP 1
#define HAVE_POPEN 1
/* #undef HAVE_PUTENV */
#define HAVE_STAT 1
#define HAVE_STRCASECMP 1
#define HAVE_SYSCONF 1
#define HAVE_SYSCTL 1
#define HAVE_TIMES 1
/* #undef HAVE_ERFC */

#define HAVE_FUNC_ATTRIBUTE_NORETURN 1


#endif /*tornadoCONFIG_INCLUDED*/

