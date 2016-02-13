#ifndef DEF_RENAMEMESETTINGSWINDOW
#define DEF_RENAMEMESETTINGSWINDOW

#include <QtWidgets>
#include <climits>
#include "RenameMeSettings.h"
#include "RenameMeMainWindow.h"

class RenameMeSettingsWindow : public QDialog
{
	Q_OBJECT

	public:
		RenameMeSettingsWindow(QWidget *parent = 0);
		~RenameMeSettingsWindow();
		
	private slots:
		void openFileDialog();
		void save();
		
	private:
		// Attributes
		// Main
		QVBoxLayout *m_mainLayout;
		// PathBox	
		QGroupBox *m_pathBox;
		QVBoxLayout *m_openLayout;
		QHBoxLayout *m_pathLayout;
		QLabel *m_pathLabel;
		QLineEdit *m_pathEdit;
		QPushButton *m_pathButton;
		QCheckBox *m_recursiveCheckBox;
		QCheckBox *m_clearCheckBox;
		// ProcessBox
		QGroupBox *m_processBox;
		QVBoxLayout *m_processLayout;
		QHBoxLayout *m_nameLayout;
		QHBoxLayout *m_startCountLayout;
		QLabel *m_nameLabel;
		QLineEdit *m_nameEdit;
		QLabel *m_startCountLabel;
		QSpinBox *m_startCountSpin;
		// Buttons
		QHBoxLayout *m_buttonLayout;
		QPushButton *m_validButton;
		QPushButton *m_resetButton;
		
		// Methods
		void createPathBox();
		void createProcessBox();
		void createPushButtons();
};

#endif
