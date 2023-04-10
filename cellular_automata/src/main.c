
#include "camera.h"
#include "app.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
int main(int argc, char* argv[]) {
  	#pragma GCC diagnostic pop
    #pragma GCC diagnostic ignored "-Wunused-variable"

    App app;

    initApp(&app, 800, 800);
    while(app.need_run){
        handleEvents(&app);
        renderApp(&app);
    }
    destroyApp(&app);

  	return 0;
}
