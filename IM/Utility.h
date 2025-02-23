#pragma once

using namespace System;
using namespace System::Globalization;

public ref class Utility abstract sealed  // static yerine ge�en "abstract + sealed" kombinasyonu
{
public:
    static String^ GetDecimalSeparator() {
        CultureInfo^ culture = CultureInfo::CurrentCulture;
        return culture->NumberFormat->NumberDecimalSeparator;
    }
};
