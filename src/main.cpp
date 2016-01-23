// QT
#include <QApplication>
#include <QPushButton>

// Project
#include "RenameMeWindow.h"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	// Create a window
        RenameMeWindow mainWindow;
        mainWindow.show();

	// Display the window
	return app.exec();
}
