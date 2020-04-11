#include "realtimedisplay.h"
#include "ui_realtimedisplay.h"

RealTimeDisplay::RealTimeDisplay(QWidget *parent) : QWidget(parent),
                                                    ui(new Ui::RealTimeDisplay)
{
    ui->setupUi(this);

    initWidget();
    initTable();
    initChart();


}

RealTimeDisplay::~RealTimeDisplay()
{
    ui->tableWidget->clearContents();

    for (DataMap::iterator it = m_data.begin(); it != m_data.end(); ++it)
    {
        delete[] it.value();
        it.value() = nullptr;
    }

    delete m_chart;
    delete m_axisX;
    delete m_axisY;
    delete m_level_line;
    delete m_depth_line;

    delete ui;
}

void RealTimeDisplay::initWidget()
{
    this->setFixedSize(500, 590);
    m_data_max_id = 0;
    m_data_list_max_count = 10;
    m_column = 0;
    m_row = 0;
    m_current_id = 1;
}

int RealTimeDisplay::getMapKey(const Data &data)
{
    int i = 1;
    for (; i <= m_data_max_id; i++)
    {
        if (strcmp(m_data[i]->first().name, data.name) == 0)
        {
            break;
        }
    }
    return i;
}

int RealTimeDisplay::getMapKey(const char *name)
{
    int i = 1;
    for (; i <= m_data_max_id; i++)
    {
        if (strcmp(m_data[i]->first().name, name) == 0)
        {
            break;
        }
    }
    return i;
}

void RealTimeDisplay::initTable()
{
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for (int column = 0; column < 10; column++, m_column++)
    {
        ui->tableWidget->insertColumn(column);
    }
    QList<QString> horizontalHeaderList = {" 监测点 ", " 公司 ", " 经度 ", " 纬度 ", " 水位 ", " 埋深 ", "GPRS\n 通信状态 ", " A/D通信 \n状态", "FLUG\n 状态 ", " 实时监测时间 "};
    ui->tableWidget->setHorizontalHeaderLabels(horizontalHeaderList);
    resizeTable();
}

void RealTimeDisplay::resizeTable()
{
    for (int column = 0; column < m_column; column++)
    {
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(column, QHeaderView::ResizeToContents);
    }
}

void RealTimeDisplay::updataTable(int id)
{
    if (ui->tableWidget->rowCount() < m_data_max_id)
    {
        insertTableRow(id);
    }
    updateTableRow(id);
}

void RealTimeDisplay::insertTableRow(int id)
{
    ui->tableWidget->insertRow(m_row++);
    setRowData(id);
}

void RealTimeDisplay::updateTableRow(int id)
{
    setRowData(id);
}

void RealTimeDisplay::setRowData(int id)
{
    setRowName(id);
    setRowCorp(id);
    setRowLongi(id);
    setRowLati(id);
    setRowLevel(id);
    setRowDepth(id);
    setRowGPRS(id);
    setRowAD(id);
    setRowFLUG(id);
    setRowTime(id);
}

void RealTimeDisplay::setRowName(int id)
{
    ui->tableWidget->setItem(getRow(id), 0, new QTableWidgetItem(m_data[id]->last().name));
}

void RealTimeDisplay::setRowCorp(int id)
{
    ui->tableWidget->setItem(getRow(id), 1, new QTableWidgetItem(m_data[id]->last().corp));
}

void RealTimeDisplay::setRowLongi(int id)
{
    ui->tableWidget->setItem(getRow(id), 2, new QTableWidgetItem(QString::number(m_data[id]->last().longitude)));
}

void RealTimeDisplay::setRowLati(int id)
{
    ui->tableWidget->setItem(getRow(id), 3, new QTableWidgetItem(QString::number(m_data[id]->last().latitude)));
}

void RealTimeDisplay::setRowLevel(int id)
{
    ui->tableWidget->setItem(getRow(id), 4, new QTableWidgetItem(QString::number(m_data[id]->last().level)));
}

void RealTimeDisplay::setRowDepth(int id)
{
    ui->tableWidget->setItem(getRow(id), 5, new QTableWidgetItem(QString::number(m_data[id]->last().depth)));
}

void RealTimeDisplay::setRowGPRS(int id)
{
    QString GPRSStatus = nullptr;
    int status = m_data[id]->last().GPRS;
    if (status == 0)
    {
        GPRSStatus = "正常";
    }
    else
    {
        GPRSStatus = "异常";
        ui->tableWidget->item(getRow(id), 6)->setForeground(Qt::red);
    }
    ui->tableWidget->setItem(getRow(id), 6, new QTableWidgetItem(GPRSStatus));
}

void RealTimeDisplay::setRowAD(int id)
{
    QString ADStatus = nullptr;
    int status = m_data[id]->last().AD;
    if (status == 0)
    {
        ADStatus = "正常";
    }
    else
    {
        ADStatus = "异常";
        ui->tableWidget->item(getRow(id), 7)->setForeground(Qt::red);
    }
    ui->tableWidget->setItem(getRow(id), 7, new QTableWidgetItem(ADStatus));
}

void RealTimeDisplay::setRowFLUG(int id)
{
    QString FLUGStatus = nullptr;
    int status = m_data[id]->last().FLUG;
    if (status == 0)
    {
        FLUGStatus = "正常";
    }
    else
    {
        FLUGStatus = "异常";
        ui->tableWidget->item(getRow(id), 8)->setForeground(Qt::red);
    }
    ui->tableWidget->setItem(getRow(id), 8, new QTableWidgetItem(FLUGStatus));
}

void RealTimeDisplay::setRowTime(int id)
{
    QString ctime = QDateTime::fromTime_t((uint)m_data[id]->last().time).toString("yyyy-MM-dd hh:mm:ss");
    ui->tableWidget->setItem(getRow(id), 9, new QTableWidgetItem(ctime));
}

void RealTimeDisplay::initChart()
{
    m_chart = new QChart;

    m_axisX = new QDateTimeAxis;
    m_axisX->setFormat("hh:mm:ss"); //璁剧疆X杞存暟鎹殑鏄剧ず鏍煎紡
    m_axisX->setTitleText("单位:时间");
    m_chart->addAxis(m_axisX, Qt::AlignBottom);

    m_axisY = new QValueAxis;
    m_axisY->setRange(-40, 40);
    m_axisY->setTitleText("单位:米");
    m_chart->addAxis(m_axisY, Qt::AlignLeft);

    m_level_line = new QLineSeries;
    m_level_line->setName("水位");
    m_chart->addSeries(m_level_line);
    m_level_line->attachAxis(m_axisX);
    m_level_line->attachAxis(m_axisY);

    m_depth_line = new QLineSeries;
    m_depth_line->setName("埋深");
    m_chart->addSeries(m_depth_line);
    m_depth_line->attachAxis(m_axisX);
    m_depth_line->attachAxis(m_axisY);

    ui->graphicsView->setChart(m_chart);
}

void RealTimeDisplay::updataChart()
{
    m_level_line->removePoints(0, m_level_line->count());
    m_depth_line->removePoints(0, m_depth_line->count());
    setLevelLineData();
    setDepthLineData();
    m_axisX->setRange(QDateTime::fromTime_t((uint)m_data[m_current_id]->first().time), QDateTime::fromTime_t((uint)m_data[m_current_id]->last().time));
}

void RealTimeDisplay::setLevelLineData()
{
    for (DataList::iterator it = m_data[m_current_id]->begin(); it != m_data[m_current_id]->end(); ++it)
    {
        m_level_line->append(QDateTime::fromTime_t((uint)it->time).toMSecsSinceEpoch(), it->level);
    }
}

void RealTimeDisplay::setDepthLineData()
{
    for (DataList::iterator it = m_data[m_current_id]->begin(); it != m_data[m_current_id]->end(); ++it)
    {
        m_depth_line->append(QDateTime::fromTime_t((uint)it->time).toMSecsSinceEpoch(), it->depth);
    }
}

int RealTimeDisplay::getRow(int id)
{
    return id - 1;
}

void RealTimeDisplay::updateData(Data data)//*****
{
    int key = getMapKey(data);
    if (key > m_data_max_id)
    {
        m_data_max_id++;
        m_data[key] = new DataList;
    };
    if (m_data[key]->size() == m_data_list_max_count)
    {
        DataList::iterator it = m_data[key]->begin();
        it = m_data[key]->erase(it);
    }
    m_data[key]->push_back(data);
    updataTable(key);
    if (key == m_current_id)
    {
        updataChart();
    }
}

void RealTimeDisplay::on_tableWidget_itemSelectionChanged()
{
    int row = ui->tableWidget->currentRow();
    QString name = ui->tableWidget->item(row, 0)->text();
    m_current_id = row + 1;
    updataChart();
}

void RealTimeDisplay::on_checkBox_stateChanged(int arg1)
{
    if (ui->checkBox->isChecked())
    {
        m_level_line->show();
    }
    else
    {
        m_level_line->hide();
    }
    updataChart();
}

void RealTimeDisplay::on_checkBox_2_stateChanged(int arg1)
{
    if (ui->checkBox_2->isChecked())
    {
        m_depth_line->show();
    }
    else
    {
        m_depth_line->hide();
    }
    updataChart();
}
