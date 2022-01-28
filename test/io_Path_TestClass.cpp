#include <tc/Exception.h>
#include <tc/io/PathUtil.h>
#include <iostream>
#include <sstream>

#include "io_Path_TestClass.h"

//---------------------------------------------------------

void io_Path_TestClass::runAllTests(void)
{
	std::cout << "[tc::io::Path] START" << std::endl;
	test_Constructor_Default();
	testPathComposition("test_PathComposition_EmptyPath", "", 0, UNIX_PATH);
	testPathComposition("test_PathComposition_RootPath", "/", 1, UNIX_PATH);
	testPathComposition("test_PathComposition_LastCharIsSlash", "some/path/ends/in/slash/", "some/path/ends/in/slash", 5, UNIX_PATH);
	testPathComposition("test_PathComposition_RelativePath", "a dir/a subdir", 2, UNIX_PATH);
	testPathComposition("test_PathComposition_AbsoluteUnixPath", "/usr/bin/bash", 4, UNIX_PATH);
	testPathComposition("test_PathComposition_AbsoluteWindowsPath", "C:\\Users\\TestUser\\Desktop\\hi.txt", 5, WIN32_PATH);
	test_Method_pop_front();
	test_Method_pop_back();
	test_Method_push_front();
	test_Method_push_back();
	test_Method_clear();
	test_Operator_Addition();
	test_Operator_Append();
	test_Scenario_AppendStressTest();
	test_Operator_EqualityTest();
	test_Operator_InequalityTest();
	std::cout << "[tc::io::Path] END" << std::endl;
}

//---------------------------------------------------------

void io_Path_TestClass::testPathComposition(const std::string& test_name, const std::string& raw_path, const std::string& expected_path, size_t expected_element_count, PathType path_type)
{
	std::cout << "[tc::io::Path] " << test_name << " : " << std::flush;
	try
	{
		tc::io::Path path(raw_path);
		std::string utf8_path;

		if (path.size() != expected_element_count)
		{
			throw tc::Exception("Path did not have expected element count (size() returned unexpected value.)");
		}

		if (path.empty() != (expected_element_count == 0))
		{
			throw tc::Exception("Path did not have expected element count (empty() returned unexpected value.)");
		}

		if (path_type == UNIX_PATH)
			tc::io::PathUtil::pathToUnixUTF8(path, utf8_path);
		else
		{
			std::u16string utf16_path;
			tc::io::PathUtil::pathToWindowsUTF16(path, utf16_path);
			tc::string::TranscodeUtil::UTF16ToUTF8(utf16_path, utf8_path);
		}
			

		if (utf8_path != expected_path)
		{
			throw tc::Exception("Composed path did not match expected output");
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void io_Path_TestClass::testPathComposition(const std::string& test_name, const std::string& raw_path, size_t expected_element_count, PathType path_type)
{
	testPathComposition(test_name, raw_path, raw_path, expected_element_count, path_type);
}

//---------------------------------------------------------

void io_Path_TestClass::test_Constructor_Default()
{
	std::cout << "[tc::io::Path] test_Constructor_Default : " << std::flush;
	try
	{
		tc::io::Path path_empty;
		
		if (path_empty.size() != 0)
		{
			throw tc::Exception("Default constructor did not create a path with 0 elements (size() != 0)");
		}

		if (path_empty.empty() != true)
		{
			throw tc::Exception("Default constructor did not create an empty path (empty() != true)");
		}

		if (path_empty.begin() != path_empty.end())
		{
			throw tc::Exception("Default constructor did not create an empty path where begin()==end()");
		}

		std::cout << "PASS"  << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void io_Path_TestClass::test_Method_pop_front()
{
	std::cout << "[tc::io::Path] test_Method_pop_front : " << std::flush;
	try
	{
		tc::io::Path path("a/b/c/d/e/f/g/h/i/j");
		std::list<std::string> expectedElements = {"a","b","c","d","e","f","g","h","i","j"};

		for (size_t i = 0; i < 10; i++, path.pop_front(), expectedElements.pop_front())
		{
			if (*path.begin() != *expectedElements.begin())
			{
				throw tc::Exception("pop_front() did not place expected element at begin()");
			}
			if (path.front() != expectedElements.front())
			{
				throw tc::Exception("pop_front() did not place expected element at front()");
			}
		}

		std::cout << "PASS"  << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void io_Path_TestClass::test_Method_pop_back()
{
	std::cout << "[tc::io::Path] test_Method_pop_back : " << std::flush;
	try
	{
		tc::io::Path path("a/b/c/d/e/f/g/h/i/j");
		std::list<std::string> expectedElements = {"a","b","c","d","e","f","g","h","i","j"};

		for (size_t i = 0; i < 10; i++, path.pop_back(), expectedElements.pop_back())
		{
			if (*(--path.end()) != *(--expectedElements.end()))
			{
				throw tc::Exception("pop_back() did not place expected element at (--end())");
			}
			if (path.back() != expectedElements.back())
			{
				throw tc::Exception("pop_back() did not place expected element at back())");
			}
		}

		std::cout << "PASS"  << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void io_Path_TestClass::test_Method_push_front()
{
	std::cout << "[tc::io::Path] test_Method_push_front : " << std::flush;
	try
	{
		tc::io::Path path("");
		std::list<std::string> expectedElements = {};

		std::list<std::string> pushCue = {"a","b","c","d","e","f","g","h","i","j"};

		for (size_t i = 0; i < 10; i++, pushCue.pop_front())
		{
			path.push_front(*(pushCue.begin()));
			expectedElements.push_front(*(pushCue.begin()));
			if (*(path.begin()) != *(expectedElements.begin()))
			{
				throw tc::Exception("push_front() did not place expected element at *(begin())");
			}
			if (path.front() != expectedElements.front())
			{
				throw tc::Exception("push_front() did not place expected element at front()");
			}
		}

		std::cout << "PASS"  << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void io_Path_TestClass::test_Method_push_back()
{
	std::cout << "[tc::io::Path] test_Method_push_back : " << std::flush;
	try
	{
		tc::io::Path path("");
		std::list<std::string> expectedElements = {};

		std::list<std::string> pushCue = {"a","b","c","d","e","f","g","h","i","j"};

		for (size_t i = 0; i < 10; i++, pushCue.pop_front())
		{
			path.push_back(*(pushCue.begin()));
			expectedElements.push_back(*(pushCue.begin()));
			if (*(--path.end()) != *(--expectedElements.end()))
			{
				throw tc::Exception("push_back() did not place expected element at *(--end())");
			}
			if (path.back() != expectedElements.back())
			{
				throw tc::Exception("push_back() did not place expected element at back())");
			}
		}

		std::cout << "PASS"  << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void io_Path_TestClass::test_Method_clear()
{
	std::cout << "[tc::io::Path] test_Method_clear : " << std::flush;
	try
	{
		tc::io::Path path("a/b/c/d/e/f/g/h/i/j");
		
		path.clear();

		if (path.size() != 0)
		{
			throw tc::Exception(".size() did not have expected value of 0 after .clear()");
		}

		if (path.empty() != true)
		{
			throw tc::Exception(".empty() did not have expected value of true after .clear()");
		}

		if (path.begin() != path.end())
		{
			throw tc::Exception(".begin() != .end() after .clear()");
		}

		std::cout << "PASS"  << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void io_Path_TestClass::test_Operator_Addition()
{
	std::cout << "[tc::io::Path] test_Operator_Addition : " << std::flush;
	try
	{
		const std::string raw_path_a = "foo/bar/";
		const std::string raw_path_b = "file.txt";
		const std::string raw_path_ab = raw_path_a + raw_path_b;

		tc::io::Path path_a(raw_path_a);
		tc::io::Path path_b(raw_path_b);
		tc::io::Path path_ab = path_a + path_b;

		std::string test_path;
		tc::io::PathUtil::pathToUnixUTF8(path_ab, test_path);

		if (test_path != raw_path_ab)
		{
			throw tc::Exception("operator+() did not operate produce expected output");
		}

		std::cout << "PASS"  << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void io_Path_TestClass::test_Operator_Append()
{
	std::cout << "[tc::io::Path] test_Operator_Append : " << std::flush;
	try
	{
		const std::string raw_path_a = "foo/bar/";
		const std::string raw_path_b = "file.txt";
		const std::string raw_path_ab = raw_path_a + raw_path_b;

		tc::io::Path path_a(raw_path_a);
		tc::io::Path path_b(raw_path_b);
		path_a += path_b;

		std::string test_path;
		tc::io::PathUtil::pathToUnixUTF8(path_a, test_path);

		if (test_path != raw_path_ab)
		{
			throw tc::Exception("operator+() did not operate produce expected output");
		}

		std::cout << "PASS"  << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void io_Path_TestClass::test_Scenario_AppendStressTest()
{
	std::cout << "[tc::io::Path] test_Scenario_AppendStressTest : " << std::flush;
	try
	{
		const std::string raw_dir_path = "foo/bar/";
		const std::string raw_file_path = "file.txt";
		size_t append_itteration_count = 1000;
		size_t expected_element_count = (append_itteration_count * 2) + 1;
	
		tc::io::Path path;
		tc::io::Path path_dir(raw_dir_path);

		for (size_t i = 0; i < append_itteration_count; i++)
			path += path_dir;

		path += tc::io::Path(raw_file_path);

		if (path.size() != expected_element_count)
		{
			throw tc::Exception("unexpected number of path elements");
		}

		if (path.empty() != (expected_element_count == 0))
		{
			throw tc::Exception("Path did not have expected element count (empty() returned unexpected value.)");
		}

		tc::io::Path::const_iterator itr = path.end();
		if (*(--itr) != "file.txt")
		{
			throw tc::Exception("Unexpected value for tested path element");
		}

		if (*(--itr) != "bar")
		{
			throw tc::Exception("Unexpected value for tested path element");
		}

		if (*(--itr) != "foo")
		{
			throw tc::Exception("Unexpected value for tested path element");
		}

		std::cout << "PASS"  << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void io_Path_TestClass::test_Operator_EqualityTest()
{
	std::cout << "[tc::io::Path] test_Operator_EqualityTest : " << std::flush;
	try
	{
		std::string raw_path_0 = "a directory/a subdirectory";

		tc::io::Path path_a(raw_path_0);
		tc::io::Path path_b(raw_path_0);

		if ((path_a == path_b) == false)
			throw tc::Exception("operator==() did not return true for equal Path objects");

		std::cout << "PASS"  << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void io_Path_TestClass::test_Operator_InequalityTest()
{
	std::cout << "[tc::io::Path] test_Operator_InequalityTest : " << std::flush;
	try
	{
		std::string raw_path_0 = "a directory/a subdirectory";
		std::string raw_path_1 = "a different directory/a different subdirectory";
		tc::io::Path path_a(raw_path_0);
		tc::io::Path path_b(raw_path_1);

		if ((path_a != path_b) == false)
			throw tc::Exception("operator!=() did not return true for unequal Path objects");

		std::cout << "PASS"  << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}