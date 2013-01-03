#pragma once

#include "..\src\DataMgrFactory.h"
#include <cppunit/extensions/HelperMacros.h>


class JSonCppMgrTest : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( JSonCppMgrTest );
	CPPUNIT_TEST( TestParsePhotoList );
	CPPUNIT_TEST( TestParsePhoto );
	CPPUNIT_TEST_SUITE_END();
public:
	JSonCppMgrTest(void);
	~JSonCppMgrTest(void);

	void setUp();
	void tearDown();
protected:
	void TestParsePhotoList();
	void TestParsePhoto();
private:
	util::IDataManager* m_pJSonCppMgr;
	string m_szTestPhotoList;
	string m_szTestPhoto;
};
