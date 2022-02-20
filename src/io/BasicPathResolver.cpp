#include <tc/io/BasicPathResolver.h>

tc::io::BasicPathResolver::BasicPathResolver() :
	mModuleLabel("tc::io::BasicPathResolver")
{

}

void tc::io::BasicPathResolver::resolvePath(const tc::io::Path& in_path, const tc::io::Path& current_working_directory, tc::io::Path& resolved_path)
{
	// check current working directory has a root path element at the front,
	if (current_working_directory.empty() || current_working_directory.front() != "")
	{
		throw tc::ArgumentOutOfRangeException(mModuleLabel, "current_working_directory is not an absolute path.");
	}

	// create output path
	tc::io::Path resolved_path_tmp;

	// get iterator for input path
	auto in_path_itr = in_path.begin();
	
	// if the begining of the path isn't empty and is the first element root path name, then the input path is an absolute path 
	if (in_path_itr != in_path.end() && *in_path_itr == "")
	{
		in_path_itr++;

		resolved_path_tmp = tc::io::Path("/");
	}
	else
	{
		resolved_path_tmp = current_working_directory;
	}

	// combine in_path with resolved_path_tmp
	for (; in_path_itr != in_path.end(); in_path_itr++)
	{
        // ignore "current directory" alias
		if (*in_path_itr == ".")
			continue;
        // ignore empty path elements
        else if (*in_path_itr == "")
            continue;
        // navigate up for "parent directory" alias
		else if (*in_path_itr == "..")
		{
			// ".." is the parent directory, so if there are path elements then we remove from the back to "go to the parent directory"
			if (resolved_path_tmp.size() > 1)
				resolved_path_tmp.pop_back();
			else
				continue;
		}
		else
			resolved_path_tmp.push_back(*in_path_itr);
	}

	// export resolved path
	resolved_path = resolved_path_tmp;
}