#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QRadioButton>
#include <QButtonGroup>
#include <QTimer>
#include <QMessageBox>
#include <QFont>
#include <QDebug>
#include <QMovie>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("HiSafe");
    this->setFixedSize(1500, 900);

    /*
    QLabel *wow = new QLabel(this);
    QMovie *movie = new QMovie(":/myImage/image/Wow-gif.gif");
    wow->setMovie(movie);
    movie->start();
    */

    /*
    QToolButton *sysbtn = new QToolButton(this);
    sysbtn->setFixedSize(180,120);
    sysbtn->setAutoRaise(true);
    sysbtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    sysbtn->setText("System Information");
    sysbtn->setStyleSheet("QToolButton{font-size:18px;}");
    sysbtn->setIcon(QIcon(":/myImage/image/system.png"));
    sysbtn->setIconSize(QSize(80, 80));
    */

    // Switch Page
    // sys
    connect(ui->sysBtn, SIGNAL(clicked()), this, SLOT(on_sysBtn_clicked()));
    connect(ui->sysBtn_1, SIGNAL(clicked()), this, SLOT(on_sysBtn_clicked()));

    // hwm
    connect(ui->hwmBtn, SIGNAL(clicked()), this, SLOT(on_hwmBtn_clicked()));
    connect(ui->hwmBtn_1, SIGNAL(clicked()), this, SLOT(on_hwmBtn_clicked()));

    // dio
    connect(ui->dioBtn, SIGNAL(clicked()), this, SLOT(on_dioBtn_clicked()));
    connect(ui->dioBtn_1, SIGNAL(clicked()), this, SLOT(on_dioBtn_clicked()));

    // wdt
    connect(ui->wdtBtn, SIGNAL(clicked()), this, SLOT(on_wdtBtn_clicked()));
    connect(ui->wdtBtn_1, SIGNAL(clicked()), this, SLOT(on_wdtBtn_clicked()));

    // fan
    connect(ui->fanBtn, SIGNAL(clicked()), this, SLOT(on_fanBtn_clicked()));
    connect(ui->fanBtn_1, SIGNAL(clicked()), this, SLOT(on_fanBtn_clicked()));

    // bus
    connect(ui->busBtn, SIGNAL(clicked()), this, SLOT(on_busBtn_clicked()));
    connect(ui->busBtn_1, SIGNAL(clicked()), this, SLOT(on_busBtn_clicked()));

    // light
    connect(ui->lightBtn, SIGNAL(clicked()), this, SLOT(on_lightBtn_clicked()));
    connect(ui->lightBtn_1, SIGNAL(clicked()), this, SLOT(on_lightBtn_clicked()));

    // wdt comboBox
    for(int i=0; i<=255; i++){
        ui->comboBox_5->addItem(QString::number(i));
        ui->comboBox_7->addItem(QString::number(i));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_sysBtn_clicked()
{
    ui->stackedWidget_title->setCurrentIndex(1);
    ui->stackedWidget_context->setCurrentIndex(1);
}


void MainWindow::on_hwmBtn_clicked()
{
    ui->stackedWidget_title->setCurrentIndex(1);
    ui->stackedWidget_context->setCurrentIndex(2);
}


void MainWindow::on_dioBtn_clicked()
{
    ui->stackedWidget_title->setCurrentIndex(1);
    ui->stackedWidget_context->setCurrentIndex(3);

    // table space
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(65);
    ui->tableWidget->horizontalHeader()->resizeSection(0,250);
    ui->tableWidget->horizontalHeader()->resizeSection(1,250);
    ui->tableWidget->horizontalHeader()->resizeSection(2,350);
    ui->tableWidget->horizontalHeader()->resizeSection(3,350);

    // Setting Mode
    for (int i=0; i<4; i++) {

        // mode radiobutton
        outBtn = new QRadioButton(tr("Output"));
        outBtn->setObjectName("outBtn");
        outBtn->setStyleSheet("QRadioButton::unchecked{color:rgb(0, 0, 0);}\
                               QRadioButton::checked{color:rgb(100, 149, 237);}\
                               QRadioButton::indicator{width:15px;height:15px;border-radius:5px}\
                               QRadioButton::indicator:unchecked{background-color:rgb(0, 0, 0);}\
                               QRadioButton::indicator:checked{background-color:rgb(100, 149, 237);}");

        inBtn = new QRadioButton(tr("Input"));
        inBtn->setObjectName("inBtn");
        inBtn->setStyleSheet("QRadioButton::unchecked{color:rgb(0, 0, 0)}\
                              QRadioButton::checked{color:rgb(144, 238, 144);}\
                              QRadioButton::indicator{width:15px;height:15px;border-radius:5px}\
                              QRadioButton::indicator:unchecked{background-color:rgb(0, 0, 0);}\
                              QRadioButton::indicator:checked{background-color:rgb(144, 238, 144);}");

        modeGroup = new QButtonGroup(this);
        modeGroup->addButton(outBtn, MO_Output);
        modeGroup->addButton(inBtn, MO_Input);
        inBtn->setChecked(true);

        // layout
        modeWidget[i] = new QWidget;
        modeLayout[i] = new QHBoxLayout;
        modeLayout[i]->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum));
        modeLayout[i]->addWidget(outBtn);
        modeLayout[i]->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum));
        modeLayout[i]->addWidget(inBtn);
        modeLayout[i]->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum));
        modeWidget[i]->setLayout(modeLayout[i]);

        ui->tableWidget->setCellWidget(i, 2, modeWidget[i]);

        inImg = new QLabel();
        inImg->setStyleSheet("border-image: url(:/myImage/image/in.png);");
        inImg->setFixedSize(90, 40);
        c_modeWidget[i] = new QWidget;
        c_modeLayout[i] = new QHBoxLayout();
        c_modeLayout[i]->addWidget(inImg);
        c_modeLayout[i]->setAlignment(inImg, Qt::AlignCenter);
        c_modeWidget[i]->setLayout(c_modeLayout[i]);

        ui->tableWidget->setCellWidget(i, 0, c_modeWidget[i]);
    }

    for (int i=4; i<8; i++) {

        // mode radiobutton
        outBtn = new QRadioButton(tr("Output"));
        outBtn->setObjectName("outBtn");
        outBtn->setStyleSheet("QRadioButton::unchecked{color:rgb(0, 0, 0);}\
                               QRadioButton::checked{color:rgb(100, 149, 237);}\
                               QRadioButton::indicator{width:15px;height:15px;border-radius:5px}\
                               QRadioButton::indicator:unchecked{background-color:rgb(0, 0, 0);}\
                               QRadioButton::indicator:checked{background-color:rgb(100, 149, 237);}");

        inBtn = new QRadioButton(tr("Input"));
        inBtn->setObjectName("inBtn");
        inBtn->setStyleSheet("QRadioButton::unchecked{color:rgb(0, 0, 0)}\
                              QRadioButton::checked{color:rgb(144, 238, 144);}\
                              QRadioButton::indicator{width:15px;height:15px;border-radius:5px}\
                              QRadioButton::indicator:unchecked{background-color:rgb(0, 0, 0);}\
                              QRadioButton::indicator:checked{background-color:rgb(144, 238, 144);}");

        modeGroup = new QButtonGroup(this);
        modeGroup->addButton(outBtn, MO_Output);
        modeGroup->addButton(inBtn, MO_Input);
        outBtn->setChecked(true);

        // layout
        modeWidget[i] = new QWidget;
        modeLayout[i] = new QHBoxLayout;
        modeLayout[i]->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum));
        modeLayout[i]->addWidget(outBtn);
        modeLayout[i]->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum));
        modeLayout[i]->addWidget(inBtn);
        modeLayout[i]->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum));
        modeWidget[i]->setLayout(modeLayout[i]);

        ui->tableWidget->setCellWidget(i, 2, modeWidget[i]);

        outImg = new QLabel();
        outImg->setStyleSheet("border-image: url(:/myImage/image/out.png);");
        outImg->setFixedSize(90, 40);
        c_modeWidget[i] = new QWidget;
        c_modeLayout[i] = new QHBoxLayout();
        c_modeLayout[i]->addWidget(outImg);
        c_modeLayout[i]->setAlignment(outImg, Qt::AlignCenter);
        c_modeWidget[i]->setLayout(c_modeLayout[i]);

        ui->tableWidget->setCellWidget(i, 0, c_modeWidget[i]);
    }

    // Setting Value
    for (int i=0; i<8; i++) {

        // mode radiobutton
        lowBtn = new QRadioButton(tr("Low"));
        lowBtn->setObjectName("lowBtn");
        lowBtn->setStyleSheet("QRadioButton::unchecked{color:rgb(0, 0, 0)}\
                              QRadioButton::checked{color:rgb(144, 238, 144);}\
                              QRadioButton::indicator{width:15px;height:15px;border-radius:5px}\
                              QRadioButton::indicator:unchecked{background-color:rgb(0, 0, 0);}\
                              QRadioButton::indicator:checked{background-color:rgb(144, 238, 144);}");

        highBtn = new QRadioButton(tr("High"));
        highBtn->setObjectName("highBtn");
        highBtn->setStyleSheet("QRadioButton::unchecked{color:rgb(0, 0, 0);}\
                               QRadioButton::checked{color:rgb(100, 149, 237);}\
                               QRadioButton::indicator{width:15px;height:15px;border-radius:5px}\
                               QRadioButton::indicator:unchecked{background-color:rgb(0, 0, 0);}\
                               QRadioButton::indicator:checked{background-color:rgb(100, 149, 237);}");
        valueGroup = new QButtonGroup(this);
        valueGroup->addButton(lowBtn, MO_Low);
        valueGroup->addButton(highBtn, MO_High);
        highBtn->setChecked(true);

        // layout
        valueWidget[i] = new QWidget;
        valueLayout[i] = new QHBoxLayout;
        valueLayout[i]->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum));
        valueLayout[i]->addWidget(lowBtn);
        valueLayout[i]->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum));
        valueLayout[i]->addWidget(highBtn);
        valueLayout[i]->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum));
        valueWidget[i]->setLayout(valueLayout[i]);

        ui->tableWidget->setCellWidget(i, 3, valueWidget[i]);

        highImg = new QLabel(tr("High"));
        highImg->setStyleSheet("QLabel {color:rgb(100, 149, 237);}\
                                QLabel {font-size:20px;}");
        c_valueWidget[i] = new QWidget;
        c_valueLayout[i] = new QHBoxLayout();
        c_valueLayout[i]->addWidget(highImg);
        c_valueLayout[i]->setAlignment(highImg, Qt::AlignCenter);
        c_valueWidget[i]->setLayout(c_valueLayout[i]);

        ui->tableWidget->setCellWidget(i, 1, c_valueWidget[i]);
    }
    QObject::connect(ui->dio_setBtn, SIGNAL(clicked(bool)), this, SLOT(on_dio_setBtn_clicked()));
}


void MainWindow::on_dio_setBtn_clicked()
{
    for(int i=0; i<ui->tableWidget->rowCount(); i++){
        QWidget *widget = ui->tableWidget->cellWidget(i, 2);
        if(widget){
            QRadioButton *radioButton = widget->findChild<QRadioButton*>("outBtn");
            if(radioButton && radioButton->isChecked()){
                outImg = new QLabel();
                outImg->setStyleSheet("border-image: url(:/myImage/image/out.png);");
                outImg->setFixedSize(90, 40);
                c_modeWidget[i] = new QWidget;
                c_modeLayout[i] = new QHBoxLayout();
                c_modeLayout[i]->addWidget(outImg);
                c_modeLayout[i]->setAlignment(outImg, Qt::AlignCenter);
            }else{
                inImg = new QLabel();
                inImg->setStyleSheet("border-image: url(:/myImage/image/in.png);");
                inImg->setFixedSize(90,40);
                c_modeWidget[i] = new QWidget;
                c_modeLayout[i] = new QHBoxLayout();
                c_modeLayout[i]->addWidget(inImg);
                c_modeLayout[i]->setAlignment(inImg, Qt::AlignCenter);
            }
            c_modeWidget[i]->setLayout(c_modeLayout[i]);
            ui->tableWidget->setCellWidget(i, 0, c_modeWidget[i]);
        }
    }

    for(int i=0; i<ui->tableWidget->rowCount(); i++){
        QWidget *widget = ui->tableWidget->cellWidget(i, 3);
        if(widget){
            QRadioButton *radioButton = widget->findChild<QRadioButton*>("lowBtn");
            if(radioButton && radioButton->isChecked()){
                lowImg = new QLabel(tr("Low"));
                lowImg->setStyleSheet("QLabel {color:rgb(144, 238, 144);}\
                                       QLabel {font-size:20px;}");
                c_valueWidget[i] = new QWidget;
                c_valueLayout[i] = new QHBoxLayout();
                c_valueLayout[i]->addWidget(lowImg);
                c_valueLayout[i]->setAlignment(lowImg, Qt::AlignCenter);
            }else{
                highImg = new QLabel(tr("High"));
                highImg->setStyleSheet("QLabel {color:rgb(100, 149, 237);}\
                                        QLabel {font-size:20px;}");
                c_valueWidget[i] = new QWidget;
                c_valueLayout[i] = new QHBoxLayout();
                c_valueLayout[i]->addWidget(highImg);
                c_valueLayout[i]->setAlignment(highImg, Qt::AlignCenter);
            }
            c_valueWidget[i]->setLayout(c_valueLayout[i]);
            ui->tableWidget->setCellWidget(i, 1, c_valueWidget[i]);
        }
    }
}


void MainWindow::on_wdtBtn_clicked()
{
    ui->stackedWidget_title->setCurrentIndex(1);
    ui->stackedWidget_context->setCurrentIndex(4);

    // Count Mode
    QButtonGroup *wdtGroup = new QButtonGroup(this);
    ui->secBtn->setStyleSheet("QRadioButton {color:rgb(255, 255, 255);}\
                               QRadioButton::indicator:unchecked {border:2px solid #FFFFFF; background-color:transparent;}\
                               QRadioButton::indicator:checked {border:2px solid #FFFFFF;background-color:rgb(255, 255, 255);}");
    ui->minBtn->setStyleSheet("QRadioButton {color:rgb(255, 255, 255);}\
                               QRadioButton::indicator:unchecked {border:2px solid #FFFFFF; background-color:transparent;}\
                               QRadioButton::indicator:checked {border:2px solid #FFFFFF;background-color:rgb(255, 255, 255);}");
    wdtGroup->addButton(ui->secBtn, MO_Sec);
    wdtGroup->addButton(ui->minBtn, MO_Min);
    ui->secBtn->setChecked(true);

    connect(ui->wdt_setBtn, SIGNAL(clicked()), this, SLOT(on_dio_setBtn_clicked()));
    connect(ui->wdt_clearBtn, SIGNAL(clicked()), this, SLOT(on_wdt_clearBtn_clicked()));
}

void MainWindow::on_wdt_setBtn_clicked()
{
    QString inputText = ui->comboBox_5->currentText();
    inputNum = inputText.toInt();
    timeRest = inputNum;
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);
    ui->wdt_setBtn->setEnabled(false);
}


void MainWindow::update()
{
    if(ui->checkBox->isChecked()){
        QString reloadText = ui->comboBox_7->currentText();
        int reloadNum = reloadText.toInt();
        if(inputNum-timeRest == reloadNum){
            timeRest = inputNum;
        }
    }
    timeRest--;
    char c_timeRest[20];
    sprintf(c_timeRest, "%d seconds remaining", timeRest);
    ui->label_19->setText(c_timeRest);
    if(timeRest <= 0){
        timer->stop();

        // Signal

    }
}


void MainWindow::on_wdt_clearBtn_clicked()
{
    timer->stop();
    timer->disconnect();
    ui->label_19->setText("0 seconds remaining");
    ui->wdt_setBtn->setEnabled(true);
}


void MainWindow::on_fanBtn_clicked()
{
    ui->stackedWidget_title->setCurrentIndex(1);
    ui->stackedWidget_context->setCurrentIndex(5);

    // Monitor Fan
    QButtonGroup *fangroup = new QButtonGroup(this);
    ui->autoBtn->setStyleSheet("QRadioButton {color:rgb(255, 255, 255);}\
                                QRadioButton::indicator:unchecked {border:2px solid #FFFFFF; background-color:transparent;}\
                                QRadioButton::indicator:checked {border:2px solid #FFFFFF;background-color:rgb(255, 255, 255);}");
    ui->manBtn->setStyleSheet("QRadioButton {color:rgb(255, 255, 255);}\
                                QRadioButton::indicator:unchecked {border:2px solid #FFFFFF; background-color:transparent;}\
                                QRadioButton::indicator:checked {border:2px solid #FFFFFF;background-color:rgb(255, 255, 255);}");

    fangroup->addButton(ui->autoBtn, MO_Auto);
    fangroup->addButton(ui->manBtn, MO_Man);
    ui->autoBtn->setChecked(true);

    // Fan Signal
    //QObject::connect(ui->fanSpin, SIGNAL(valueChanged(int)), ui->fanSlider, SLOT(setValue(int)));
    QObject::connect(ui->fanSlider, SIGNAL(valueChanged(int)), ui->fanSpin, SLOT(setValue(int)));
    ui->fanSpin->setReadOnly(true);
}


void MainWindow::on_busBtn_clicked()
{
    ui->stackedWidget_title->setCurrentIndex(1);
    ui->stackedWidget_context->setCurrentIndex(6);

    // Smbus Setting
    QButtonGroup *busGroup = new QButtonGroup(this);
    ui->rbBtn->setStyleSheet("QRadioButton {color:rgb(255, 255, 255);}\
                              QRadioButton::indicator:unchecked {border:2px solid #FFFFFF; background-color:transparent;}\
                              QRadioButton::indicator:checked {border:2px solid #FFFFFF;background-color:rgb(255, 255, 255);}");
    ui->rwBtn->setStyleSheet("QRadioButton {color:rgb(255, 255, 255);}\
                              QRadioButton::indicator:unchecked {border:2px solid #FFFFFF; background-color:transparent;}\
                              QRadioButton::indicator:checked {border:2px solid #FFFFFF;background-color:rgb(255, 255, 255);}");
    ui->wbBtn->setStyleSheet("QRadioButton {color:rgb(255, 255, 255);}\
                              QRadioButton::indicator:unchecked {border:2px solid #FFFFFF; background-color:transparent;}\
                              QRadioButton::indicator:checked {border:2px solid #FFFFFF;background-color:rgb(255, 255, 255);}");
    ui->wwBtn->setStyleSheet("QRadioButton {color:rgb(255, 255, 255);}\
                              QRadioButton::indicator:unchecked {border:2px solid #FFFFFF; background-color:transparent;}\
                              QRadioButton::indicator:checked {border:2px solid #FFFFFF;background-color:rgb(255, 255, 255);}");


    busGroup->addButton(ui->rbBtn, MO_RB);
    busGroup->addButton(ui->rwBtn, MO_RW);
    busGroup->addButton(ui->wbBtn, MO_WB);
    busGroup->addButton(ui->wwBtn, MO_WW);
    ui->rbBtn->setChecked(true);
}


void MainWindow::on_lightBtn_clicked()
{
    ui->stackedWidget_title->setCurrentIndex(1);
    ui->stackedWidget_context->setCurrentIndex(7);

    // Backlight Signal
    QObject::connect(ui->lightSlider_1, SIGNAL(valueChanged(int)), ui->lightSpin_1, SLOT(setValue(int)));
    ui->lightSpin_1->setReadOnly(true);

    QObject::connect(ui->lightSlider_2, SIGNAL(valueChanged(int)), ui->lightSpin_2, SLOT(setValue(int)));
    ui->lightSpin_2->setReadOnly(true);

    QObject::connect(ui->lightSlider_3, SIGNAL(valueChanged(int)), ui->lightSpin_3, SLOT(setValue(int)));
    ui->lightSpin_3->setReadOnly(true);
}

