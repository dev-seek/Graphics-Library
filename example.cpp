#include <string.h>
#include <iostream>
#include <errno.h>
#include "vugl.cpp"

#define HEIGHT 600
#define WIDTH 800
#define ROWS 6
#define COLS 8
#define COL_HEIGHT (HEIGHT/ROWS)
#define COL_WIDTH (WIDTH/COLS)

#define BACKGROUND_COLOR 0xFF202020 

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./stb/stb_image_write.h"

#pragma GCC diagnostic pop

static uint32_t  pixels[HEIGHT*WIDTH];

bool triangle(void){
	vugl_fill_color(pixels,BACKGROUND_COLOR,HEIGHT,WIDTH);
	vugl_fill_circle(pixels,0xff0000ff,HEIGHT,WIDTH, WIDTH/2, HEIGHT/2,10); //Red
	vugl_fill_circle(pixels,0xff00ff00,HEIGHT,WIDTH, WIDTH/2, HEIGHT/4,10); //Green
	vugl_fill_circle(pixels,0xccff0000,HEIGHT,WIDTH, WIDTH/3, HEIGHT/8,10); //blue
	/* vugl_fill_triangle(pixels,0xff2020ff,HEIGHT,WIDTH, WIDTH/2, WIDTH/4, WIDTH/3, HEIGHT/2, HEIGHT/4, HEIGHT/8); */
	vugl_fill_triangle(pixels,0xff2020ff,HEIGHT,WIDTH, WIDTH/2, WIDTH/2, WIDTH/3, HEIGHT/2, HEIGHT/4, HEIGHT/8);

	const char * filename = "triangle.png";
	if (!stbi_write_png(filename, WIDTH , HEIGHT, 4, pixels, WIDTH*sizeof(uint32_t))) {
		std::cout<<stderr<< "ERROR: could not save file"<< filename << ":" << strerror(errno)<<std::endl;
        return false;
    }
	std::cout<<"GENERATED "<<filename<<std::endl;
	return true;
}


bool circle(void){
	vugl_fill_color(pixels,BACKGROUND_COLOR,HEIGHT,WIDTH);
	for(int i=1 ; i<ROWS-1 ; i++){
		for(int j=1 ; j<COLS-1 ; j++){
			size_t radius = COL_WIDTH;
			if(radius > COL_HEIGHT){
				radius = COL_HEIGHT;
			}
			vugl_fill_circle(pixels,0xff2020ff,HEIGHT,WIDTH, j*COL_WIDTH + COL_WIDTH/2, i*COL_HEIGHT + COL_HEIGHT/2,radius/2);
		}
	}


	const char * filename = "circle.png";
	if (!stbi_write_png(filename, WIDTH , HEIGHT, 4, pixels, WIDTH*sizeof(uint32_t))) {
		std::cout<<stderr<< "ERROR: could not save file"<< filename << ":" << strerror(errno)<<std::endl;
        return false;
    }
	std::cout<<"GENERATED "<<filename<<std::endl;
	return true;
}



bool line(void){
	
	vugl_fill_color(pixels,BACKGROUND_COLOR,HEIGHT,WIDTH);

	vugl_fill_line(pixels , 0xff2020ff , HEIGHT , WIDTH , 0 , WIDTH-1 , 0 ,HEIGHT-1);

	vugl_fill_line(pixels , 0xff2020ff , HEIGHT , WIDTH , WIDTH , 0 , 0 ,HEIGHT-1);
	vugl_fill_line(pixels , 0xff2020ff , HEIGHT , WIDTH , 0 , WIDTH/2 , WIDTH/2 ,HEIGHT-1);


	const char * filename = "line.png";
	if (!stbi_write_png(filename, WIDTH , HEIGHT, 4, pixels, WIDTH*sizeof(uint32_t))) {
		std::cout<<stderr<< "ERROR: could not save file"<< filename << ":" << strerror(errno)<<std::endl;
        return false;
    }
	std::cout<<"GENERATED "<<filename<<std::endl;
	return true;
}


bool rectangle(void){
	
	vugl_fill_color(pixels,BACKGROUND_COLOR,HEIGHT,WIDTH);
	for(int i=0 ; i<ROWS ; i++){
		for(int j=0 ; j<COLS ; j++){
			uint32_t color = BACKGROUND_COLOR;
			if((i+j)%2==0){
				color = 0xff2020ff;
			}
			vugl_fill_rect(pixels,color,HEIGHT,WIDTH,j*COL_WIDTH,i*COL_HEIGHT,COL_HEIGHT,COL_WIDTH);
		}
	}

	const char * filename = "rectangle.png";
	if (!stbi_write_png(filename, WIDTH , HEIGHT, 4, pixels, WIDTH*sizeof(uint32_t))) {
		std::cout<<stderr<< "ERROR: could not save file"<< filename << ":" << strerror(errno)<<std::endl;
        return false;
    }
	std::cout<<"GENERATED "<<filename<<std::endl;
	return true;

}

int main(void){
	if(!rectangle()){
		return -1;
	}

	if(!circle()){
		return -1;
	}

	if(!line()){
		return -1 ;
	}

	if(!triangle()){
		return -1 ;
	}


	return 0;
}
