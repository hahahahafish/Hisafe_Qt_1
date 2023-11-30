#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QRadioButton>
#include <QButtonGroup>
#include <QMessageBox>
#include <QFont>
#include <QHBoxLayout>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // dio mode
    typedef enum {
        MO_Output,
        MO_Input,
    }modeType;

    // dio signal
    typedef enum {
        MO_Low,
        MO_High,
    }valueType;

    // wdt mode
    typedef enum {
        MO_Sec,
        MO_Min,
    }wdtType;

    // fan mode
    typedef enum {
        MO_Auto,
        MO_Man,
    }fanType;

    // smbus mode
    typedef enum {
        MO_RB,
        MO_RW,
        MO_WB,
        MO_WW,
    }busType;

private slots:
    void on_sysBtn_clicked();

    void on_hwmBtn_clicked();

    void on_dioBtn_clicked();

    void on_wdtBtn_clicked();

    void on_fanBtn_clicked();

    void on_busBtn_clicked();

    void on_lightBtn_clicked();

    void on_wdt_setBtn_clicked();

    void update();

    void on_dio_setBtn_clicked();

    void on_wdt_clearBtn_clicked();


private:
    Ui::MainWindow *ui;

    QTimer *timer = new QTimer(this);
    int timeRest = 0;
    int inputNum = 0;

    QWidget *modeWidget[8];
    QHBoxLayout *modeLayout[8];
    QRadioButton *outBtn;
    QRadioButton *inBtn;
    QButtonGroup *modeGroup;
    QWidget *c_modeWidget[8];
    QHBoxLayout *c_modeLayout[8];
    QLabel *outImg;
    QLabel *inImg;

    QWidget *valueWidget[8];
    QHBoxLayout *valueLayout[8];
    QRadioButton *lowBtn;
    QRadioButton *highBtn;
    QButtonGroup *valueGroup;
    QWidget *c_valueWidget[8];
    QHBoxLayout *c_valueLayout[8];
    QLabel *lowImg;
    QLabel *highImg;
};
#endif // MAINWINDOW_H
