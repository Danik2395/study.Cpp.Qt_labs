#pragma once
#include <QWidget>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QKeyEvent>
#include <QIntValidator>
#include <QBoxLayout>
#include <qobject.h>
#include <stdexcept>
#include "../Interfaces.h"
#include "../ui/ui_Lab8Widget.h"
#include "classes/Patrol.h"

namespace Ui
{
    class Lab8Widget_ui;
}

#define LAB8_RESULT_TEMPL "Number is correct: %1"

class Lab8Widget : public QWidget, public ILabWindow
{
    Q_OBJECT

signals:
    void close_requested();

public:
    Lab8Widget(QString name = "Lab", QWidget* parent = nullptr) : QWidget(parent), name_(name)
    {
        lab8_ui = new Ui::Lab8Widget_ui;
        lab8_ui->setupUi(this);

        lab8_ui->edit_number->setValidator(new QIntValidator(this));
        lab8_ui->label_result->setProperty("patrol_templ", LAB8_RESULT_TEMPL);

        connect(lab8_ui->edit_number,
                &QLineEdit::editingFinished,
                this,
                [this](){
                bool ok_int = false;
                int value = lab8_ui->edit_number->text().toInt(&ok_int);
                if (!ok_int) return;

                try
                {
                    patrol.check(value);
                    lab8_ui->label_result->setText(
                        lab8_ui->label_result->property("patrol_templ").toString().arg(patrol.get_number()));
                }
                catch (const std::invalid_argument& error)
                {
                    lab8_ui->label_result->setText(error.what());
                }
                });
    }

    ~Lab8Widget() { delete lab8_ui; }

    QString get_name(void) const
    {
        return name_;
    }

private:
    QString name_;
    Ui::Lab8Widget_ui* lab8_ui;

    Patrol patrol;
};
