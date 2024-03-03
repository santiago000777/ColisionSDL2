#include "common.h"
#include "SDL.h"

/* 
	1. "Solution Platforms" -> x64
*/

//#define PressedKey(s)	GetAsyncKeyState(toupper(s) )

//#define PressedKey(s) ((GetAsyncKeyState(s) & 0x80000000) ? 1 : 0)
//bool PressedKey(int Key) {
//
///*	short i;
//	i = GetAsyncKeyState(Key);
//	if ((i & (short)0x8000) != 0) {
//		return true;
//	}
//	else {
//		return false;
//	}
//	i++;*/
//	return 0;
//}

bool PressedKey(short key) {
	short i = GetAsyncKeyState(toupper(key));
	if ((i & 0x8000) == 0) {
		return false;
	}
	return true;
}
#define FPS		165

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

	const float deltaTime = 1000.0f / FPS;
	std::chrono::time_point<std::chrono::high_resolution_clock> first, second;
	std::chrono::milliseconds duration;


	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("TITLE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 1);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	TPosition gravity(0, 1);

	SDL_Rect *rect1 = new SDL_Rect();
	rect1->x = 30;
	rect1->y = 30;
	rect1->w = 30;
	rect1->h = 40;
	TPosition vec1(0, 0);


	SDL_Rect* rect2 = new SDL_Rect();
	/*rect2->x = 230;
	rect2->y = 230;
	rect2->w = 80;
	rect2->h = 140;*/
	rect2->x = 10;
	rect2->y = 550;
	rect2->w = 700;
	rect2->h = 10;
	TPosition vec2(0, 0);

	SDL_Event *e = new SDL_Event();
	bool end = false;

	first = std::chrono::high_resolution_clock::now();
	while (!end) {
		if (PressedKey(VK_SPACE))
			__debugbreak();
		if(PressedKey(VK_ESCAPE))
			end = true;

		Sleep(2);
		

		// Je stisknuta klavesa	
		vec1.x = 0;
		vec1.y = 0;

		vec2.x = 0;
		vec2.y = 0;

		
		if (PressedKey(VK_UP)) {
			vec1.y = -1;
		}
		else if (PressedKey(VK_DOWN)) {
			vec1.y = 1;
		}
		else if (PressedKey(VK_LEFT)) {
			vec1.x = -1;
		}
		else if (PressedKey(VK_RIGHT)) {
			vec1.x = 1;
		}
		//vec1 = vec1 + gravity;
		

		
		if (PressedKey('w')) {
			vec2.y = -1;
		}
		else if (PressedKey('s')) {
			vec2.y = 1;
		}
		else if (PressedKey('a')) {
			vec2.x = -1;
		}
		else if (PressedKey('d')) {
			vec2.x = 1;
		}
		

		

		Posun(rect1, &vec1, rect2, &vec2);
		Posun(rect2, &vec2, rect1, &vec1);

		duration = std::chrono::duration_cast<std::chrono::milliseconds>(second - first);

		if (duration.count() >= deltaTime) {
			first = std::chrono::high_resolution_clock::now();

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);
			SDL_RenderPresent(renderer);


			SDL_RenderClear(renderer);

			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
			SDL_RenderFillRect(renderer, rect1);
			SDL_SetRenderDrawColor(renderer, 127, 255, 255, 255);
			SDL_RenderFillRect(renderer, rect2);

			SDL_RenderPresent(renderer);
		}
		second = std::chrono::high_resolution_clock::now();
		
	}

	return 0;
}
