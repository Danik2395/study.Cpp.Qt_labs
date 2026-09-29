#pragma once
#include <iostream>
#include <string>

class Crimes_Base
{
protected:
    std::string name;
    int years_imprisonment;
    int severity_of_crime;
    int monetary_penalty_for_crime;

public:
    Crimes_Base(std::string crime_name, int years, int severity, int monetary) :
        name(crime_name),
        years_imprisonment(years),
        severity_of_crime(severity),
        monetary_penalty_for_crime(monetary)
    {}

    virtual void print_info()
    {
        std::cout << '\n'
                  << "Years imprisonment: "         << years_imprisonment         << '\n'
                  << "Severity of crime: "          << severity_of_crime          << '\n'
                  << "Monetary penalty for crime: " << monetary_penalty_for_crime << '\n';
    }

    virtual void how_many_days()
    {
        int years_imprisonment_multiplied;

        if (severity_of_crime < 4)
        {
            years_imprisonment_multiplied = years_imprisonment * 365 / 2;
        }
        else if (severity_of_crime <= 4 && severity_of_crime <= 10)
        {
            years_imprisonment_multiplied = years_imprisonment * 365;
        }
        else
        {
            years_imprisonment_multiplied = years_imprisonment * 365 * 2;
        }

        std::cout << "\nYears imprisonment multiplied: " << years_imprisonment_multiplied << '\n';
    }
};

class Strong_Crime : public Crimes_Base
{
public:
    Strong_Crime(std::string crime_name, int years, int severity, int monetary) :
        Crimes_Base(crime_name, years, severity, monetary)
    {}

    void print_info() override
    {
        std::cout << "Name: " << name << '\n';
        Crimes_Base::print_info();
    }

    void how_many_days() override
    {
        Crimes_Base::how_many_days();
    }
};
