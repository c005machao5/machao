
#ifndef REALTIMEDISPLAY_H
#define REALTIMEDISPLAY_H

#include <QWidget>
#include <QMap>
#include <QList>
#include <QtCharts>
#include "signal_s.h"
namespace Ui
{
class RealTimeDisplay;
}

//struct Data
//{
//    int cmdnum;
//    int totalsize;
//    char name[128];   //鐩戞祴鐐瑰悕绉?
//    char corp[128];   //鍗曚綅
//    double longitude; //缁忓害
//    double latitude;  //绾害
//    double level;     //姘翠綅
//    double depth;     //鍦颁笅姘存繁
//    int GPRS;         //GPRS閫氫俊鐘舵€?
//    int AD;           //A/D杞崲鍣ㄧ姸鎬?
//    int FLUG;         //姘翠綅璁￠€氫俊鐘舵€?
//    time_t time;      //閲囬泦鏁版嵁鏃堕棿
//};

typedef QMap<int, QList<Data> *> DataMap;
typedef QList<Data> DataList;

class RealTimeDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit RealTimeDisplay(QWidget *parent = nullptr);
    ~RealTimeDisplay();

private:
    Ui::RealTimeDisplay *ui;

private:
    DataMap m_data;            //鏁版嵁
    int m_data_max_id;         //鏁版嵁id
    int m_data_list_max_count; //鏁版嵁鏈€澶т釜鏁?
    int m_current_id;
    int m_column; //琛ㄦ牸鎬诲垪
    int m_row;    //琛ㄦ牸鎬昏

    QChart *m_chart;
    QDateTimeAxis *m_axisX;    //妯酱
    QValueAxis *m_axisY;       //绾佃酱
    QLineSeries *m_level_line; //姘翠綅绾?
    QLineSeries *m_depth_line; //鍩嬫繁绾?

private:
    void initWidget(); //鍒濆鍖栫獥鍙?
    int getMapKey(const Data &data);
    int getMapKey(const char *name);
    int insertData(const Data &data);

    //-----琛ㄧ浉鍏?-----
    void initTable();         //鍒濆鍖栬〃鏍?
    void resizeTable();       //璋冩暣琛ㄦ牸瀹藉害
    void updataTable(int id); //鏇存柊琛ㄦ牸
    int getRow(int id);
    void insertTableRow(int id); //鎻掑叆鏂扮殑琛屾暟鎹?
    void updateTableRow(int id); //鏇存柊琛屾暟鎹?
    void setRowData(int id);     //璁剧疆琛屾暟鎹?

    void setRowName(int id);
    void setRowCorp(int id);
    void setRowLongi(int id);
    void setRowLati(int id);
    void setRowLevel(int id);
    void setRowDepth(int id);
    void setRowGPRS(int id);
    void setRowAD(int id);
    void setRowFLUG(int id);
    void setRowTime(int id);
    //---------------

    //-----鍥剧浉鍏?-----
    void initChart();        //鍒濆鍖栨洸绾垮浘
    void updataChart();      //鏇存柊鏇茬嚎鍥?
    void setLevelLineData(); //璁剧疆姘翠綅鏇茬嚎鏁版嵁
    void setDepthLineData(); //璁剧疆鍩嬫繁鏇茬嚎鏁版嵁
    //---------------

public slots:
    void updateData(Data data); //鏇存柊鏁版嵁

private slots:
    void on_tableWidget_itemSelectionChanged();
    void on_checkBox_stateChanged(int arg1);
    void on_checkBox_2_stateChanged(int arg1);
};

#endif // REALTIMEDISPLAY_H
