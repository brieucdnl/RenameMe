#include "RenameMeWindow.h"

RenameMeWindow::RenameMeWindow() : QMainWindow()
{
    this->resize(QSize(600,450));

    m_textEdit = new QPlainTextEdit;
    setCentralWidget(m_textEdit);

    createMenu();
}

RenameMeWindow::~RenameMeWindow()
{
    delete m_toolBar;
    delete m_openAct;
    delete m_textEdit;
}

// SLOTS
void RenameMeWindow::open()
{
    m_currentDir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly);
    if(m_currentDir != NULL)
    {
        m_runAct->setEnabled(true);
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
