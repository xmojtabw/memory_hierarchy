#ifndef SHOW_GRAPH_H
#define SHOW_GRAPH_H

#include <QDialog>
#include "memory.h"
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

namespace Ui {
class show_graph;
}

class show_graph : public QDialog
{
    Q_OBJECT

public:
    explicit show_graph(query_detail temp_qd, response_detail temp_rd, QWidget *parent = nullptr);
    ~show_graph();

private:
    Ui::show_graph *ui;
    query_detail qd;
    response_detail rd;
};

#endif // SHOW_GRAPH_H
