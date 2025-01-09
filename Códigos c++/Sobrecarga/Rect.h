#ifndef RECT_H
#define RECT_H

class Rect{
	private:
		double x;
		double y;
	public:
		Rect();
		Rect(double, double);
		Rect operator+(Rect val);
		Rect operator-(Rect val);
		void setX(double x);
		void setY(double y);
		double getX();
		double getY();
		~Rect();
};
#endif // RECT_H
