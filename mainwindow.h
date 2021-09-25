#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
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
    int copy_isdir;
    int reduce_isdir;
};

char *get_myrelativecwd(char *src_origin);

char *get_parentpwd(char *src_origin);

#endif // MAINWINDOW_H
