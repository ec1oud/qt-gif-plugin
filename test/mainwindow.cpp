#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QImageWriter>
#include <QImageReader>
#include <QLibraryInfo>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	qDebug("libpaths:");
	foreach (QString libpath, QCoreApplication::libraryPaths ())
		qDebug("   %s", libpath.toAscii().constData());
	qDebug("plugin path:\n   %s", QLibraryInfo::location(QLibraryInfo::PluginsPath).toAscii().constData());
	qDebug("supported image formats for reading:");
	foreach(QByteArray f, QImageReader::supportedImageFormats())
		qDebug("   %s", f.constData());
	qDebug("supported image formats for writing:");
	foreach(QByteArray f, QImageWriter::supportedImageFormats())
		qDebug("   %s", f.constData());
	commentText.setWindowFlags(Qt::Dialog);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::open(char* filename)
{
	open(QString(filename));
}

void MainWindow::open(QString filename)
{
	lastFileName = filename;
	image = QImage(filename);
	ui->label->setPixmap(QPixmap::fromImage(image));
	commentText.setPlainText(image.text());
	QFileInfo fi(filename);
	ui->actionSave->setEnabled(
		QString::compare(fi.suffix(), "gif", Qt::CaseInsensitive) == 0);
	setWindowTitle(QString("GIFTest %1").arg(filename));
}

void MainWindow::on_actionOpen_triggered()
{
  QString fileName = QFileDialog::getOpenFileName(this,
	 tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp *.gif)"));
  open(fileName);
//  image = QImage(fileName);
//  ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_actionExport_GIF_triggered()
{
	QString fileName = QFileDialog::getSaveFileName(this,
		tr("Export GIF Image"), "", tr("GIF Files (*.gif)"));
	save(fileName);
}

void MainWindow::save(QString fileName)
{
	QImageWriter wr(fileName, "gif");
	qDebug("supports description? %d", wr.supportsOption(QImageIOHandler::Description));
	QString comment = commentText.toPlainText();
	if (!comment.isEmpty())
	{
		int colonIdx = comment.indexOf(":");
		if (colonIdx >= 0)
		{
//			qDebug() << "setText" << comment.left(colonIdx) << comment.mid(colonIdx + 2);
			wr.setText(comment.left(colonIdx), comment.mid(colonIdx + 2));
		}
		else
			wr.setText("", comment);
	}
	if (!wr.write(image))
		qCritical() << "error" << wr.error() << ": " << wr.errorString();
}

void MainWindow::on_actionComment_triggered()
{
	commentText.setVisible(true);
}

void MainWindow::on_actionSave_triggered()
{
	save(lastFileName);
}
