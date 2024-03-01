#include "common.h"
#include "SDL.h"

/* 
	1. "Solution Platforms" -> x64
*/

#define PressedKey(s)	GetAsyncKeyState(toupper(s))

struct TPosition {
public:
	int x, y;

	TPosition(int x, int y) {
		this->x = x;
		this->y = y;
	}

	TPosition operator+(const TPosition& p) const {
		return {this->x + p.x, this->y + p.y};
	}

	TPosition operator-(const TPosition& p) const {
		return { this->x - p.x, this->y - p.y };
	}
};

void Posun(SDL_Rect *rect1, TPosition *posun1, SDL_Rect* rect2, TPosition* posun2) {
	
	if((rect1->x + posun1->x + rect1->w > rect2->x && rect1->x + posun1->x < rect2->x + rect2->w)
		&& (rect1->y + posun1->y + rect1->h > rect2->y && rect1->y + posun1->y < rect2->y + rect2->h)) {
		
		if (posun1->x > 0 && posun2->x > 0) {
			posun1->x = rect2->x + posun2->x - (rect1->x + rect1->w);
		}
		else if (posun1->x < 0 && posun2->x < 0) {
			posun1->x = rect1->x - posun2->x - (rect2->x + rect2->w);
			posun1->x *= -1;
		}
		else if (posun1->y > 0 && posun2->y > 0) {
			posun1->y = rect2->y + posun2->y - (rect1->y + rect1->h);
		}
		else if (posun1->y < 0 && posun2->y < 0) {
			posun1->y = rect1->y - posun2->y - (rect2->y + rect2->h);
			posun1->y *= -1;
		}
		else if (posun1->x > 0) {
			posun1->x = rect2->x - (rect1->x + rect1->w);
		}
		else if (posun1->x < 0) {
			posun1->x = rect1->x - (rect2->x + rect2->w);
			posun1->x *= -1;
		}
		else if (posun1->y > 0) {
			posun1->y = rect2->y - (rect1->y + rect1->h);
		}
		else if (posun1->y < 0) {
			posun1->y = rect1->y - (rect2->y + rect2->h);
			posun1->y *= -1;
		}
	}

	rect1->x += posun1->x;
	rect1->y += posun1->y;

}


int main(int argc, char* args[]) {

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("TITLE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 1);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	SDL_Rect *rect1 = new SDL_Rect();
	rect1->x = 30;
	rect1->y = 30;
	rect1->w = 30;
	rect1->h = 40;
	TPosition vec1(0, 0);


	SDL_Rect* rect2 = new SDL_Rect();
	rect2->x = 230;
	rect2->y = 230;
	rect2->w = 80;
	rect2->h = 140;
	TPosition vec2(0, 0);

	SDL_Event *e = new SDL_Event();
	bool end = false;
	while (!end) {
		while (SDL_PollEvent(e)) {
			if(e->type == SDL_QUIT)
				end = true;
			else if (e->type == SDL_KEYDOWN) {

				vec1.x = 0;
				vec1.y = 0;

				vec2.x = 0;
				vec2.y = 0;

				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderClear(renderer);
				SDL_RenderPresent(renderer);

				if (PressedKey(VK_UP)) {
					vec1.y = -13;
				}
				else if (PressedKey(VK_DOWN)) {
					vec1.y = 13;
				}
				else if (PressedKey(VK_LEFT)) {
					vec1.x = -13;
				}
				else if (PressedKey(VK_RIGHT)) {
					vec1.x = 13;
				}
				

				if (PressedKey('w')) {
					vec2.y = -6;
				}
				else if (PressedKey('s')) {
					vec2.y = 6;
				}
				else if (PressedKey('a')) {
					vec2.x = -6;
				}
				else if (PressedKey('d')) {
					vec2.x = 6;
				}
				
				if(PressedKey(VK_SPACE))
					__debugbreak();

				Posun(rect1, &vec1, rect2, &vec2);
				Posun(rect2, &vec2, rect1, &vec1);

				SDL_RenderClear(renderer);

				SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
				SDL_RenderFillRect(renderer, rect1);
				SDL_SetRenderDrawColor(renderer, 127, 255, 255, 255);
				SDL_RenderFillRect(renderer, rect2);

				SDL_RenderPresent(renderer);
				
			}
			
		}
	}

	return 0;
}
