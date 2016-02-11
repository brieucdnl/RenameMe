#ifndef DEF_RENAMEMESETTINGS
#define DEF_RENAMEMESETTINGS

#include <unordered_map>

class RenameMeSettings
{
	public:
		RenameMeSettings(std::string pathFile);
		~RenameMeSettings();
		bool readDatas();
		void writeDatas();
		std::string getDatas(std::string key);
		void setDatas(std::string key, std::string value);
		bool strToBool(std::string str);
		std::string boolToStr(bool boolean);

	private:	
		std::string m_configFile;
		std::unordered_map<std::string, std::string> m_mapSettings;
};

#endif
