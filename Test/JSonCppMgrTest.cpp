//#pragma comment(lib,"../../../thirdparty/jsoncpp/trunk/jsoncpp/build/vs71/debug/lib_json/json_vc71_libmtd.lib")
//#pragma comment(lib,"json_vc71_libmtd.lib")

#include "JSonCppMgrTest.h"
#include <FacebookPhotoModel.h>
#include <NetServiceErr.h>
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
	 szTestFile = "../Test/TestData/10photos.txt";
	fStream.open(szTestFile.c_str(),std::ios::binary);
	if (fStream.fail()){
		szTestFile += " Read Fail!!!";
		CPPUNIT_FAIL(szTestFile.c_str());
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
	szTestFile = "../Test/TestData/1photo.txt";
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
	int nResult = util::CDataMgrFactory::DeleteInstance(m_pJSonCppMgr);
	char szResult[100];
	memset(szResult,0x0,100);
	sprintf(szResult,"Delete Instance Fail: %d", nResult);
	CPPUNIT_ASSERT_MESSAGE(szResult , nResult ==S_OK);
}

void JSonCppMgrTest::TestParsePhotoList()
{
	//IPhotoList iPhotoList;
	model::CFacebookPhotoList iPhotoList;
	int nResult = m_pJSonCppMgr->ParsePhotoList(m_szTestPhotoList,iPhotoList, util::Facebook);
	char szResult[100];
	memset(szResult,0x0,100);
	sprintf(szResult,"function fail : %d",nResult);
	CPPUNIT_ASSERT_MESSAGE(szResult,nResult==S_OK);
}

void JSonCppMgrTest::TestParsePhoto()
{
	model::CFacebookPhoto iPhoto;
	int nResult = m_pJSonCppMgr->ParsePhoto(m_szTestPhoto,iPhoto, util::Facebook);
	char szResult[100];
	memset(szResult,0x0,100);
	sprintf(szResult,"function fail : %d",nResult);
	CPPUNIT_ASSERT_MESSAGE(szResult,nResult==S_OK);
}
