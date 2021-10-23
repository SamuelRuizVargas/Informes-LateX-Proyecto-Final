#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <QGraphicsItem>
#include <QPainter>

#define PATH_P1 ":/imagenes/player1.png"
#define g -15.0f
class personaje  : public QGraphicsItem
{
    int h=40;
    int an=28;
    float posx;
    float posy;
    float vx=0;
    float vy=80;
    float vy2=0;
    bool caida=true;

public:
    personaje(int,int);
    ~personaje();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    void setVX(float velocidadx);
    void setVY(float velocidady);
    void free(float dt);
    void resetVX();
    void resetVY();
    void resetVY2();
    void changedown();
    bool getcaida();
    void setposis(float x, float y);
    float getX();
    float getY();
    float getVY();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void jump(float dt);
};


#endif // PERSONAJE_H
