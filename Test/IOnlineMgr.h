#ifndef _IONLINEMGR_
#define _IONLINEMGR_

class GDataUploader;
class BackgroundUploadProgress;

#define MAX_URL 320

struct IOnlineUploader
{
	// DailyMotion related APIs
	virtual void SetAPIKey(LPCWSTR lpwszAPIKey) = 0;
	virtual void SetSecretKey(LPCWSTR lpwszSecretKey) = 0;

	/// Info
	virtual BOOL GetUploadLimits(double& dSizeLimit, double& dTimeLimit) = 0;
	virtual BOOL StartUpload(LPCWSTR lpszTitle, LPCWSTR lpszDescription, LPCWSTR lpszTag, LPCWSTR lpszChannel, LPCWSTR lpszPrivate, LPCWSTR lpszFileName) = 0;
	virtual DWORD GetStatusCodeAfterUpload() = 0;
	virtual void GetServerResponseAfterUpload(LPSTR szBuf, UINT *puBufSize) = 0;  

	/// Upload
	virtual void GetResultURL(WCHAR* pwszResult) = 0;

	/// from Thread.h
	virtual unsigned Join() = 0;

	/// Get Login & Permission URL instead of using ShellExecute
	virtual BOOL GetLoginPermissionURL(__inout_ecount(MAX_URL) WCHAR* pwszResult) = 0;
	/// return TRUE means the URL is the last page
	virtual BOOL CheckLoginResult(LPCWSTR lpszURL, BOOL& bSuccess) = 0;
	virtual BOOL DoRefreshToken(LPCWSTR lpszRefreshToken) = 0;
	virtual HRESULT UpdateChannelList() = 0;
	virtual UINT GetChannelSize() = 0;
	virtual HRESULT GetChannelIDbyIndex(UINT nIndex, LPWSTR pwszResult) = 0;
	virtual HRESULT GetChannelNamebyIndex(UINT nIndex, LPWSTR pwszResult) = 0;
	virtual LPCWSTR GetScope() = 0;
	virtual LPCWSTR GetRefreshToken() = 0;
	virtual BOOL GetAuthToken(WCHAR* lpszAuthToken) = 0;

	virtual BOOL GetRealUserName(WCHAR* pUserName) = 0; //Only for YouTube, empty for upload-denied
	virtual BOOL GetDisplayUserName(WCHAR* pUserName) = 0; //Only for YouTube
	virtual BOOL CreatePlaylist(WCHAR* lpszTitle, WCHAR* lpszSummary, WCHAR** lppszPlaylistID) = 0; //Only for YouTube
	virtual BOOL AddVideoIntoPlaylist(WCHAR* lpszVideoID, WCHAR* lpszPlaylistID) = 0; //Only for YouTube
	virtual void SetVideo3D(BOOL bIs3D) = 0; //Only for YouTube, not working, don't use it
	virtual INT ValidateToken(WCHAR* lpszAuthToken) = 0; //Only for YouTube, return value is the expires_in, -1 for invalid
};

typedef IOnlineUploader* (*pfnCreateOnlineUploader) (BackgroundUploadProgress *pProgress);
typedef void (*pfnReleaseOnlineUploader) (IOnlineUploader*);


#endif