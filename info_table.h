#ifndef INFO_TABLE_H
#define INFO_TABLE_H

#include <QDialog>
#include "memory.h"

namespace Ui {
class info_table;
}

class info_table : public QDialog
{
    Q_OBJECT

public:
    explicit info_table(query_detail temp_qd, response_detail temp_rd, QWidget *parent = nullptr);
    ~info_table();

private:
    Ui::info_table *ui;
    query_detail qd;
    response_detail rd;
};

#endif // INFO_TABLE_H
