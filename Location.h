#pragma once
#include <vector>
#include <string>
#include "Puzzle.h"

class Location {
private:
    int id;
    std::vector<std::string> map; // ASCII-форма локации
    bool isOpen;
    Puzzle* puzzle; // Указатель на головоломку (NULL, если нет)

public:
    Location(int id, std::vector<std::string> m, bool open, Puzzle* p = nullptr);
    ~Location(); // Деструктор для очистки памяти

    int getId() const;
    bool getIsOpen() const;
    void openLocation();

    // Возвращает символ на карте по координатам
    char getTile(int x, int y) const;

    // Отрисовка карты с учетом позиции игрока
    void render(int playerX, int playerY) const;
};


