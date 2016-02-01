#include "RenameMeSettingsWindow.h"
#include <iostream>

RenameMeSettingsWindow::RenameMeSettingsWindow(QWidget *parent) : QDialog(parent)
{
	// Initializing datas
	m_settings = new RenameMeSettings("/home/brieuc/Documents/RenameMe/build/debug/config.txt");
	m_settings->readDatas();
	m_mainLayout = new QVBoxLayout;
	// Creating GroupBoxes
	createPathBox();
	// Adding groupBoxes to the mainLayout
	m_mainLayout->addWidget(m_pathBox);
	setLayout(m_mainLayout);
}

RenameMeSettingsWindow::~RenameMeSettingsWindow()
{
	delete m_settings;
	delete m_pathLabel;
	delete m_pathEdit;
	delete m_pathLayout;
	delete m_pathBox;	
}

void RenameMeSettingsWindow::createPathBox()
{
	m_pathBox = new QGroupBox(tr("Default Path"));
	m_pathLayout = new QHBoxLayout;
	m_pathLabel = new QLabel(tr("Default Path"));
	m_pathEdit = new QLineEdit(QString(m_settings->getDatas("Default-path").c_str()));
	m_pathButton = new QPushButton(tr("Browse"));
	m_pathLayout->addWidget(m_pathLabel);
	m_pathLayout->addWidget(m_pathEdit);
	m_pathLayout->addWidget(m_pathButton);
	m_pathBox->setLayout(m_pathLayout);
}
