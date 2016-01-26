#ifndef DEF_RENAMEMEPHOTOS
#define DEF_RENAMEMEPHOTOS

// STL
#include <iostream>
#include <regex>

// Boost
#include <boost/filesystem.hpp>

// Exiv2
#include <exiv2/exiv2.hpp>

class RenameMePhotos
{
	public:
		static int openDirectory(std::string path, std::vector<std::pair<boost::filesystem::path, time_t> > &vec, bool recursive = false, bool clear = true);
		static int sortAndRename(std::vector<std::pair<boost::filesystem::path, time_t> > &vec, std::string prefix = "", int sufixStart = 0);	
	
	private:
		static bool compare(const std::pair<boost::filesystem::path, time_t> &i, const std::pair<boost::filesystem::path, time_t> &j);
};
#endif
