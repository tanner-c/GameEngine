#include "app.h"
#include <iostream>

using namespace Game;

int main() {
  App &app = App::instance();
  app.begin();

  while (app.isActive()) {
    app.tick();
    app.render();
  }
}