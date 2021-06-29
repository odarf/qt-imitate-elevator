#ifndef DIALOG1_H
#define DIALOG1_H

#include <QDialog>
# include <QHBoxLayout>
#include <QtCharts/QChart>
# include <QtCharts/QLogValueAxis>
# include <QtCharts/QLineSeries>
# include <QtCharts/QValueAxis>
# include <QtCharts/QChartView>

namespace Ui {
class Dialog1;
}

class Dialog1 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog1(QWidget *parent = nullptr);
    ~Dialog1();

private:
    Ui::Dialog1 *ui;
};

#endif // DIALOG1_H
