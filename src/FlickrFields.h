#pragma once

#define FLICK_PARAM_AUTH_TOKEN "auth_token"
#define FLICK_PARAM_API_KEY "api_key"
#define FLICK_PARAM_API_SIG "api_sig"
#define FLICK_PARAM_PERMISSION "perms"
#define FLICK_PARAM_FORMAT "format"
#define FLICK_PARAM_METHOD "method"
#define FLICK_PARAM_FROB "frob"
#define FLICK_PARAM_PERPAGE "per_page"
#define FLICK_PARAM_PAGE "page"
#define FLICK_PARAM_PAGES "pages"
#define FLICK_PARAM_USER_ID "user_id"
#define FLICK_PARAM_NO_JSON_CALLBACK "nojsoncallback"
#define FLICK_PARAM_MEDIA "media"
#define FLICK_PARAM_PHOTOSET_ID "photoset_id"

#define FLICK_OAUTH_CALLBACK "oauth_callback"

#define FLICK_FORMAT_JSON "json"

#define FLICK_FIELD_STAT "stat"
#define FLICK_FIELD_CONTENT "_content"
#define FLICK_FIELD_FROB FLICK_PARAM_FROB
#define FLICK_FIELD_EXTRA		"extras"

#define FLICK_VALUE_MEDIA_PHOTO "photo"

#define FLICK_AUTH "auth"
#define FLICK_AUTH_TOKEN "token"
#define FLICK_AUTH_NSID "nsid"
#define FLICK_AUTH_USER "user"
#define FLICK_AUTH_TOKEN_CONTENT FLICK_FIELD_CONTENT

#define FLICK_PHOTOSETS		"photosets"
#define FLICK_PHOTOSETS_PAGE FLICK_PARAM_PAGE
#define FLICK_PHOTOSETS_PAGES FLICK_PARAM_PAGES
#define FLICK_PHOTOSETS_PERPAGE "perpage"
#define FLICK_PHOTOSETS_TOTAL "total"
#define FLICK_PHOTOSET	"photoset"
#define FLICK_PHOTOSET_ID			"id"
#define FLICK_PHOTOSET_SERVER "server"
#define FLICK_PHOTOSET_PRIMARY "primary"
#define FLICK_PHOTOSET_SECRET "secret"
#define FLICK_PHOTOSET_FARM		"farm"
#define FLICK_PHOTOSET_PHOTOS "photos"
#define FLICK_PHOTOSET_VIDEOS "videos"
#define FLICK_PHOTOSET_TITLE "title"
#define FLICK_PHOTOSET_DESCRIPTION "description"

#define FLICK_CONTACTS "contacts"
#define FLICK_CONTACTS_PAGE FLICK_PARAM_PAGE
#define FLICK_CONTACTS_PAGES FLICK_PARAM_PAGES
#define FLICK_CONTACTS_PERPAGE FLICK_PHOTOSETS_PERPAGE
#define FLICK_CONTACTS_TOTAL FLICK_PHOTOSETS_TOTAL
#define FLICK_CONTACTS_CONTACT "contact"
#define FLICK_CONTACT_NSID "nsid"
#define FLICK_CONTACT_USR_NAME "username"
#define FLICK_CONTACT_ICON_SVR "iconserver"
#define FLICK_CONTACT_ICON_FARM "iconfarm"
#define FLICK_CONTACT_REAL_NAME "realname"
#define FLICK_CONTACT_FRIEND "friend"
#define FLICK_CONTACT_FAMILY "family"

#define FLICK_PEOPLE_PERSON "person"
#define FLICK_PEOPLE_PERSON_ID FLICK_PHOTOSET_ID
#define FLICK_PEOPLE_PERSON_NSID FLICK_CONTACT_NSID
#define FLICK_PEOPLE_PERSON_ISPRO "ispro"
#define FLICK_PEOPLE_PERSON_ISFRIEND FLICK_CONTACT_FRIEND
#define FLICK_PEOPLE_PERSON_ISFAMILY FLICK_CONTACT_FAMILY
#define FLICK_PEOPLE_PERSON_ICONSVR FLICK_CONTACT_ICON_SVR
#define FLICK_PEOPLE_PERSON_ICONFARM FLICK_CONTACT_ICON_FARM
#define FLICK_PEOPLE_PERSON_USR_NAME FLICK_CONTACT_USR_NAME
#define FLICK_PEOPLE_PERSON_REAL_NAME FLICK_CONTACT_REAL_NAME
#define FLICK_PEOPLE_PERSON_DESCRIPTION FLICK_PHOTOSET_DESCRIPTION


#define FLICK_PHOTOS	"photos"
#define FLICK_PHOTOS_PAGE  FLICK_PARAM_PAGE
#define FLICK_PHOTOS_PAGES  FLICK_PARAM_PAGES
#define FLICK_PHOTOS_PERPAGE  FLICK_PHOTOSETS_PERPAGE
#define FLICK_PHOTOS_TOTAL FLICK_PHOTOSETS_TOTAL
#define FLICK_PHOTO		FLICK_VALUE_MEDIA_PHOTO
#define FLICK_PHOTO_ID				FLICK_PHOTOSET_ID
#define FLICK_PHOTO_SERVER FLICK_PHOTOSET_SERVER
#define FLICK_PHOTO_SECRET FLICK_PHOTOSET_SECRET
#define FLICK_PHOTO_FARM "farm"
#define FLICK_PHOTO_TITLE "title"
#define FLICK_PHOTO_OWNER "owner"
#define FLICK_PHOTO_ISPUBLIC "ispublic"
#define FLICK_PHOTO_ISFRIEND "isfriend"
#define FLICK_PHOTO_ISFAMILY "isfamily"
#define FLICK_PHOTO_MEDIA		FLICK_PARAM_MEDIA
#define FLICK_PHOTO_URL "url"
#define FLICK_PHOTO_SQ "_sq"
#define FLICK_PHOTO_T		"_t"
#define FLICK_PHOTO_S		"_s"
#define FLICK_PHOTO_Q		"_q"
#define FLICK_PHOTO_M	"_m"
#define FLICK_PHOTO_N		"_n"
#define FLICK_PHOTO_Z		"_z"
#define FLICK_PHOTO_C		"_c"
#define FLICK_PHOTO_L		"_l"
#define FLICK_PHOTO_O		"_o"
#define FLICK_PHOTO_URL_SQ		FLICK_PHOTO_URL FLICK_PHOTO_SQ
#define FLICK_PHOTO_URL_T		FLICK_PHOTO_URL FLICK_PHOTO_T
#define FLICK_PHOTO_URL_S		FLICK_PHOTO_URL FLICK_PHOTO_S
#define FLICK_PHOTO_URL_Q		FLICK_PHOTO_URL FLICK_PHOTO_Q
#define FLICK_PHOTO_URL_M		FLICK_PHOTO_URL FLICK_PHOTO_M
#define FLICK_PHOTO_URL_N		FLICK_PHOTO_URL FLICK_PHOTO_N
#define FLICK_PHOTO_URL_Z		FLICK_PHOTO_URL FLICK_PHOTO_Z
#define FLICK_PHOTO_URL_C		FLICK_PHOTO_URL FLICK_PHOTO_C
#define FLICK_PHOTO_URL_L		FLICK_PHOTO_URL FLICK_PHOTO_L
#define FLICK_PHOTO_URL_O		FLICK_PHOTO_URL FLICK_PHOTO_O

#define FLICK_PHOTO_WIDTH			"width"
#define FLICK_PHOTO_WIDTH_SQ	FLICK_PHOTO_WIDTH FLICK_PHOTO_SQ
#define FLICK_PHOTO_WIDTH_T 		FLICK_PHOTO_WIDTH FLICK_PHOTO_T	
#define FLICK_PHOTO_WIDTH_S 		FLICK_PHOTO_WIDTH FLICK_PHOTO_S	
#define FLICK_PHOTO_WIDTH_Q 		FLICK_PHOTO_WIDTH FLICK_PHOTO_Q	
#define FLICK_PHOTO_WIDTH_M 	FLICK_PHOTO_WIDTH FLICK_PHOTO_M	
#define FLICK_PHOTO_WIDTH_N 		FLICK_PHOTO_WIDTH FLICK_PHOTO_N	
#define FLICK_PHOTO_WIDTH_Z 		FLICK_PHOTO_WIDTH FLICK_PHOTO_Z	
#define FLICK_PHOTO_WIDTH_C 		FLICK_PHOTO_WIDTH FLICK_PHOTO_C	
#define FLICK_PHOTO_WIDTH_L 		FLICK_PHOTO_WIDTH FLICK_PHOTO_L	
#define FLICK_PHOTO_WIDTH_O 		FLICK_PHOTO_WIDTH FLICK_PHOTO_O	

#define FLICK_PHOTO_HEIGHT		"height"
#define FLICK_PHOTO_HEIGHT_SQ	FLICK_PHOTO_HEIGHT FLICK_PHOTO_SQ 
#define FLICK_PHOTO_HEIGHT_T 	FLICK_PHOTO_HEIGHT FLICK_PHOTO_T	
#define FLICK_PHOTO_HEIGHT_S 	FLICK_PHOTO_HEIGHT FLICK_PHOTO_S	
#define FLICK_PHOTO_HEIGHT_Q 	FLICK_PHOTO_HEIGHT FLICK_PHOTO_Q	
#define FLICK_PHOTO_HEIGHT_M 	FLICK_PHOTO_HEIGHT FLICK_PHOTO_M	
#define FLICK_PHOTO_HEIGHT_N 	FLICK_PHOTO_HEIGHT FLICK_PHOTO_N	
#define FLICK_PHOTO_HEIGHT_Z 	FLICK_PHOTO_HEIGHT FLICK_PHOTO_Z	
#define FLICK_PHOTO_HEIGHT_C 	FLICK_PHOTO_HEIGHT FLICK_PHOTO_C	
#define FLICK_PHOTO_HEIGHT_L 		FLICK_PHOTO_HEIGHT FLICK_PHOTO_L	
#define FLICK_PHOTO_HEIGHT_O 	FLICK_PHOTO_HEIGHT FLICK_PHOTO_O	
#define FLICK_PHOTO_ORIGINAL_FORMAT		"original_format"

#define FLICK_ERROR_STAT FLICK_FIELD_STAT
#define FLICK_ERROR_CODE "code"
#define FLICK_ERROR_MSG "message"

#define FLICK_METHOD_PHOTO_SEARCH "flickr.photos.search"
#define FLICK_METHOD_AUTH_GETFROB "flickr.auth.getFrob"
#define FLICK_METHOD_AUTH_GETTOKEN "flickr.auth.getToken"
#define FLICK_METHOD_PHOTOSET_GETLIST "flickr.photosets.getList"
#define FLICK_METHOD_PHOTOSET_GETPHOTOS "flickr.photosets.getPhotos"
#define FLICK_METHOD_CONTACTS_GETLIST "flickr.contacts.getList"
#define FLICK_METHOD_CONTACTS_GETPUBLICLIST "flickr.contacts.getPublicList"
#define FLICK_METHOD_PEOPLE_GETINFO "flickr.people.getInfo"