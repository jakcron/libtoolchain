#include <tc/filesystem.h>
#include <tc/Exception.h>
#include <iostream>
#include <tc/SharedPtr.h>

std::ostream& operator<<(std::ostream& lhs, const tc::filesystem::Path& rhs)
{
	for (size_t i = 0; i < rhs.getPathElementList().size(); i++)
	{
		const std::string& element = rhs.getPathElementList()[i];
		lhs << element;
		if (i+1 < rhs.getPathElementList().size())
			lhs << "/";
		else if (element == "" && i == 0)
			lhs << "/";
	}

	return lhs;
}



void testGetDirectory()
{
	tc::SharedPtr<tc::filesystem::IFileSystem> fs = new tc::filesystem::LocalFileSystem();
	
	tc::filesystem::Path cur_dir;
	(*fs)->getCurrentDirectory(cur_dir);
	std::cout << "Real directory: " << cur_dir << std::endl;

	tc::SharedPtr<tc::filesystem::IFileSystem> sb_fs = new tc::filesystem::SandboxFileSystem(fs, tc::filesystem::Path(".."));

	(*sb_fs)->getCurrentDirectory(cur_dir);
	std::cout << "Sbox directory: " << cur_dir << std::endl;

	tc::SharedPtr<tc::filesystem::IFile> file = (*sb_fs)->openFile(tc::filesystem::Path("/../../../.././././././././../../LibToolChain/test/../././././././README.md"), tc::filesystem::FileAccessMode::FAM_READ);

	std::cout << "README.md size: " << (*file)->size() << std::endl;
}

int main(int argc, char** argv)
{
	testGetDirectory();
}