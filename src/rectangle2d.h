#ifndef RECTANGLE2D_H
#define RECTANGLE2D_H


class Rectangle2D
{
public:
    Rectangle2D();
    Rectangle2D(double x, double y, double w, double h);

    double getX() const;
    double getY() const;
    double getW() const;
    double getH() const;
    double getRight() const;
    double getBottom() const;
private:
    double _x,_y,_w,_h;
    double _right, _bottom;
};

#endif // RECTANGLE2D_H
