

#include "config.h"

#include <stdexcept>


std::string TrimString(const std::string& str, const std::string& whitespace = " \t");

Config::Config() { }

Config::~Config()
{
    this->Elements.clear();
}

void Config::Update(const std::string& key, const std::string& value)
{
    this->Elements[TrimString(key)] = TrimString(value);
}

bool Config::GetBool(const std::string& varName)
{
    if (this->Elements.find(varName) == this->Elements.end())
        throw std::invalid_argument("Requested element not in config");
    
    std::string value = this->Elements[varName];
    if (value != "0" && value != "1")
        throw std::invalid_argument("Requested element is not a boolean");

    return value != "0";
}

int Config::GetInt(const std::string& varName)
{
    if (this->Elements.find(varName) == this->Elements.end())
        throw std::invalid_argument("Requested element not in config");

    std::string value = this->Elements[varName];
    return std::stoi(value);
}

std::string Config::GetString(const std::string& varName)
{
    if (this->Elements.find(varName) == this->Elements.end())
        throw std::invalid_argument("Requested element not in config");

    return this->Elements[varName];
}

std::map<std::string, std::string> Config::GetElements()
{
    return std::map(this->Elements);
}

std::string TrimString(const std::string& str, const std::string& whitespace)
{
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

