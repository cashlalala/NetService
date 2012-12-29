#include "StdAfx.h"
#include "BaseService.h"
#include "MapHelper.h"

using util::CMapHelper;

const SysMaps::HttpMethod2Str
CBaseSocialService::S_MAP_HTTP_METHOD = CMapHelper::CreateHttpMethodMap();
