#include "RenameMePhotos.h"

bool RenameMePhotos::compare(const std::pair<boost::filesystem::path, time_t> &i, const std::pair<boost::filesystem::path, time_t> &j)
{
	return i.second < j.second;
}

int RenameMePhotos::openDirectory(std::string p, std::vector<std::pair<boost::filesystem::path, time_t> > &vec, bool recursive, bool clear)
{
	if(clear)
	{
		vec.clear();
	}
	// Var Declaration
	struct tm t;
	std::vector<boost::filesystem::path> vecTmp;
	std::pair<boost::filesystem::path, time_t> file;
	std::string strTmp;
	time_t timestamp;
	boost::filesystem::path path(p);

	Exiv2::ExifData exifData;
	Exiv2::Image::AutoPtr image;
	
	// Body
	if(exists(path))
	{
		if(is_directory(path))
		{		
			if(recursive)
			{
				std::copy(boost::filesystem::recursive_directory_iterator(path), boost::filesystem::recursive_directory_iterator(), std::back_inserter(vecTmp));
			}
			else
			{
				std::copy(boost::filesystem::directory_iterator(path), boost::filesystem::directory_iterator(), std::back_inserter(vecTmp));
			}

			for(std::vector<boost::filesystem::path>::const_iterator it(vecTmp.begin()); it != vecTmp.end(); it++)
			{
				if(!is_directory(*it))
				{
					image = Exiv2::ImageFactory::open((*it).c_str());
					if(image.get() != 0)
					{
						image->readMetadata();
						exifData = image->exifData();
						if(!exifData.empty())
						{
							strTmp = exifData["Exif.Photo.DateTimeOriginal"].toString();
							strptime(strTmp.c_str(), "%Y:%m:%d %H:%M:%S", &t);
							timestamp = mktime(&t);
							file = std::make_pair(*it, timestamp);
							vec.push_back(file);
						}
						else
						{
							// Error for at least an image in metadata
						}
					}
				}
			}
		}
		else
		{
			// Error 2: The selected path is not a directory
		}
	}
	else
	{
		// Error 1: There is no such path
	}
}

int RenameMePhotos::sortAndRename(std::vector<std::pair<boost::filesystem::path, time_t> > &vec, std::string prefix, int sufixStart)
{
	int iCount = 1;
	if(sufixStart != 0)
	{
		iCount = sufixStart;
	}
	std::sort(vec.begin(), vec.end(), compare);
	
	for(std::vector<std::pair<boost::filesystem::path, time_t> >::const_iterator it(vec.begin()); it != vec.end(); it++)
	{
		std::regex r("(.*\\/)(.*)(\\..{3})");
		std::smatch match;	
		std::string s((*it).first.string());
		std::stringstream ss;
		if(std::regex_search(s, match, r))
		{
			ss << match[1] << match[2] << "_tmp" << match[3];	
		}
		std::rename(s.c_str(), ss.str().c_str());	
	}
	for(std::vector<std::pair<boost::filesystem::path, time_t> >::const_iterator it(vec.begin()); it != vec.end(); it++)
	{	
		std::regex r("(.*\\/)(.*)(\\..{3})");
		std::smatch match;	
		std::stringstream ss, ss2;
		std::string s((*it).first.string());
		if(std::regex_search(s, match, r))
		{
			if(prefix == "")
			{
				prefix = "IMG";
			}
			ss << match[1] << match[2] << "_tmp" << match[3];
			ss2 << match[1] << prefix << "_" << std::to_string(iCount++) << match[3];	
		}
		std::rename(ss.str().c_str(), ss2.str().c_str());
	}
}
