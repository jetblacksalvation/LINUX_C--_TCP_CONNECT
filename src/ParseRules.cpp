#include "ParseRules.hpp"
#include <typeinfo>
#include <iostream>

ParseRules::
AbstractTerminal::
AbstractTerminal()
{

};
void ParseRules::AbstractTerminal::_ApplySelfGloballyWrapper() 
{
    std::cout<< typeid(this).name();
    if(this->_can_has_global)
        this->ApplySelfGlobally();
    else
        std::cout<< "Object "<<typeid(this).name()<<" Cannot be Applied Globally\n";
    
}
// ParseRules::Type::Type(std::string )