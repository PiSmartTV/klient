#include "mainwindow.h"
#include "../ui/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->fileLineEdit = this->centralWidget()->findChild<QLineEdit*>("fileLineEdit");
    this->addressLineEdit = this->centralWidget()->findChild<QLineEdit*>("addressLineEdit");
}

MainWindow::~MainWindow()
{
    delete this->addressLineEdit;
    delete this->fileLineEdit;
    delete ui;
}


void MainWindow::on_browseButton_clicked()
{
    // Open dialog to choose file
    QString filename = QFileDialog::getOpenFileName(this, tr("Open movie"), QDir::homePath(), tr("Movie files (*.mp4 *.avi *.mov);; All files (*.*)"));

    this->fileLineEdit->setText(filename);
}

void MainWindow::on_playButton_clicked()
{
    // Validate inputs
    QString filename = this->fileLineEdit->text();
    QString address = this->addressLineEdit->text();

    if (!QFile::exists(filename)) {
        QMessageBox::critical(this, tr("File doesn't exist."), tr("File doesn't exist. Please enter valid path."), QMessageBox::Ok);
    }
    // TODO: Validate IP address

    QString output = QString("udp://%1:23000").arg(address);

    // Starting thread
    QFuture<int> stream_future = QtConcurrent::run(stream, output, filename);
    if (stream_future.result() != 0) {
        QMessageBox::critical(this, tr("Stream failed."), tr("Stream exited with status code 1."), QMessageBox::Ok);
    }
}
