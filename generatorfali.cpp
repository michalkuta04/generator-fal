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
    QString waveFrequency = QString::number(ui->spinBoxFrequency->value());
    QString waveSampling = QString::number(ui->spinBoxSampling->value());
    QLabel *outputLabel = ui->outputLabel;
    outputLabel->setText(waveFrequency + " " + waveSampling);
}

