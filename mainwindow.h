#ifndef L2V2_MAINWINDOW_H
#define L2V2_MAINWINDOW_H


#include <QtWidgets/QMainWindow>
#include "UI.h"
#include "HashSet.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
public:
Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void on_remove_button_clicked();

    void on_add_button_clicked();

    void on_addWriter_clicked();

    void on_clear_button_clicked();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_writersList_currentIndexChanged(int index);

private:
    void Update();

    int currentIndex;
    int arrayLength = 0;
    Ui::MainWindow *ui;
    std::string writers[20];
    HashSet<std::string> genres[20];

    void clearAll();
};


#endif //L2V2_MAINWINDOW_H
