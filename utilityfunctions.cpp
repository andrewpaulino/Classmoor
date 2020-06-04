#include "utilityfunctions.h"

UtilityFunctions::UtilityFunctions()
{

}

std::string UtilityFunctions::convertAWSStringToStdString(Aws::String v)
{
    return std::string(v.c_str(), v.size());
}

QString UtilityFunctions::convertStdStringToQString(std::string v)
{
    return QString::fromStdString(v);
}

Aws::String UtilityFunctions::convertStdStringToAWSString(std::string v)
{
    return Aws::String(v.c_str(), v.size());
}

Aws::String UtilityFunctions::convertQStringToAWSString(QString v)
{
    return convertStdStringToAWSString(convertQStringToStdString(v));
}

std::string UtilityFunctions::convertQStringToStdString(QString v)
{
    return v.toStdString();
}

