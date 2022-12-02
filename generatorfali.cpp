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
        QElapsedTimer timer;
        uint waveFrequency;
        uint sampleRateHz = ui->spinBoxSampling->value();
        double sampleRateMs = 1000/sampleRateHz;
        double elapsedSamplingRateMs = sampleRateMs;
        double y;

        ui->pushButton->setText("Stop");
        timer.start();
        // Po wcisnieciu start rozpoczyna petle która czeka na tyle żeby próbkowanie się zgadzało
        while (ui->pushButton->text() == "Stop")
        {
            sampleRateHz = ui->spinBoxSampling->value();
            sampleRateMs = 1000/sampleRateHz;
            if (timer.elapsed() >= elapsedSamplingRateMs) // Czekaj na próbkowanie
            {
                waveFrequency = ui->spinBoxFrequency->value();
                y = sin(2*M_PI*elapsedSamplingRateMs/1000*waveFrequency); // Oblicz wartość fali
                if (ui->comboBoxShape->currentIndex() == 1) // Jeżeli kwadratowa to przybliż do całości
                {
                    if (y > 0)
                        y = 1;
                    if (y <= 0)
                        y = -1;
                }
                outputLabel->setText(QString::number(y)); // Wyświetl wartość fali
                elapsedSamplingRateMs += sampleRateMs; // Kiedy następne próbkowanie
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

