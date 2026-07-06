#pragma once
#include <string>

class Puzzle {
private:
    std::string question;
    std::string answer;

public:
    Puzzle(std::string q, std::string a);
    bool solve(); // Возвращает true, если игрок угадал
};


