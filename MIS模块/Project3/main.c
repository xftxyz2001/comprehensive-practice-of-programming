#include "store.h"
#include "menu.h"

int main(int argc, char const *argv[])
{
    initStore();

    mainMenu();

    destroyStore();
    return 0;
}
