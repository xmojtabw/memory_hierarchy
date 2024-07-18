#include "show_graph.h"
#include "ui_show_graph.h"

show_graph::show_graph(query_detail temp_qd, response_detail temp_rd, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::show_graph)
{
    ui->setupUi(this);
    qd = temp_qd;
    rd = temp_rd;
    QPieSeries* series = new QPieSeries();
    series->append("L1 hit-time", rd.l1_hit_time);
    series->append("L2 hit-time", rd.l2_hit_time);
    series->append("L3 hit-time", rd.l3_hit_time);

    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("cache chart");

    QChartView* chartView = new QChartView(chart);
    chartView->setParent(ui->horizontalFrame);
    chartView->setFixedWidth(480);

    QPieSeries* series2 = new QPieSeries();
    series2->append("L1 total-time", qd.l1_time*rd.l1_time);
    series2->append("L2 total-time", qd.l2_time*rd.l2_time);
    series2->append("L3 total-time", qd.l3_time*rd.l3_time);
    // series2->
    QChart* chart2 = new QChart();
    chart2->addSeries(series2);
    chart2->setTitle("cache time chart");

    QChartView* chartView2 = new QChartView(chart2);
    chartView2->setParent(ui->horizontalFrame_2);
    chartView2->setFixedWidth(480);
}

show_graph::~show_graph()
{
    delete ui;
}
