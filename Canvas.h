#pragma once

#include <vector>
#include "common.h"

struct Point{
	float position[2];
	float color[3];
};

class Canvas {
public:
	std::vector<Point> points;

	Canvas() {
		for (int index_y = 0; index_y < WINDOW_HEIGHT; index_y++)
			for (int index_x = 0; index_x < WINDOW_WIDTH; index_x++)
				points.push_back({
					{windowCoordToPixel(index_x, xCoord), windowCoordToPixel(index_y, yCoord)},
					{DEF_COLOR_R, DEF_COLOR_G, DEF_COLOR_B}
					});
	}
	
    
	void drawBetween(int x1, int y1, int x2, int y2, float color_R, float color_G, float color_B, int size) {
		int dx = abs(x2 - x1);
		int dy = abs(y2 - y1);
        int firstPixelIndex = getIndexOfWindowPos(x1, y1);

        if (dx > dy)
            plotPixel(x1, y1, x2, y2, dx, dy, 0, color_R, color_G, color_B, size);
        else
            plotPixel(y1, x1, y2, x2, dy, dx, 1, color_R, color_G, color_B, size);

	}
	
    void plotPixel(int x1, int y1, int x2, int y2, int dx, int dy, int decide, float color_R, float color_G, float color_B, int size)
    {
        int pk = 2 * dy - dx;
        for (int i = 0; i <= dx; i++) {
            x1 < x2 ? x1++ : x1--;
            if (pk < 0) {
                if (decide == 0)
                    drawPixel(x1, y1, color_R, color_G, color_B, size);
                else
                    drawPixel(y1, x1, color_R, color_G, color_B, size);
                pk = pk + 2 * dy;
            }
            else {
                y1 < y2 ? y1++ : y1--;
                if (decide == 0)
                    drawPixel(x1, y1, color_R, color_G, color_B, size);
                else
                    drawPixel(y1, x1, color_R, color_G, color_B, size);
                pk = pk + 2 * dy - 2 * dx;
            }
        }
    }

    void drawPixel(int xpos, int ypos, float color_R, float color_G, float color_B, int size) {
        // https://stackoverflow.com/questions/1201200/fast-algorithm-for-drawing-filled-circles
        // Peut etre considerer a utiliser une variante du (Bresenhamís circle drawing algorithm) for filled circle...
        // Algorithme brute force:
        for (int y = -size; y <= size; y++)
            for (int x = -size; x <= size; x++)
                if (x * x + y * y <= size * size) {
                    int index = getIndexOfWindowPos(xpos+x, ypos+y);
                    points[index].color[0] = color_R;
                    points[index].color[1] = color_G;
                    points[index].color[2] = color_B;
                }
    }

	int getIndexOfWindowPos(int xpos, int ypos) {return ypos * WINDOW_WIDTH + xpos;}
};