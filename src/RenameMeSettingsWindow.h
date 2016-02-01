#ifndef DEF_RENAMEMESETTINGSWINDOW
#define DEF_RENAMEMESETTINGSWINDOW

#include <QtWidgets>
#include "RenameMeSettings.h"
#include "RenameMeMainWindow.h"

class RenameMeSettingsWindow : public QDialog
{
	Q_OBJECT

	public:
		RenameMeSettingsWindow(QWidget *parent = 0);
		~RenameMeSettingsWindow();
	
	private:
		// Attributes
		QVBoxLayout *m_mainLayout;
		QVBoxLayout *m_openLayout;
		QGroupBox *m_pathBox;
		QHBoxLayout *m_pathLayout;
		QHBoxLayout *m_recursiveLayout;
		QLabel *m_pathLabel;
		QLineEdit *m_pathEdit;
		QCheckBox *m_recursiveCheckBox;
		QPushButton *m_pathButton;
		// Methods
		void createPathBox();
};

#endif
