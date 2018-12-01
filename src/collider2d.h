#ifndef COLLIDER2D_H
#define COLLIDER2D_H


class Collider2D
{
public:
    Collider2D();

    bool isTouching(Collider2D collider);
};

#endif // COLLIDER2D_H
