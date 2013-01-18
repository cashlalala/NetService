#pragma once

namespace model
{
	struct CFBError;
	struct CFkrError;

	struct CFBPhoto;
	struct CFkrPhoto;
	struct CFBPhotoList;
	struct CFkrPhotoList;

	struct CFBAlbum;
	struct CFkrAlbum;
	struct CFBAlbumList;
	struct CFkrAlbumList;
	
	struct CFBImage;
	struct CFkrImage;
	struct CFBImageList;
	struct CFkrImageList;

	struct CFBUser;
	struct CFkrUser;
	struct CFBUserList;
	struct CFkrUserList;	

	struct CFBVideoList;
	struct CFBVideo;
	struct CFBVideoFormat;

}

using namespace model;

namespace util
{
	//error rulers
	struct IErrorParseRuler {
		virtual int Traverse(CFBError& pFBErr) = 0;
		virtual int Traverse(CFkrError& pFkrErr) = 0;
	};

	struct IErrorParsable {
		virtual int AcceptErrorParser(IErrorParseRuler& errParse) = 0;
	};

	//photo rulers
	struct IPhotoParseRuler {
		virtual void Traverse(CFBPhoto& cFBPhoto) = 0;
		virtual void Traverse(CFkrPhoto& cFkrPhoto) = 0;
	};

	struct PhotoParsable {
		virtual void AcceptErrorParser(IPhotoParseRuler& cPhotoParser) = 0;
	};

	struct IPhotoListParseRuler {
		virtual void Traverse(CFBPhotoList& cFBPhotoList) = 0;
		virtual void Traverse(CFkrPhotoList& cFkrPhotoList) = 0;
	};

	struct PhotoListParsable {
		virtual void AcceptErrorParser(IPhotoListParseRuler& cPhotoListParser) = 0;
	};

	//albums rulers
	struct IAlbumParseRuler {
		virtual void Traverse(CFBAlbum& cFBAlbum) = 0;
		virtual void Traverse(CFkrAlbum& cFkrAlbum) = 0;
	};

	struct AlbumParsable {
		virtual void AcceptErrorParser(IAlbumParseRuler& cAlbumParser) = 0;
	};

	struct IAlbumListParseRuler {
		virtual void Traverse(CFBAlbumList& cFBAlbumList) = 0;
		virtual void Traverse(CFkrAlbumList& cFkrAlbumList) = 0;
	};

	struct AlbumListParsable {
		virtual void AcceptErrorParser(IAlbumListParseRuler& cAlbumListParser) = 0;
	};

	//Images rulers
	struct IImageParseRuler {
		virtual void Traverse(CFBImage& cFBImage) = 0;
		virtual void Traverse(CFkrImage& cFkrImage) = 0;
	};

	struct ImageParsable {
		virtual void AcceptErrorParser(IImageParseRuler& cImageParser) = 0;
	};

	struct IImageListParseRuler {
		virtual void Traverse(CFBImageList& cFBImageList) = 0;
		virtual void Traverse(CFkrImageList& cFkrImageList) = 0;
	};

	struct ImageListParsable {
		virtual void AcceptErrorParser(IImageListParseRuler& cImageListParser) = 0;
	};

	//Users rulers
	struct IUserParseRuler {
		virtual void Traverse(CFBUser& cFBUser) = 0;
		virtual void Traverse(CFkrUser& cFkrUser) = 0;
	};

	struct UserParsable {
		virtual void AcceptErrorParser(IUserParseRuler& cUserParser) = 0;
	};

	struct IUserListParseRuler {
		virtual void Traverse(CFBUserList& cFBUserList) = 0;
		virtual void Traverse(CFkrUserList& cFkrUserList) = 0;
	};

	struct UserListParsable {
		virtual void AcceptErrorParser(IUserListParseRuler& cUserListParser) = 0;
	};

	//Videos rulers
	struct IVideoFormatParseRuler {
		virtual void Traverse(CFBVideoFormat& cFBVideoFormat) = 0;
	};

	struct VideoFormatParsable {
		virtual void AcceptErrorParser(IVideoFormatParseRuler& cVideoFormatParser) = 0;
	};

	struct IVideoParseRuler {
		virtual void Traverse(CFBVideo& cFBVideo) = 0;
		//virtual void Traverse(CFkrVideo& cFkrVideo) = 0;
	};

	struct VideoParsable {
		virtual void AcceptErrorParser(IVideoParseRuler& cVideoParser) = 0;
	};

	struct IVideoListParseRuler {
		virtual void Traverse(CFBVideoList& cFBVideoList) = 0;
		//virtual void Traverse(CFkrVideoList& cFkrVideoList) = 0;
	};

	struct VideoListParsable {
		virtual void AcceptErrorParser(IVideoListParseRuler& cVideoListParser) = 0;
	};
}

