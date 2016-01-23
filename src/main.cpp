// STL
#include <iostream>
#include <regex>

// Boost
#include <boost/filesystem.hpp>

// Exiv2
#include <exiv2/exiv2.hpp>

bool compare(const std::pair<boost::filesystem::path, time_t> &i, const std::pair<boost::filesystem::path, time_t> &j)
{
	return i.second < j.second;
}

int main(int agc, char * argv[])
{
	boost::filesystem::path p(argv[1]);
	int iComp(0), iRaw(0);				
	// START TRACKING
	clock_t start, end, startInit, endInit, startExif, endExif, startSort, endSort;
	double diffExif, diffSort;
	// END TRACKING
	start = clock();
	if(exists(p))
	{
		if(is_directory(p))
		{
			struct tm t;
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
				if(!is_directory(*it))	
				{
					std::pair<boost::filesystem::path, time_t> file;
					Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open((*it).c_str());
					if(image.get() != 0)
					{
						image->readMetadata();
						std::string str;
						time_t timestamp;
						Exiv2::ExifData &exifData = image->exifData();
						if(!exifData.empty())
						{
							str = exifData["Exif.Photo.DateTimeOriginal"].toString();
							strptime(str.c_str(), "%Y:%m:%d %H:%M:%S", &t);
							timestamp = mktime(&t);
							file = std::make_pair(*it, timestamp);
							v.push_back(file);
						}
					}
				}
			}
			endExif = clock();
			//std::cout << ctime(&timestamp);
			// sorting by timestamp (descending order)
			startSort = clock();
			std::sort(v.begin(), v.end(), compare);
			endSort = clock();		
			
			for(std::vector<std::pair<boost::filesystem::path, time_t> >::const_iterator it2(v.begin()); it2 != v.end(); it2++)
			{
				std::regex r("(.*\\/)(.*)(\\..{3})");
				std::smatch match;
				std::string s((*it2).first.string());
				if(std::regex_search(s, match, r))
				{
					std::stringstream ss;
					std::regex re("(.jpg|.png|.bmp)");
					std::string prefix;
					if(std::regex_search(s, re))
					{
						ss <<  match[1] << "COMP_" << std::to_string(++iComp) << match[3];
					}
					else
					{
						ss <<  match[1] << "RAW_" << std::to_string(++iRaw) << match[3];
					}
					std::string result(ss.str()); 
					std::cout << result << std::endl;	
				}
			}

			// OUTPUT TRACKING
			std::cout << "Time Execution 'Init': " << (double)(endInit - startInit)/CLOCKS_PER_SEC << "sec" << std::endl; 
			std::cout << "Time Execution 'Exif': " << (double)(endExif - startExif)/CLOCKS_PER_SEC << "sec" << std::endl;
			std::cout << "Time Execution 'Sort': " << (double)(endSort - startSort)/CLOCKS_PER_SEC << "sec" << std::endl;
		}
		else
		{
			std::cout << "Error: The path you entered is not a directory !" << std::endl;
		}
	}
	else
	{
		std::cout << "Error: Path doesn't exist !" << std::endl;
	}
	end = clock();
	std::cout << "Total Time Execution: " << (double)(end - start)/CLOCKS_PER_SEC << "sec - Number of files processed: " << iComp + iRaw << std::endl;
}
