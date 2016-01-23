#ifndef DEF_RENAMEMEWINDOW
#define DEF_RENAMEMEWINDOW

#include <QtWidgets>
#include <iostream>

class RenameMeWindow : public QMainWindow
{
    Q_OBJECT

    public:
        RenameMeWindow();
        ~RenameMeWindow();
        void createMenu();

    private slots:
        void open();
        void run();

    private:
        QPlainTextEdit *m_textEdit;

        QString m_currentDir;

        QToolBar *m_toolBar;
        QAction *m_openAct;
        QAction *m_runAct;
};

#endif
