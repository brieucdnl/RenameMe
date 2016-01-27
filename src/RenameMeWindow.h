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
		void loadTable();

	private slots:
		void open();
		void run();
		void update();

	private:
		std::vector<std::pair<boost::filesystem::path, time_t> > m_vec;

		QString m_currentDir;

		QTableWidget *m_table;
		QStringList m_tabHeader;
		QToolBar *m_toolBar;
		QAction *m_openAct;
		QAction *m_runAct;
		QAction *m_updateAct;
};

#endif
