#pragma once

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <windows.h>

#include "ISocialNetworkService.h"

#ifdef NETSERVICE_EXPORTS
#define NETSERVICE_API __declspec(dllexport)
#else
#define NETSERVICE_API __declspec(dllimport)
#endif

#ifndef NETSERVCIE_EXTERNC
#define NETSERVCIE_EXTERNC extern "C"
#endif
