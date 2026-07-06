#include <iostream>
#include <vector>
#include <conio.h> // Нужен для функции _getch() (ввод без Enter)
#include "Player.h"
#include "Location.h"
#include "Puzzle.h"

int main() {
    // Настраиваем кодировку консоли для поддержки русского языка
    setlocale(LC_ALL, "Russian");

    // 1. Создаем головоломку для 2-й локации
    Puzzle* mathPuzzle = new Puzzle("Решите уравнение: 5 + x = 12. Чему равен x?", "7");

    // 2. Создаем 3 локации в соответствии с ТЗ (ASCII-символы)
    // Цифры '2' и '3' на карте — это двери-переходы в локации №2 и №3
    std::vector<Location*> dungeon;

    // Локация 1 (Стартовая, всегда открыта)
    dungeon.push_back(new Location(1, {
        "##########",
        "#        #",
        "#  @     2", // Переход в локацию 2
        "#        #",
        "##########"
        }, true));

    // Локация 2 (Промежуточная, изначально закрыта головоломкой)
    dungeon.push_back(new Location(2, {
        "##############",
        "#            #",
        "1      C     3", // 1 - назад к старту, 3 - к выходу
        "#            #",
        "##############"
        }, false, mathPuzzle));

    // Локация 3 (Последняя, победная, изначально закрыта)
    dungeon.push_back(new Location(3, {
        "#######",
        "#     #",
        "# WIN #",
        "#######"
        }, false));

    // 3. Создаем игрока в локации №1 на координатах X=3, Y=2
    Player player(1, 3, 2);

    std::cout << "ДОБРО ПОЖАЛОВАТЬ В ЛАБИРИНТ!\nВаша задача — выбраться. Изучайте комнаты и ищите проходы.\n";
    system("pause");

    // Главный игровой цикл
    while (true) {
        system("cls"); // Очистка экрана консоли перед каждым шагом

        // Находим текущую локацию игрока в векторе
        Location* currentLoc = nullptr;
        for (auto loc : dungeon) {
            if (loc->getId() == player.getCurrentLocationId()) {
                currentLoc = loc;
                break;
            }
        }

        // Проверяем условия победы (если зашли в локацию 3)
        if (currentLoc->getId() == 3) {
            currentLoc->render(player.getX(), player.getY());
            std::cout << "\nПОЗДРАВЛЯЕМ! Вы выбрались из лабиринта и победили!\n";
            break;
        }

        // Рисуем карту
        std::cout << "Управление: W, A, S, D (английская раскладка). Текущая локация: " << currentLoc->getId() << "\n\n";
        currentLoc->render(player.getX(), player.getY());

        // Считываем нажатие клавиши БЕЗ нажатия Enter
        char key = _getch();
        int targetX = player.getX();
        int targetY = player.getY();

        if (key == 'w' || key == 'W') targetY--;
        if (key == 's' || key == 'S') targetY++;
        if (key == 'a' || key == 'A') targetX--;
        if (key == 'd' || key == 'D') targetX++;

        // Проверяем, куда наступил игрок
        char nextTile = currentLoc->getTile(targetX, targetY);

        if (nextTile == ' ') {
            // Обычный пустой шаг
            player.setPosition(targetX, targetY);
        }
        else if (nextTile == '1' || nextTile == '2' || nextTile == '3') {
            // Игрок наступил на переход в другую локацию (конвертируем символ в число ID)
            int nextLocId = nextTile - '0';

            // Находим целевую локацию
            Location* targetLoc = nullptr;
            for (auto loc : dungeon) {
                if (loc->getId() == nextLocId) {
                    targetLoc = loc;
                    break;
                }
            }

            // Если локация закрыта — запускаем головоломку
            if (!targetLoc->getIsOpen()) {
                // Если у локации есть головоломка и игрок ее решил
                if (targetLoc->getId() == 2 && mathPuzzle->solve()) {
                    targetLoc->openLocation();
                }
                // Для локации 3 головоломки нет, она откроется автоматически, если открыта 2
                else if (targetLoc->getId() == 3) {
                    targetLoc->openLocation();
                }
            }

            // Если локация теперь открыта — перемещаем игрока (ставим его в центр новой комнаты)
            if (targetLoc->getIsOpen()) {
                if (nextLocId == 1) player.changeLocation(1, 7, 2); // Возврат к первой комнате
                if (nextLocId == 2) player.changeLocation(2, 2, 2); // Переход во вторую
                if (nextLocId == 3) player.changeLocation(3, 2, 2); // Переход в победную
            }
        }
    }

    // Очищаем динамическую память в конце игры
    for (auto loc : dungeon) {
        delete loc;
    }

    return 0;
}