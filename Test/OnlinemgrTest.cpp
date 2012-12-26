
#include "OnlinemgrTest.h"

#include <Shlwapi.h>
#include <tchar.h>

CPPUNIT_TEST_SUITE_REGISTRATION( COnlinemgrTest );


void COnlinemgrTest::setUp()
{
	TCHAR szExePath[_MAX_PATH];
	GetModuleFileName(NULL, szExePath, _MAX_PATH);
	PathRemoveFileSpec(szExePath);
	_tcscat_s(szExePath, _T("OnlineMgr.dll"));
	m_hOnlineMgr = LoadLibrary(szExePath);

	pfnCreateOnlineUploader fnCreateFacebookUploader = (pfnCreateOnlineUploader) GetProcAddress(m_hOnlineMgr, "CreateFacebookUploader");
	//m_pFacebookUploader = fnCreateFacebookUploader(this);
}

void COnlinemgrTest::tearDown()
{
	if (m_hOnlineMgr)
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

		FreeLibrary(m_hOnlineMgr);
		m_hOnlineMgr = NULL;
	}
}

void COnlinemgrTest::testLoginUrl()
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
