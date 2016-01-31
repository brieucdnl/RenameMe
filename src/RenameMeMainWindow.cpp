#include "RenameMeMainWindow.h"

RenameMeMainWindow::RenameMeMainWindow() : QMainWindow()
{
	std::vector<std::pair<boost::filesystem::path, time_t> > m_vec;	
	  
	this->resize(QSize(600,450));

  createMenu();
  m_table = new QTableWidget(0, 3, this);
  m_tabHeader << "Path" << "Date" << "";
  m_table->setHorizontalHeaderLabels(m_tabHeader);
	m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	m_table->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
	m_table->setSortingEnabled(false);
	setCentralWidget(m_table);
}

RenameMeMainWindow::~RenameMeMainWindow()
{
	delete m_openAct;
	delete m_runAct;
	delete m_updateAct;
	delete m_settingsAct;
	delete m_table;
	delete m_toolBar;
}


// SLOTS
void RenameMeMainWindow::open()
{
	m_table->setRowCount(0);
	m_currentDir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly);
	if(m_currentDir != NULL)
	{
		m_runAct->setEnabled(true);
		m_table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
		m_table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
		m_table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
		RenameMePhotos::openDirectory(m_currentDir.toStdString(), m_vec, true, true);
		loadTable();	
	}
}

void RenameMeMainWindow::run()
{
	bool run = true;
	// Pre-loading Datas
	std::vector<std::pair<boost::filesystem::path, time_t> > vecTmp, vecNotChecked, vecError;
	for(unsigned int i = 0; i < m_vec.size(); i++)
	{
		if(m_table->item(i, 2)->checkState() == Qt::Checked)
		{
			vecTmp.push_back(m_vec[i]);
		}
		else
		{
			vecNotChecked.push_back(m_vec[i]);
		}
	}
	
	if(!vecNotChecked.empty())
	{
		if(RenameMePhotos::checkConflict(vecNotChecked, vecError, m_vec.size() - vecTmp.size(), "Image", 1))
		{
			std::stringstream ss;
			ss << vecError.size() << " files in conflict ! We can resolve these conflicts by adding conflicted files to the process, would you go for it ?";
			int result  = QMessageBox(QMessageBox::Critical, "Error !", QString::fromStdString(ss.str()), QMessageBox::Yes | QMessageBox::No).exec();	
			run = (result == QMessageBox::Yes);
			if(run)
			{
				RenameMePhotos::solveConflict(vecTmp, vecError);
				vecError.clear();	
			}
		}
	}
	if(run)
	{
		std::stringstream ss;
		ss << "<p align='center'>This action can't be undone. Are you sure, you want to rename " << vecTmp.size() << " files ?</p>";
		// Display a warning message
		int result = QMessageBox(QMessageBox::Warning, "Warning !", QString::fromStdString(ss.str()), QMessageBox::Yes | QMessageBox::No).exec();
		if(result == QMessageBox::Yes)
		{
			RenameMePhotos::sortAndRename(vecTmp, "Image", 1);		
			m_runAct->setEnabled(false);
			m_updateAct->setEnabled(true);	
			// Display a success message
			std::stringstream ss2;
			ss2 << vecTmp.size() << " files renamed successfully !";
			QMessageBox(QMessageBox::Information, "Success !", QString::fromStdString(ss2.str())).exec();
		}
		else if(result == QMessageBox::No)
		{
			// Display an abort message
			QMessageBox(QMessageBox::Information, "Abort !", "The abort was successfully executed !").exec();
		}
	}
}

void RenameMeMainWindow::update()
{
	RenameMePhotos::openDirectory(m_currentDir.toStdString(), m_vec, true);
	loadTable();
	m_runAct->setEnabled(true);
}

void RenameMeMainWindow::settings()
{
	RenameMeSettingsWindow settingsWindow(this);
	settingsWindow.exec();
}

// METHODS
void RenameMeMainWindow::createMenu()
{
	m_toolBar = addToolBar(tr("File"));
	m_toolBar->setMovable(false);
	m_toolBar->setFloatable(false);

	m_openAct = new QAction(QIcon("../../images/open.png"), tr("&Open a directory"), this);
	m_runAct = new QAction(QIcon("../../images/run.png"), tr("&Rename files"), this);
	m_runAct->setEnabled(false);
	m_updateAct = new QAction(QIcon("../../images/update.png"), tr("&Update directory"), this);
	m_updateAct->setEnabled(false);
	m_settingsAct = new QAction(QIcon("../../images/settings.png"), tr("&Change Settings"), this);

	m_toolBar->addAction(m_openAct);
	m_toolBar->addAction(m_runAct);
	m_toolBar->addAction(m_updateAct);
	m_toolBar->addAction(m_settingsAct);

	connect(m_openAct, SIGNAL(triggered()), this, SLOT(open()));
	connect(m_runAct, SIGNAL(triggered()), this, SLOT(run()));
	connect(m_updateAct, SIGNAL(triggered()), this, SLOT(update()));
	connect(m_settingsAct, SIGNAL(triggered()), this, SLOT(settings()));
}

void RenameMeMainWindow::loadTable()
{
	int i = 0;
	m_table->setRowCount(0); // Reinit NbRow in table
	for(std::vector<std::pair<boost::filesystem::path, time_t> >::const_iterator it(m_vec.begin()); it != m_vec.end(); it++)
	{
		m_table->setRowCount(m_table->rowCount() + 1);
		// vPath
		QString vPath((*it).first.c_str());
		// vDate
		char dateTmp[20];
		strftime(dateTmp, 20, "%Y-%m-%d %H:%M:%S", localtime(&(*it).second));
		QString vDate(dateTmp); 	
		// CheckBox
		QTableWidgetItem *item3 = new QTableWidgetItem();
		item3->setCheckState(Qt::Checked);

		m_table->setItem(i, 0, new QTableWidgetItem(vPath));
		m_table->setItem(i, 1, new QTableWidgetItem(vDate));
		m_table->setItem(i, 2, item3);
		i++;
	}
}
