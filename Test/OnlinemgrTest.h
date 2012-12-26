#pragma once

#include <cppunit/extensions/HelperMacros.h>
#include <Windows.h>
#include "UploadProgress.h"
#include "IOnlineMgr.h"

const WCHAR UPLOAD_UNKNOWN_ERR[_MAX_PATH] = L"UPLOAD_UNKNOWN_ERR";
const WCHAR NO_LINKED_ACCOUNT[_MAX_PATH] = L"NO_LINKED_ACCOUNT";

#define TOKAN_MAX 1024

enum ONLINE_TYPE
{
	ONLINE_NONE,
	ONLINE_FACEBOOK,
	ONLINE_YOUTUBE
};

class COnlinemgrTest : public CPPUNIT_NS::TestFixture, public BackgroundUploadProgress
{
	CPPUNIT_TEST_SUITE( COnlinemgrTest );
	CPPUNIT_TEST( testLoginUrl );
	CPPUNIT_TEST( testGetAccessToken );
	CPPUNIT_TEST( testCheckLoginResult );
	CPPUNIT_TEST_SUITE_END();
public:
	COnlinemgrTest();
	~COnlinemgrTest();

	void setUp();

	void tearDown();

	void testLoginUrl();
	void testGetAccessToken();
	void testCheckLoginResult();

protected:
	void SetCurrentUploader(ONLINE_TYPE onlineType);
	bool CreateUploader(ONLINE_TYPE onlineType);

public:
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
	ONLINE_TYPE m_onlineType;
	bool m_bCancelUpload;
	HINSTANCE m_hOnlineMgr;
	IOnlineUploader* m_pFacebookUploader;
	IOnlineUploader* m_pYouTubeUploader;
	IOnlineUploader* m_pCurrentUploader;

};
