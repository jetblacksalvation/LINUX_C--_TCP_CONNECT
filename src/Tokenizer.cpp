#include "Tokenizer.hpp"
#include <fstream>
std::vector<std::string> tokenize(std::string string){

    std::vector<std::string> tokens;
    std::string buffer;
    for (auto& character : string){
        if (isalnum(character) && seperateTokensBy.find(character)==std::string::npos){
            //append to buffer tokens until it is in sperate tokens by...
            buffer += character;
        }
        else{
            if( !isblank(character) && seperateTokensBy.find(character)!=std::string::npos){
                if (buffer.size() >0){
                    tokens.push_back(buffer);

                }
                //
                tokens.emplace_back(1,character);
                //do not push, if ' ' !
            }
            else if (isblank(character) && seperateTokensBy.find(character)!=std::string::npos){
                if (buffer.size() >0){
                    tokens.push_back(buffer);

                }
            }
            buffer = "";
        }
        // if (isalnum(character) && std::find(std::begin(seperateTokensBy), std::end(seperateTokensBy), character));

    }
    return tokens;
    //accumilate string if char is not in seperateTokensBy and is alphanumeric aka visable ...
}
std::vector<std::vector<std::string>>  getCode(std::fstream& stream){
    std::string line;
    std::vector<std::vector<std::string>> code;
    while (std::getline(stream, line)) {
        code.push_back(tokenize(line+' '));
    }
    return code;
};