#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    srand(static_cast<unsigned>(time(nullptr)));
    ui->setupUi(this);
    ui->t_locality->setMaximum(3);
    ui->p_locality->setMaximum(100);
    ui->p_locality->setMinimum(1);
    ui->t_locality->setTickInterval(1);
    ui->p_locality->setTickInterval(1);


    ui->L1_len->setValue(4);
    ui->L1_block->setValue(2);
    ui->L1_time->setValue(1);

    ui->L2_len->setValue(6);
    ui->L2_block->setValue(3);
    ui->L2_time->setValue(4);

    ui->L3_len->setValue(8);
    ui->L3_block->setValue(4);
    ui->L3_time->setValue(8);

    ui->mem_len->setValue(14);
    ui->main_mem_time->setValue(50);

    ui->t_table_len->setValue(16);
    ui->t_table_time->setValue(80);

    ui->tlb_len->setValue(8);
    ui->tlb_time->setValue(10);

    ui->disk_time->setMaximum(9999);
    ui->disk_time->setValue(200);
    ui->address_count->setMaximum(99999);
    ui->address_count->setValue(2000);

}

response_detail MainWindow::runSimulation(const query_detail& qd)
{
    //int vir_addr_len =
    response_detail rd;
    rd.tlb_time = qd.address_count;
    for( QBitArray & adr : virtual_addresses)
    {
        if(TLB->getData(adr))
        {
            //hit
            rd.tlb_hit_time++;
        }
        else
        {
            //tlb miss
            //ask trans table
            rd.t_table_time++;
            if(t_table->getData(adr))
            {
                //valid in transilate table
                rd.t_table_hit_time ++;
            }
            else
            {
                //page fault
                rd.disk_time++;
            }
        }
    }
    rd.l1_time = qd.address_count;
    for( QBitArray & adr : physical_addresses)
    {

        if(L1->getData(adr))
        {
            //l1 hit
            rd.l1_hit_time++;
        }
        else
        {
            //l1 miss
            rd.l2_time++;
            if(L2->getData(adr))
            {
                //l2 hit
                rd.l2_hit_time++;
            }
            else
            {
                rd.l3_time++;
                if(L3->getData(adr))
                {
                    //l3 hit
                    rd.l3_hit_time++;
                }
                else
                {
                    //ask memory
                    rd.mem_time++;
                }
            }
        }
    }
    return rd;

}

void  MainWindow::makeSimulation(const query_detail &qd)
{
    int l1_tag = qd.mem_len - (qd.l1_len+ qd.l1_blocks)  ;
    L1 = new Memory(qd.l1_len,l1_tag,1,qd.l1_blocks,sram,map);

    int l2_tag = qd.mem_len - (qd.l2_len+qd.l2_blocks);
    L2 = new Memory(qd.l2_len,l2_tag,1,qd.l2_blocks,sram,map);

    int l3_tag = (qd.mem_len) - (qd.l3_len+qd.l3_blocks);
    L3 = new Memory(qd.l3_len,l3_tag,1,qd.l3_blocks,sram,map);

    TLB = new Memory(qd.tlb_len,qd.tlb_len,1,1,tlb,qd.cpt);
    t_table = new Memory(qd.virtual_len,qd.virtual_len,1,1,ttable,fully);
}

query_detail MainWindow::createQuery()
{
    query_detail qd ;
    qd.address_count = ui->address_count->value();
    qd.l1_blocks = ui->L1_block->value();
    qd.l1_len = ui->L1_len->value();
    qd.l1_time = ui->L1_time->value();
    qd.l2_blocks = ui->L2_block->value();
    qd.l2_len = ui->L2_len->value();
    qd.l2_time = ui->L2_time->value();
    qd.l3_blocks = ui->L3_block->value();
    qd.l3_len = ui->L3_len->value();
    qd.l3_time = ui->L3_time->value();

    qd.tlb_len=ui->tlb_len->value();
    qd.tlb_time = ui->tlb_time->value();

    qd.mem_len = ui->mem_len->value();
    qd.mem_time = ui->main_mem_time->value();

    qd.virtual_len = ui->t_table_len->value();
    qd.t_table_time = ui->t_table_time->value();

    qd.disk_time = ui->disk_time->value();

    qd.t_locality = ui->t_locality->value();
    qd.p_locality = ui->p_locality->value();

    QString cp = ui->cpt->currentText();
    if(cp=="LRU")qd.cpt=lru;
    if(cp=="MRU")qd.cpt=mru;
    if(cp=="LFU")qd.cpt=lfu;
    if(cp=="FIFO")qd.cpt=fifo;
    if(cp=="RR")qd.cpt=rr;
    return qd;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_run_btn_clicked()
{
    if(physical_addresses.size()==0 or virtual_addresses.size()==0)
    {
        on_generattor_btn_clicked();
    }
    const query_detail qd = createQuery();
    response_detail rd;
    makeSimulation(qd);
    rd = runSimulation(qd);

    qDebug() << "policy" << qd.cpt;
    qDebug() << "L1 count"<<rd.l1_time;
    qDebug() << "L2 count"<<rd.l2_time;
    qDebug() << "L3 count"<<rd.l3_time;
    qDebug() << "memory count "<<rd.mem_time;
    qDebug() << "TLB count"<<rd.tlb_time;
    qDebug() << "Translate table count" <<rd.t_table_time;
    qDebug() << "disk count" <<rd.disk_time;

    qDebug() << "L1 hit count"<<rd.l1_hit_time;
    qDebug() << "L2 hit count"<<rd.l2_hit_time;
    qDebug() << "L3 hit count"<<rd.l3_hit_time;
    qDebug() << "TLB hit count"<<rd.tlb_hit_time;
    qDebug() << "Translate table hit count" <<rd.t_table_hit_time;

    qDebug() << "L1 total time" <<qd.l1_time*rd.l1_time;
    qDebug() << "L2 total time" <<qd.l2_time*rd.l2_time;
    qDebug() << "L3 total time" <<qd.l3_time*rd.l3_time;
    qDebug() << "memory total time" <<qd.mem_time *rd.mem_time;
    qDebug() << "TLB total time"<<qd.mem_time* rd.tlb_time;
    qDebug() << "Translate table total time" << qd.t_table_time * rd.t_table_time;
    qDebug() << "disk total time" <<qd.disk_time *  rd.disk_time;
    show_graph *sGraph = new show_graph(qd,rd, this);
    sGraph->show();
    info_table *i_table = new info_table(qd,rd, this);
    i_table->show();
}


void MainWindow::on_generattor_btn_clicked()
{
    query_detail qd = createQuery();
    virtual_addresses = generateAddresses(qd.t_locality,qd.p_locality,qd.address_count,qd.virtual_len ) ;
    physical_addresses = generateAddresses(qd.t_locality,qd.p_locality,qd.address_count,qd.mem_len ) ;

    int l1_num = pow(2, ui->L1_len->value() + ui->L1_block->value());
    ui->L1_size->display(l1_num);

    int l2_num = pow(2, ui->L2_len->value() + ui->L2_block->value());
    ui->L2_size->display(l2_num);

    int l3_num = pow(2, ui->L3_len->value() + ui->L3_block->value());
    ui->L3_size->display(l3_num);

    int t1_size = pow(2, ui->t_table_len->value());
    ui->t_table_size->display(t1_size);

    int tlb_size = pow(2, ui->tlb_len->value());
    ui->tlb_size->display(tlb_size);

    int mem_size = pow(2, ui->mem_len->value());
    ui->mem_size->display(mem_size);
}


