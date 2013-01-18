#pragma once

namespace model
{
	struct CFBProfile;

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
	//for future decoupling of executor
	struct IExecutor {
		virtual void SetExecutor(void* pExecutor) = 0;
	};

	//error rulers
	struct IErrorParseRuler : public IExecutor {
		virtual int Traverse(CFBError& pFBErr) = 0;
		virtual int Traverse(CFkrError& pFkrErr) = 0;
	};

	struct IErrorParsable {
		virtual int AcceptErrorParser(IErrorParseRuler& errParse) = 0;
	};

	//photo rulers
	struct IPhotoParseRuler : public IExecutor {
		virtual void Traverse(CFBPhoto& cFBPhoto) = 0;
		virtual void Traverse(CFkrPhoto& cFkrPhoto) = 0;
	};

	struct IPhotoParsable {
		virtual void AcceptPhotoParser(IPhotoParseRuler& cPhotoParser) = 0;
	};

	struct IPhotoListParseRuler : public IExecutor {
		virtual void Traverse(CFBPhotoList& cFBPhotoList) = 0;
		virtual void Traverse(CFkrPhotoList& cFkrPhotoList) = 0;
	};

	struct IPhotoListParsable {
		virtual void AcceptPhotoListParser(IPhotoListParseRuler& cPhotoListParser) = 0;
	};

	//albums rulers
	struct IAlbumParseRuler : public IExecutor {
		virtual void Traverse(CFBAlbum& cFBAlbum) = 0;
		virtual void Traverse(CFkrAlbum& cFkrAlbum) = 0;
	};

	struct IAlbumParsable {
		virtual void AcceptAlbumParser(IAlbumParseRuler& cAlbumParser) = 0;
	};

	struct IAlbumListParseRuler : public IExecutor {
		virtual void Traverse(CFBAlbumList& cFBAlbumList) = 0;
		virtual void Traverse(CFkrAlbumList& cFkrAlbumList) = 0;
	};

	struct IAlbumListParsable {
		virtual void AcceptAlbumListParser(IAlbumListParseRuler& cAlbumListParser) = 0;
	};

	//Images rulers
	struct IImageParseRuler : public IExecutor {
		virtual void Traverse(CFBImage& cFBImage) = 0;
		virtual void Traverse(CFkrImage& cFkrImage) = 0;
	};

	struct IImageParsable {
		virtual void AcceptImageParser(IImageParseRuler& cImageParser) = 0;
	};

	struct IImageListParseRuler : public IExecutor {
		virtual void Traverse(CFBImageList& cFBImageList) = 0;
		virtual void Traverse(CFkrImageList& cFkrImageList) = 0;
	};

	struct IImageListParsable {
		virtual void AcceptImageListParser(IImageListParseRuler& cImageListParser) = 0;
	};

	//Users rulers
	struct IUserParseRuler : public IExecutor {
		virtual void Traverse(CFBUser& cFBUser) = 0;
		virtual void Traverse(CFkrUser& cFkrUser) = 0;
	};

	struct IUserParsable {
		virtual void AcceptUserParser(IUserParseRuler& cUserParser) = 0;
	};

	struct IUserListParseRuler : public IExecutor {
		virtual void Traverse(CFBUserList& cFBUserList) = 0;
		virtual void Traverse(CFkrUserList& cFkrUserList) = 0;
	};

	struct IUserListParsable {
		virtual void AcceptUserListParser(IUserListParseRuler& cUserListParser) = 0;
	};

	//Videos rulers
	struct IVideoFormatParseRuler : public IExecutor {
		virtual void Traverse(CFBVideoFormat& cFBVideoFormat) = 0;
	};

	struct IVideoFormatParsable {
		virtual void AcceptVideoFormatParser(IVideoFormatParseRuler& cVideoFormatParser) = 0;
	};

	struct IVideoParseRuler : public IExecutor {
		virtual void Traverse(CFBVideo& cFBVideo) = 0;
		//virtual void Traverse(CFkrVideo& cFkrVideo) = 0;
	};

	struct IVideoParsable {
		virtual void AcceptVideoParser(IVideoParseRuler& cVideoParser) = 0;
	};

	struct IVideoListParseRuler : public IExecutor {
		virtual void Traverse(CFBVideoList& cFBVideoList) = 0;
		//virtual void Traverse(CFkrVideoList& cFkrVideoList) = 0;
	};

	struct IVideoListParsable {
		virtual void AcceptVideoListParser(IVideoListParseRuler& cVideoListParser) = 0;
	};
}

