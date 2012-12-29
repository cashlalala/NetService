#pragma once

//////////////////////////////////////////////////////////////////////////////
//
// This file defines the error codes used by Net Service.
//
// NETSERVICE error codes are COM HRESULTs whose format is defined in "WinError.h".
// Search for "COM Error Codes" in "WinError.h" for detailed information on 
// COM HRESULTs.
// http://msdn.microsoft.com/en-us/library/ms819772.aspx
// http://msdn.microsoft.com/en-us/library/ms679751(VS.85).aspx
//
// For NETSERVICE, the "Code" section is further divided into "Interface Code"
// and "Status Code" as below:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +-+-+-+-+-+---------------------+-----------+-------------------+
//  |S|R|C|N|r|    Facility         | Interface |    Status         |
//  +-+-+-+-+-+---------------------+-----------+-------------------+
//
// NETSERVICE can also return standard COM HRESULTs and converted Windows system errors
// using the HRESULT_FROM_WIN32 function.
// http://msdn.microsoft.com/en-us/library/windows/desktop/ms680746(v=vs.85).aspx
//
//////////////////////////////////////////////////////////////////////////////

#ifdef _WINDOWS
	#include <WinError.h>
#else
	#define HRESULT int  

	#define S_OK		 0x00000000
	#define E_FAIL    0x80004005
	#define SEVERITY_SUCCESS    0
	#define SEVERITY_ERROR      1
#endif


#define MAKE_NETSERVICE_HRESULT(sev, itf, err) \
	MAKE_HRESULT(sev, FACILITY_ITF, ((unsigned long)(itf) << 10 | (unsigned long)(err)))

#define MAKE_NETSERVICE_INFO(itf, err) \
	MAKE_NETSERVICE_HRESULT(SEVERITY_SUCCESS, itf, err)

#define MAKE_NETSERVICE_ERROR(itf, err) \
	MAKE_NETSERVICE_HRESULT(SEVERITY_ERROR, itf, err)

//
// Interface codes (6 bits, 0x00 ~ 0x3F allowed)
// Status codes (10 bits, 0x000 ~ 0x3FF allowed)
//

#define ITF_SOCIALNETWORKSERVICE        0x01       // ISOCIALNETWORKSERVICE
#define ITF_DATAMANAGER           0x02       // IDATAMANAGER

///////////////////////////////////////////////////////////////////////////////
//
// ISOCIALNETWORKSERVICE
//
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//
// IDATAMANAGER
//
///////////////////////////////////////////////////////////////////////////////


#define NS_E_DMGR_PARSE_DATA_FAIL_ILL_FORMED	MAKE_NETSERVICE_ERROR(ITF_DATAMANAGER,0x001)
#define NS_E_DMGR_DELETE_MGR_FAIL_NO_TYPE	MAKE_NETSERVICE_ERROR(ITF_DATAMANAGER,0x002)

#define NS_S_DMGR_NO_DATA_OWNER	MAKE_NETSERVICE_ERROR(ITF_DATAMANAGER,0x999)