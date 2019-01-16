/**
 * @file Exception.h
 * @brief Declaration of tc::Exception
 * @author Jack (jakcron)
 * @version 0.1
 * @date 2019/01/15
 */
#pragma once
#include <exception>
#include <string>

namespace tc {

	class Exception : public std::exception
	{
	public:
		Exception() noexcept;
		Exception(const std::string& what) noexcept;
		Exception(const std::string& module, const std::string& what) noexcept;

		const char* what() const noexcept;
		const char* module() const noexcept;
		const char* error() const noexcept;
	private:
		std::string what_;
		std::string module_;
		std::string error_;
	};

} // namespace tc
