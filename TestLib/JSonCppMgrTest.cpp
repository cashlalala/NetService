//#pragma comment(lib,"../../../thirdparty/jsoncpp/trunk/jsoncpp/build/vs71/debug/lib_json/json_vc71_libmtd.lib")
//#pragma comment(lib,"json_vc71_libmtd.lib")

#include "JSonCppMgrTest.h"
#include <NetServiceErr.h>
#include <FBPhotoModel.h>
#include <FBErrorModel.h>

#include <fstream>

CPPUNIT_TEST_SUITE_REGISTRATION( JSonCppMgrTest );

JSonCppMgrTest::JSonCppMgrTest(void)
{

	m_pJSonCppMgr = NULL;
	
	std::ifstream fStream;
	int nLen = 0;
	char* lpszTemp = NULL;
	string szTestFile;

	//gen the access_token by yourself

	//load photo list test data 
	//queried by https://graph.facebook.com/me/photos?fields=link,images,height,width,id&limit=10&access_token=[yourtoken]
	 szTestFile = "..\\TestData\\10photos.txt";
	fStream.open(szTestFile.c_str(),std::ios::binary);
	if (fStream.fail()){
		szTestFile += " Read Fail!!!";
		char a[100];
		memset(a,0x0,100);
		strcpy(a,szTestFile.c_str());
		CPPUNIT_FAIL(a);
		return;
	}
	fStream.seekg (0, std::ios::end);
	 nLen = fStream.tellg();
	fStream.seekg (0, std::ios::beg);
	lpszTemp= new char[nLen+1];
	memset(lpszTemp,0x0,sizeof(lpszTemp));
	fStream.read(lpszTemp,nLen);
	m_szTestPhotoList = string(lpszTemp);

	delete[] lpszTemp;
	fStream.close();
	
	//load photo test data
	//queried by https://graph.facebook.com/4589117478468
	szTestFile = "..\\TestData\\1photo.txt";
	fStream.open(szTestFile.c_str(),std::ios::binary);
	if (fStream.fail()){
		szTestFile += " Read Fail!!!\0";
		CPPUNIT_FAIL(szTestFile.c_str());
		return;
	}
	fStream.seekg (0, std::ios::end);
	nLen = fStream.tellg();
	fStream.seekg (0, std::ios::beg);
	lpszTemp= new char[nLen+1];
	memset(lpszTemp,0x0,sizeof(lpszTemp));
	fStream.read(lpszTemp,nLen);
	m_szTestPhoto = string(lpszTemp);

	delete[] lpszTemp;
	fStream.close();
	
}

JSonCppMgrTest::~JSonCppMgrTest(void)
{

}

void JSonCppMgrTest::setUp()
{
	m_pJSonCppMgr = util::CDataMgrFactory::GetInstance(util::JsonCpp);
}

void JSonCppMgrTest::tearDown()
{
	//int nResult = util::CDataMgrFactory::DeleteInstance(m_pJSonCppMgr);
	delete m_pJSonCppMgr;
	//m_pJSonCppMgr = NULL;
	//char szResult[100];
	//memset(szResult,0x0,100);
	//sprintf(szResult,"Delete Instance Fail: %d", nResult);
	//CPPUNIT_ASSERT_MESSAGE(szResult , nResult ==0);
}

void JSonCppMgrTest::TestParsePhotoList()
{
	model::CFBPhotoList iPhotoList;
	model::CFBError cFBError;
	int nResult = m_pJSonCppMgr->ParsePhotoList(iPhotoList,m_szTestPhotoList, util::Facebook,cFBError);
	CPPUNIT_ASSERT_MESSAGE(cFBError.szMsg.c_str(),nResult==0);
}

void JSonCppMgrTest::TestParsePhoto()
{
	model::CFBPhoto iPhoto;
	model::CFBError cFbErr;
	int nResult = m_pJSonCppMgr->ParsePhoto(iPhoto, m_szTestPhoto, util::Facebook, cFbErr);
	CPPUNIT_ASSERT_MESSAGE(cFbErr.szMsg.c_str(),nResult==0);
}
