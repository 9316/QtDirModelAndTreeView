#include "dialog.h"
#include "ui_dialog.h"
#include <QInputDialog>
#include<QFile>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    model = new QDirModel(this);
    model->setReadOnly(false);

    ui->treeView->setModel(model);
    model->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name);//sorting(დახარისხება) //ignorCase(იგნორის შემთხვევაში)
    QModelIndex index = model->index("C:/");
    ui->treeView->expand(index); //expand(გაფართოება)
    ui->treeView->scrollTo(index);//scrollto(გადახვევა)
    ui->treeView->setCurrentIndex(index); //დაყენე მიმდინარე ინდექსის მიხედვით
    ui->treeView->resizeColumnToContents(0);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
QModelIndex index = ui->treeView->currentIndex();
if(!index.isValid()) return;
QString name = QInputDialog::getText(this, "ფაილის შექმნა","შეიყვანეთ სახელი");
if(name.isEmpty()) return;
model->mkdir(index,name);

}



void Dialog::on_pushButton_2_clicked()
{
    QModelIndex index = ui->treeView->currentIndex();
    if(!index.isValid()) return;

    if(model->fileInfo(index).isDir()){

        model->isDir(index);

        model->rmdir(index);



    }
    else{
        model->remove(index);

    }
}
