	/**
	 * @file VirtualFileSystem.h
	 * @brief Declaration of tc::io::VirtualFileSystem
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2021/01/09
	 **/
#pragma once
#include <tc/io/IStorage.h>
#include <tc/io/DirectoryNotFoundException.h>
#include <tc/io/FileNotFoundException.h>

namespace tc { namespace io {

	/**
	 * @class VirtualFileSystem
	 * @brief A virtual filesystem populated using user-generated filesystem metadata.
	 * 
	 * @details
	 * User supplies:
	 * * a @ref VirtualFileSystem::FileSystemMeta struct which contains vectors of directory and file entries, including mapping between absolute tc::io::Path to dir/file entry.
	 * * optionally an implementation of @ref VirtualFileSystem::IPathResolver to determine the absolute path from a relative path and the current directory. Providing a custom IPathResolver implementation is only required when special logic (like case insensitivity) is required to resolve the correct absolute path.
	 **/	
class VirtualFileSystem : public tc::io::IStorage
{
public:
	struct FileSystemMeta
	{
		FileSystemMeta() :
			dir_entries(),
			file_entries(),
			dir_hash_map(),
			file_hash_map()
		{
		}

		struct DirEntry
		{
			tc::io::sDirectoryListing dir_listing;
		};

		struct FileEntry
		{
			std::shared_ptr<tc::io::IStream> stream;
		};

		std::vector<DirEntry> dir_entries;
		std::vector<FileEntry> file_entries;
		std::map<tc::io::Path, size_t> dir_hash_map;
		std::map<tc::io::Path, size_t> file_hash_map;
	};

	class IPathResolver
	{
	public:
		virtual ~IPathResolver() = default;
		virtual void resolvePath(const tc::io::Path& in_path, const tc::io::Path& current_working_directory, tc::io::Path& resolved_path) = 0;
	};

	VirtualFileSystem();
	VirtualFileSystem(const FileSystemMeta& fs_meta, const std::shared_ptr<IPathResolver>& path_resolver = nullptr);

	tc::ResourceStatus state();
	void dispose();

	void createFile(const tc::io::Path& path);

	void removeFile(const tc::io::Path& path);

	void openFile(const tc::io::Path& path, tc::io::FileMode mode, tc::io::FileAccess access, std::shared_ptr<tc::io::IStream>& stream);
	
	void createDirectory(const tc::io::Path& path);

	void removeDirectory(const tc::io::Path& path);

	void getWorkingDirectory(tc::io::Path& path);

	void setWorkingDirectory(const tc::io::Path& path);

	void getDirectoryListing(const tc::io::Path& path, tc::io::sDirectoryListing& info);
private:
	std::string mModuleLabel;

	FileSystemMeta::DirEntry* mCurDir;
	FileSystemMeta mFsMeta;
	std::shared_ptr<IPathResolver> mPathResolver;

	class DefaultPathResolver : public IPathResolver
	{
	public:
		DefaultPathResolver();

		void resolvePath(const tc::io::Path& in_path, const tc::io::Path& current_working_directory, tc::io::Path& resolved_path);
	};
};

}} // namespace tc::io