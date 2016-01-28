// QT
#include <QApplication>
#include <QPushButton>

// Project
#include "RenameMeMainWindow.h"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	// Create a window
  	RenameMeMainWindow mainWindow;
    mainWindow.show();

	// Display the window
	return app.exec();
}
