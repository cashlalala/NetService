#include "StdAfx.h"
#include "JSonCppMgr.h"
#include "NetServiceErr.h"

#include "FBFields.h"
#include "FlickrFields.h"

#include "ErrorParseRuler.h"
#include "PhotoParseRuler.h"
#include "UserParseRuler.h"
#include "AlbumParseRuler.h"
#include "ProfileParseRuler.h"
#include "ImageParseRuler.h"
#include "VideoParseRuler.h"

#include <json/json.h>

#define ERROR_RETURN(retVal) if(!SUCCEEDED(retVal)) return retVal;

using util::CJsonCppMgr;

CJsonCppMgr::CJsonCppMgr(void)
{
	m_pLogger = util::CLoggerMgr::GetLogger(Log4Cxx,"CJsonCppMgr");
}

CJsonCppMgr::~CJsonCppMgr(void)
{
}

int util::CJsonCppMgr::ParsePhotoList( IPhotoList& iPhotoList, string szInput, IError& iError  ) 
{
	int nResult = E_FAIL;
	Json::Reader jrReader;
	Json::Value jvRoot;
	if (jrReader.parse(szInput.c_str(),jvRoot))
	{
		CErrorParseRuler cErrRuler((void*)&jvRoot);
		nResult = iError.AcceptErrorParser(cErrRuler);
		ERROR_RETURN(nResult)

		CPhotoListParseRuler cPhotoLstRuler((void*)&jvRoot);
		iPhotoList.AcceptPhotoListParser(cPhotoLstRuler);		
	}
	else
		nResult = NS_E_DMGR_PARSE_DATA_FAIL_ILL_FORMED;

	return nResult;
}

int util::CJsonCppMgr::ParsePhoto( IPhoto& iPhoto, string szInput, IError& iError  ) 
{
	int nResult = E_FAIL;
	Json::Reader jrReader;
	Json::Value jvRoot;

	if (jrReader.parse(szInput.c_str(),jvRoot))
	{
		CErrorParseRuler cErrRuler((void*)&jvRoot);
		nResult = iError.AcceptErrorParser(cErrRuler);
		ERROR_RETURN(nResult)

		CPhotoParseRuler cPhotoRuler((void*)&jvRoot);
		iPhoto.AcceptPhotoParser(cPhotoRuler);
	}
	else
		nResult = NS_E_DMGR_PARSE_DATA_FAIL_ILL_FORMED;

	return nResult;
}

int util::CJsonCppMgr::ParseUser( IUser& iUser, string szInput, IError& iError )
{
	int nResult = E_FAIL;
	Json::Reader jrReader;
	Json::Value jvRoot;

	if (jrReader.parse(szInput.c_str(),jvRoot))
	{
		CErrorParseRuler cErrRuler((void*)&jvRoot);
		nResult = iError.AcceptErrorParser(cErrRuler);
		ERROR_RETURN(nResult)

		CUserParseRuler cUserRuler((void*)&jvRoot);
		iUser.AcceptUserParser(cUserRuler);
	}
	else
		nResult = NS_E_DMGR_PARSE_DATA_FAIL_ILL_FORMED;

	return nResult;
}


int util::CJsonCppMgr::ParseError( IError& iError, string szInput )
{
	int nResult = E_FAIL;
	Json::Reader jrReader;
	Json::Value jvRoot;

	if (jrReader.parse(szInput.c_str(),jvRoot))
	{
		CErrorParseRuler cErrRuler((void*)&jvRoot);
		nResult = iError.AcceptErrorParser(cErrRuler);
		ERROR_RETURN(nResult)
	}
	else
		nResult = NS_E_DMGR_PARSE_DATA_FAIL_ILL_FORMED;

	return nResult;
}

int util::CJsonCppMgr::ParseFriendList( IUserList& iUserList, string szInput, IError& iError )
{
	int nResult = E_FAIL;
	Json::Reader jrReader;
	Json::Value jvRoot;

	if (jrReader.parse(szInput.c_str(),jvRoot))
	{
		CErrorParseRuler cErrRuler((void*)&jvRoot);
		nResult = iError.AcceptErrorParser(cErrRuler);
		ERROR_RETURN(nResult)

		CUserListParseRuler cUsrLstRuler((void*)&jvRoot);
		iUserList.AcceptUserListParser(cUsrLstRuler);	
	}
	else
		nResult = NS_E_DMGR_PARSE_DATA_FAIL_ILL_FORMED;

	return nResult;
}

int util::CJsonCppMgr::ParseVideoList( IVideoList&iVideoList, string szInput, IError& iError )
{
	int nResult = E_FAIL;
	Json::Reader jrReader;
	Json::Value jvRoot;

	if (jrReader.parse(szInput.c_str(),jvRoot))
	{
		CErrorParseRuler cErrRuler((void*)&jvRoot);
		nResult = iError.AcceptErrorParser(cErrRuler);
		ERROR_RETURN(nResult)

		CVideoListParseRuler cVideoLstRuler((void*)&jvRoot);
		iVideoList.AcceptVideoListParser(cVideoLstRuler);
	}
	else
		nResult = NS_E_DMGR_PARSE_DATA_FAIL_ILL_FORMED;

	return nResult;
}

int util::CJsonCppMgr::ParseAlbumList( IAlbumList& iAlbumList, string szInput, IError& iError )
{
	int nResult = E_FAIL;
	Json::Reader jrReader;
	Json::Value jvRoot;

	if (jrReader.parse(szInput.c_str(),jvRoot))
	{
		CErrorParseRuler cErrRuler((void*)&jvRoot);
		nResult = iError.AcceptErrorParser(cErrRuler);
		ERROR_RETURN(nResult)

		CAlbumListParseRuler cAlbumLstRuler((void*)&jvRoot);
		iAlbumList.AcceptAlbumListParser(cAlbumLstRuler);		
	}
	else
		nResult = NS_E_DMGR_PARSE_DATA_FAIL_ILL_FORMED;

	return nResult;
}

int util::CJsonCppMgr::ParseImageList( IImageList& listImage, string szInput, IError& iError )
{
	int nResult = E_FAIL;
	Json::Reader jrReader;
	Json::Value jvRoot;
	if (jrReader.parse(szInput.c_str(),jvRoot))
	{
		CErrorParseRuler cErrRuler((void*)&jvRoot);
		nResult = iError.AcceptErrorParser(cErrRuler);
		ERROR_RETURN(nResult)

		CImageListParseRuler cImgLstRuler((void*)&jvRoot);
		listImage.AcceptImageListParser(cImgLstRuler);
	}
	else
		nResult = NS_E_DMGR_PARSE_DATA_FAIL_ILL_FORMED;

	return nResult;
}

int util::CJsonCppMgr::ParseProfile( IProfile& iProfile, string szInput, IError& iError )
{
	int nResult = E_FAIL;
	Json::Reader jrReader;
	Json::Value jvRoot;

	if (jrReader.parse(szInput.c_str(),jvRoot))
	{
		CErrorParseRuler cErrRuler((void*)&jvRoot);
		nResult = iError.AcceptErrorParser(cErrRuler);
		ERROR_RETURN(nResult)

		CProfileParseRuler cProfileRuler((void*)&jvRoot);
		iProfile.AcceptProfileParser(cProfileRuler);
	}
	else
		nResult = NS_E_DMGR_PARSE_DATA_FAIL_ILL_FORMED;

	return nResult;
}

int util::CJsonCppMgr::ParseFkrFrob( string& szFrob, string szInput, IError& iError )
{
	int nResult = E_FAIL;
	Json::Reader jrReader;
	Json::Value jvRoot;

	if (jrReader.parse(szInput.c_str(),jvRoot))
	{
		CErrorParseRuler cErrRuler((void*)&jvRoot);
		nResult = iError.AcceptErrorParser(cErrRuler);
		ERROR_RETURN(nResult)

		szFrob = jvRoot[FLICK_FIELD_FROB][FLICK_FIELD_CONTENT].asString();
		nResult = S_OK;
	}
	else
		nResult = NS_E_DMGR_PARSE_DATA_FAIL_ILL_FORMED;

	return nResult;
}

int util::CJsonCppMgr::ParseFkrAuthToken( SysMaps::Str2Str& mapAuth, string szInput,IError& iError )
{
	int nResult = E_FAIL;
	Json::Reader jrReader;
	Json::Value jvRoot;
	if (jrReader.parse(szInput.c_str(),jvRoot))
	{
		CErrorParseRuler cErrRuler((void*)&jvRoot);
		nResult = iError.AcceptErrorParser(cErrRuler);
		ERROR_RETURN(nResult)

		mapAuth[FLICK_AUTH_TOKEN] = jvRoot[FLICK_AUTH][FLICK_AUTH_TOKEN][FLICK_AUTH_TOKEN_CONTENT].asString();
		mapAuth[FLICK_AUTH_NSID] = jvRoot[FLICK_AUTH][FLICK_AUTH_USER][FLICK_AUTH_NSID].asString();
		nResult = S_OK;
	}
	else
		nResult = NS_E_DMGR_PARSE_DATA_FAIL_ILL_FORMED;

	return nResult;
}

int util::CJsonCppMgr::ParseFBSrouceSmall( SysList::Str2StrMapList& listMap, string szInput, IError& iError )
{
	int nResult = E_FAIL;
	Json::Reader jrReader;
	Json::Value jvRoot;

	if (jrReader.parse(szInput.c_str(),jvRoot))
	{
		CErrorParseRuler cErrRuler((void*)&jvRoot);
		nResult = iError.AcceptErrorParser(cErrRuler);
		ERROR_RETURN(nResult)

		int nSize = jvRoot[FB_DATA].size();
		for (int i=0;i<nSize;++i)
		{
			SysMaps::Str2Str mapCoverPhoto;
			mapCoverPhoto[FB_IMAGE_SOURCE_SMALL] = jvRoot[FB_DATA][i][FB_IMAGE_SOURCE_SMALL].asString();
			mapCoverPhoto[FB_ALBUM_OBJECT_ID] = jvRoot[FB_DATA][i][FB_ALBUM_OBJECT_ID].asString();
			listMap.push_back(mapCoverPhoto);
		}
		nResult = S_OK;
	}
	else
		nResult = NS_E_DMGR_PARSE_DATA_FAIL_ILL_FORMED;

	return nResult;
}
