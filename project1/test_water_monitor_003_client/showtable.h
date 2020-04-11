#ifndef SHOWTABLE_H
#define SHOWTABLE_H

#include <QMainWindow>

namespace Ui {
class ShowTable;
}

class ShowTable : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShowTable(QWidget *parent = 0);
    ~ShowTable();

private:
    Ui::ShowTable *ui;
public slots:
    void m_show_table_slot(std::map<int,double> data_map,QStringList list_selection);
};

#endif // SHOWTABLE_H
