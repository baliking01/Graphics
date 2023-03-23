#include "ball.h"

#include <GL/gl.h>

#include <math.h>

void init_ball(Ball* ball, float x, float y)
{
    ball->x = x;
    ball->y = y;
    ball->radius = 10;
    ball->speed_x = 300;
    ball->speed_y = 300;
}

void update_ball(Ball* ball, double time)
{
    ball->x += ball->speed_x * time;
    ball->y += ball->speed_y * time;
}

void render_ball(Ball* ball)
{
    double angle;
    double x;
    double y;

    glPushMatrix();
    glTranslatef(ball->x, ball->y, 0.0);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0, 0.9, 0.8);
    glVertex2f(0, 0);
    angle = 0;
    while (angle < 2.0 * M_PI + 1) {
        x = cos(angle) * ball->radius;
        y = sin(angle) * ball->radius;
        glVertex2f(x, y);
        angle += 0.2;
    }
	
	/*double side_len = 10;
	int precision = 100;
	double tmpX = 0;
	double tmpY = 0;
	
	Point p = {}
	for(int i = 0; i < precision; i++){
		tmpX = p.x + side_len*cos(rotation*(M_PI/180));
		tmpY = p.y + side_len*sin(rotation*(M_PI/180));
		p.x = tmpX;
		p.y = tmpY;
		glVertex2f(x, y);
		rotation += deg;
	}*/
	
    glEnd();
    glPopMatrix();
}
