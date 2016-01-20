// STL
#include <iostream>

// Boost
#include <boost/filesystem.hpp>

// LibRaw
#include "libraw/libraw.h"

bool compare(const std::pair<boost::filesystem::path, time_t> &i, const std::pair<boost::filesystem::path, time_t> &j)
{
	return i.second < j.second;
}

int main(int agc, char * argv[])
{
	LibRaw rawProcessor;
	boost::filesystem::path p(argv[1]);
	time_t timestamp;

	if(exists(p))
	{
		if(is_directory(p))
		{
			std::vector<std::pair<boost::filesystem::path, time_t> > v;
	
			// init temporary
			std::vector<boost::filesystem::path> v_tmp;	
			std::copy(boost::filesystem::recursive_directory_iterator(p), boost::filesystem::recursive_directory_iterator(), std::back_inserter(v_tmp));
			
			// getting information on files
			for(std::vector<boost::filesystem::path>::const_iterator it(v_tmp.begin()); it != v_tmp.end(); it++)
			{
				std::pair<boost::filesystem::path, time_t> file;
				if(rawProcessor.open_file((*it).c_str()) == LIBRAW_SUCCESS)
				{
					rawProcessor.unpack();
					timestamp = rawProcessor.imgdata.other.timestamp;
					file = std::make_pair(*it, timestamp);
					v.push_back(file);
				}
			}

			// sorting by timestamp (descending order)
			std::sort(v.begin(), v.end(), compare);
			for(std::vector<std::pair<boost::filesystem::path, time_t> >::const_iterator it2(v.begin()); it2 != v.end(); it2++)
			{
				std::cout << (*it2).first.c_str() << " - Timestamp : " << ctime(&((*it2).second));
			}
		}
		else
		{
			std::cout << "Error: The path you entered is not a directory !" << std::endl;
		}
	}
	else
	{
		std::cout << "Path doesn't exist !" << std::endl;
	}
	rawProcessor.recycle();
}
