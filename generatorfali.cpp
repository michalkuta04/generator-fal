#include "generatorfali.hpp"
#include "./ui_generatorfali.h"

GeneratorFali::GeneratorFali(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GeneratorFali)
{
    ui->setupUi(this);
}

GeneratorFali::~GeneratorFali()
{
    delete ui;
}


void GeneratorFali::on_pushButton_clicked()
{
    QLabel *outputLabel = ui->outputLabel;
    if (ui->pushButton->text() == "Start")
    {
        QString waveFrequency = QString::number(ui->spinBoxFrequency->value());
        QElapsedTimer timer;
        int waveSampling;
        int i = 0;
        ui->pushButton->setText("Stop");
        timer.start();
        // Po wcisnieciu start rozpoczyna petle która czeka na tyle żeby próbkowanie się zgadzało
        while (ui->pushButton->text() == "Stop")
        {
            waveSampling = ui->spinBoxSampling->value();
            if (timer.elapsed() > 1000/waveSampling)
            {
                outputLabel->setText(QString::number(i++));
                timer.restart();
            }
            QCoreApplication::processEvents(QEventLoop::AllEvents, 1);
        }
    }
    else if (ui->pushButton->text() == "Stop")
    {
        ui->pushButton->setText("Start");
        outputLabel->setText("0");
    }
}

