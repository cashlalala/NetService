#pragma once

#define FLICK_PARAM_AUTH_TOKEN "auth_token"
#define FLICK_PARAM_API_KEY "api_key"
#define FLICK_PARAM_API_SIG "api_sig"
#define FLICK_PARAM_PERMISSION "perms"
#define FLICK_PARAM_FORMAT "format"
#define FLICK_PARAM_METHOD "method"
#define FLICK_PARAM_FROB "frob"
#define FLICK_PARAM_PERPAGE "perpage"
#define FLICK_PARAM_PAGE "page"
#define FLICK_PARAM_PAGES "pages"
#define FLICK_PARAM_USER_ID "user_id"

#define FLICK_OAUTH_CALLBACK "oauth_callback"

#define FLICK_FORMAT_JSON "json"

#define FLICK_FIELD_STAT "stat"
#define FLICK_FIELD_CONTENT "_content"
#define FLICK_FIELD_FROB FLICK_PARAM_FROB

#define FLICK_AUTH "auth"
#define FLICK_AUTH_TOKEN "token"
#define FLICK_AUTH_TOKEN_CONTENT FLICK_FIELD_CONTENT

#define FLICK_ERROR_STAT FLICK_FIELD_STAT
#define FLICK_ERROR_CODE "code"
#define FLICK_ERROR_MSG "message"

#define FLICK_METHOD_PHOTO_SEARCH "flickr.photos.search"
#define FLICK_METHOD_AUTH_GETFROB "flickr.auth.getFrob"
#define FLICK_METHOD_AUTH_GETTOKEN "flickr.auth.getToken"