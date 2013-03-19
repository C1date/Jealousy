#pragma once
class RCMinder
{
	public:
		RCMinder(void) { mLoaded = false; }
		~RCMinder(void) {}
		
		inline char *GetData(void) { return mRCData; }
		inline unsigned long GetSize(void) { return mSz; }
		
		/**
		returns true on success
		returns false if no resource is loaded
		*/
		bool Write(char *, char *);

		/**
		returns 0 on success
		returns -1 on FindResource error
		returns -2 on LoadResource error
		returns -3 on LockResource error
	    */
		int Load(int, LPCTSTR);
	
	private:
		bool mLoaded;
		HRSRC mRC;
		HGLOBAL mRCHandle;
		char *mRCData;
		char mPathAndName[64];
		unsigned long mSz;
};
