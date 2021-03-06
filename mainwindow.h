#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QTimer>
#include <QThread>

#include "MyCopy.h"
#include "MyPack.h"
#include "MyCompress.h"
#include "MyDiff.h"
#include "MyOpenssl.h"
#include "MyTimer.h"

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <utime.h>
#include <time.h>
#include <sys/time.h>
#include <utility>
#include <vector>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //备份文件选择
    void on_pushButton_clicked();
    //备份路径选择
    void on_pushButton_2_clicked();
    //开始备份
    void on_pushButton_3_clicked();
    //选择还原文件
    void on_pushButton_4_clicked();
    //开始还原
    void on_pushButton_5_clicked();

    void on_checkBox_3_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_checkBox_stateChanged(int arg1);

    void on_pushButton_6_clicked();

    void on_checkBox_4_stateChanged(int arg1);

    void on_checkBox_5_stateChanged(int arg1);

    void on_pushButton_7_clicked();

    void on_checkBox_7_stateChanged(int arg1);

    void on_pushButton_8_clicked();

    void on_checkBox_6_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    QString src_file;
    QString des_file;
    QString reduction_src_file;
    QString copy_input_password;
    QString reduction_des_file;
    int IS_Encryption;
    int IS_Compress;
    int IS_Pack;
    int IS_Timer;
    int copy_isdir;
    int reduce_isdir;

    MyTimer *mt;

    std::vector<MyTimer *> timerVec;
    std::vector<QString> nameVec;

};

char *get_myrelativecwd(char *src_origin);

char *get_parentpwd(char *src_origin);

#endif // MAINWINDOW_H
