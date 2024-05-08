#define WIDTH 800
#define HEIGHT 600

#include "vugl.cpp"

/* float sqrtf(float x); */
/* float sinf(float x); */
/* float cosf(float x); */
/* float atan2f(float y, float x); */

//p1(acos , bson) a = height/2 b = width/2
float rotation = 0.0;

uint32_t pixels[WIDTH * HEIGHT];

/* void rotate(int *x , int *y){ */
/* 	int dx = *x - WIDTH/2; */
/* 	int dy = *y - HEIGHT/2; */
/* 	float magnitude = sqrtf(dx*dx + dy*dy); */
/* 	float angle = atan2f(dy,dx)+rotation; */
/* 	*x = WIDTH/2 + magnitude*cosf(angle); */
/* 	*y = HEIGHT/2 + magnitude*sinf(angle); */
/* } */

uint32_t* render() {
	/* rotation += (3.14159265358979323846*time)/10; */
	vugl_fill_color(pixels,0xFF202020 ,HEIGHT,WIDTH);
	{
	vugl_fill_circle(pixels,0xff2020ff,HEIGHT,WIDTH, WIDTH/2, HEIGHT/2,10);
	vugl_fill_circle(pixels,0xff2020ff,HEIGHT,WIDTH, WIDTH/2, HEIGHT/4,10); 
	vugl_fill_circle(pixels,0xff2020ff,HEIGHT,WIDTH, WIDTH/3, HEIGHT/8,10); 
	vugl_fill_triangle(pixels,0xff2020ff,HEIGHT,WIDTH, WIDTH/2, WIDTH/4, WIDTH/3, HEIGHT/2, HEIGHT/4, HEIGHT/8);
	
	/* /1* int x1 = WIDTH/2; *1/ */
	/* /1* int y1 = HEIGHT/8; *1/ */
	/* /1* int x2 = WIDTH/8; *1/ */
	/* /1* int y2 = HEIGHT/2; *1/ */
	/* /1* int x3 = WIDTH*7/8; *1/ */
	/* /1* int y3 = HEIGHT*7/8; *1/ */
	/* /1* rotate(&x1,&y1); *1/ */
	/* /1* rotate(&x2,&y2); *1/ */
	/* /1* rotate(&x3,&y3); *1/ */
	/* vugl_fill_circle(pixels,0xff2020ff,HEIGHT,WIDTH,x1,y1,10); */
	/* vugl_fill_circle(pixels,0xff2020ff,HEIGHT,WIDTH, x2, y2,10); */ 
	/* vugl_fill_circle(pixels,0xff2020ff,HEIGHT,WIDTH, x3, y3,10); */
	/* /1* vugl_fill_triangle(pixels,0xff2020ff,HEIGHT,WIDTH, WIDTH/2, WIDTH/4, WIDTH/3, HEIGHT/2, HEIGHT/4, HEIGHT/8); *1/ */
	
	/* vugl_fill_triangle(pixels,0xff2020ff,HEIGHT,WIDTH, x1 , x2 ,x3, y1, y2 , y3); */
	}
	return pixels;
}

