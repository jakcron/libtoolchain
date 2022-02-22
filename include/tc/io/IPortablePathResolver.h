	/**
	 * @file IPortablePathResolver.h
	 * @brief Declaration of tc::io::IPortablePathResolver
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/02/22
	 **/
#pragma once
#include <tc/io/IPathResolver.h>

namespace tc { namespace io {

	    /**
		 * @class IPortablePathResolver
		 * @brief This is an extension for the IPathResolver interface that specifies additional methods for setting the current directory. For more information see @ref tc::io::IPathResolver.
		 */
	class IPortablePathResolver : public IPathResolver
	{
	public:
		virtual ~IPortablePathResolver() = default;
		
			/**
			 * @brief Set the current directory path
			 * 
			 * @param path Canonical current directory path.
			 */
		virtual void setCurrentDirectory(const tc::io::Path& path) = 0;

			/**
			 * @brief Get the current directory path
			 * 
			 * @return tc::io::Path Canonical current directory path.
			 */
		virtual const tc::io::Path& getCurrentDirectory() const = 0;

			/**
			 * @brief Resolve path to its canonical path
			 * 
			 * @param path Input path.
			 * @param canonical_path Output path to write resolved canonical path.
			 */
		virtual void resolveCanonicalPath(const tc::io::Path& path, tc::io::Path& canonical_path) const = 0;

			/**
			 * @brief Resolve path to its canonical path
			 * 
			 * @param path Input path.
			 * 
			 * @return Resolved canonical path.
			 */
		virtual tc::io::Path resolveCanonicalPath(const tc::io::Path& path) const = 0;
	};

}} // namespace tc::io