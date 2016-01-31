#include "RenameMeSettingsWindow.h"

RenameMeSettingsWindow::RenameMeSettingsWindow(QWidget *parent) : QDialog(parent)
{
	m_mainLayout = new QVBoxLayout;
	createPathBox();
	m_mainLayout->addWidget(m_pathBox);
	setLayout(m_mainLayout);
}

RenameMeSettingsWindow::~RenameMeSettingsWindow()
{
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
	m_pathEdit = new QLineEdit;
	m_pathButton = new QPushButton(tr("Browse"));
	m_pathLayout->addWidget(m_pathLabel);
	m_pathLayout->addWidget(m_pathEdit);
	m_pathLayout->addWidget(m_pathButton);
	m_pathBox->setLayout(m_pathLayout);
}
