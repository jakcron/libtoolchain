#include <tc/Exception.h>
#include <iostream>
#include <sstream>

#include "fs_Path_TestClass.h"

void fs_Path_TestClass::pathToUnixUtf8(const tc::fs::Path& path, std::string& out)
{
	std::stringstream out_stream;

	for (size_t i = 0; i < path.getPathElementList().size(); i++)
	{
		const std::string& element = path.getPathElementList()[i];
		out_stream << element;
		if (i+1 < path.getPathElementList().size())
			out_stream << "/";
		else if (element == "" && i == 0)
			out_stream << "/";
	}

	out = out_stream.str();
}

void fs_Path_TestClass::pathToWindowsUtf8(const tc::fs::Path& path, std::string& out)
{
	std::stringstream out_stream;

	for (size_t i = 0; i < path.getPathElementList().size(); i++)
	{
		const std::string& element = path.getPathElementList()[i];
		out_stream << element;
		if (i+1 < path.getPathElementList().size())
			out_stream << "\\";
		else if (element == "" && i == 0)
			out_stream << "\\";
	}

	out = out_stream.str();
}



void fs_Path_TestClass::testPathComposition(const std::string& test_name, const std::string& raw_path, const std::string& expected_path, size_t expected_element_count, PathType path_type)
{
	std::cout << "[tc::fs::Path] " << test_name << " : ";
	try
	{
		tc::fs::Path path(raw_path);
		std::string utf8_path;

		if (path.getPathElementList().size() != expected_element_count)
		{
			throw tc::Exception("Path did not have expected element count");
		}

		if (path_type == UNIX_PATH)
			pathToUnixUtf8(path, utf8_path);
		else 
			pathToWindowsUtf8(path, utf8_path);

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

void fs_Path_TestClass::testPathComposition(const std::string& test_name, const std::string& raw_path, size_t expected_element_count, PathType path_type)
{
	testPathComposition(test_name, raw_path, raw_path, expected_element_count, path_type);
}


void fs_Path_TestClass::testEqualComparisonOperator()
{
	std::cout << "[tc::fs::Path] testEqualComparisonOperator : ";
	try
	{
		std::string raw_path_0 = "a directory/a subdirectory";

		tc::fs::Path path_a(raw_path_0);
		tc::fs::Path path_b(raw_path_0);

		if ((path_a == path_b) == false)
			throw tc::Exception("operator==() did not return true for equal Path objects");

		std::cout << "PASS"  << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void fs_Path_TestClass::testUnequalComparisonOperator()
{
	std::cout << "[tc::fs::Path] testUnequalComparisonOperator : ";
	try
	{
		std::string raw_path_0 = "a directory/a subdirectory";
		std::string raw_path_1 = "a different directory/a different subdirectory";
		tc::fs::Path path_a(raw_path_0);
		tc::fs::Path path_b(raw_path_1);

		if ((path_a != path_b) == false)
			throw tc::Exception("operator!=() did not return true for unequal Path objects");

		std::cout << "PASS"  << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void fs_Path_TestClass::testAdditionOperator()
{
	std::cout << "[tc::fs::Path] testAdditionOperator : ";
	try
	{
		const std::string raw_path_a = "foo/bar/";
		const std::string raw_path_b = "file.txt";
		const std::string raw_path_ab = raw_path_a + raw_path_b;

		tc::fs::Path path_a(raw_path_a);
		tc::fs::Path path_b(raw_path_b);
		tc::fs::Path path_ab = path_a + path_b;

		std::string test_path;
		pathToUnixUtf8(path_ab, test_path);

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

void fs_Path_TestClass::testAppendOperator()
{
	std::cout << "[tc::fs::Path] testAppendOperator : ";
	try
	{
		const std::string raw_path_a = "foo/bar/";
		const std::string raw_path_b = "file.txt";
		const std::string raw_path_ab = raw_path_a + raw_path_b;

		tc::fs::Path path_a(raw_path_a);
		tc::fs::Path path_b(raw_path_b);
		path_a += path_b;

		std::string test_path;
		pathToUnixUtf8(path_a, test_path);

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

void fs_Path_TestClass::testAppendStressTest()
{
	std::cout << "[tc::fs::Path] testAppendStressTest : ";
	try
	{
		const std::string raw_dir_path = "foo/bar/";
		const std::string raw_file_path = "file.txt";
		size_t append_itteration_count = 1000;
		size_t expected_element_count = (append_itteration_count * 2) + 1;
	
		tc::fs::Path path;
		tc::fs::Path path_dir(raw_dir_path);

		for (size_t i = 0; i < append_itteration_count; i++)
			path += path_dir;

		path += tc::fs::Path(raw_file_path);

		if (path.getPathElementList().size() != expected_element_count)
		{
			throw tc::Exception("unexpected number of path elements");
		}

		if (path.getPathElementList()[expected_element_count-1] != "file.txt")
		{
			throw tc::Exception("Unexpected value for tested path element");
		}

		if (path.getPathElementList()[expected_element_count-2] != "bar")
		{
			throw tc::Exception("Unexpected value for tested path element");
		}

		if (path.getPathElementList()[expected_element_count-3] != "foo")
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

void fs_Path_TestClass::runAllTests(void)
{
	testPathComposition("testEmptyPath", "", 0, UNIX_PATH);
	testPathComposition("testRootPath", "/", 1, UNIX_PATH);
	testPathComposition("testLastCharIsSlash", "some/path/ends/in/slash/", "some/path/ends/in/slash", 5, UNIX_PATH);
	testPathComposition("testRelativePath", "a dir/a subdir", 2, UNIX_PATH);
	testPathComposition("testAbsoluteUnixPath", "/usr/bin/bash", 4, UNIX_PATH);
	testPathComposition("testAbsoluteWindowsPath", "C:\\Users\\TestUser\\Desktop\\hi.txt", 5, WIN32_PATH);
	testEqualComparisonOperator();
	testUnequalComparisonOperator();
	testAdditionOperator();
	testAppendOperator();
	testAppendStressTest();
	
}