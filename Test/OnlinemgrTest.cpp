
#include "OnlinemgrTest.h"
#include <Windows.h>
#include "IOnlineMgr.h"
#include <Shlwapi.h>
#include <tchar.h>

CPPUNIT_TEST_SUITE_REGISTRATION( COnlinemgrTest );

static HINSTANCE g_hOnlineMgr;


void COnlinemgrTest::setUp()
{
	TCHAR szExePath[_MAX_PATH];
	GetModuleFileName(NULL, szExePath, _MAX_PATH);
	PathRemoveFileSpec(szExePath);
	_tcscat_s(szExePath, _T("OnlineMgr.dll"));
	g_hOnlineMgr = LoadLibrary(szExePath);

	pfnCreateOnlineUploader fnCreateFacebookUploader = (pfnCreateOnlineUploader) GetProcAddress(g_hOnlineMgr, "CreateFacebookUploader");
}

void COnlinemgrTest::tearDown()
{
	if (g_hOnlineMgr)
	{
		//if (m_pFacebookUploader)
		//{
		//	pfnReleaseOnlineUploader fnReleaseFacebookUploader = (pfnReleaseOnlineUploader) GetProcAddress(m_hOnlineMgr, "ReleaseFacebookUploader");
		//	fnReleaseFacebookUploader(m_pFacebookUploader);
		//	m_pFacebookUploader = NULL;
		//}

		//if (m_pYouTubeUploader)
		//{
		//	pfnReleaseOnlineUploader fnReleaseYouTubeUploader = (pfnReleaseOnlineUploader) GetProcAddress(m_hOnlineMgr, "ReleaseYouTubeUploader");
		//	fnReleaseYouTubeUploader(m_pYouTubeUploader);
		//	m_pYouTubeUploader = NULL;
		//}

		FreeLibrary(g_hOnlineMgr);
		g_hOnlineMgr = NULL;
	}
}

void COnlinemgrTest::testLoginUrl()
{

}
