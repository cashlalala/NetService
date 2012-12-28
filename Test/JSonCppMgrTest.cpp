//#pragma comment(lib,"../../../thirdparty/jsoncpp/trunk/jsoncpp/build/vs71/debug/lib_json/json_vc71_libmtd.lib")
//#pragma comment(lib,"json_vc71_libmtd.lib")

#include "JSonCppMgrTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION( JSonCppMgrTest );

JSonCppMgrTest::JSonCppMgrTest(void)
{
}

JSonCppMgrTest::~JSonCppMgrTest(void)
{
}

void JSonCppMgrTest::setUp()
{
	m_pJSonCppMgr = util::CDataMgrFactory::GetInstance(util::JsonCpp);
	m_szTestPhotoListString = 
		" {\"data\":[{\"id\":\"4589117478468\",\"link\":\"http://www.facebook.com/photo.php?fbid=4589117478468&set=p.4589117478468&type=1\",\"source\":\"http://sphotos-a.ak.fbcdn.net/hphotos-ak-snc6/s720x720/222394_4589117478468_374208013_n.jpg\",\"width\":540,\"height\":720,\"images\":[{\"height\":2048,\"width\":1536,\"source\":\"http://sphotos-a.ak.fbcdn.net/hphotos-ak-snc6/s2048x2048/222394_4589117478468_374208013_n.jpg\"},{\"height\":960,\"width\":720,\"source\":\"http://sphotos-a.ak.fbcdn.net/hphotos-ak-snc6/222394_4589117478468_374208013_n.jpg\"},{\"height\":720,\"width\":540,\"source\":\"http://sphotos-a.ak.fbcdn.net/hphotos-ak-snc6/s720x720/222394_4589117478468_374208013_n.jpg\"},{\"height\":600,\"width\":450,\"source\":\"http://sphotos-a.ak.fbcdn.net/hphotos-ak-snc6/s600x600/222394_4589117478468_374208013_n.jpg\"},{\"height\":480,\"width\":360,\"source\":\"http://sphotos-a.ak.fbcdn.net/hphotos-ak-snc6/s480x480/222394_4589117478468_374208013_n.jpg\"},{\"height\":320,\"width\":240,\"source\":\"http://sphotos-a.ak.fbcdn.net/hphotos-ak-snc6/s320x320/222394_4589117478468_374208013_n.jpg\"},{\"height\":240,\"width\":180,\"source\":\"http://photos-a.ak.fbcdn.net/hphotos-ak-snc6/222394_4589117478468_374208013_a.jpg\"},{\"height\":130,\"width\":97,\"source\":\"http://photos-a.ak.fbcdn.net/hphotos-ak-snc6/222394_4589117478468_374208013_s.jpg\"},{\"height\":130,\"width\":97,\"source\":\"http://photos-a.ak.fbcdn.net/hphotos-ak-snc6/s75x225/222394_4589117478468_374208013_s.jpg\"}],\"created_time\":\"2012-12-12T15:49:46+0000\"},{\"id\":\"4589116918454\",\"link\":\"http://www.facebook.com/photo.php?fbid=4589116918454&set=p.4589116918454&type=1\",\"source\":\"http://sphotos-h.ak.fbcdn.net/hphotos-ak-ash4/s720x720/391987_4589116918454_154158580_n.jpg\",\"width\":540,\"height\":720,\"images\":[{\"height\":2048,\"width\":1536,\"source\":\"http://sphotos-h.ak.fbcdn.net/hphotos-ak-ash4/s2048x2048/391987_4589116918454_154158580_n.jpg\"},{\"height\":960,\"width\":720,\"source\":\"http://sphotos-h.ak.fbcdn.net/hphotos-ak-ash4/391987_4589116918454_154158580_n.jpg\"},{\"height\":720,\"width\":540,\"source\":\"http://sphotos-h.ak.fbcdn.net/hphotos-ak-ash4/s720x720/391987_4589116918454_154158580_n.jpg\"},{\"height\":600,\"width\":450,\"source\":\"http://sphotos-h.ak.fbcdn.net/hphotos-ak-ash4/s600x600/391987_4589116918454_154158580_n.jpg\"},{\"height\":480,\"width\":360,\"source\":\"http://sphotos-h.ak.fbcdn.net/hphotos-ak-ash4/s480x480/391987_4589116918454_154158580_n.jpg\"},{\"height\":320,\"width\":240,\"source\":\"http://sphotos-h.ak.fbcdn.net/hphotos-ak-ash4/s320x320/391987_4589116918454_154158580_n.jpg\"},{\"height\":240,\"width\":180,\"source\":\"http://photos-h.ak.fbcdn.net/hphotos-ak-ash4/391987_4589116918454_154158580_a.jpg\"},{\"height\":130,\"width\":97,\"source\":\"http://photos-h.ak.fbcdn.net/hphotos-ak-ash4/391987_4589116918454_154158580_s.jpg\"},{\"height\":130,\"width\":97,\"source\":\"http://photos-h.ak.fbcdn.net/hphotos-ak-ash4/s75x225/391987_4589116918454_154158580_s.jpg\"}],\"created_time\":\"2012-12-12T15:49:41+0000\"}],\"paging\":{\"previous\":\"https://graph.facebook.com/724760664/photos?fields=id,link,source,width,height,images&limit=2&access_token=AAACEdEose0cBAMoK5FX3sFEfc8jtEAPSxkUSNO9CPWZBuIq53Gv0DeputFQshajW1wy7gcKfs9Iwz7koMyasxY7C6fqGuyX5IIjAvuQZDZD&since=1355327386&__previous=1\",\"next\":\"https://graph.facebook.com/724760664/photos?fields=id,link,source,width,height,images&limit=2&access_token=AAACEdEose0cBAMoK5FX3sFEfc8jtEAPSxkUSNO9CPWZBuIq53Gv0DeputFQshajW1wy7gcKfs9Iwz7koMyasxY7C6fqGuyX5IIjAvuQZDZD&until=1355327380\"}}";
}

void JSonCppMgrTest::tearDown()
{
	//delete m_pJSonCppMgr;
}

void JSonCppMgrTest::TestParsePhotoList()
{
	
}
