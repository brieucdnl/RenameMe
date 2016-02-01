#ifndef DEF_RENAMEMESETTINGS
#define DEF_RENAMEMESETTINGS

#include <unordered_map>

class RenameMeSettings
{
	public:
		RenameMeSettings(std::string pathFile);
		~RenameMeSettings();
		bool readDatas();
		std::string getDatas(std::string key);

	private:	
		std::string m_configFile;
		std::unordered_map<std::string, std::string> m_mapSettings;
};

#endif
