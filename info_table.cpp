#include "info_table.h"
#include "ui_info_table.h"

info_table::info_table(query_detail temp_qd, response_detail temp_rd, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::info_table)
{
    ui->setupUi(this);
    qd = temp_qd;
    rd = temp_rd;
    QTableWidgetItem *item11 = new QTableWidgetItem();
    QTableWidgetItem *item12 = new QTableWidgetItem();
    QTableWidgetItem *item13 = new QTableWidgetItem();
    QTableWidgetItem *item14 = new QTableWidgetItem();
    QTableWidgetItem *item15 = new QTableWidgetItem();
    QTableWidgetItem *item21 = new QTableWidgetItem();
    QTableWidgetItem *item22 = new QTableWidgetItem();
    QTableWidgetItem *item23 = new QTableWidgetItem();
    QTableWidgetItem *item24 = new QTableWidgetItem();
    QTableWidgetItem *item25 = new QTableWidgetItem();
    QTableWidgetItem *item31 = new QTableWidgetItem();
    QTableWidgetItem *item32 = new QTableWidgetItem();
    QTableWidgetItem *item33 = new QTableWidgetItem();
    QTableWidgetItem *item34 = new QTableWidgetItem();
    QTableWidgetItem *item35 = new QTableWidgetItem();
    QTableWidgetItem *item41 = new QTableWidgetItem();
    QTableWidgetItem *item42 = new QTableWidgetItem();
    QTableWidgetItem *item43 = new QTableWidgetItem();
    QTableWidgetItem *item44 = new QTableWidgetItem();
    QTableWidgetItem *item45 = new QTableWidgetItem();
    QTableWidgetItem *item51 = new QTableWidgetItem();
    QTableWidgetItem *item52 = new QTableWidgetItem();
    QTableWidgetItem *item53 = new QTableWidgetItem();
    QTableWidgetItem *item54 = new QTableWidgetItem();
    QTableWidgetItem *item55 = new QTableWidgetItem();
    QTableWidgetItem *item61 = new QTableWidgetItem();
    QTableWidgetItem *item62 = new QTableWidgetItem();
    QTableWidgetItem *item63 = new QTableWidgetItem();
    QTableWidgetItem *item64 = new QTableWidgetItem();
    QTableWidgetItem *item65 = new QTableWidgetItem();
    QTableWidgetItem *item71 = new QTableWidgetItem();
    QTableWidgetItem *item72 = new QTableWidgetItem();
    QTableWidgetItem *item73 = new QTableWidgetItem();
    QTableWidgetItem *item74 = new QTableWidgetItem();
    QTableWidgetItem *item75 = new QTableWidgetItem();


    item11->setText(QString::number(rd.l1_hit_time));
    ui->tableWidget->setItem(0,0, item11);
    item12->setText(QString::number(rd.l1_time - rd.l1_hit_time));
    ui->tableWidget->setItem(0,1, item12);
    item13->setText(QString::number(rd.l1_time));
    ui->tableWidget->setItem(0,2, item13);
    item14->setText(QString::number(((double)rd.l1_hit_time/(double)(rd.l1_time - rd.l1_hit_time))*100));
    ui->tableWidget->setItem(0,3, item14);
    item15->setText(QString::number(qd.l1_time*rd.l1_time));
    ui->tableWidget->setItem(0,4, item15);

    item21->setText(QString::number(rd.l2_hit_time));
    ui->tableWidget->setItem(1,0, item21);
    item22->setText(QString::number(rd.l2_time - rd.l2_hit_time));
    ui->tableWidget->setItem(1,1, item22);
    item23->setText(QString::number(rd.l2_time));
    ui->tableWidget->setItem(1,2, item23);
    item24->setText(QString::number(((double)rd.l2_hit_time/(double)(rd.l2_time - rd.l2_hit_time))*100));
    ui->tableWidget->setItem(1,3, item24);
    item25->setText(QString::number(qd.l2_time*rd.l2_time));
    ui->tableWidget->setItem(1,4, item25);

    item31->setText(QString::number(rd.l3_hit_time));
    ui->tableWidget->setItem(2,0, item31);
    item32->setText(QString::number(rd.l3_time - rd.l3_hit_time));
    ui->tableWidget->setItem(2,1, item32);
    item33->setText(QString::number(rd.l3_time));
    ui->tableWidget->setItem(2,2, item33);
    item34->setText(QString::number(((double)rd.l3_hit_time/(double)(rd.l3_time - rd.l3_hit_time))*100));
    ui->tableWidget->setItem(2,3, item34);
    item35->setText(QString::number(qd.l3_time*rd.l3_time));
    ui->tableWidget->setItem(2,4, item35);

    item41->setText(QString::number(rd.tlb_hit_time));
    ui->tableWidget->setItem(3,0, item41);
    item42->setText(QString::number(rd.tlb_time - rd.tlb_hit_time));
    ui->tableWidget->setItem(3,1, item42);
    item43->setText(QString::number(rd.tlb_time));
    ui->tableWidget->setItem(3,2, item43);
    item44->setText(QString::number(((double)rd.tlb_hit_time/(double)(rd.tlb_time - rd.tlb_hit_time))*100));
    ui->tableWidget->setItem(3,3, item44);
    item45->setText(QString::number(qd.tlb_time*rd.tlb_time));
    ui->tableWidget->setItem(3,4, item45);

    item51->setText(QString::number(rd.t_table_hit_time));
    ui->tableWidget->setItem(4,0, item51);
    item52->setText(QString::number(rd.t_table_time - rd.t_table_hit_time));
    ui->tableWidget->setItem(4,1, item52);
    item53->setText(QString::number(rd.t_table_time));
    ui->tableWidget->setItem(4,2, item53);
    item54->setText(QString::number(((double)rd.t_table_hit_time/(double)(rd.t_table_time - rd.t_table_hit_time))*100));
    ui->tableWidget->setItem(4,3, item54);
    item55->setText(QString::number(qd.t_table_time*rd.t_table_time));
    ui->tableWidget->setItem(4,4, item55);

    item61->setText("---");
    ui->tableWidget->setItem(5,0, item61);
    item62->setText("---");
    ui->tableWidget->setItem(5,1, item62);
    item63->setText(QString::number(rd.mem_time));
    ui->tableWidget->setItem(5,2, item63);
    item64->setText("---");
    ui->tableWidget->setItem(5,3, item64);
    item65->setText(QString::number(qd.mem_time*rd.mem_time));
    ui->tableWidget->setItem(5,4, item65);

    item71->setText("---");
    ui->tableWidget->setItem(6,0, item71);
    item72->setText("---");
    ui->tableWidget->setItem(6,1, item72);
    item73->setText(QString::number(rd.disk_time));
    ui->tableWidget->setItem(6,2, item73);
    item74->setText("---");
    ui->tableWidget->setItem(6,3, item74);
    item75->setText(QString::number(qd.disk_time*rd.disk_time));
    ui->tableWidget->setItem(6,4, item75);
}

info_table::~info_table()
{
    delete ui;
}
