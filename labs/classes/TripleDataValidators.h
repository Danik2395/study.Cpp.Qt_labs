#pragma once
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <qobject.h>

// Validates space separated ints: "18 188 88 0"
class IntDataValidator : public QRegularExpressionValidator
{
public:
    explicit IntDataValidator(QObject* parent = nullptr) :
        QRegularExpressionValidator(QRegularExpression(R"(^(\d+( \d+)*)?$)"), parent) {}
};

// Validates space separated doubles: "18.0 18.8 .88 0 5"
// Commas are not allowed (so "1,000,000.0" is invalid)
class DoubleDataValidator : public QRegularExpressionValidator
{
public:
    explicit DoubleDataValidator(QObject* parent = nullptr) :
        QRegularExpressionValidator(
            QRegularExpression(R"(^((\.\d+|\d+(\.\d+)?)( (\.\d+|\d+(\.\d+)?))*)?$)"),
            parent) {}
};

// Validates any string of characters that can be casted to char
class CharDataValidator : public QRegularExpressionValidator
{
public:
    explicit CharDataValidator(QObject* parent = nullptr) :
        QRegularExpressionValidator(QRegularExpression(R"(^[\x20-\x7E]*$)"), parent) {}
};
