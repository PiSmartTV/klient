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

    // Checking if filepath exists
    if (!QFile::exists(filename)) {
        QMessageBox::critical(this, tr("File doesn't exist."), tr("File doesn't exist. Please enter valid path."), QMessageBox::Ok);
        return;
    }

    // Checking if IPv4 is valid
    QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    QString ipPattern = QString("^%1\\.%1\\.%1\\.%1$").arg(ipRange);
    QRegExp ipRegex(ipPattern);
    if(!ipRegex.exactMatch(address)) {
        QMessageBox::critical(this, tr("IP address is invalid."), tr("IP address is not valid. Please enter valid IP address."), QMessageBox::Ok);
        return;
    }

    QString output = QString("udp://%1:23000").arg(address);

    // Starting thread
    QFuture<int> stream_future = QtConcurrent::run(stream, output, filename);
    if (stream_future.result() != 0) {
        QMessageBox::critical(this, tr("Stream failed."), tr("Stream exited with status code 1."), QMessageBox::Ok);
    }
}
