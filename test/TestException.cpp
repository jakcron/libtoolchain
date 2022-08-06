#include "TestException.h"

tc::TestException::TestException() noexcept :
	what_("")
{

}

tc::TestException::TestException(const std::string & what) noexcept :
	what_(what)
{
}

const char* tc::TestException::what() const noexcept 
{
	return what_.c_str();
}
