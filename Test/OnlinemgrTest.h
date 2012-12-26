#pragma once

#include <cppunit/extensions/HelperMacros.h>
#include <Windows.h>
#include "UploadProgress.h"
#include "IOnlineMgr.h"


class COnlinemgrTest : public CPPUNIT_NS::TestFixture, public BackgroundUploadProgress
{
	CPPUNIT_TEST_SUITE( COnlinemgrTest );
	CPPUNIT_TEST( testLoginUrl );
	CPPUNIT_TEST_SUITE_END();
public:
	//COnlinemgrTest();
	//~COnlinemgrTest();

	void setUp();

	void tearDown();

	void testLoginUrl();

	// Interface in BackgroundUploadProgress
	virtual void OnBackgroundUploadBegin() {}
	virtual void OnBackgroundUploadComplete(HRESULT hr);

	// Interface in UploadProgress
	virtual void OnResolvingName(LPCTSTR lpsz) {}
	virtual void OnNameResolved(LPCTSTR lpsz) {}
	virtual void OnConnectingToServer(LPCTSTR lpsz) {}
	virtual void OnConnectedToServer(LPCTSTR lpsz) {}
	virtual void OnSendingRequest() {}
	virtual void OnRequestSent(DWORD dwBytesSent) {}
	virtual void OnReceivingResponse() {}
	virtual void OnResponseReceived(DWORD dwBytesReceived) {}
	virtual void OnClosingConnection() {}
	virtual void OnConnectionClosed() {}

	virtual void OnFileBegin(LPCTSTR lpszPathName) {}
	virtual void OnFileProgress(LPCTSTR lpszPathName, DWORD dwFileBytesSent, DWORD dwFileBytesTotal, DWORD dwSecondsToFileCompletion, DWORD dwOverallBytesSent, DWORD dwOverallBytesTotal, DWORD dwSecondsToOverallCompletion, DWORD dwBytesPerSecond);
	virtual void OnFileComplete(LPCTSTR lpszPathName, HRESULT hr) {};

	virtual bool CheckCancel();
	virtual void OnExtensionURLHandle(LPCTSTR lpszEvent, LPCTSTR lpszURL) {};

private:
	bool m_bCancelUpload;
	HINSTANCE m_hOnlineMgr;
	IOnlineUploader* m_pFacebookUploader;

};
