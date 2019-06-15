	/**
	 * @file GenericFileSystem.h
	 * @brief Declaration of tc::fs::GenericFileSystem
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2019/05/21
	 */
#pragma once
#include <tc/fs/IFileSystem.h>
#include <tc/SharedPtr.h>

namespace tc { namespace fs {

	/**
	 * @class GenericFileSystem
	 * @brief A realisation of IFileSystem that can be assigned (copy or move) the value of another IFileSystem object
	 * 
	 * This relies on @ref tc::fs::IFileSystem::copyInstance() & @ref tc::fs::IFileSystem::moveInstance() 
	 */
class GenericFileSystem : public IFileSystem
{
public:
		/** 
		 * @brief Default constuctor
		 */
	GenericFileSystem();

		/**
		 * @brief Generic Copy Constructor (from IFileSystem)
		 * @param[in] other GenericFileSystem object to copy
		 */
	GenericFileSystem(const tc::fs::IFileSystem& other);

		/**
		 * @brief Generic Move Constructor (from IFileSystem)
		 * @param[in] other GenericFileSystem object to move
		 */
	GenericFileSystem(tc::fs::IFileSystem&& other);

		/**
		 * @brief Copy Constructor
		 * @param[in] other GenericFileSystem object to copy
		 */
	GenericFileSystem(const tc::fs::GenericFileSystem& other);

		/**
		 * @brief Move Constructor
		 * @param[in] other GenericFileSystem object to move
		 */
	GenericFileSystem(tc::fs::GenericFileSystem&& other);

		/// Destructor
	~GenericFileSystem();

		/**
		 * @brief Copy Assignment Operator
		 * @param[in] other GenericFileSystem object to copy
		 * 
		 * @return this object
		 */
	GenericFileSystem& operator=(const tc::fs::GenericFileSystem& other);

		/**
		 * @brief Move Assignment Operator
		 * @param[in] other GenericFileSystem object to move
		 * 
		 * @return this object
		 */
	GenericFileSystem& operator=(tc::fs::GenericFileSystem&& other);

	virtual void createFile(const tc::fs::Path& path);
	virtual void removeFile(const tc::fs::Path& path);
	virtual void openFile(const tc::fs::Path& path, tc::fs::FileAccessMode mode, tc::fs::GenericFileObject& file);
	virtual void createDirectory(const tc::fs::Path& path);
	virtual void removeDirectory(const tc::fs::Path& path);
	virtual void getWorkingDirectory(tc::fs::Path& path);
	virtual void setWorkingDirectory(const tc::fs::Path& path);
	virtual void getDirectoryListing(const tc::fs::Path& path, tc::fs::sDirectoryListing& info);

	virtual tc::fs::IFileSystem* copyInstance() const;
	virtual tc::fs::IFileSystem* moveInstance();

		/// Determine if this object is uninitialised
	bool isNull() const;

private:
	static const std::string kClassName;

	tc::fs::IFileSystem* mPtr;

	void deletePtr();
};

}} // namespace tc::fs