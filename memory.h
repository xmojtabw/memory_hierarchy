#ifndef MEMORY_H
#define MEMORY_H

#include <QObject>
#include <QVector>
#include <QBitArray>
#include <math.h>
#include <QDebug>
#include <algorithm>
#include <random>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdlib>

enum mem_types{sram, tlb,ttable};
enum cache_pt{map,fully,lru,mru,lfu,fifo,rr};
struct response_detail
{
    unsigned int l1_time=0;
    unsigned int l2_time=0;
    unsigned int l3_time=0;
    unsigned int tlb_time=0;
    unsigned int t_table_time=0;


    unsigned int l1_hit_time=0;
    unsigned int l2_hit_time=0;
    unsigned int l3_hit_time=0;
    unsigned int tlb_hit_time=0;
    unsigned int t_table_hit_time=0;

    unsigned int disk_time=0;
    unsigned int mem_time=0;
};

struct query_detail
{
    unsigned int l1_time=0;
    unsigned int l2_time=0;
    unsigned int l3_time=0;
    unsigned int tlb_time=0;
    unsigned int t_table_time=0;
    unsigned int mem_time=0;
    unsigned int disk_time=0;


    unsigned int address_count;
    cache_pt cpt;


    int l1_len=0;
    int l2_len=0;
    int l3_len=0;
    int tlb_len=0;
    int mem_len=0;
    int virtual_len=0;
    int l1_blocks=0;
    int l2_blocks=0;
    int l3_blocks=0;
    int p_locality =0;
    int t_locality =0;
};

QVector<QBitArray>  generateAddresses(int t_locality,int p_locality,int records_len,int addresslen );
QVector<QBitArray>  generateAddresses(int locality, int Address_len, int records_len);
QString checkQ(query_detail qd);

class Memory : public QObject
{
    Q_OBJECT
public:
    Memory(int len,int tag_bits,int ctrl_bits ,int block_size,mem_types mt,cache_pt cpt);
    bool getData(const QBitArray& address);
    QBitArray extractBits(const int& start, const int& end,const QBitArray& address);
private:
    int len;
    int x_len ; // pow(2,len)
    int block_size;
    int tag_len;
    mem_types mt;
    cache_pt  cpt;
    QVector<QBitArray> mem;
    QVector<QBitArray> ctrl_bits;


    // replacement policy
    unsigned int * TUsed=nullptr; // time base used for mru and lru
    unsigned int * FUsed=nullptr; // frequently base used for lfu
    unsigned int * add_time=nullptr; // for fifo
    unsigned int query_count = 0 ;//for mru and lfu
    unsigned int add_count =0 ; //for fifo


signals:
};

#endif // MEMORY_H
