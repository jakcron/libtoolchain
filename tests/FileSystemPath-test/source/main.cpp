#include <tc/fs.h>
#include <tc/unicode.h>
#include <tc/Exception.h>
#include <iostream>
#include <sstream>

static std::string kDirPath = "./testdir";
static std::string kUtf8DirPath = "./ЀЁЂЃЄЅテスト";
static std::string kAsciiFilePath = "LocalFileTest.bin";
static std::string kUtf8TestPath = "ЀЁЂЃЄЅ-מבחן-тест-テスト.bin";
static std::string kNotExistFilePath = "ThisDoesNotExist.bin";
static std::string kTestPhrase = "Hello world!\n";
static std::string kRandomString = "uUkMx4MYhJdwUnr38Jk7nZvXQnW0IhGNQqjMRyKoRuxXwmxBS3p2Alzrv7BijPN2LDI1QGkEfQ3vrpoOGwKciwidTyuOPRRg9sj8QggPk7QSvJrrWKN3PfzN7JvEwax3vX3QaHIoX0afJtUiulzVf9SMlotimwrdOHbeAhLzQUSCAz6moIHhZd6DO0hFxjCxGpHUnDKE";

void pathToUnixUtf8(const tc::filesystem::Path& path, std::string& out)
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

void pathToWindowsUtf8(const tc::filesystem::Path& path, std::string& out)
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

void testPathComposition(const std::string& test_name, const std::string& raw_path, const std::string& expected_path, size_t expected_element_count, bool is_unix)
{
	try
	{
		tc::filesystem::Path path(raw_path);
		std::string utf8_path;

		if (path.getPathElementList().size() != expected_element_count)
		{
			throw tc::Exception("main.cpp", "Path did not have expected element count");
		}

		if (is_unix)
			pathToUnixUtf8(path, utf8_path);
		else
			pathToWindowsUtf8(path, utf8_path);

		if (utf8_path != expected_path)
		{
			throw tc::Exception("main.cpp", "Composed path did not match expected output");
		}

		std::cout << "[FileSystemPath-test] " << test_name << "() : PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "[FileSystemPath-test] " << test_name << "() : FAIL (" << e.error() << ")" << std::endl;
	}
}

void testPathComposition(const std::string& test_name, const std::string& raw_path, size_t expected_element_count, bool is_unix)
{
	testPathComposition(test_name, raw_path, raw_path, expected_element_count, is_unix);
}


void testEqualComparisonOperator()
{
	std::string raw_path_0 = "a directory/a subdirectory";

	try
	{
		tc::filesystem::Path path_a(raw_path_0);
		tc::filesystem::Path path_b(raw_path_0);

		if ((path_a == path_b) == false)
			throw tc::Exception("main.cpp", "operator==() did not return true for equal Path objects");

		std::cout << "[FileSystemPath-test] testEqualComparisonOperator() : PASS"  << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "[FileSystemPath-test] testEqualComparisonOperator() : FAIL (" << e.error() << ")" << std::endl;
	}
}

void testUnequalComparisonOperator()
{
	std::string raw_path_0 = "a directory/a subdirectory";
	std::string raw_path_1 = "a different directory/a different subdirectory";

	try
	{
		tc::filesystem::Path path_a(raw_path_0);
		tc::filesystem::Path path_b(raw_path_1);

		if ((path_a != path_b) == false)
			throw tc::Exception("main.cpp", "operator!=() did not return true for unequal Path objects");

		std::cout << "[FileSystemPath-test] testUnequalComparisonOperator() : PASS"  << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "[FileSystemPath-test] testUnequalComparisonOperator() : FAIL (" << e.error() << ")" << std::endl;
	}
}

void testAdditionOperator()
{
	const std::string raw_path_a = "foo/bar/";
	const std::string raw_path_b = "file.txt";
	const std::string raw_path_ab = raw_path_a + raw_path_b;

	try
	{
		tc::filesystem::Path path_a(raw_path_a);
		tc::filesystem::Path path_b(raw_path_b);
		tc::filesystem::Path path_ab = path_a + path_b;

		std::string test_path;
		pathToUnixUtf8(path_ab, test_path);

		if (test_path != raw_path_ab)
		{
			throw tc::Exception("main.cpp", "operator+() did not operate produce expected output");
		}

		std::cout << "[FileSystemPath-test] testAdditionOperator() : PASS"  << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "[FileSystemPath-test] testAdditionOperator() : FAIL (" << e.error() << ")" << std::endl;
	}
}

void testAppendOperator()
{
	const std::string raw_path_a = "foo/bar/";
	const std::string raw_path_b = "file.txt";
	const std::string raw_path_ab = raw_path_a + raw_path_b;

	try
	{
		tc::filesystem::Path path_a(raw_path_a);
		tc::filesystem::Path path_b(raw_path_b);
		path_a += path_b;

		std::string test_path;
		pathToUnixUtf8(path_a, test_path);

		if (test_path != raw_path_ab)
		{
			throw tc::Exception("main.cpp", "operator+() did not operate produce expected output");
		}

		std::cout << "[FileSystemPath-test] testAppendOperator() : PASS"  << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "[FileSystemPath-test] testAppendOperator() : FAIL (" << e.error() << ")" << std::endl;
	}
}

void testAppendStressTest()
{
	const std::string raw_dir_path = "foo/bar/";
	const std::string raw_file_path = "file.txt";
	size_t append_itteration_count = 1000;
	size_t expected_element_count = (append_itteration_count * 2) + 1;

	try
	{
		tc::filesystem::Path path;
		tc::filesystem::Path path_dir(raw_dir_path);

		for (size_t i = 0; i < append_itteration_count; i++)
			path += path_dir;

		path += tc::filesystem::Path(raw_file_path);

		if (path.getPathElementList().size() != expected_element_count)
		{
			throw tc::Exception("main.cpp", "unexpected number of path elements");
		}

		if (path.getPathElementList()[expected_element_count-1] != "file.txt")
		{
			throw tc::Exception("main.cpp", "Unexpected value for tested path element");
		}

		if (path.getPathElementList()[expected_element_count-2] != "bar")
		{
			throw tc::Exception("main.cpp", "Unexpected value for tested path element");
		}

		if (path.getPathElementList()[expected_element_count-3] != "foo")
		{
			throw tc::Exception("main.cpp", "Unexpected value for tested path element");
		}

		std::cout << "[FileSystemPath-test] testAppendStressTest() : PASS"  << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "[FileSystemPath-test] testAppendStressTest() : FAIL (" << e.error() << ")" << std::endl;
	}
}

/*
void testAppendToPath()
{
	tc::filesystem::Path path("a directory/a subdirectory");

	path += tc::filesystem::Path("a file");

	std::string utf8_path;

	pathToUnixUtf8(path, utf8_path);

	std::cout << "[testAppendToPath] \"" << utf8_path << "\"" << std::endl;
}

void testAppendToPathStressTest()
{
	tc::filesystem::Path path("a directory/a subdirectory");


	for (size_t i = 0; i < 100; i++)
		path += tc::filesystem::Path("a dir");

	std::string utf8_path;

	pathToUnixUtf8(path, utf8_path);

	std::cout << "[testAppendToPathStressTest] \"" << utf8_path << "\"" << std::endl;
}
*/

int main(int argc, char** argv)
{
	testPathComposition("testEmptyPath", "", 0, true);
	testPathComposition("testRootPath", "/", 1, true);
	testPathComposition("testLastCharIsSlash", "some/path/ends/in/slash/", "some/path/ends/in/slash", 5, true);
	testPathComposition("testRelativePath", "a dir/a subdir", 2, true);
	testPathComposition("testAbsoluteUnixPath", "/usr/bin/bash", 4, true);
	testPathComposition("testAbsoluteWindowsPath", "C:\\Users\\TestUser\\Desktop\\hi.txt", 5, false);
	testEqualComparisonOperator();
	testUnequalComparisonOperator();
	testAdditionOperator();
	testAppendOperator();
	testAppendStressTest();
	
}