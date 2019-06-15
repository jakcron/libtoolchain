	/**
	 * @file GenericFileObject.h
	 * @brief Declaration of tc::fs::GenericFileObject
	 * @author Jack (jakcron)
	 * @version	0.1
	 * @date 2019/05/21
	 */
#pragma once
#include <tc/fs/IFileObject.h>
#include <tc/SharedPtr.h>

namespace tc { namespace fs {

	/**
	 * @class GenericFileObject
	 * @brief A realisation of IFileObject that can be assigned (copy or move) the value of another IFileObject object
	 * 
	 * This relies on @ref tc::fs::IFileObject::copyInstance() & @ref tc::fs::IFileObject::moveInstance() 
	 */
class GenericFileObject : public IFileObject
{
public:
		/** 
		 * @brief Default constuctor
		 */
	GenericFileObject();

		/**
		 * @brief Generic Copy Constructor (from IFileObject)
		 * @param[in] other GenericFileObject object to copy
		 */
	GenericFileObject(const tc::fs::IFileObject& other);

		/**
		 * @brief Generic Move Constructor (from IFileObject)
		 * @param[in] other GenericFileObject object to move
		 */
	GenericFileObject(tc::fs::IFileObject&& other);

		/**
		 * @brief Copy Constructor
		 * @param[in] other GenericFileObject object to copy
		 */
	GenericFileObject(const tc::fs::GenericFileObject& other);

		/**
		 * @brief Move Constructor
		 * @param[in] other GenericFileObject object to move
		 */
	GenericFileObject(tc::fs::GenericFileObject&& other);

		/// Destructor
	~GenericFileObject();

		/**
		 * @brief Copy Assignment Operator
		 * @param[in] other GenericFileObject object to copy
		 * 
		 * @return this object
		 */
	GenericFileObject& operator=(const tc::fs::GenericFileObject& other);

		/**
		 * @brief Move Assignment Operator
		 * @param[in] other GenericFileObject object to move
		 * 
		 * @return this object
		 */
	GenericFileObject& operator=(tc::fs::GenericFileObject&& other);

	virtual uint64_t size();
	virtual void seek(uint64_t offset);
	virtual uint64_t pos();
	virtual void read(byte_t* data, size_t len);
	virtual void write(const byte_t* data, size_t len);

	virtual tc::fs::IFileObject* copyInstance() const;
	virtual tc::fs::IFileObject* moveInstance();

		/// Determine if this object is uninitialised
	bool isNull() const;
	
private:
	static const std::string kClassName;

	tc::fs::IFileObject* mPtr;

	void deletePtr();
};

}} // namespace tc::fs