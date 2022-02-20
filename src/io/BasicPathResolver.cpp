#include <tc/io/BasicPathResolver.h>

tc::io::BasicPathResolver::BasicPathResolver()
{

}

void tc::io::BasicPathResolver::resolvePath(const tc::io::Path& in_path, const tc::io::Path& current_working_directory, tc::io::Path& resolved_path)
{
	tc::io::Path in_tmp = in_path;
	tc::io::Path tmp = current_working_directory;
	
	 // clear the empty root path name (this should always be true, check done for readablility)
	if (tmp.front().empty())
		tmp.pop_front();
	
	// if input has empty root path at front, then this is an absolute path
	if (in_tmp.front().empty())
	{
		in_tmp.pop_front();

		// also clear tmp
		tmp.clear();
	}

	// combine in_tmp with tmp
	for (auto itr = in_tmp.begin(); itr != in_tmp.end(); itr++)
	{
        // ignore "current directory" alias
		if (*itr == ".")
			continue;
        // ignore empty path elements
        if (*itr == "")
            continue;
        // navigate up for "parent directory" alias
		else if (*itr == "..")
		{
			// ".." is the parent directory, so if there are path elements then we remove from the back to "go to the parent directory"
			if (!tmp.empty())
				tmp.pop_back();
			else
				continue;
		}
		else
			tmp.push_back(*itr);
	}

	// re-add empty root path name
	tmp.push_front("");

	resolved_path = tmp;
}