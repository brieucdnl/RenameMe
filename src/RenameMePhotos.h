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
		RenameMePhotos();
		~RenameMePhotos();
		int openDirectory(std::string path, bool recursive = false);
		std::vector<std::pair<boost::filesystem::path, time_t> > getPhotos(); 
		
	private:
		std::vector<std::pair<boost::filesystem::path, time_t> > m_vec;
		int m_comp;
		int m_raw;
};
#endif
