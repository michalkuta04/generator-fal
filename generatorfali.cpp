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
    QGraphicsView *plot = ui->plot;
    int plotViewHeight = plot->size().height();
    QGraphicsScene plotScene;
    plot->setScene(&plotScene);
    QPen pen;
    pen.setWidth(4);
    QLine line;
    std::vector<double> values;
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
                plotScene.clear();
                waveFrequency = ui->spinBoxFrequency->value();
                y = sin(2*M_PI*elapsedSamplingRateMs/1000*waveFrequency); // Oblicz wartość fali
                if (ui->comboBoxShape->currentIndex() == 1) // Jeżeli kwadratowa to przybliż do całości
                {
                    if (y > 0)
                        y = 1;
                    if (y <= 0)
                        y = -1;
                }
                values.push_back(y);
                elapsedSamplingRateMs += sampleRateMs; // Kiedy następne próbkowanie

                // Rysowanie fali na GraphicsView
                // działa strasznie wolno ale działa.
                if (values.size() >= 2)
                {
                    float x1 = 0;
                    for (auto rit = values.rbegin(); rit < values.rend()-1; rit++)
                    {
                        if (x1 > plot->size().width())
                        {
                            values.erase((rit+1).base());
                            break;
                        }
                        float x2 = x1 + 300/sampleRateHz;
                        float y1 = (*rit)*(plotViewHeight/2-2);
                        float y2 = *(rit+1)*(plotViewHeight/2-2);
                        line.setLine(x1, y1, x2, y2);
                        plotScene.addLine(line,pen);
                        x1 = x2;
                    }
                }
            }
            QCoreApplication::processEvents(QEventLoop::AllEvents, 1);
        }
    }
    else if (ui->pushButton->text() == "Stop")
    {
        ui->pushButton->setText("Start");
    }
}

