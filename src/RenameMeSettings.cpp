#include "RenameMeSettings.h"
#include <fstream>
#include <iostream>
#include <sstream>

RenameMeSettings::RenameMeSettings(std::string pathFile)
{
	m_configFile = pathFile;
	std::unordered_map<std::string, std::string> m_mapSettings;
}

RenameMeSettings::~RenameMeSettings()
{
}

bool RenameMeSettings::readDatas()
{
	std::fstream file;
	std::string line;

	file.open(m_configFile);
	if(file.is_open())
	{
		while(std::getline(file, line))
		{
			std::istringstream is_line(line);
			std::string key;
			if(std::getline(is_line, key, '='))
			{
				std::string value;
				if(std::getline(is_line, value))
				{
					m_mapSettings[key] = value;
				}
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

std::string RenameMeSettings::getDatas(std::string key)
{
	return m_mapSettings[key];
}

bool RenameMeSettings::strToBool(std::string str)
{
	bool b;
	std::istringstream is(str);
	is >> std::boolalpha >> b;
	return b;
}
