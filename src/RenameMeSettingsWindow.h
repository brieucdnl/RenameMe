#ifndef DEF_RENAMEMESETTINGSWINDOW
#define DEF_RENAMEMESETTINGSWINDOW

#include <QtWidgets>
#include "RenameMeSettings.h"

class RenameMeSettingsWindow : public QDialog
{
	Q_OBJECT

	public:
		RenameMeSettingsWindow(QWidget *parent = 0);
		~RenameMeSettingsWindow();
	
	private:
		// Attributes
		RenameMeSettings *m_settings;
		QVBoxLayout *m_mainLayout;
		QGroupBox *m_pathBox;
		QHBoxLayout *m_pathLayout;
		QLabel *m_pathLabel;
		QLineEdit *m_pathEdit;
		QPushButton *m_pathButton;
		// Methods
		void createPathBox();
};

#endif
