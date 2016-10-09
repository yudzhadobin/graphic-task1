#include "Graphics.h";

void activePixel(Brush^ brush,Bitmap^ bm, int x, int y) {
	Graphics ^im = Graphics::FromImage(bm);
	im->FillRectangle(brush, x, y, 2, 2);
}

void drawLineWithBrezenhem(Brush^ brush, Bitmap^ bm, int start_x, int start_y, int end_x, int end_y) {
		int cur_x = start_x;
		int cur_y = start_y;
		int delta_x = std::abs(end_x - start_x);
		int delta_y = std::abs(end_y - start_y);
		int s1 = (end_x - start_x) > 0 ? 1 : -1;
		int s2 = (end_y - start_y) > 0 ? 1 : -1;

		bool was_swap;
		if (was_swap = delta_y > delta_x) {
			int sub = delta_x;
			delta_x = delta_y;
			delta_y = sub;
		}

		int error = 2 * delta_y - delta_x;
		int i = 1;
		while (i <= delta_x)
		{
			activePixel(brush, bm, cur_x, cur_y);

			if (error >= 0) {
				if (was_swap) {
					cur_x = cur_x + s1;
				}
				else {
					cur_y = cur_y + s2;
				}
				error = error - 2 * delta_x;
			}
			else {
				if (!was_swap) {
					cur_x = cur_x + s1;
				}
				else {
					cur_y = cur_y + s2;
				}
				error += 2 * delta_y;
				i += 1;
			}
		}
	}

void drawCircule(Brush^ brush, Bitmap^ bm, int start_x, int start_y, int radius) {
		int cur_x = 0;
		int cur_y = radius;
		int delta = 2 * (1 - radius);
		int limit = 0;
		while (true) {
			activePixel(brush, bm, start_x + cur_x, start_y + cur_y);
			activePixel(brush, bm, start_x + cur_x, start_y - cur_y);
			activePixel(brush, bm, start_x - cur_x, start_y + cur_y);
			activePixel(brush, bm, start_x - cur_x, start_y - cur_y);
			if (cur_y <= 0) break;

			if (delta >= 0) {
				if (delta > 0) {
					int gamma = 2 * delta - 2 * cur_x - 1;
					if (gamma <= 0) {
						cur_x += 1;
						cur_y -= 1;
						delta += 2 * cur_x - 2 * cur_y + 2;
					}
					else {
						cur_y -= 1;
						delta -= 2 * cur_y + 1;
					}

				}
				else {
					cur_x += 1;
					cur_y -= 1;
					delta += 2 * cur_x - 2 * cur_y + 2;
				}
			}
			else {
				int gamma = 2 * delta + 2 * cur_y - 1;
				if (gamma <= 0) {
					cur_x += 1;
					delta += 2 * cur_x + 1;
				}
				else {
					cur_x += 1;
					cur_y -= 1;
					delta += 2 * cur_x - 2 * cur_y + 2;
				}
			}
		}
	}

void drawElipse(Brush^ brush, Bitmap^ bm, int start_x, int start_y, int a, int b) {
		int cur_y = b;
		int cur_x = 0;
		int b2 = b*b;
		int a2 = a*a;

		int delta = 0;
		int gamma = 0;
		while (true)
		{
			if (cur_y < 0) {
				break;
			}
			activePixel(brush, bm, start_x + cur_x, start_y + cur_y);
			activePixel(brush, bm, start_x + cur_x, start_y - cur_y);
			activePixel(brush, bm, start_x - cur_x, start_y + cur_y);
			activePixel(brush, bm, start_x - cur_x, start_y - cur_y);
			int i = 2 * Math::Pow((cur_x + 1), 2) + a2 * Math::Pow((cur_y - 1), 2);
			int j = a2*b2;
			delta = b2 * Math::Pow((cur_x + 1), 2) + a2 * Math::Pow((cur_y - 1), 2) - a2*b2;

			if (delta >= 0) {// Выбираем между (x, y-1) и (x+1, y-1)
				gamma = b2 * Math::Pow((2 * cur_x - 1), 2) + a2 * Math::Pow((2 * cur_y + 2), 2) - 4 * a2*b2;
				if (gamma <= 0) { //Выбираем (x + 1, y-1)
					cur_y--;
					cur_x++;
				}
				else { //Выбираем (x, y -1)
					cur_y--;
				}
			}
			else { // Выбираем между (x + 1, y) и (x + 1, y - 1)
				gamma = b2 * Math::Pow((2 * cur_x + 2), 2) + a2 * Math::Pow((2 * cur_y - 1), 2) - 4 * a2*b2;
				if (gamma < 0) { //Выбираем (x + 1, y)
					cur_x++;
				}
				else { //Выбираем (x + 1, y-1)
					cur_y--;
					cur_x++;
				}
			}
		}
	}