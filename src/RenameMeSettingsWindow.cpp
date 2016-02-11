#include "RenameMeSettingsWindow.h"

RenameMeSettingsWindow::RenameMeSettingsWindow(QWidget *parent) : QDialog(parent)
{
	// Initializing datas
	this->setMinimumWidth(500);
	m_mainLayout = new QVBoxLayout;
	// Creating GroupBoxes
	createPathBox();
	createPushButtons();
	// Adding groupBoxes to the mainLayout
	m_mainLayout->addWidget(m_pathBox);
	m_mainLayout->addLayout(m_buttonLayout);
	setLayout(m_mainLayout);
}

RenameMeSettingsWindow::~RenameMeSettingsWindow()
{
	delete m_pathLabel;
	delete m_pathEdit;
	delete m_pathButton;
	delete m_recursiveCheckBox;
	delete m_clearCheckBox;
	delete m_validButton;
	delete m_resetButton;
	delete m_pathLayout;
	delete m_openLayout;
	delete m_buttonLayout;
	delete m_pathBox;	
	delete m_mainLayout;
}

void RenameMeSettingsWindow::openFileDialog()
{
	RenameMeMainWindow* parent = (RenameMeMainWindow*)this->parentWidget();
	QString str = QFileDialog::getExistingDirectory(this, tr("Open Directory"),parent->getSettings()->getDatas("Default-path").c_str());
	m_pathEdit->setText(str);
}

void RenameMeSettingsWindow::save()
{
	RenameMeMainWindow* parent = (RenameMeMainWindow*)this->parentWidget();
	parent->getSettings()->setDatas("Default-path", m_pathEdit->text().toStdString());
	parent->getSettings()->setDatas("Recursive", parent->getSettings()->boolToStr(m_recursiveCheckBox->isChecked()));
	parent->getSettings()->setDatas("Clear", parent->getSettings()->boolToStr(m_clearCheckBox->isChecked()));
	parent->getSettings()->writeDatas();
	this->close();
}

void RenameMeSettingsWindow::createPathBox()
{
	RenameMeMainWindow* parent = (RenameMeMainWindow*)this->parentWidget();
	m_pathBox = new QGroupBox(tr("Directory Settings"));
	m_openLayout = new QVBoxLayout;
	m_pathLayout = new QHBoxLayout;
	m_pathLabel = new QLabel(tr("Default Path :"));
	m_pathEdit = new QLineEdit(parent->getSettings()->getDatas("Default-path").c_str());
	m_pathButton = new QPushButton(tr("Browse"));
	m_recursiveCheckBox = new QCheckBox("Use recursive directory");
	m_clearCheckBox = new QCheckBox("Clear directory's list when opening a new directory");
	if(parent->getSettings()->strToBool(parent->getSettings()->getDatas("Recursive")))
	{
		m_recursiveCheckBox->setCheckState(Qt::Checked);
	}
	if(parent->getSettings()->strToBool(parent->getSettings()->getDatas("Clear")))
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

void RenameMeSettingsWindow::createPushButtons()
{
	m_buttonLayout = new QHBoxLayout;
	m_validButton = new QPushButton(tr("Valid"));
	m_resetButton = new QPushButton(tr("Reset"));
	m_buttonLayout->addWidget(m_validButton);
	m_buttonLayout->addWidget(m_resetButton);

	connect(m_validButton, SIGNAL(released()), this, SLOT(save()));
}
