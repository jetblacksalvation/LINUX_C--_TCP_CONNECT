#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <vector>

static inline std::string seperateTokensBy = ", []():+-*/\r\n";
std::vector<std::string> tokenize(std::string string);
std::vector<std::vector<std::string> > getCode(std::fstream& stream);

#endif