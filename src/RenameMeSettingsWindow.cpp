#include "RenameMeSettingsWindow.h"

RenameMeSettingsWindow::RenameMeSettingsWindow(QWidget *parent) : QDialog(parent)
{
	// Initializing datas
	this->setMinimumWidth(500);
	m_mainLayout = new QVBoxLayout;
	// Creating GroupBoxes
	createPathBox();
	// Adding groupBoxes to the mainLayout
	m_mainLayout->addWidget(m_pathBox);
	setLayout(m_mainLayout);
}

RenameMeSettingsWindow::~RenameMeSettingsWindow()
{
	delete m_pathLabel;
	delete m_pathEdit;
	delete m_pathButton;
	delete m_recursiveCheckBox;
	delete m_clearCheckBox;
	delete m_pathLayout;
	delete m_openLayout;
	delete m_pathBox;	
	delete m_mainLayout;
}

void RenameMeSettingsWindow::openFileDialog()
{
	RenameMeMainWindow* parent = (RenameMeMainWindow*)this->parentWidget();
	QString str = QFileDialog::getExistingDirectory(this, tr("Open Directory"),parent->getSettings().getDatas("Default-path").c_str());
	m_pathEdit->setText(str);
}

void RenameMeSettingsWindow::createPathBox()
{
	RenameMeMainWindow* parent = (RenameMeMainWindow*)this->parentWidget();
	m_pathBox = new QGroupBox(tr("Directory Settings"));
	m_openLayout = new QVBoxLayout;
	m_pathLayout = new QHBoxLayout;
	m_pathLabel = new QLabel(tr("Default Path :"));
	m_pathEdit = new QLineEdit(parent->getSettings().getDatas("Default-path").c_str());
	m_pathButton = new QPushButton(tr("Browse"));
	m_recursiveCheckBox = new QCheckBox("Use recursive directory");
	m_clearCheckBox = new QCheckBox("Clear directory's list when opening a new directory");
	if(parent->getSettings().strToBool(parent->getSettings().getDatas("Recursive")))
	{
		m_recursiveCheckBox->setCheckState(Qt::Checked);
	}
	if(parent->getSettings().strToBool(parent->getSettings().getDatas("Clear")))
	{
		m_clearCheckBox->setCheckState(Qt::Checked);
	}
	m_pathLayout->addWidget(m_pathLabel);
	m_pathLayout->addWidget(m_pathEdit);
	m_pathLayout->addWidget(m_pathButton);
	m_openLayout->addLayout(m_pathLayout);
	m_openLayout->addWidget(m_recursiveCheckBox);
	m_openLayout->addWidget(m_clearCheckBox);
	m_pathBox->setLayout(m_openLayout);

	connect(m_pathButton, SIGNAL(released()), this, SLOT(openFileDialog()));
}
