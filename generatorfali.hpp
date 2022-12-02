#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class GeneratorFali; }
QT_END_NAMESPACE

class GeneratorFali : public QMainWindow
{
    Q_OBJECT

public:
    GeneratorFali(QWidget *parent = nullptr);
    ~GeneratorFali();

private:
    Ui::GeneratorFali *ui;
};
