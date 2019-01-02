#include "mainwindow.h"
#include <QWebEngineView>
#include <QWebEngineSettings>
#include <QPushButton>
#include <QFileDialog>
#include "ui_mainwindow.h"

#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->webEngineView->settings()->setAttribute(QWebEngineSettings::JavascriptEnabled, true);

    channel = new QWebChannel(this);
    channel->registerObject("external", &jsBridge);
    ui->webEngineView->page()->setWebChannel(channel);

    ui->webEngineView->setUrl(QUrl("qrc:///app/app.html"));

    connect(ui->actionOpen, &QAction::triggered, [&]{
        QFile animation(QFileDialog::getOpenFileName(this, "Choose Lottie animation", nullptr, "*.json"));
        animation.open(QFile::ReadOnly | QFile::Text);
        QTextStream animationStream(&animation);

        jsBridge.displayAnimation(animationStream.readAll());
    });

    connect(&jsBridge, &JSBridge::onAnimationLoaded, [&](int frames, int frameRate) {
        ui->frameCount->setText("Frame count: "+QString::number(frames));
        ui->frameRate->setText("Frame rate: "+QString::number(frameRate));
        ui->frameNavigator->setMaximum(frames);
        ui->frameNavigator->setValue(0);
        ui->speedSlider->setValue(100);
        ui->playCheckbox->setChecked(true);
    });

    connect(ui->playCheckbox, &QCheckBox::toggled, [&](bool playing) {
        if (playing) {
            jsBridge.playAnimation();
        } else {
            jsBridge.pauseAnimation();
        }
    });

    connect(ui->frameNavigator, &QSlider::sliderMoved, [&](int position) {
        if (!ui->playCheckbox->isChecked()) {
            jsBridge.seekToFrame(position);
        }
    });

    connect(ui->actionExit, &QAction::triggered, [&]{
        QApplication::exit();
    });

    connect(&jsBridge, &JSBridge::onEnterFrame, [&](int frame) {
        if (ui->playCheckbox->isChecked()) {
            ui->frameNavigator->setValue(frame);
        }
    });

    connect(ui->speedSlider, &QSlider::valueChanged, [&](int value) {
        jsBridge.setSpeed(value);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
    delete channel;
}
