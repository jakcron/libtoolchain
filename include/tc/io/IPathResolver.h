	/**
	 * @file IPathResolver.h
	 * @brief Declaration of tc::io::IPathResolver
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/02/20
	 **/
#pragma once
#include <tc/io/Path.h>

namespace tc { namespace io {

	    /**
		 * @class IPathResolver
		 * @brief This is an interface for a class that resolves relative paths to absolute paths.
		 */
	class IPathResolver
	{
	public:
		virtual ~IPathResolver() = default;
			/**
			 * @brief Resolve path to absolute path
			 * 
			 * @param in_path Input path.
			 * @param current_working_directory Path of current working directory.
			 * @param resolved_path Output path to write resolved absolute path.
			 */
		virtual void resolvePath(const tc::io::Path& in_path, const tc::io::Path& current_working_directory, tc::io::Path& resolved_path) = 0;
	};

}} // namespace tc::io