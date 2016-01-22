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
	// START TRACKING
	clock_t startInit, endInit, startExif, endExif, startSort, endSort;
	double diffExif, diffSort;
	// END TRACKING

	if(exists(p))
	{
		if(is_directory(p))
		{
			std::vector<std::pair<boost::filesystem::path, time_t> > v;
	
			// init temporary
			std::vector<boost::filesystem::path> v_tmp;
			startInit = clock();
			std::copy(boost::filesystem::recursive_directory_iterator(p), boost::filesystem::recursive_directory_iterator(), std::back_inserter(v_tmp));
			endInit = clock();	
			// getting information on files
			startExif = clock();
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
			endExif = clock();
			// sorting by timestamp (descending order)
			startSort = clock();
			std::sort(v.begin(), v.end(), compare);
			endSort = clock();

			// OUTPUT TRACKING
			std::cout << "Time Execution 'Init': " << (double)(endInit - startInit)/CLOCKS_PER_SEC << "sec" << std::endl; 
			std::cout << "Time Execution 'Exif': " << (double)(endExif - startExif)/CLOCKS_PER_SEC << "sec" << std::endl;
			std::cout << "Time Execution 'Sort': " << (double)(endSort - startSort)/CLOCKS_PER_SEC << "sec" << std::endl;
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
