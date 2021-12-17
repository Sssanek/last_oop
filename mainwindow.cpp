#include <QFileDialog>
#include "mainwindow.h"
#include "HashSet.cpp"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    clearAll();
}

void MainWindow::on_remove_button_clicked() {
    genres[currentIndex].erase(ui->lineEdit->text().toStdString());
    ui->lineEdit->clear();
    Update();
}

void MainWindow::on_add_button_clicked() {
    genres[currentIndex] << ui->lineEdit->text().toStdString();
    Update();
}

void MainWindow::on_clear_button_clicked() {
    clearAll();
    Update();
}

void MainWindow::on_actionOpen_triggered() {
    if (currentIndex==-1)
        return;;
    QString file_name = QFileDialog::getOpenFileName(this,
                                                     "Open the file");
    genres[currentIndex].load(file_name.toStdString());
    Update();
}

void MainWindow::on_actionSave_triggered() {
    if (currentIndex==-1)
        return;;
    QString file_name = QFileDialog::getSaveFileName(this,
                                                     "Save the file");
    genres[currentIndex].save(file_name.toStdString());
}

void MainWindow::Update() {
    ui->listWidget->clear();
    ui->remove_button->setEnabled (currentIndex != -1);
    ui->add_button->setEnabled (currentIndex != -1);
    if (currentIndex == -1) {
        HashSet<std::string> hs = genres[0];
        for (int i=1; i<arrayLength; i++){
            hs = hs && genres[i];
        }
        for (const auto& bucket : hs.buckets_) {
            if (!bucket.empty()) {
                for (const auto& elem : bucket) {
                    QString item = QString::fromStdString(elem);
                    ui->listWidget->addItem(item);
                }
            }
        }
    } else {
        if (genres[currentIndex].empty()) {
            return;
        }
        for (const auto& bucket : genres[currentIndex].buckets_) {
            if (!bucket.empty()) {
                for (const auto& elem : bucket) {
                    QString item = QString::fromStdString(elem);
                    ui->listWidget->addItem(item);
                }
            }
        }
    }
}

void MainWindow::clearAll() {
    ui->writersList->clear();
    ui->writersList->addItem("All");
    arrayLength = 0;
    for (int i=0; i<20; i++) {
        writers[i]="";
        genres[i].clear();
    }
    currentIndex=-1;
    Update();
}

void MainWindow::on_addWriter_clicked() {
    writers[arrayLength++]=(ui->writerEdit->text().toStdString());
    ui->writersList->addItem(ui->writerEdit->text());
    Update();
}

void MainWindow::on_writersList_currentIndexChanged(int index) {
    currentIndex = index - 1;
    Update();
}
