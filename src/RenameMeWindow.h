#ifndef DEF_RENAMEMEWINDOW
#define DEF_RENAMEMEWINDOW

#include <QtWidgets>
#include <iostream>
#include "RenameMePhotos.h"

class RenameMeWindow : public QMainWindow
{
	Q_OBJECT

	public:
		RenameMeWindow();
		~RenameMeWindow();
		void createMenu();

	private slots:
		void open();
		void run();

	private:
		std::vector<std::pair<boost::filesystem::path, time_t> > m_vec;

		QTableWidget *m_table;
		QStringList m_tabHeader;
		QString m_currentDir;
		QToolBar *m_toolBar;
		QAction *m_openAct;
		QAction *m_runAct;
};

#endif
