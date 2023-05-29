#include "app.h"

void draw_origin(){
	glLineWidth(3);
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(2, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 2, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 2);

    glEnd();
}

void initApp(App* app, unsigned int width, unsigned int height){
	int error_code;
	app->need_run = false;
   	error_code = SDL_Init(SDL_INIT_EVERYTHING);
  	if (error_code != 0) {
    	printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
    	exit(0);
  	}

  	app->window = SDL_CreateWindow(
    	"OpenGL Exercise",
    	SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    	width, height,
    	SDL_WINDOW_OPENGL
    );

  	app->gl_context = SDL_GL_CreateContext(app->window);

  	initOpenGl(app, width, height);
  	initCamera(&app->camera, &app->scene);
  	initScene(&app->scene, 100, 100, 100, vcube, faces);
    fillGrid(&app->scene, 10, 2);

    app->need_run = true;
}

void initOpenGl(App* app, unsigned int width, unsigned int height){
	glViewport(0, 0, width, height);

  	glClearColor(0, 0, 0, 1);
  	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  	glEnable(GL_DEPTH_TEST);
  	glEnable(GL_CULL_FACE);

  	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 1, 100);

    app->prevTime = SDL_GetTicks();
    app->elapsedTime = 0;
    app->currentTime = 0;
}

void handleEvents(App* app){
  	static bool is_mouse_down = false;
  	static int currentx;
  	static int currenty;
  	int x;
  	int y;
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
       	switch (event.type) {
       	case SDL_KEYDOWN:
           	switch (event.key.keysym.scancode) {
           		case SDL_SCANCODE_ESCAPE: app->need_run = false; break;
                //case SDL_SCANCODE_S: updateScene(&elapsedTime, &prevTime, &currentTime, &scene); break;
                case SDL_SCANCODE_R: fillGrid(&app->scene, 1, 5); break;
                case SDL_SCANCODE_C: clearGrid(&app->scene); break;
                case SDL_SCANCODE_N: app->scene.neighbourCount = VN; break;
                case SDL_SCANCODE_M: app->scene.neighbourCount = M; break;
           		default: break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
	        is_mouse_down = true;
	        SDL_GetMouseState(&currentx, &currenty);
	        break;
	    case SDL_MOUSEMOTION:
	        SDL_GetMouseState(&x, &y);
	        if (is_mouse_down) {
	           	app->camera.degY += (double)(currenty - y)/5;
	           	if(app->camera.degY >= 80) setRotationY(&app->camera, 80);
	           	if(app->camera.degY <= -80) setRotationY(&app->camera, 80);

	            	app->camera.degX += (double)(currentx - x)/5;
	            	currentx = x;
	            	currenty = y;
	        }
	        break;
	    case SDL_MOUSEWHEEL:
	      	app->camera.scaleRatio += (double)event.wheel.y/(10*(1/app->camera.scaleRatio));
	       	if(app->camera.scaleRatio >= 1) setScale(&app->camera, 1);
	       	if(app->camera.scaleRatio <= 0.5/app->camera.maxZoom) setScale(&app->camera, 0.5/app->camera.maxZoom);
	       	break;
	    case SDL_MOUSEBUTTONUP:
	        is_mouse_down = false;
	        break;
	    case SDL_QUIT:
          	app->need_run = false;
           	break;
        default:
          	break;
        }
    }
}

void renderApp(App* app){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
  // Update camera
    updateCamera(&app->scene, &app->camera);

  //Update scene
    updateScene(&app->elapsedTime, &app->prevTime, &app->currentTime, &app->scene);

    //Render scene
  	draw_origin();
    drawBorder(&app->scene, vcube, faces);
    renderGrid(&app->scene);
    glPopMatrix();
    SDL_GL_SwapWindow(app->window);
}


void destroyApp(App* app){
	deleteScene(&app->scene);
  	SDL_GL_DeleteContext(app->gl_context);
 	SDL_DestroyWindow(app->window);
  	SDL_Quit();
}