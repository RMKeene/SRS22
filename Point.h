#pragma once
namespace SRS22 {

	class Point {
	public:
		int X;
		int Y;

		Point() : X(0), Y(0) {}
		Point(int x, int y) : X(x), Y(y) {}

		int DistSquared(Point& p) {
			return p.X * p.X + p.Y * p.Y;
		}

		int DistSquared(Point& p, Point& other) {
			const int dx = p.X - other.X;
			const int dy = p.Y - other.Y;
			return dx * dx + dy * dy;
		}

		int Dist(Point& p) {
			return (int)sqrtf(p.X * p.X + p.Y * p.Y);
		}

		int Dist(Point& p, Point& other) {
			const int dx = p.X - other.X;
			const int dy = p.Y - other.Y;
			return (int)sqrtf(dx * dx + dy * dy);
		}

		int manhattanDist(Point& p) {
			const int dx = p.X < 0 ? -p.X : p.X;
			const int dy = p.Y < 0 ? -p.Y : p.Y;
			return dx + dy;
		}

		int manhattanDist(Point& p, Point& other) {
			const int dx = p.X - other.X;
			const int dy = p.Y - other.Y;
			const int adx = dx < 0 ? -dx : dx;
			const int ady = dy < 0 ? -dy : dy;
			return adx + ady;
		}
	};
}