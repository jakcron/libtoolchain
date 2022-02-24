#include <tc/Exception.h>
#include <fmt/core.h>

#include <tc/io/BasicPathResolver.h>
#include <tc/io/PathUtil.h>

#include "io_BasicPathResolver_TestClass.h"
#include "StreamTestUtil.h"

void io_BasicPathResolver_TestClass::runAllTests(void)
{
	fmt::print("[tc::io::BasicPathResolver] START\n");
	test_ResolveRootDirRelativePaths();
	test_ResolveWorkingDirectoryRelativePaths();
	fmt::print("[tc::io::BasicPathResolver] END\n");
}

void io_BasicPathResolver_TestClass::test_ResolveRootDirRelativePaths()
{
	fmt::print("[tc::io::BasicPathResolver] test_ResolveRootDirRelativePaths : ");
	try
	{
		try 
		{
			struct ResolutionTest {
				std::string in_path;
				std::string in_working_directory_path;
				std::string expected_resolved_path;
			};

			std::vector<ResolutionTest> tests = {
				{"/a/path", "/", "/a/path"},
				{"/a/path", "/a/working/directory", "/a/path"},
				{"/a/path/////with/empty//path/elements/", "/a/working/directory", "/a/path/with/empty/path/elements/"},
				{"/a/path", "/another/working/directory", "/a/path"},
				{"/a/path", "/a/very/long/working/directory/path/indeed/this/is/more/than/ten/elements", "/a/path"},
				{"/a/path/with/../some/../../parent/directory/aliases/../", "/a/working/directory", "/a/parent/directory"},
				{"/a/path/with/./some/././current/directory/aliases/./", "/a/working/directory", "/a/path/with/some/current/directory/aliases"},
				{"/a/path/with/./a/./../mix/./of/../../parent/and/../current/directory/aliases/./", "/a/working/directory", "/a/path/with/parent/current/directory/aliases"},
				{"/a/path/with/../../../more/../../parent/directory/../../../aliases/../than/../path/../elements/../..", "/a/working/directory", "/"},
			};

			for (auto itr = tests.begin(); itr != tests.end(); itr++)
			{
				util_RunResolutionTest(tc::io::Path(itr->in_path), tc::io::Path(itr->in_working_directory_path), tc::io::Path(itr->expected_resolved_path));
			}
			

			fmt::print("PASS\n");
		}
		catch (const tc::Exception& e)
		{
			fmt::print("FAIL ({:s})\n", e.error());
		}
	}
	catch (const std::exception& e)
	{
		fmt::print("UNHANDLED EXCEPTION ({:s})\n", e.what());
	}
}

void io_BasicPathResolver_TestClass::test_ResolveWorkingDirectoryRelativePaths()
{
	fmt::print("[tc::io::BasicPathResolver] test_ResolveWorkingDirectoryRelativePaths : ");
	try
	{
		try 
		{
			struct ResolutionTest {
				std::string in_path;
				std::string in_working_directory_path;
				std::string expected_resolved_path;
			};

			std::vector<ResolutionTest> tests = {
				{"./a/path", "/", "/a/path"},
				{"a/path", "/", "/a/path"},
				{"./a/path", "/a/working/directory", "/a/working/directory/a/path"},
				{"a/path", "/a/working/directory", "/a/working/directory/a/path"},
				{"./a/path", "/a/very/long/working/directory/path/indeed/this/is/more/than/ten/elements", "/a/very/long/working/directory/path/indeed/this/is/more/than/ten/elements/a/path"},
				{"a/path", "/a/very/long/working/directory/path/indeed/this/is/more/than/ten/elements", "/a/very/long/working/directory/path/indeed/this/is/more/than/ten/elements/a/path"},
				{"./a/path/with/../some/../../parent/directory/aliases/../", "/a/working/directory", "/a/working/directory/a/parent/directory"},
				{"a/path/with/../some/../../parent/directory/aliases/../", "/a/working/directory", "/a/working/directory/a/parent/directory"},
				{"./a/path/with/./a/./../mix/./of/../../parent/and/../current/directory/aliases/./", "/a/working/directory", "/a/working/directory/a/path/with/parent/current/directory/aliases/"},
				{"a/path/with/./a/./../mix/./of/../../parent/and/../current/directory/aliases/./", "/a/working/directory", "/a/working/directory/a/path/with/parent/current/directory/aliases/"},
				{"./a/path/with/../../../more/../../parent/directory/../../../aliases/../than/../path/../elements/../../very/different/path", "/a/working/directory", "/very/different/path"},
				{"a/path/with/../../../more/../../parent/directory/../../../aliases/../than/../path/../elements/../../very/different/path", "/a/working/directory", "/very/different/path"},

			};

			for (auto itr = tests.begin(); itr != tests.end(); itr++)
			{
				util_RunResolutionTest(tc::io::Path(itr->in_path), tc::io::Path(itr->in_working_directory_path), tc::io::Path(itr->expected_resolved_path));
			}
			

			fmt::print("PASS\n");
		}
		catch (const tc::Exception& e)
		{
			fmt::print("FAIL ({:s})\n", e.error());
		}
	}
	catch (const std::exception& e)
	{
		fmt::print("UNHANDLED EXCEPTION ({:s})\n", e.what());
	}
}

void io_BasicPathResolver_TestClass::util_RunResolutionTest(const tc::io::Path& in_path, const tc::io::Path& in_working_dir_path, const tc::io::Path& expected_resolved_path)
{
	tc::io::BasicPathResolver res;

	tc::io::Path resolved_path;
	res.resolvePath(in_path, in_working_dir_path, resolved_path);

	if (resolved_path != expected_resolved_path)
	{
		std::string in_path_str, in_working_dir_path_str, expected_resolved_path_str, resolved_path_str;

		tc::io::PathUtil::pathToUnixUTF8(in_path, in_path_str);
		tc::io::PathUtil::pathToUnixUTF8(in_working_dir_path, in_working_dir_path_str);
		tc::io::PathUtil::pathToUnixUTF8(expected_resolved_path, expected_resolved_path_str);
		tc::io::PathUtil::pathToUnixUTF8(resolved_path, resolved_path_str);

		throw tc::Exception(fmt::format("Resolve (path=\"{:s}\", workingdir= \"{:s}\") returned \"{:s}\"  (expected: \"{:s}\").", in_path_str, in_working_dir_path_str, resolved_path_str, expected_resolved_path_str));
	}
}