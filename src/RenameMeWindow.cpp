#include "RenameMeWindow.h"

RenameMeWindow::RenameMeWindow() : QMainWindow()
{
    this->resize(QSize(600,450));
    createMenu();

    m_table= new QTableWidget(0, 3, this);
    m_tabHeader << "Path" << "Date" << "";
    m_table->setHorizontalHeaderLabels(m_tabHeader);
    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
		m_table->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    m_table->setSortingEnabled(false);

    setCentralWidget(m_table);
}

RenameMeWindow::~RenameMeWindow()
{
    delete m_toolBar;
    delete m_openAct;
    delete m_table;
}

// SLOTS
void RenameMeWindow::open()
{

	  //m_currentDir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly);
   	RenameMePhotos photos;
		int i = 0;
		m_currentDir = "/home/brieuc/Images/Samples/";
    if(m_currentDir != NULL)
    {
        m_runAct->setEnabled(true);
				m_table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
				m_table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
				m_table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
        photos.openDirectory(m_currentDir.toStdString(), true);
	
				std::vector<std::pair<boost::filesystem::path, time_t> > vec = photos.getPhotos();
				for(std::vector<std::pair<boost::filesystem::path, time_t> >::const_iterator it(vec.begin()); it != vec.end(); it++)
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
}

void RenameMeWindow::run()
{
    int result = QMessageBox::warning(this, "Warning: This is non-reversible", "<p align='center'>This action can't be undone. Are you sure, you want to rename all these files ?</p>", QMessageBox::Yes | QMessageBox::No);
    if(result == QMessageBox::Yes)
    {

    }
    else if(result == QMessageBox::No)
    {
        QMessageBox::information(this, "Abort successful", "The abort was successfully executed !");
    }
}


// METHODS
void RenameMeWindow::createMenu()
{
    m_toolBar = addToolBar(tr("File"));
    m_toolBar->setMovable(false);
    m_toolBar->setFloatable(false);

    m_openAct = new QAction(QIcon("../images/open.png"), tr("&Open a directory"), this);
    m_runAct = new QAction(QIcon("../images/run.png"), tr("&Rename files"), this);
    m_runAct->setEnabled(false);

    m_toolBar->addAction(m_openAct);
    m_toolBar->addAction(m_runAct);

    connect(m_openAct, SIGNAL(triggered()), this, SLOT(open()));
    connect(m_runAct, SIGNAL(triggered()), this, SLOT(run()));
}
