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

#define FLICK_OAUTH_CALLBACK "oauth_callback"

#define FLICK_FORMAT_JSON "json"

#define FLICK_FIELD_STAT "stat"
#define FLICK_FIELD_CONTENT "_content"
#define FLICK_FIELD_FROB FLICK_PARAM_FROB
#define FLICK_FIELD_EXTRA		"extras"

#define FLICK_AUTH "auth"
#define FLICK_AUTH_TOKEN "token"
#define FLICK_AUTH_TOKEN_CONTENT FLICK_FIELD_CONTENT

#define FLICK_PHOTOS	"photos"
#define FLICK_PHOTOS_PAGE  FLICK_PARAM_PAGE
#define FLICK_PHOTOS_PAGES  FLICK_PARAM_PAGES
#define FLICK_PHOTOS_PERPAGE  "perpage"
#define FLICK_PHOTOS_TOTAL "total"
#define FLICK_PHOTO		"photo"
#define FLICK_PHOTO_ID				"id"
#define FLICK_PHOTO_SERVER "server"
#define FLICK_PHOTO_SECRET "secret"
#define FLICK_PHOTO_FARM "farm"
#define FLICK_PHOTO_TITLE "title"
#define FLICK_PHOTO_OWNER "owner"
#define FLICK_PHOTO_ISPUBLIC "ispublic"
#define FLICK_PHOTO_ISFRIEND "isfriend"
#define FLICK_PHOTO_ISFAMILY "isfamily"
#define FLICK_PHOTO_MEDIA		"media"
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