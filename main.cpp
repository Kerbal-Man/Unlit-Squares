#include <iostream>
#include <string>
#include <vector>
#include "raylib.h"
using namespace std;
constexpr auto tileCountX = 7;
constexpr auto tileCountY = 5;
constexpr auto tileSize = (960 / (tileCountX + 2));

struct gridObj {
	bool tiles[tileCountX][tileCountY];
	const Color lit = RED;       //todo: texture
	const Color unlit = GREEN;  //todo: texture
};

int main(void) {

	const int width = (tileCountX + 2) * tileSize;
	const int height = (tileCountY + 2) * tileSize;
	string title = "Unlit Squares";
	SetConfigFlags(FLAG_MSAA_4X_HINT);
	InitWindow(width, height, title.c_str());

	gridObj grid;

	for (int y = 0; y < tileCountY; y++) {
		for (int x = 0; x < tileCountX; x++) {
			grid.tiles[x][y] = 0;
		}
	}

	while (!WindowShouldClose()) {

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			for (int y = 0; y < tileCountY; y++) {
				for (int x = 0; x < tileCountX; x++)
				{
					if (CheckCollisionPointRec(GetMousePosition(), { (float)(x + 1) * tileSize, (float)(y + 1) * tileSize, tileSize, tileSize })) {
						grid.tiles[x][y] = !grid.tiles[x][y];
						if (x + 1 <= tileCountX - 1) grid.tiles[x + 1][y] = !grid.tiles[x + 1][y];
						if (y + 1 <= tileCountY - 1) grid.tiles[x][y + 1] = !grid.tiles[x][y + 1];
						if (x - 1 >= 0)            grid.tiles[x - 1][y] = !grid.tiles[x - 1][y];
						if (y - 1 >= 0)            grid.tiles[x][y - 1] = !grid.tiles[x][y - 1];
					}
				}
			}
		}

		BeginDrawing();
		ClearBackground(BLACK);
		DrawFPS(15, 15);
		for (int y = 0; y < tileCountY; y++) {
			for (int x = 0; x < tileCountX; x++)
			{
				if (! grid.tiles[x][y]) { //this is lit
					DrawRectangle((x + 1) * tileSize, (y + 1) * tileSize, tileSize, tileSize, grid.lit);
				}
				else {
					DrawRectangle((x + 1) * tileSize, (y + 1) * tileSize, tileSize, tileSize, grid.unlit);
				}
			}
		}
		EndDrawing();
	}
	CloseWindow();
}
