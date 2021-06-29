#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QStringListModel>
#include <QAbstractItemView>
#include <QTimer>
#include <QString>
#include <QWidget>
#include <QtWidgets>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   explicit MainWindow(QWidget *parent = nullptr);
   ~MainWindow();

private:
   Ui::MainWindow *ui;
   QStringListModel *modelIn, *LiftIn1, *LiftIn2, *LiftOut1, *LiftOut2;
   QStringListModel *modelOut;
   QSortFilterProxyModel *proxyModel1, *proxyModel2;
   QTimer *timer;  //таймер
   bool timerstatus;
   qint32 k, lift1, lift2, randin, n;
   bool l1,l2;
private slots:
   void updateList();
   void changeList();
   void on_pushButton_clicked();
   void on_pushButton_2_clicked();
   void on_pushButton_3_clicked();
   bool compare();
   void movelift1();
   void movelift2();
};

#endif // MAINWINDOW_H

