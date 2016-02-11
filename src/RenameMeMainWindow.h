#ifndef DEF_RENAMEMEMAINWINDOW
#define DEF_RENAMEMEMAINWINDOW

#include <QtWidgets>
#include "RenameMePhotos.h"
#include "RenameMeSettingsWindow.h"
#include "RenameMeSettings.h"

class RenameMeMainWindow : public QMainWindow
{
	Q_OBJECT

	public:
		RenameMeMainWindow();
		~RenameMeMainWindow();
		RenameMeSettings* getSettings();

	private slots:
		void open();
		void run();
		void update();
		void settings();

	private:
		// Attributes
		std::vector<std::pair<boost::filesystem::path, time_t> > m_vec;
		RenameMeSettings *m_settings;
		QString m_currentDir;
		QTableWidget *m_table;
		QStringList m_tabHeader;
		QToolBar *m_toolBar;
		QAction *m_openAct;
		QAction *m_runAct;
		QAction *m_updateAct;
		QAction *m_settingsAct;
		// Methods
		void createMenu();
		void loadTable();
};

#endif
