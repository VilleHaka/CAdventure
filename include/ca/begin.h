#ifndef CA_BEGIN_H
#define CA_BEGIN_H

#include <time.h>
#include <Windows.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef _WIN32
#ifdef CA_BUILD_DLL
#define CA_API __declspec(dllexport)
#else
#define CA_API __declspec(dllimport)
#endif // CA_BUILD_DLL
#else
#define CA_API
#endif // _WIN32

#ifdef __cplusplus
#define CA_EXTERN_BEGIN extern "C" {
#define CA_EXTERN_END }
#else
#define CA_EXTERN_BEGIN
#define CA_EXTERN_END
#endif // __cplusplus

#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *) 0)
#endif // __cplusplus
#endif // NULL

#endif