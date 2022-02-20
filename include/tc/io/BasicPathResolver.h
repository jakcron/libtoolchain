	/**
	 * @file BasicPathResolver.h
	 * @brief Declaration of tc::io::BasicPathResolver
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/02/20
	 **/
#pragma once
#include <tc/io/IPathResolver.h>

namespace tc { namespace io {

	    /**
		 * @class BasicPathResolver
		 * @brief This implementation of IPathResolver resolves a path and working directory to an absolute path, resolving only '`.`', '`..`' and empty path elements.
		 * @details This does not consider the local file-system/environemnt, so links or `~` will not be resolved properly. It is intended for processing archived/stand-alone filesystems.
		 */
	class BasicPathResolver : public tc::io::IPathResolver
	{
	public:
			/// Default Constructor
		BasicPathResolver();

			/**
			 * @brief Resolve path to absolute path
			 * 
			 * @param in_path Input path.
			 * @param current_working_directory Path of current working directory.
			 * @param resolved_path Output path to write resolved absolute path.
			 */
		void resolvePath(const tc::io::Path& in_path, const tc::io::Path& current_working_directory, tc::io::Path& resolved_path);
	};

}} // namespace tc::io