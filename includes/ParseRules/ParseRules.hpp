#ifndef PARSERULES_HPP
#define PARSERULES_HPP
#include "Tokenizer.hpp"
#include <memory>
#include <functional>

namespace ParseRules
{
    static inline auto Tokenize = tokenize;
    using string = std::string;

    class AbstractTerminal
    {
    public:
        AbstractTerminal();
        // USE ONLY AS ROOT FOR NEW GRAMMAR RULE!!
        void _ApplySelfGloballyWrapper();
        virtual void ApplySelfGlobally()
        {

            static_assert("AbstractTerminal Cannot Be Instantiated");
        };
        virtual string GetName()
        {
            static_assert("AbstractTerminal Has No Name");
        }
    private:
        std::vector < ParseRules::AbstractTerminal > _children;
        bool _can_has_global = false;//readonly "static" private, only ever set in constructor of inheritor.
        bool _has_global     = false;
    };

    class StringCollectionTerminal : public AbstractTerminal 
    {
        public:
            std::vector<string> stringCollection;
            string returnStringInCollection(string input)
            {
                string returnStr = "";
                for (auto it : this->stringCollection )
                {
                    returnStr = ((it == input) ? it : "" );
                }
                return returnStr;
            }
        private:
    }; 
    class Type : public StringCollectionTerminal 
    {
    public:
        Type() {};
        void ApplySelfGlobally(){};
    };
    class TokenInterface 
    {
        // -> members have a list of static instances of abstract terminal objects
        // abstract terminal objects are nodes, where node is interface
        // TokenInterface manages parse tree created with these nodes
    public:
        TokenInterface();

    private:
        static inline std::vector<ParseRules::AbstractTerminal> _root; 
    };

}

#endif