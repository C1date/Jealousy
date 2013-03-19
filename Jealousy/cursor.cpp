#include "cursor.h"


int RCMinder::Load(int rc_name, LPCTSTR rc_type)
{
	if ((mRC = FindResource(GetModuleHandle(NULL), MAKEINTRESOURCE(rc_name), rc_type)) == NULL)
		return -1;

	if ((mRCHandle = LoadResource(GetModuleHandle(NULL), mRC)) == NULL)
		return -2;

	if ((mRCData = (char *)LockResource(mRCHandle)) == NULL)
		return -3;

	mSz = SizeofResource(GetModuleHandle(NULL), mRC);
	mLoaded = true;

	return 0;
}

bool RCMinder::Write(char *path, char *file_name)
{
	if (!mLoaded) return false;
	
	sprintf(mPathAndName, "%s%s", path, file_name);
	
	std::ofstream f(mPathAndName, std::ios::binary);
	f.write((const char *) mRCData, mSz);
	f.close();

	return true;
}