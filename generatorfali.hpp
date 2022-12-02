#pragma once

#include <QMainWindow>
#include <QElapsedTimer>
#include <math.h>

QT_BEGIN_NAMESPACE
namespace Ui { class GeneratorFali; }
QT_END_NAMESPACE

class GeneratorFali : public QMainWindow
{
    Q_OBJECT

public:
    GeneratorFali(QWidget *parent = nullptr);
    ~GeneratorFali();

private slots:
    void on_pushButton_clicked();

private:
    Ui::GeneratorFali *ui;
};
