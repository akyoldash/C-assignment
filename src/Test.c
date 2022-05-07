#include "Oyun.h"

int main()
{
	Oyun game = new_Oyun();

	game->start();

	game->delete(game);

	return 0;


}

