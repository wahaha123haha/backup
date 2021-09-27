
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setReadOnly(true);
    ui->lineEdit_2->setReadOnly(true);
    ui->lineEdit_3->setReadOnly(true);
    ui->lineEdit_4->setReadOnly(true);
    IS_Compress=0;
    IS_Encryption=0;
    IS_Pack=0;
    IS_Timer=0;
    copy_isdir=1;
    reduce_isdir=1;
}

MainWindow::~MainWindow()
{
    delete ui;
}

//选择备份文件
void MainWindow::on_pushButton_clicked()
{
    if(copy_isdir==1)
        src_file=QFileDialog::getExistingDirectory(this,"test","/");
    else
        src_file=QFileDialog::getOpenFileName(this,"test","/");
    ui->lineEdit->setText(src_file);
}

//选择备份路径
void MainWindow::on_pushButton_2_clicked()
{
    des_file=QFileDialog::getExistingDirectory(this,"test","/");
    ui->lineEdit_2->setText(des_file);
}


//开始按要求备份
void MainWindow::on_pushButton_3_clicked()
{
    char *src_c,*des_c;
    QByteArray temp=src_file.toLatin1();
    src_c=temp.data();
    if(temp.isEmpty()){
        QMessageBox::information(NULL, "错误", "请选择备份文件路径");
        return;
    }
    temp=des_file.toLatin1();
    des_c=temp.data();
    if(temp.isEmpty()){
        QMessageBox::information(NULL, "错误", "请选择目标路径");
        return;
    }
    if(this->IS_Encryption==1){
        bool ok;
        QString password = QInputDialog::getText(this, tr("密码"),tr("请输入密码"), QLineEdit::Password,0, &ok);
        if(ok&&!password.isEmpty()){
            this->copy_input_password=password;
        }
    }
    if(this->IS_Timer==1){
        int time_interval;
        if(!ui->lineEdit_5->text().isEmpty())
            time_interval=ui->lineEdit_5->text().toInt()*1000;
        else
            time_interval=5000;
        timerVec.push_back(new MyTimer(src_file.toStdString(),des_file.toStdString(),time_interval,IS_Encryption,IS_Pack,IS_Compress,copy_input_password.toStdString(),NULL));
        nameVec.push_back(src_file);
        ui->comboBox->addItem(src_file);
        return;
    }
    if(this->IS_Encryption==1){
        MyOpenssl mo(src_file.toStdString(),des_file.toStdString());
        mo.Encryption(copy_input_password.toStdString());
        QMessageBox::information(NULL, "备份成功", "已完成备份");
        return;
    }
    if(this->IS_Compress==1){
        MyCompress mc(src_c,des_c);
        mc.Compress();
        QMessageBox::information(NULL, "备份成功", "已完成备份");
        return;
    }
    if(this->IS_Pack==1){
        MyPack mp(src_c,des_c);
        mp.Pack();
        QMessageBox::information(NULL, "备份成功", "已完成备份");
        return;
    }
    MyCopy(src_c,des_c);
    QMessageBox::information(NULL, "备份成功", "已完成备份");
}

//选择还原备份文件
void MainWindow::on_pushButton_4_clicked()
{
    if(reduce_isdir==1)
        reduction_src_file=QFileDialog::getExistingDirectory(this,"test","/");
    else
        reduction_src_file=QFileDialog::getOpenFileName(this,"test","/");
    ui->lineEdit_3->setText(reduction_src_file);
}

//开始还原
void MainWindow::on_pushButton_5_clicked()
{
    char *src_c,*des_c;
    QByteArray temp=reduction_src_file.toLatin1();
    src_c=temp.data();
    if(temp.isEmpty()){
        QMessageBox::information(NULL, "错误", "请选择备份文件路径");
        return;
    }
    temp=reduction_des_file.toLatin1();
    des_c=temp.data();
    if(temp.isEmpty()){
        QMessageBox::information(NULL, "错误", "请选择目标路径");
        return;
    }
    char *src_temp=src_c+strlen(src_c)-4;
    int is_dec=!strcmp(".des3",src_c+strlen(src_c)-5);
    if(is_dec){
        bool ok;
        QString password = QInputDialog::getText(this, tr("密码"),tr("请输入密码"), QLineEdit::Password,0, &ok);
        if(ok&&!password.isEmpty()){
            MyOpenssl mo(reduction_src_file.toStdString(),des_c);
            mo.Deciphering(password.toStdString());
            QMessageBox::information(NULL, "还原成功", "已完成还原");
            return;
        }

    }
    int is_tar=!strcmp(".tar",src_c+strlen(src_c)-4);
    if(is_tar){
        MyPack mp(src_c,des_c);
        mp.RePack();
        QMessageBox::information(NULL, "还原成功", "已完成还原");
        return;
    }
    src_temp=src_c+strlen(src_c)-7;
    int is_gz=!strcmp(".tar.gz",src_c+strlen(src_c)-7);
    if(is_gz){
        MyCompress mc(src_c,des_c);
        mc.ReCompress();
        QMessageBox::information(NULL, "还原成功", "已完成还原");
        return;
    }
    MyCopy(src_c,des_c);
    QMessageBox::information(NULL, "还原成功", "已完成还原");
}

//设置打包
void MainWindow::on_checkBox_3_stateChanged(int arg1)
{
    this->IS_Pack=abs(1-this->IS_Pack);
}

//设置压缩
void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    if(!ui->checkBox_3->isChecked()){
        ui->checkBox_3->setChecked(true);
    }
    this->IS_Compress=abs(1-this->IS_Compress);
}

//设置加密
void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(!ui->checkBox_3->isChecked()){
        ui->checkBox_3->setChecked(true);
    }
    this->IS_Encryption=abs(1-this->IS_Encryption);
}

//设置还原目标路径
void MainWindow::on_pushButton_6_clicked()
{
    reduction_des_file=QFileDialog::getExistingDirectory(this,"test","/");
    ui->lineEdit_4->setText(reduction_des_file);
}

//获取目录/文件名
char *get_myrelativecwd(char *src_origin){
    int i,j;
    char dest_temp[100],dest_end[100];
    char* dest=new char[1024];
    for(i=strlen(src_origin)-1,j=0;src_origin[i]!='/';i--){
        dest_temp[j++]=src_origin[i];
    }
    dest_temp[j]='\0';
    for(i=0;i<strlen(dest_temp);i++){
        dest_end[i]=dest_temp[strlen(dest_temp)-i-1];
    }
    dest_end[i]='\0';
    strcpy(dest,dest_end);
    return dest;
}

//获取父目录
char *get_parentpwd(char *src_origin){
    int i=strlen(src_origin)-1;
    while(src_origin[i]!='/')
        i--;
    char temp[1024];
    char *parent=new char[1024];
    for(int j=0;j<i;j++)
        temp[j]=src_origin[j];
    temp[i]='\0';
    strcpy(parent,temp);
    return parent;
};

//备份目录/文件
void MainWindow::on_checkBox_4_stateChanged(int arg1)
{
    copy_isdir=abs(1-copy_isdir);
}

//还原目录/文件
void MainWindow::on_checkBox_5_stateChanged(int arg1)
{
    reduce_isdir=abs(1-reduce_isdir);
}

//查找文件不同
void MainWindow::on_pushButton_7_clicked()
{
    MyDiff md(reduction_src_file.toStdString(),reduction_des_file.toStdString());
    md.FindDiff();
}

//是否定时
void MainWindow::on_checkBox_7_stateChanged(int arg1)
{
    IS_Timer=abs(1-IS_Timer);
}

//关闭定时
void MainWindow::on_pushButton_8_clicked()
{
    QString path = ui->comboBox->currentText();
    size_t index = 0;
    for(;index < nameVec.size(); ++index){
        if(nameVec[index] == path){
            mt = timerVec[index];
            delete mt;
            timerVec.erase(timerVec.begin()+index);
            nameVec.erase(nameVec.begin()+index);
            ui->comboBox->removeItem(ui->comboBox->currentIndex());
            break;
        }
    }
}

//设置加密
void MainWindow::on_checkBox_6_stateChanged(int arg1)
{
    if(!ui->checkBox_3->isChecked()){
        ui->checkBox_3->setChecked(true);
    }
    this->IS_Encryption=abs(1-this->IS_Encryption);
}

