#include <tc/Exception.h>
#include <iostream>
#include <sstream>

#include "fs_GenericFileSystem_TestClass.h"

#include <tc/fs/GenericFileSystem.h>

void fs_GenericFileSystem_TestClass::runAllTests()
{
	test_DefaultConstructor_IsNull();
	test_GenericCopyConstructor();
	test_GenericMoveConstructor();
	test_CopyConstructor();
	test_MoveConstructor();
	test_CopyOperator();
	test_MoveOperator();
	test_Generic_Passthrough();
	test_Close();
}

void fs_GenericFileSystem_TestClass::test_DefaultConstructor_IsNull()
{
	std::cout << "[tc::fs::GenericFileSystem] test_DefaultConstructor_IsNull : ";
	try
	{
		bool threwException = false;
		tc::fs::GenericFileSystem fs;

		if (fs.getFsState().test(tc::RESFLAG_READY) == true)
		{
			throw tc::Exception("getFsState().test(tc::RESFLAG_READY) returned true on uninitialised GenericFileSystem");
		}

		try {
			fs.createFile(tc::fs::Path());
		} catch(const tc::Exception&)
		{
			threwException = true;
		}
		if (threwException == false)
		{
			throw tc::Exception("Did not throw exception on null GenericFileSystem::createFile()");
		}

		try {
			fs.removeFile(tc::fs::Path());
		} catch(const tc::Exception&)
		{
			threwException = true;
		}
		if (threwException == false)
		{
			throw tc::Exception("Did not throw exception on null GenericFileSystem::removeFile()");
		}

		try {
			tc::fs::GenericFileObject file;
			fs.openFile(tc::fs::Path(), tc::fs::FILEACCESS_READ, file);
		} catch(const tc::Exception&)
		{
			threwException = true;
		}
		if (threwException == false)
		{
			throw tc::Exception("Did not throw exception on null GenericFileSystem::openFile()");
		}

		try {
			fs.createDirectory(tc::fs::Path());
		} catch(const tc::Exception&)
		{
			threwException = true;
		}
		if (threwException == false)
		{
			throw tc::Exception("Did not throw exception on null GenericFileSystem::createDirectory()");
		}

		try {
			fs.removeDirectory(tc::fs::Path());
		} catch(const tc::Exception&)
		{
			threwException = true;
		}
		if (threwException == false)
		{
			throw tc::Exception("Did not throw exception on null GenericFileSystem::removeDirectory()");
		}

		try {
			tc::fs::Path path;
			fs.getWorkingDirectory(path);
		} catch(const tc::Exception&)
		{
			threwException = true;
		}
		if (threwException == false)
		{
			throw tc::Exception("Did not throw exception on null GenericFileSystem::getWorkingDirectory()");
		}

		try {
			fs.setWorkingDirectory(tc::fs::Path());
		} catch(const tc::Exception&)
		{
			threwException = true;
		}
		if (threwException == false)
		{
			throw tc::Exception("Did not throw exception on null GenericFileSystem::setWorkingDirectory()");
		}

		try {
			tc::fs::sDirectoryListing listing;
			fs.getDirectoryListing(tc::fs::Path(), listing);
		} catch(const tc::Exception&)
		{
			threwException = true;
		}
		if (threwException == false)
		{
			throw tc::Exception("Did not throw exception on null GenericFileSystem::getDirectoryListing()");
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void fs_GenericFileSystem_TestClass::test_GenericCopyConstructor()
{
	class DummyFileSystem : public DummyFileSystemBase
	{
	public:
		DummyFileSystem() : mState(1 << tc::RESFLAG_READY), mPath() {}

		virtual tc::ResourceState getFsState()
		{
			return mState;
		}

		virtual void closeFs()
		{
			mState = 0;
		}

		virtual void getWorkingDirectory(tc::fs::Path& path)
		{
			path = mPath;
		}

		virtual void setWorkingDirectory(const tc::fs::Path& path)
		{
			mPath = path;
		}

		virtual tc::fs::IFileSystem* copyInstance() const
		{
			return new DummyFileSystem(*this);
		}

		virtual tc::fs::IFileSystem* moveInstance()
		{
			return new DummyFileSystem(std::move(*this));
		}
	private:
		tc::ResourceState mState;
		tc::fs::Path mPath;
	};

	std::cout << "[tc::fs::GenericFileSystem] test_GenericCopyConstructor : ";
	try
	{
		tc::fs::Path working_dir;
		static const tc::fs::Path kExpectedWorkingDir("test_GenericCopyConstructor");
		
		// init dummyFS
		DummyFileSystem dummyFS;
		dummyFS.setWorkingDirectory(kExpectedWorkingDir);

		// copy construct genFS
		tc::fs::GenericFileSystem genFS(dummyFS);

		// check isNull
		if (genFS.getFsState().test(tc::RESFLAG_READY) == false)
		{
			throw tc::Exception("getFsState().test(tc::RESFLAG_READY) returned false on initialised GenericFileSystem");
		}
		
		// confirm workdir is correct
		genFS.getWorkingDirectory(working_dir);
		if (working_dir != kExpectedWorkingDir)
		{
			throw tc::Exception("GenericFileSystem::getWorkingDirectory() did not return expected value");
		}

		// test original retained
		dummyFS.getWorkingDirectory(working_dir);
		if (working_dir != kExpectedWorkingDir)
		{
			throw tc::Exception("Source FileSystem didn't retain expected value when copied");
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void fs_GenericFileSystem_TestClass::test_GenericMoveConstructor()
{
	class DummyFileSystem : public DummyFileSystemBase
	{
	public:
		DummyFileSystem() : mState(1 << tc::RESFLAG_READY), mPath() {}

		virtual tc::ResourceState getFsState()
		{
			return mState;
		}

		virtual void closeFs()
		{
			mState = 0;
		}

		virtual void getWorkingDirectory(tc::fs::Path& path)
		{
			path = mPath;
		}

		virtual void setWorkingDirectory(const tc::fs::Path& path)
		{
			mPath = path;
		}

		virtual tc::fs::IFileSystem* copyInstance() const
		{
			return new DummyFileSystem(*this);
		}

		virtual tc::fs::IFileSystem* moveInstance()
		{
			return new DummyFileSystem(std::move(*this));
		}
	private:
		tc::ResourceState mState;
		tc::fs::Path mPath;
	};

	std::cout << "[tc::fs::GenericFileSystem] test_GenericMoveConstructor : ";
	try
	{
		tc::fs::Path working_dir;
		static const tc::fs::Path kExpectedWorkingDir("test_GenericMoveConstructor");
		
		// init dummyFS
		DummyFileSystem dummyFS;
		dummyFS.setWorkingDirectory(kExpectedWorkingDir);

		// move construct genFS
		tc::fs::GenericFileSystem genFS(std::move(dummyFS));

		// check isNull
		if (genFS.getFsState().test(tc::RESFLAG_READY) == false)
		{
			throw tc::Exception("getFsState().test(tc::RESFLAG_READY) returned false on initialised GenericFileSystem");
		}
		
		// confirm workdir is correct
		genFS.getWorkingDirectory(working_dir);
		if (working_dir != kExpectedWorkingDir)
		{
			throw tc::Exception("GenericFileSystem::getWorkingDirectory() did not return expected value");
		}

		// test original retained
		dummyFS.getWorkingDirectory(working_dir);
		if (working_dir == kExpectedWorkingDir)
		{
			throw tc::Exception("Source FileSystem did retain expected value when moved");
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void fs_GenericFileSystem_TestClass::test_CopyConstructor()
{
	class DummyFileSystem : public DummyFileSystemBase
	{
	public:
		DummyFileSystem() : mState(1 << tc::RESFLAG_READY), mPath() {}

		virtual tc::ResourceState getFsState()
		{
			return mState;
		}

		virtual void closeFs()
		{
			mState = 0;
		}

		virtual void getWorkingDirectory(tc::fs::Path& path)
		{
			path = mPath;
		}

		virtual void setWorkingDirectory(const tc::fs::Path& path)
		{
			mPath = path;
		}

		virtual tc::fs::IFileSystem* copyInstance() const
		{
			return new DummyFileSystem(*this);
		}

		virtual tc::fs::IFileSystem* moveInstance()
		{
			return new DummyFileSystem(std::move(*this));
		}
	private:
		tc::ResourceState mState;
		tc::fs::Path mPath;
	};

	std::cout << "[tc::fs::GenericFileSystem] test_GenericCopyConstructor : ";
	try
	{
		tc::fs::Path working_dir;
		static const tc::fs::Path kExpectedWorkingDir("test_GenericCopyConstructor");
		
		// init dummyFS
		DummyFileSystem dummyFS;
		dummyFS.setWorkingDirectory(kExpectedWorkingDir);

		// copy construct genFS
		tc::fs::GenericFileSystem genFS(dummyFS);

		// copy construct newgenFS from genFS
		tc::fs::GenericFileSystem newgenFS(genFS);

		// check isNull
		if (genFS.getFsState().test(tc::RESFLAG_READY) == false)
		{
			throw tc::Exception("getFsState().test(tc::RESFLAG_READY) returned false on initialised GenericFileSystem");
		}

		// check isNull
		if (newgenFS.getFsState().test(tc::RESFLAG_READY) == false)
		{
			throw tc::Exception("getFsState().test(tc::RESFLAG_READY) returned false on initialised GenericFileSystem");
		}
		
		// confirm workdir is correct
		genFS.getWorkingDirectory(working_dir);
		if (working_dir != kExpectedWorkingDir)
		{
			throw tc::Exception("GenericFileSystem::getWorkingDirectory() did not return expected value");
		}

		// confirm workdir is correct
		newgenFS.getWorkingDirectory(working_dir);
		if (working_dir != kExpectedWorkingDir)
		{
			throw tc::Exception("GenericFileSystem::getWorkingDirectory() did not return expected value");
		}

		// test original retained
		dummyFS.getWorkingDirectory(working_dir);
		if (working_dir != kExpectedWorkingDir)
		{
			throw tc::Exception("Source FileSystem didn't retain expected value when copied");
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void fs_GenericFileSystem_TestClass::test_MoveConstructor()
{
	class DummyFileSystem : public DummyFileSystemBase
	{
	public:
		DummyFileSystem() : mState(1 << tc::RESFLAG_READY), mPath() {}

		virtual tc::ResourceState getFsState()
		{
			return mState;
		}

		virtual void closeFs()
		{
			mState = 0;
		}

		virtual void getWorkingDirectory(tc::fs::Path& path)
		{
			path = mPath;
		}

		virtual void setWorkingDirectory(const tc::fs::Path& path)
		{
			mPath = path;
		}

		virtual tc::fs::IFileSystem* copyInstance() const
		{
			return new DummyFileSystem(*this);
		}

		virtual tc::fs::IFileSystem* moveInstance()
		{
			return new DummyFileSystem(std::move(*this));
		}
	private:
		tc::ResourceState mState;
		tc::fs::Path mPath;
	};

	std::cout << "[tc::fs::GenericFileSystem] test_GenericCopyConstructor : ";
	try
	{
		tc::fs::Path working_dir;
		static const tc::fs::Path kExpectedWorkingDir("test_GenericCopyConstructor");
		
		// init dummyFS
		DummyFileSystem dummyFS;
		dummyFS.setWorkingDirectory(kExpectedWorkingDir);

		// copy construct genFS
		tc::fs::GenericFileSystem genFS(dummyFS);

		// mvoe construct newgenFS from genFS
		tc::fs::GenericFileSystem newgenFS(std::move(genFS));

		// check isNull
		if (genFS.getFsState().test(tc::RESFLAG_READY) == true)
		{
			throw tc::Exception("getFsState().test(tc::RESFLAG_READY) returned true on uninitialised GenericFileSystem");
		}

		// check isNull
		if (newgenFS.getFsState().test(tc::RESFLAG_READY) == false)
		{
			throw tc::Exception("getFsState().test(tc::RESFLAG_READY) returned false on initialised GenericFileSystem");
		}

		// confirm workdir is correct
		newgenFS.getWorkingDirectory(working_dir);
		if (working_dir != kExpectedWorkingDir)
		{
			throw tc::Exception("GenericFileSystem::getWorkingDirectory() did not return expected value");
		}

		// test original retained
		dummyFS.getWorkingDirectory(working_dir);
		if (working_dir != kExpectedWorkingDir)
		{
			throw tc::Exception("Source FileSystem didn't retain expected value when copied");
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void fs_GenericFileSystem_TestClass::test_CopyOperator()
{
	class DummyFileSystem : public DummyFileSystemBase
	{
	public:
		DummyFileSystem() : mState(1 << tc::RESFLAG_READY), mPath() {}

		virtual tc::ResourceState getFsState()
		{
			return mState;
		}

		virtual void closeFs()
		{
			mState = 0;
		}

		virtual void getWorkingDirectory(tc::fs::Path& path)
		{
			path = mPath;
		}

		virtual void setWorkingDirectory(const tc::fs::Path& path)
		{
			mPath = path;
		}

		virtual tc::fs::IFileSystem* copyInstance() const
		{
			return new DummyFileSystem(*this);
		}

		virtual tc::fs::IFileSystem* moveInstance()
		{
			return new DummyFileSystem(std::move(*this));
		}
	private:
		tc::ResourceState mState;
		tc::fs::Path mPath;
	};

	std::cout << "[tc::fs::GenericFileSystem] test_GenericCopyOperator : ";
	try
	{
		tc::fs::Path working_dir;
		static const tc::fs::Path kExpectedWorkingDir("test_GenericCopyOperator");
		
		// init dummyFS
		DummyFileSystem dummyFS;
		dummyFS.setWorkingDirectory(kExpectedWorkingDir);

		// copy construct genFS
		tc::fs::GenericFileSystem genFS(dummyFS);

		// copy construct newgenFS from genFS
		tc::fs::GenericFileSystem newgenFS;
		newgenFS = genFS;

		// check isNull
		if (genFS.getFsState().test(tc::RESFLAG_READY) == false)
		{
			throw tc::Exception("getFsState().test(tc::RESFLAG_READY) returned false on initialised GenericFileSystem");
		}

		// check isNull
		if (newgenFS.getFsState().test(tc::RESFLAG_READY) == false)
		{
			throw tc::Exception("getFsState().test(tc::RESFLAG_READY) returned false on initialised GenericFileSystem");
		}
		
		// confirm workdir is correct
		genFS.getWorkingDirectory(working_dir);
		if (working_dir != kExpectedWorkingDir)
		{
			throw tc::Exception("GenericFileSystem::getWorkingDirectory() did not return expected value");
		}

		// confirm workdir is correct
		newgenFS.getWorkingDirectory(working_dir);
		if (working_dir != kExpectedWorkingDir)
		{
			throw tc::Exception("GenericFileSystem::getWorkingDirectory() did not return expected value");
		}

		// test original retained
		dummyFS.getWorkingDirectory(working_dir);
		if (working_dir != kExpectedWorkingDir)
		{
			throw tc::Exception("Source FileSystem didn't retain expected value when copied");
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void fs_GenericFileSystem_TestClass::test_MoveOperator()
{
	class DummyFileSystem : public DummyFileSystemBase
	{
	public:
		DummyFileSystem() : mState(1 << tc::RESFLAG_READY), mPath() {}

		virtual tc::ResourceState getFsState()
		{
			return mState;
		}

		virtual void closeFs()
		{
			mState = 0;
		}

		virtual void getWorkingDirectory(tc::fs::Path& path)
		{
			path = mPath;
		}

		virtual void setWorkingDirectory(const tc::fs::Path& path)
		{
			mPath = path;
		}

		virtual tc::fs::IFileSystem* copyInstance() const
		{
			return new DummyFileSystem(*this);
		}

		virtual tc::fs::IFileSystem* moveInstance()
		{
			return new DummyFileSystem(std::move(*this));
		}
	private:
		tc::ResourceState mState;
		tc::fs::Path mPath;
	};

	std::cout << "[tc::fs::GenericFileSystem] test_GenericMoveOperator : ";
	try
	{
		tc::fs::Path working_dir;
		static const tc::fs::Path kExpectedWorkingDir("test_GenericMoveOperator");
		
		// init dummyFS
		DummyFileSystem dummyFS;
		dummyFS.setWorkingDirectory(kExpectedWorkingDir);

		// copy construct genFS
		tc::fs::GenericFileSystem genFS(dummyFS);

		// mvoe construct newgenFS from genFS
		tc::fs::GenericFileSystem newgenFS;
		newgenFS = std::move(genFS);

		// check isNull
		if (genFS.getFsState().test(tc::RESFLAG_READY) == true)
		{
			throw tc::Exception("getFsState().test(tc::RESFLAG_READY) returned true on uninitialised GenericFileSystem");
		}

		// check isNull
		if (newgenFS.getFsState().test(tc::RESFLAG_READY) == false)
		{
			throw tc::Exception("getFsState().test(tc::RESFLAG_READY) returned false on initialised GenericFileSystem");
		}

		// confirm workdir is correct
		newgenFS.getWorkingDirectory(working_dir);
		if (working_dir != kExpectedWorkingDir)
		{
			throw tc::Exception("GenericFileSystem::getWorkingDirectory() did not return expected value");
		}

		// test original retained
		dummyFS.getWorkingDirectory(working_dir);
		if (working_dir != kExpectedWorkingDir)
		{
			throw tc::Exception("Source FileSystem didn't retain expected value when copied");
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void fs_GenericFileSystem_TestClass::test_Generic_Passthrough()
{
	static const tc::fs::Path kCreateFileExpectedPath("createFile");
	static const tc::fs::Path kRemoveFileExpectedPath("removeFile");
	static const tc::fs::Path kOpenFileExpectedPath("openFile");
	static const tc::fs::FileAccessMode kOpenFileExpectedAccessMode = tc::fs::FILEACCESS_EDIT;
	static const uint64_t kOpenFileExpectedFileSize = 1337;
	static const tc::fs::Path kCreateDirectoryExpectedPath("createDirectory");
	static const tc::fs::Path kRemoveDirectoryExpectedPath("removeDirectory");
	static const tc::fs::Path kGetWorkingDirectoryExpectedPath("getWorkingDirectory");
	static const tc::fs::Path kSetWorkingDirectoryExpectedPath("setWorkingDirectory");
	static const tc::fs::Path kGetDirectoryListingExpectedPath("getDirectoryListing");
	static const tc::fs::sDirectoryListing kGetDirectoryListingExpectedListing{kGetDirectoryListingExpectedPath, {"dir1","dir2"}, {"file1","file2"}};

	class DummyFile : public DummyFileBase
	{
	public:
		DummyFile() : DummyFile(0) {}

		DummyFile(uint64_t size) : mState(1 << tc::RESFLAG_READY), mSize(size) {}

		virtual tc::ResourceState state()
		{
			return mState;
		}

		virtual void close()
		{
			mState = 0;
		}

		virtual uint64_t size()
		{
			return mSize;
		}

		virtual tc::fs::IFileObject* copyInstance() const
		{
			return new DummyFile(*this);
		}

		virtual tc::fs::IFileObject* moveInstance()
		{
			return new DummyFile(std::move(*this));
		}
	private:
		tc::ResourceState mState;
		uint64_t mSize;
	};

	class DummyFileSystem : public DummyFileSystemBase
	{
	public:
		DummyFileSystem() : mState(1 << tc::RESFLAG_READY) {}

		virtual tc::ResourceState getFsState()
		{
			return mState;
		}

		virtual void closeFs()
		{
			mState = 0;
		}

		virtual void createFile(const tc::fs::Path& path)
		{
			if (path != kCreateFileExpectedPath)
			{
				throw tc::Exception("GenericFileSystem passthrough failed for createFile() for parameter path");
			}
		}

		virtual void removeFile(const tc::fs::Path& path)
		{
			if (path != kRemoveFileExpectedPath)
			{
				throw tc::Exception("GenericFileSystem passthrough failed for removeFile() for parameter path");
			}
		}

		virtual void openFile(const tc::fs::Path& path, tc::fs::FileAccessMode mode, tc::fs::GenericFileObject& file)
		{
			if (path != kOpenFileExpectedPath)
			{
				throw tc::Exception("GenericFileSystem passthrough failed for openFile() for parameter path");
			}
			if (mode != kOpenFileExpectedAccessMode)
			{
				throw tc::Exception("GenericFileSystem passthrough failed for openFile() for parameter mode");
			}
			if (file.state().test(tc::RESFLAG_READY) == false || file.size() != kOpenFileExpectedFileSize)
			{
				throw tc::Exception("GenericFileSystem passthrough failed for openFile() for parameter file");
			}
		}

		virtual void createDirectory(const tc::fs::Path& path)
		{
			if (path != kCreateDirectoryExpectedPath)
			{
				throw tc::Exception("GenericFileSystem passthrough failed for createDirectory() for parameter path");
			}
		}

		virtual void removeDirectory(const tc::fs::Path& path)
		{
			if (path != kRemoveDirectoryExpectedPath)
			{
				throw tc::Exception("GenericFileSystem passthrough failed for removeDirectory() for parameter path");
			}
		}

		virtual void getWorkingDirectory(tc::fs::Path& path)
		{
			if (path != kGetWorkingDirectoryExpectedPath)
			{
				throw tc::Exception("GenericFileSystem passthrough failed for getWorkingDirectory() for parameter path");
			}
		}

		virtual void setWorkingDirectory(const tc::fs::Path& path)
		{
			if (path != kSetWorkingDirectoryExpectedPath)
			{
				throw tc::Exception("GenericFileSystem passthrough failed for setWorkingDirectory() for parameter path");
			}
		}

		virtual void getDirectoryListing(const tc::fs::Path& path, tc::fs::sDirectoryListing& info)
		{
			if (path != kGetDirectoryListingExpectedPath)
			{
				throw tc::Exception("GenericFileSystem passthrough failed for getDirectoryListing() for parameter path");
			}

			if (info.abs_path != kGetDirectoryListingExpectedListing.abs_path \
			||	info.dir_list != kGetDirectoryListingExpectedListing.dir_list \
			||	info.file_list != kGetDirectoryListingExpectedListing.file_list)
			{
				throw tc::Exception("GenericFileSystem passthrough failed for getDirectoryListing() for parameter info");	
			}
		}

		virtual tc::fs::IFileSystem* copyInstance() const
		{
			return new DummyFileSystem(*this);
		}

		virtual tc::fs::IFileSystem* moveInstance()
		{
			return new DummyFileSystem(*this);
		}
	private:
		tc::ResourceState mState;
	};

	std::cout << "[tc::fs::GenericFileSystem] test_Generic_Passthrough : ";
	try
	{
		tc::fs::GenericFileSystem fs(std::move(DummyFileSystem()));

		fs.createFile(kCreateFileExpectedPath);
		
		fs.removeFile(kRemoveFileExpectedPath);

		tc::fs::GenericFileObject file(std::move(DummyFile(kOpenFileExpectedFileSize)));
		fs.openFile(kOpenFileExpectedPath, kOpenFileExpectedAccessMode, file);
		
		fs.createDirectory(kCreateDirectoryExpectedPath);
		
		fs.removeDirectory(kRemoveDirectoryExpectedPath);
		
		tc::fs::Path path = kGetWorkingDirectoryExpectedPath;
		fs.getWorkingDirectory(path);
		
		fs.setWorkingDirectory(kSetWorkingDirectoryExpectedPath);
		
		tc::fs::sDirectoryListing listing = kGetDirectoryListingExpectedListing;
		fs.getDirectoryListing(kGetDirectoryListingExpectedPath, listing);

		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void fs_GenericFileSystem_TestClass::test_Close()
{
	class DummyFileSystem : public DummyFileSystemBase
	{
	public:
		DummyFileSystem() : mState(1 << tc::RESFLAG_READY), mPath() {}

		virtual tc::ResourceState getFsState()
		{
			return mState;
		}

		virtual void closeFs()
		{
			mState = 0;
		}

		virtual void getWorkingDirectory(tc::fs::Path& path)
		{
			path = mPath;
		}

		virtual void setWorkingDirectory(const tc::fs::Path& path)
		{
			mPath = path;
		}

		virtual tc::fs::IFileSystem* copyInstance() const
		{
			return new DummyFileSystem(*this);
		}

		virtual tc::fs::IFileSystem* moveInstance()
		{
			return new DummyFileSystem(std::move(*this));
		}
	private:
		tc::ResourceState mState;
		tc::fs::Path mPath;
	};

	std::cout << "[tc::fs::GenericFileSystem] test_Close : ";
	try
	{
		tc::fs::Path working_dir;
		static const tc::fs::Path kExpectedWorkingDir("test_Close");
		
		// init dummyFS
		DummyFileSystem dummyFS;
		dummyFS.setWorkingDirectory(kExpectedWorkingDir);

		// copy construct genFS
		tc::fs::GenericFileSystem genFS(dummyFS);

		// check isNull
		if (genFS.getFsState().test(tc::RESFLAG_READY) == false)
		{
			throw tc::Exception("getFsState().test(tc::RESFLAG_READY) returned false on initialised GenericFileSystem");
		}
		
		// confirm workdir is correct
		genFS.getWorkingDirectory(working_dir);
		if (working_dir != kExpectedWorkingDir)
		{
			throw tc::Exception("GenericFileSystem::getWorkingDirectory() did not return expected value");
		}

		genFS.closeFs();

		// check isNull
		if (genFS.getFsState().test(tc::RESFLAG_READY) == true)
		{
			throw tc::Exception("getFsState().test(tc::RESFLAG_READY) returned true on uninitialised GenericFileSystem");
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}