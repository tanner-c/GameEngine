#include "app.h"
#include <iostream>

using namespace Game;

int main(int argc, char* argv[]) {
  App &app = App::instance();

  if (argc > 0) {
    App::instance().programArgs(argc, argv);
  }

  app.begin();

  while (app.isActive()) {
    app.tick();
    app.render();
  }
}