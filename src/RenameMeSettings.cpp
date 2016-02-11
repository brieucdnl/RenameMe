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

	file.open(m_configFile, std::ios::in);
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
		file.close();
		return true;
	}
	else
	{
		return false;
	}
}

void RenameMeSettings::writeDatas()
{
	std::fstream file;	
	file.open(m_configFile, std::ios::out | std::ios::trunc);
	if(file.is_open())
	{	
		file << "Default-path=" << m_mapSettings["Default-path"] << std::endl;
		file << "Recursive=" << m_mapSettings["Recursive"] << std::endl;
		file << "Clear=" << m_mapSettings["Clear"] << std::endl;	
	}
	else
	{
		std::cout << "File is not open" << std::endl;
	}	
	file.close();
}

std::string RenameMeSettings::getDatas(std::string key)
{ 
	return m_mapSettings[key];
}

void RenameMeSettings::setDatas(std::string key, std::string value)
{
	m_mapSettings[key] = value;
}

bool RenameMeSettings::strToBool(std::string str)
{
	bool b;
	std::istringstream is(str);
	is >> std::boolalpha >> b;
	return b;
}

std::string RenameMeSettings::boolToStr(bool boolean)
{
	std::string str = "false";
	if(boolean)
	{
		str = "true";
	}
	return str;
}
