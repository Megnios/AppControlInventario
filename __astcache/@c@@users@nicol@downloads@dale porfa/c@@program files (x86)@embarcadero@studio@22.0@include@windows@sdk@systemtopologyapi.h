﻿#pragma option push -b -a8 -pc -A- -w-pun /*P_O_Push*/
/********************************************************************************
*                                                                               *
* consoleapi.h -- ApiSet Contract for api-ms-win-core-systemtopology-l1         *
*                                                                               *
* Copyright (c) Microsoft Corporation. All rights reserved.                     *
*                                                                               *
********************************************************************************/

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#ifndef _SYSTEMTOPOLOGY_H_
#define _SYSTEMTOPOLOGY_H_

#include <apiset.h>
#include <apisetcconv.h>
#include <minwindef.h>
#include <minwinbase.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma region Desktop Family or OneCore Family
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)

WINBASEAPI
BOOL
WINAPI
GetNumaHighestNodeNumber(
    _Out_ PULONG HighestNodeNumber
    );


#if _WIN32_WINNT >= 0x0601

WINBASEAPI
BOOL
WINAPI
GetNumaNodeProcessorMaskEx(
    _In_ USHORT Node,
    _Out_ PGROUP_AFFINITY ProcessorMask
    );


#endif // (_WIN32_WINNT >=0x0601)

#if _WIN32_WINNT >= 0x0601

WINBASEAPI
BOOL
WINAPI
GetNumaProximityNodeEx(
    _In_ ULONG ProximityId,
    _Out_ PUSHORT NodeNumber
    );


#endif // (_WIN32_WINNT >=0x0601)

#endif // WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)
#pragma endregion

#ifdef __cplusplus
}
#endif

#endif // _SYSTEMTOPOLOGY_H_
#pragma option pop /*P_O_Pop*/
