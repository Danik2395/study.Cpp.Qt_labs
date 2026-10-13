#pragma once
#include <QWidget>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QKeyEvent>
#include <QBoxLayout>
#include <qobject.h>
#include <concepts>
#include <ranges>
#include <stdexcept>
#include <string>
#include <vector>
#include "../Interfaces.h"
#include "../ui/ui_Lab7Widget.h"
#include "classes/triple_data_template_array.h"
#include "classes/TripleDataValidators.h"

namespace Ui
{
    class Lab7Widget_ui;
}

class Lab7Widget : public QWidget, public ILabWindow
{
    Q_OBJECT

signals:
    void close_requested();

public:
    Lab7Widget(QString name = "Lab", QWidget* parent = nullptr) : QWidget(parent), name_(name)
    {
        lab7_ui = new Ui::Lab7Widget_ui;
        lab7_ui->setupUi(this);

        lab7_ui->edit_int->setValidator(new IntDataValidator(this));
        lab7_ui->edit_double->setValidator(new DoubleDataValidator(this));
        lab7_ui->edit_char->setValidator(new CharDataValidator(this));

        connect(lab7_ui->edit_int,
                &QLineEdit::editingFinished,
                this,
                [this](){ data_int.update_data(split_to_int(lab7_ui->edit_int->text())); });

        connect(lab7_ui->edit_double,
                &QLineEdit::editingFinished,
                this,
                [this](){ data_double.update_data(split_to_double(lab7_ui->edit_double->text())); });

        connect(lab7_ui->edit_char,
                &QLineEdit::editingFinished,
                this,
                [this](){ data_char.update_data(split_to_char(lab7_ui->edit_char->text())); });

        connect(lab7_ui->btn_show_results,
                &QPushButton::clicked,
                this,
                &Lab7Widget::show_results);
    }

    ~Lab7Widget() { delete lab7_ui; }

    QString get_name(void) const
    {
        return name_;
    }

protected:
    // ESC closes the lab tab (MainWindow handles close_requested)
    void keyPressEvent(QKeyEvent* event) override
    {
        if (event->key() == Qt::Key_Escape)
        {
            emit close_requested();
            return;
        }

        QWidget::keyPressEvent(event);
    }

private:
    QString name_;
    Ui::Lab7Widget_ui* lab7_ui;

    TripleDataArray<int>    data_int;
    TripleDataArray<double> data_double;
    TripleDataArray<char>   data_char;

    static std::vector<int> split_to_int(const QString& text)
    {
        std::string text_str = text.toStdString();
        std::vector<int> data;

        try
        {
            for (auto word : std::views::split(text_str, ' '))
            {
                if (word.empty()) continue;
                data.push_back(std::stoi(std::string(std::from_range, word)));
            }
        }
        catch (const std::exception&) // For stoi and std::string() fault
        {
            data.clear();
        }

        return data;
    }

    static std::vector<double> split_to_double(const QString& text)
    {
        std::string text_str = text.toStdString();
        std::vector<double> data;

        try
        {
            for (auto word : std::views::split(text_str, ' '))
            {
                if (word.empty()) continue;
                data.push_back(std::stod(std::string(std::from_range, word)));
            }
        }
        catch (const std::exception&)
        {
            data.clear();
        }

        return data;
    }

    static std::vector<char> split_to_char(const QString& text)
    {
        std::vector<char> data;
        data.reserve(text.size());

        for (QChar ch : text)
        {
            data.push_back(static_cast<char>(ch.toLatin1()));
        }

        return data;
    }

    template<typename T>
    QString get_result_string(TripleDataArray<T>& data)
    {
        try
        {
            T result = data.get_result();

            if constexpr (std::same_as<char, T>)
            {
                // Show ascii code in brackets
                return QString("'%1' (%2)").arg(QChar(result)).arg(static_cast<int>(result));
            }
            else
            {
                return QString::number(result);
            }
        }
        catch (const std::exception&)
        {
            return "empty";
        }
    }

    void show_results()
    {
        QString result_text = QString("Results:\n") +
                                      "int: " + get_result_string(data_int)       + '\n' +
                                      "double: " + get_result_string(data_double) + '\n' +
                                      "char: " + get_result_string(data_char);
        QMessageBox msg_box(QMessageBox::Information, "Results", result_text, QMessageBox::Ok, this);

        msg_box.exec();
    }
};
