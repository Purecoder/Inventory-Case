#pragma once

using namespace System;
using namespace System::Globalization;

public ref class Utility abstract sealed  // static yerine geçen "abstract + sealed" kombinasyonu
{
public:
    static String^ GetDecimalSeparator() {
        CultureInfo^ culture = CultureInfo::CurrentCulture;
        return culture->NumberFormat->NumberDecimalSeparator;
    }
};
