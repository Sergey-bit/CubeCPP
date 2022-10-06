#include <vector>
#include <cmath>

class Cube
{
private:
	struct Point
	{
		double x;
		double y;
		double z;
	};
	std::vector<Point> coord ={
		{ 0.5, -0.5, -0.5 },
		{ 0.5, 0.5, -0.5 },
		{ -0.5, 0.5, -0.5 },
		{ -0.5, -0.5, -0.5 },
		{ 0.5, -0.5, 0.5 },
		{ 0.5, 0.5, 0.5 },
		{ -0.5, 0.5, 0.5 },
		{ -0.5, -0.5, 0.5 },
	};

	const double pi = acos(-1);

	SDL_Renderer* renderer;
	const Point center;

	const double scale;

	SDL_Point get_proection(const Point& p) const
	{
		SDL_Point np;

		np.x = std::round(center.x + tile * p.x);
		np.y = std::round(center.y - tile * p.y);

		return np;
	}
	void draw_line(const Point& p1, const Point& p2) const
	{
		SDL_Point np1 = get_proection(p1), np2 = get_proection(p2);
		SDL_RenderDrawLine(renderer, np1.x, np1.y, np2.x, np2.y);
	}

public:
	Cube(SDL_Renderer* renderer, double x, double y, double z, int scale) : renderer(renderer), center{ x, y, z }, scale(scale) { }

	double degreeToRadians(double degree) const
	{
		return pi / 180.0 * degree;
	}

	void rotateX(const double angle)
	{
		for (Point& point: coord)
		{
			double y = point.y;

			point.y = cos(angle) * y + sin(angle) * point.z;
			point.z = cos(angle) * point.z - sin(angle) * y;
		}
	}
	void rotateY(const double angle)
	{
		for (Point& point : coord)
		{
			double x = point.x;

			point.x = cos(angle) * x + sin(angle) * point.z;
			point.z = cos(angle) * point.z - sin(angle) * x;
		}
	}
	void rotateZ(const double angle)
	{
		for (Point& point : coord)
		{
			double x = point.x;

			point.x = cos(angle) * x + sin(angle) * point.y;
			point.y = cos(angle) * point.y - sin(angle) * x;
		}
	}

	void draw() const
	{
		// Front face
		draw_line(coord[0], coord[1]);
		draw_line(coord[0], coord[3]);
		draw_line(coord[1], coord[2]);
		draw_line(coord[2], coord[3]);

		// Back face
		draw_line(coord[4], coord[5]);
		draw_line(coord[4], coord[7]);
		draw_line(coord[5], coord[6]);
		draw_line(coord[6], coord[7]);

		// bound lines
		draw_line(coord[0], coord[4]);
		draw_line(coord[1], coord[5]);
		draw_line(coord[2], coord[6]);
		draw_line(coord[3], coord[7]);
	}
};