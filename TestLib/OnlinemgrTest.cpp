
#include "OnlinemgrTest.h"

#include <Shlwapi.h>
#include <tchar.h>

CPPUNIT_TEST_SUITE_REGISTRATION( COnlinemgrTest );

void COnlinemgrTest::testLoginUrl()
{
	WCHAR buf[4096] = L"";
	m_pCurrentUploader->GetLoginPermissionURL(buf);
	wprintf(L"LogUrl: [%s]",buf);
	CPPUNIT_ASSERT(wcscmp(buf,L"")!=0);
}

void COnlinemgrTest::testGetAccessToken()
{
	WCHAR szToken[TOKAN_MAX] = L"";
	if (!m_pCurrentUploader->GetAuthToken(szToken))
	{
		CPPUNIT_FAIL("[OnlineMgr] GetAuthToken(): fail to get token!");
	}
	wprintf(L"AccessToken:[%s]",szToken);
	CPPUNIT_ASSERT(wcscmp(szToken,L"")!=0);

}


void COnlinemgrTest::testCheckLoginResult()
{

	//WCHAR buf[4096] = L"";
	//m_pCurrentUploader->GetLoginPermissionURL(buf);

	//navigate2()

	//if (!lpwszTitle)
	//{
	//	return Py_BuildValue("s", "");
	//}
	//if (!m_pCurrentUploader)
	//{
	//	dprintf(L"[PyOnlineMgr] CheckLoginResult(): uploader %d instance does not exist!", m_onlineType);
	//	return Py_BuildValue("s", "");
	//}

	//BOOL bSuccess(FALSE);
	//if (m_pCurrentUploader->CheckLoginResult(lpwszTitle, bSuccess))
	//{
	//	if (bSuccess)
	//	{
	//		return Py_BuildValue("s", "granted");
	//	}
	//	else
	//	{
	//		return Py_BuildValue("s", "refused");
	//	}
	//}
}


void COnlinemgrTest::setUp()
{
	SetCurrentUploader(ONLINE_FACEBOOK);
}

void COnlinemgrTest::tearDown()
{

}



void COnlinemgrTest::OnBackgroundUploadComplete( HRESULT hr )
{
	throw std::exception("The method or operation is not implemented.");
}

bool COnlinemgrTest::CheckCancel()
{
	return m_bCancelUpload;
}

void COnlinemgrTest::OnFileProgress( LPCTSTR lpszPathName, DWORD dwFileBytesSent, DWORD dwFileBytesTotal, DWORD dwSecondsToFileCompletion, DWORD dwOverallBytesSent, DWORD dwOverallBytesTotal, DWORD dwSecondsToOverallCompletion, DWORD dwBytesPerSecond )
{

}

COnlinemgrTest::COnlinemgrTest() : m_onlineType(ONLINE_NONE), m_hOnlineMgr(NULL), m_pFacebookUploader(NULL), m_pYouTubeUploader(NULL), m_pCurrentUploader(NULL), m_bCancelUpload(false)
{
	TCHAR szExePath[_MAX_PATH];
	GetModuleFileName(NULL, szExePath, _MAX_PATH);
	PathRemoveFileSpec(szExePath);
	PathAddBackslash(szExePath);
	_tcscat_s(szExePath, _T("OnlineMgr.dll"));
	m_hOnlineMgr = LoadLibrary(szExePath);

	pfnCreateOnlineUploader fnCreateFacebookUploader = (pfnCreateOnlineUploader) GetProcAddress(m_hOnlineMgr, "CreateFacebookUploader");
}

COnlinemgrTest::~COnlinemgrTest()
{
	if (m_hOnlineMgr)
	{
		if (m_pFacebookUploader)
		{
			pfnReleaseOnlineUploader fnReleaseFacebookUploader = (pfnReleaseOnlineUploader) GetProcAddress(m_hOnlineMgr, "ReleaseFacebookUploader");
			fnReleaseFacebookUploader(m_pFacebookUploader);
			m_pFacebookUploader = NULL;
		}

		//if (m_pYouTubeUploader)
		//{
		//	pfnReleaseOnlineUploader fnReleaseYouTubeUploader = (pfnReleaseOnlineUploader) GetProcAddress(m_hOnlineMgr, "ReleaseYouTubeUploader");
		//	fnReleaseYouTubeUploader(m_pYouTubeUploader);
		//	m_pYouTubeUploader = NULL;
		//}

		FreeLibrary(m_hOnlineMgr);
		m_hOnlineMgr = NULL;
	}
}

void COnlinemgrTest::SetCurrentUploader( ONLINE_TYPE onlineType )
{
	m_pCurrentUploader = NULL;
	switch (onlineType)
	{
	case ONLINE_FACEBOOK:
		if (m_pFacebookUploader)
		{
			m_pCurrentUploader = m_pFacebookUploader;
		}
		else if (CreateUploader(onlineType))
		{
			m_pCurrentUploader = m_pFacebookUploader;
		}
		break;
	case ONLINE_YOUTUBE:
		if (m_pYouTubeUploader)
		{
			m_pCurrentUploader = m_pYouTubeUploader;
		}
		else if (CreateUploader(onlineType))
		{
			m_pCurrentUploader = m_pYouTubeUploader;
		}
		break;
	}

	if (m_pCurrentUploader)
	{
		m_onlineType = onlineType;
	}
}

BOOL COnlinemgrTest::CreateUploader( ONLINE_TYPE onlineType )
{
	if (!m_hOnlineMgr)
	{
		return FALSE;
	}

	BOOL bSuc = FALSE;
	switch (onlineType)
	{
	case ONLINE_FACEBOOK:
		if (!m_pFacebookUploader)
		{
			pfnCreateOnlineUploader fnCreateFacebookUploader = (pfnCreateOnlineUploader) GetProcAddress(m_hOnlineMgr, "CreateFacebookUploader");
			if (!fnCreateFacebookUploader)
			{
				printf("[PyOnlineMgr] CreateUploader(): Get function CreateFacebookUploader failed!");
			}
			m_pFacebookUploader = fnCreateFacebookUploader(this);
			if (m_pFacebookUploader)
				bSuc = TRUE;
		}
		break;
	case ONLINE_YOUTUBE:
		if (!m_pYouTubeUploader)
		{
			pfnCreateOnlineUploader fnCreateYouTubeUploader = (pfnCreateOnlineUploader) GetProcAddress(m_hOnlineMgr, "CreateYouTubeUploader");
			if (!fnCreateYouTubeUploader)
			{
				printf("[PyOnlineMgr] CreateUploader(): Get function CreateYouTubeUploader failed!");
			}
			m_pYouTubeUploader = fnCreateYouTubeUploader(this);
			if (m_pYouTubeUploader)
				bSuc = TRUE;
		}
		break;
	}

	return bSuc;
}
