#pragma once

#define FB_ID "id"
#define FB_DATA "data"
#define FB_FIELDS "fields"
#define FB_LIMIT "limit"
#define FB_OFFSET "offset"

#define FB_PAGING "paging"
#define FB_PAGING_NEXT "next"
#define FB_PAGING_PREVIOUS "previous"

#define FB_USER_NAME  "name"
#define FB_USER_PICTURE  "picture"
#define FB_USER_PICTURE_DATA								FB_DATA
#define FB_USER_PICTURE_DATA_URL  "url"
#define FB_USER_PICTURE_DATA_IS_SILHOUETTE  "is_silhouette"

#define FB_ERROR				"error"
#define FB_ERROR_CODE    "code"
#define FB_ERROR_MSG    "message"

#define FB_IMAGE_WIDTH "width"
#define FB_IMAGE_HEIGHT "height"
#define FB_IMAGE_SOURCE "source"
#define FB_IMAGE_SOURCE_SMALL "src_small"
#define FB_IMAGE_SOURCE_SMALL_WIDTH		FB_IMAGE_SOURCE_SMALL "_" FB_IMAGE_WIDTH
#define FB_IMAGE_SOURCE_SMALL_HEIGHT		FB_IMAGE_SOURCE_SMALL "_" FB_IMAGE_HEIGHT

#define FB_PHOTO_THUBMNAIL									FB_USER_PICTURE
#define FB_PHOTO_LINK "link"
#define FB_PHOTO_IMAGES "images"
#define FB_PHOTO_AID "aid"

#define FB_VIDEO_THUMBNAIL									FB_PHOTO_THUBMNAIL
#define FB_VIDEO_SOURCE											FB_IMAGE_SOURCE
#define FB_VIDEO_WIDTH											FB_IMAGE_WIDTH
#define FB_VIDEO_HEIGHT											FB_IMAGE_HEIGHT
#define FB_VIDEO_FORMAT "format"
#define FB_VIDEO_EMBED_HTML "embed_html"

#define FB_ALBUM_COVER_PHOTO	"cover_photo"
#define FB_ALBUM_PHOTO_COUNT "count"
#define FB_ALBUM_NAME FB_USER_NAME
#define FB_ALBUM_OBJECT_ID "album_object_id"

#define FB_PROFILE_PIC "pic"
#define FB_PROFILE_PIC_BIG "pic_big"
#define FB_PROFILE_PIC_SMALL "pic_small"
#define FB_PROFILE_PIC_SQUARE "pic_square"