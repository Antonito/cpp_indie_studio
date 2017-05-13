#include <iostream>
#include "Ini.hpp"
#include "Section.hpp"

int main()
{
    try
    {
    ini::Ini i1;

    i1.loadFrom("normal.ini");
    i1.saveAs("normal_saved.ini");

    ini::Ini i2;

    i2["section1"]["val1"] = "192.1.1.2";
    i2[""]["val42"] = "192.1.1.1";
    i2["section2"]["val1"] = "192.1.1.3";
    i2["section2"]["val2"] = "192.1.1.4";

    i2.saveAs("saved.ini");
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
    return (0);
}
