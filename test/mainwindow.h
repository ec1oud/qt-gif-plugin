#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QPlainTextEdit>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
	void open(char* filename);

private:
	void open(QString filename);
	void save(QString filename);

private slots:
	void on_actionSave_triggered();
	void on_actionComment_triggered();
	void on_actionExport_GIF_triggered();
	void on_actionOpen_triggered();

private:
    Ui::MainWindow *ui;
	QImage image;
	QPlainTextEdit commentText;
	QString lastFileName;
};

#endif // MAINWINDOW_H
