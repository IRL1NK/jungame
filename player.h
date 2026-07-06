#pragma once

class Player {
private:
    int x;
    int y;
    int currentLocationId;

public:
    Player(int startLocationId, int startX, int startY);

    int getX() const;
    int getY() const;
    int getCurrentLocationId() const;

    void setPosition(int newX, int newY);
    void changeLocation(int newLocationId, int newX, int newY);
};
