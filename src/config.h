

#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <map>
#include <fstream>


class Config
{
private:
    std::map<std::string, std::string> Elements;
public:
    // constructor
    Config();
    // destructor
    ~Config();
    // methods
    void        Update(const std::string& key, const std::string& value);
    bool        GetBool(const std::string& varName);
    int         GetInt(const std::string& varName);
    std::string GetString(const std::string& varName);
    std::map<std::string, std::string> GetElements();
};

#endif


