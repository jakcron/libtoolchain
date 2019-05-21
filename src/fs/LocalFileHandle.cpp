#include "LocalFileHandle.h"

#ifdef _WIN32
#include <direct.h>
#include <cstdlib>
#else
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#endif

tc::fs::LocalFileHandle::LocalFileHandle(fs_handle_t file_handle):
	mFileHandle(file_handle)
{

}

tc::fs::LocalFileHandle::~LocalFileHandle()
{
#ifdef _WIN32
	CloseHandle(mFileHandle);
#else
	close(mFileHandle);
#endif
}

tc::fs::fs_handle_t tc::fs::LocalFileHandle::getHandle()
{
	return mFileHandle;
}