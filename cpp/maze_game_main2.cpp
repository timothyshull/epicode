#include "magic_maze_game2.h"
#include "maze_game2.h"
#include "ordinary_maze_game2.h"

int main(int argc, char* argv[])
{
    // @include
    MazeGame* ordinaryMazeGame =
            (new OrdinaryMazeGameCreator())->FactoryMethod();
    MazeGame* magicMazeGame = (new MagicMazeGameCreator())->FactoryMethod();
    // @exclude
    return 0;
}
