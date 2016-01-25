#include "RenameMePhotos.h"

RenameMePhotos::RenameMePhotos()
{
	std::vector<std::pair<boost::filesystem::path, time_t> > m_vec;
	int m_comp(0);
	int m_raw(0);
}

RenameMePhotos::~RenameMePhotos()
{
}

std::vector<std::pair<boost::filesystem::path, time_t> > RenameMePhotos::getPhotos()
{
	return m_vec;
}

int RenameMePhotos::openDirectory(std::string p, bool recursive)
{
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
							m_vec.push_back(file);
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
