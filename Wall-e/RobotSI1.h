//
// MATLAB Compiler: 4.18.1 (R2013a)
// Date: Sat Apr 19 23:03:12 2014
// Arguments: "-B" "macro_default" "-W" "cpplib:RobotSI1" "-T" "link:lib" "-d"
// "C:\Users\Rafal.Rafal\Desktop\mat\RobotSI1\src" "-w"
// "enable:specified_file_mismatch" "-w" "enable:repeated_file" "-w"
// "enable:switch_ignored" "-w" "enable:missing_lib_sentinel" "-w"
// "enable:demo_license" "-v" "I:\MATLAB FUNCTIONS\robot1.m" 
//

#ifndef __RobotSI1_h
#define __RobotSI1_h 1

#if defined(__cplusplus) && !defined(mclmcrrt_h) && defined(__linux__)
#  pragma implementation "mclmcrrt.h"
#endif
#include "mclmcrrt.h"
#include "mclcppclass.h"
#ifdef __cplusplus
extern "C" {
#endif

#if defined(__SUNPRO_CC)
/* Solaris shared libraries use __global, rather than mapfiles
 * to define the API exported from a shared library. __global is
 * only necessary when building the library -- files including
 * this header file to use the library do not need the __global
 * declaration; hence the EXPORTING_<library> logic.
 */

#ifdef EXPORTING_RobotSI1
#define PUBLIC_RobotSI1_C_API __global
#else
#define PUBLIC_RobotSI1_C_API /* No import statement needed. */
#endif

#define LIB_RobotSI1_C_API PUBLIC_RobotSI1_C_API

#elif defined(_HPUX_SOURCE)

#ifdef EXPORTING_RobotSI1
#define PUBLIC_RobotSI1_C_API __declspec(dllexport)
#else
#define PUBLIC_RobotSI1_C_API __declspec(dllimport)
#endif

#define LIB_RobotSI1_C_API PUBLIC_RobotSI1_C_API


#else

#define LIB_RobotSI1_C_API

#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_RobotSI1_C_API 
#define LIB_RobotSI1_C_API /* No special import/export declaration */
#endif

extern LIB_RobotSI1_C_API 
bool MW_CALL_CONV RobotSI1InitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_RobotSI1_C_API 
bool MW_CALL_CONV RobotSI1Initialize(void);

extern LIB_RobotSI1_C_API 
void MW_CALL_CONV RobotSI1Terminate(void);



extern LIB_RobotSI1_C_API 
void MW_CALL_CONV RobotSI1PrintStackTrace(void);

extern LIB_RobotSI1_C_API 
bool MW_CALL_CONV mlxRobot1(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);


#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

/* On Windows, use __declspec to control the exported API */
#if defined(_MSC_VER) || defined(__BORLANDC__)

#ifdef EXPORTING_RobotSI1
#define PUBLIC_RobotSI1_CPP_API __declspec(dllexport)
#else
#define PUBLIC_RobotSI1_CPP_API __declspec(dllimport)
#endif

#define LIB_RobotSI1_CPP_API PUBLIC_RobotSI1_CPP_API

#else

#if !defined(LIB_RobotSI1_CPP_API)
#if defined(LIB_RobotSI1_C_API)
#define LIB_RobotSI1_CPP_API LIB_RobotSI1_C_API
#else
#define LIB_RobotSI1_CPP_API /* empty! */ 
#endif
#endif

#endif

extern LIB_RobotSI1_CPP_API void MW_CALL_CONV robot1(int nargout, mwArray& out, const mwArray& left, const mwArray& front, const mwArray& right, const mwArray& path);

#endif
#endif
