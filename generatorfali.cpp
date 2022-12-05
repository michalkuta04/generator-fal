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
    int plotViewWidth= plot->size().width();
    int plotViewHeight = plot->size().height();
    QGraphicsScene plotScene;
    plot->setScene(&plotScene);
    QPen pen;
    pen.setWidth(4);
    std::vector<std::tuple<double, double>> waveValues;
    if (ui->pushButton->text() == "Start")
    {
        std::tuple<double, double> lastValue;
        QString debugText = "";
        uint waveFrequency = ui->spinBoxFrequency->value();
        uint sampleRateMs = ui->spinBoxSampling->value();
        int i = 0;
        ui->pushButton->setText("Stop");
        // Oblicza wartosci fali dla kazdego interwału próbkowania i rysuje fale.
        // TODO: Nic nie działa
        lastValue = {0, sin(2*M_PI*0*waveFrequency)};
        do
        {
            i += sampleRateMs;
            double x = i * plotViewWidth;
            double y = 0.25 * plotViewHeight;
            plotScene.addLine(std::get<0>(lastValue), std::get<1>(lastValue), x, y);
            lastValue = {x, y};
        } while (i <= 1000);
        ui->debugLabel->setText(debugText);
    }
    else if (ui->pushButton->text() == "Stop")
    {
        ui->pushButton->setText("Start");
    }
}

