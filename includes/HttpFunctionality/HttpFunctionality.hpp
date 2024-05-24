#ifndef HTTPFUNCTIONALITY_HPP
#define HTTPFUNCTIONALITY_HPP

#include <string>
#include <vector>
#include <unordered_map>
namespace HttpFunctionality 
{
    
    using string = std::string; 
    string getLocalIp();

    using _DictT = std::unordered_map< string, string >;

    // _DictT upcast to Dictionary, Dictionary simply defines helper functions to load into it
    class Dictionary : public _DictT
    { 
    public:
        static Dictionary PopulateFromString(std::string );
        std::vector<string> HttpRequest = {""};

    private:
        string method = "" ;
    };
}

#endif