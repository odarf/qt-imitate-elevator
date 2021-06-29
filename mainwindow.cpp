#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    k=0;
    n=1;

    lift1=1;
    l1=1;//vverh
    lift2=n;
    l2=0;

    ui->setupUi(this);
    timerstatus=false;
    timer= new QTimer(this);
    //модель запросов
    modelIn = new QStringListModel(this);
    ui->listView->setModel(modelIn);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // модель лифт 1
    LiftIn1 = new QStringListModel(this);
    proxyModel1 = new QSortFilterProxyModel ;
    proxyModel1 -> setSourceModel (LiftIn1);
    ui->listView_2->setModel(proxyModel1);
    ui->listView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //модель лифт 2
    LiftIn2 = new QStringListModel(this);
    proxyModel2 = new QSortFilterProxyModel ;
    proxyModel2 -> setSourceModel (LiftIn2);
    ui->listView_3->setModel(proxyModel2);
    ui->listView_3->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //модель обработанных
    modelOut = new QStringListModel(this);
    ui->listView_4->setModel(modelOut);
    ui->listView_4->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //Для графика
    LiftOut1 = new QStringListModel(this);
    LiftOut2 = new QStringListModel(this);

    timer->setInterval(50);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateList()));
   // timer->start();
    QTimer::singleShot(5000, this, SLOT(changeList()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::changeList()
{
  // timerstatus=true;
}
bool MainWindow::compare()
{
    if (LiftIn1->rowCount()!=0&&LiftIn2->rowCount()!=0)
        if ((l1&&l2)||(!l1&&!l2))
            if (abs(lift1-randin)<=abs(lift2-randin))
                return 0;
            else return 1;
        else
            if (!l1&&l2)
                if ((randin-lift1)<=(lift2-randin))
                    return 0;
                else return 1;
            else
                if ((lift1-randin)<=(randin-lift2))
                    return 0;
                else return 1;
    else
        if (LiftIn1->rowCount()==0&&LiftIn2->rowCount()!=0)
                if (abs(lift1-randin)<=abs(lift2-randin))
                   {
                    if ((lift1-randin)>0)
                        l1=0;
                    else l1=1;
                    return 0;
                    }
                else return 1;
        else
            if (LiftIn1->rowCount()!=0&&LiftIn2->rowCount()==0)
                    if (abs(lift1-randin)<=abs(lift2-randin))
                        return 0;
                    else
                    {if ((lift2-randin)>0)
                            l2=0;
                        else l2=1;
                     return 1;
                    }
            else
                    if (abs(lift1-randin)<=abs(lift2-randin))
                        return 0;
                    else return 1;
}
void MainWindow::movelift1()
{
    int row1 = LiftOut1->rowCount();
    LiftOut1->insertRows(row1,1);
    QModelIndex index1 = LiftOut1->index(row1);
    if (LiftIn1->rowCount())
    {
        if (lift1<QVariant(LiftIn1->data(LiftIn1->index(0))).toInt())
            lift1++;
        else
            if (lift1>QVariant(LiftIn1->data(LiftIn1->index(0))).toInt())
                lift1--;
        if (lift1==QVariant(LiftIn1->data(LiftIn1->index(0))).toInt())
        {

            int row = modelOut->rowCount();
            modelOut->insertRows(row,1);
            QModelIndex index = modelOut->index(row);
            modelOut->setData(index,LiftIn1->data(LiftIn1->index(0)));
            LiftIn1->removeRows(0,1);
           // proxyModel1->removeRows(0,1);
        }
    }
    if(lift1<10)
       LiftOut1->setData(index1,"00"+QVariant(lift1).toString());
    else
        if (lift1<100)
            LiftOut1->setData(index1,"0"+QVariant(lift1).toString());
        else
            LiftOut1->setData(index1,QVariant(lift1).toString());
}
void MainWindow::movelift2()
{
    int row1 = LiftOut2->rowCount();
    LiftOut2->insertRows(row1,1);
    QModelIndex index1 = LiftOut2->index(row1);
    if (LiftIn2->rowCount())
    {
        if (lift2>QVariant(LiftIn2->data(LiftIn2->index(0))).toInt())
        {
            lift2--;
    
        }
        else
            if (lift2<QVariant(LiftIn2->data(LiftIn2->index(0))).toInt())
            {
                lift2++;
    
            }
        if (lift2==QVariant(LiftIn2->data(LiftIn2->index(0))).toInt())
        {
            int row = modelOut->rowCount();
            modelOut->insertRows(row,1);
            QModelIndex index = modelOut->index(row);
            modelOut->setData(index,LiftIn2->data(LiftIn2->index(0)));
            LiftIn2->removeRows(0,1);
             //proxyModel2->removeRows(0,1);
        }
    }
    if(lift2<10)
       LiftOut2->setData(index1,"00"+QVariant(lift2).toString());
    else
        if (lift2<100)
            LiftOut2->setData(index1,"0"+QVariant(lift2).toString());
        else
            LiftOut2->setData(index1,QVariant(lift2).toString());
}
void MainWindow::updateList()
{

   movelift1();
   ui->label->setText(QVariant(lift1).toString());

   movelift2();
   ui->label_2->setText(QVariant(lift2).toString());
   if(!timerstatus)
   {
        if (k||!k)
       {
           int row = modelIn->rowCount();
           modelIn->insertRows(row,1);
           QModelIndex index = modelIn->index(row);
           randin = (rand()&n);
           randin = n-randin;
           if (!randin){randin++;}
           if(randin<10)
               modelIn->setData(index,"00"+QVariant(randin).toString());
           else
               if (randin<100)
                   modelIn->setData(index,"0"+QVariant(randin).toString());
               else
                   modelIn->setData(index,QVariant(randin).toString());
           k=0;
           //вызов лифта и сравнение кто ближе
           if (!compare())
           {
               int row1 = LiftIn1->rowCount();
               LiftIn1->insertRows(row1,1);
               QModelIndex index1 = LiftIn1->index(row1);            
               if (randin<10)
                   LiftIn1->setData(index1,"00"+QVariant(randin).toString());
               else
               {
                   if (randin<100)
                    LiftIn1->setData(index1,"0"+QVariant(randin).toString());
                   else
                     LiftIn1->setData(index1,QVariant(randin).toString());
               }
               if (!l1)
               {
                   proxyModel1->sort(0, Qt::DescendingOrder);
                   LiftIn1->sort(0, Qt::DescendingOrder);
               }
               else
               {
                   proxyModel1->sort(0, Qt::AscendingOrder);
                   LiftIn1->sort(0, Qt::AscendingOrder);
               }

           }
           else
           {
               int row2 = LiftIn2->rowCount();
               LiftIn2->insertRows(row2,1);
               QModelIndex index2 = LiftIn2->index(row2);
               if (randin<10)
                   LiftIn2->setData(index2,"00"+QVariant(randin).toString());
               else
               {
                   if (randin<100)
                    LiftIn2->setData(index2,"0"+QVariant(randin).toString());
                   else
                    LiftIn2->setData(index2,QVariant(randin).toString());
               }
               if (!l2)
               {
                   proxyModel2->sort(0, Qt::DescendingOrder);
                   LiftIn2->sort(0, Qt::DescendingOrder);
               }
               else 
               {
                   proxyModel2->sort(0, Qt::AscendingOrder);
                   LiftIn2->sort(0, Qt::AscendingOrder);
               }
           }

       }
        else k=1;
   }
   else
   {
       ui->label->setText("hello");
       timerstatus = true;
      // QTimer::singleShot(16000, this, SLOT(changeList()));
   }
}

void MainWindow::on_pushButton_clicked()
{
    n=QVariant(ui->lineEdit->text()).toInt();
    if (n>0)
    {
        lift2 = n;
        timer->start();
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    timer->stop();
}

void MainWindow::on_pushButton_3_clicked()
{
    timer->stop();
    modelIn->removeRows(0,modelIn->rowCount());
    LiftIn1->removeRows(0,LiftIn1->rowCount());
    LiftIn2->removeRows(0,LiftIn2->rowCount());
    modelOut->removeRows(0,modelOut->rowCount());
}
