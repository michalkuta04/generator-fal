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

