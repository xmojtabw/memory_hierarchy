#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "memory.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    response_detail runSimulation(const query_detail& qd);
    // response_detail makeSimulation(const query_detail& qd);
    void makeSimulation(const query_detail& qd);
    query_detail createQuery();
    ~MainWindow();

private slots:
    void on_run_btn_clicked();

    void on_generattor_btn_clicked();

private:
    Ui::MainWindow *ui;
    Memory * L1;
    Memory * L2;
    Memory * L3;
    Memory * t_table;
    Memory * TLB;
    QVector<QBitArray> virtual_addresses;
    QVector<QBitArray> physical_addresses;
};
#endif // MAINWINDOW_H
