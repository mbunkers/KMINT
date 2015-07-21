#include <algorithm>

struct Vector2D{
	double x;
	double y;

	Vector2D() :x(0.0), y(0.0){}
	Vector2D(double a, double b){ x = a; y = b; }

	inline void Zero(){
		x = 0.0;
		y = 0.0;
	}

	inline bool isZero()const{
		return x == 0 && y == 0;
	}

	inline double Length()const{
		return sqrt(x*x + y*y);
	}
	inline double LengthSq()const{
		return x*x + y*y;
	}
	inline void Normalize(){
		x = x / Length();
		y = y / Length();
	}
	inline double Dot(const Vector2D& v2)const{
		return (x * v2.x) + (y * v2.y);
	}
	inline int Sign(const Vector2D& v2)const{
		return Dot(v2);
	}
	inline Vector2D Perp()const;
	inline void Truncate(double max);
	inline double Distance(const Vector2D& v2)const{
		return sqrt(pow(v2.x - x, 2) + pow(v2.y - y, 2));
	}
	inline double DistanceSq(const Vector2D& v2)const{
		return pow(v2.x - x, 2) + pow(v2.y - y, 2);
	}
	inline Vector2D GetReverse()const;

	const Vector2D operator+=(const Vector2D &rhs){
		double newX = x + rhs.x;
		double newY = y + rhs.y;

		return Vector2D(newX, newY);
	}
	const Vector2D operator-=(const Vector2D &rhs){
		double newX = x - rhs.x;
		double newY = y - rhs.y;

		return Vector2D(newX, newY);
	}
	const Vector2D operator*=(const double& rhs){
		double newX = x * rhs;
		double newY = y * rhs;

		return Vector2D(newX, newY);
	}
	const Vector2D operator/=(const double& rhs){
		double newX = x / rhs;
		double newY = y / rhs;

		return Vector2D(newX, newY);
	}
	bool operator==(const Vector2D& rhs)const{
		return this == &rhs;
	}
	bool operator!=(const Vector2D& rhs)const{
		return this != &rhs;
	}
};