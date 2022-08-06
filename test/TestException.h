	/**
	 * @file TestException.h
	 * @brief Declaration of tc::TestException
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/08/04
	 **/
#pragma once
#include <exception>
#include <string>

namespace tc {

	/**
	 * @class TestException
	 * @brief An extension of std::exception specifically for raising exceptions during tests
	 **/
class TestException : public std::exception
{
public:
		/// Default Constructor
	TestException() noexcept;

		/**
		 * @brief Basic Parameterized Constructor
		 * 
		 * Inherited from std::exception
		 * 
		 * @param[in] what Explanation for exception
		 * 
		 * @post
		 * - what() == what
		 * - module() == ""
		 * - error() == what
		 **/
	TestException(const std::string& what) noexcept;

		/// Get explanation for exception (inherited from std::exception)
	const char* what() const noexcept;

private:
	std::string what_;
};

} // namespace tc
