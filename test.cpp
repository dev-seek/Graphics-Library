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

#define STB_IMAGE_IMPLEMENTATION
#include "./stb/stb_image.h"

#pragma GCC diagnostic pop


#define BACKGROUND_COLOR 0xFF202020
#define RED_COLOR 0xFF2020AA
#define GREEN_COLOR 0xFF20AA20
#define BLUE_COLOR 0xFFAA2020
#define ERROR_COLOR 0xFFFF00FF

#define return_defer(value) do{result = (value); goto defer;}while(0)

#define UNIMPLEMENTED(message) do{std::cout <<stderr<<" "<< __FILE__ << " : " << __LINE__ <<" "<< message <<std::endl; exit(1);}while(0)
#define UNREACHABLE(message) do{std::cout << stderr <<" "<<__FILE__ << " : " << __LINE__ <<" "<<message <<std::endl; exit(1);}while(0)

static uint32_t  pixels[HEIGHT*WIDTH];

char hexchar(uint8_t x)
{
    if (x < 10) return x + '0';
    if (10 <= x && x < 16) return x - 10 + 'A';
    UNREACHABLE("hexchar");
}

const char *display_hexcolor(uint32_t c)
{
    static char buffer[1 + 8 + 1];
    buffer[0] = '#';
    buffer[1] = hexchar((c>>(1*4))&0xF);
    buffer[2] = hexchar((c>>(0*4))&0xF);
    buffer[3] = hexchar((c>>(3*4))&0xF);
    buffer[4] = hexchar((c>>(2*4))&0xF);
    buffer[5] = hexchar((c>>(5*4))&0xF);
    buffer[6] = hexchar((c>>(4*4))&0xF);
    buffer[7] = hexchar((c>>(7*4))&0xF);
    buffer[8] = hexchar((c>>(6*4))&0xF);
    buffer[9] = '\0';
    return buffer;
}

bool check_test_case_again(const char *filename){
	if(!stbi_write_png(filename, WIDTH, HEIGHT, 4, pixels, WIDTH*4)){
		std::cout << stderr << " Failed to write image: " << filename << std::endl;
		return false;
	}
	std::cout << " File Generated " << filename << std::endl;
	return true;
}

bool check_test_case(const char *programe_name , const char *actual_filename , const char *failed_filename){
	uint32_t *expected_pixels = NULL;
	bool result = true;
	{
	int expected_width , expected_height ;
	expected_pixels = (uint32_t *)stbi_load(actual_filename, &expected_width, &expected_height, NULL, 4);
	if(expected_pixels == NULL){
		std::cout<< stderr << " could not able to read file : " << actual_filename<<" "<< strerror(errno) <<std::endl;
		if(errno == ENOENT){
			std::cout << "consider to make the " << actual_filename << " by doing "<<programe_name<<" record "<< std::endl;
		}
		return_defer(false);
	}
	if(expected_width != WIDTH || expected_height != HEIGHT){
		std::cout << stderr << " Expected image size is " << WIDTH << " x " << HEIGHT << " but got " << expected_width << " x " << expected_height << std::endl;
		return_defer(false);
	}

	bool failed = false;
	for(int i = 0; i < HEIGHT; i++){
		for(int j = 0; j < WIDTH; j++){
			if(pixels[i*WIDTH + j] != expected_pixels[i*WIDTH + j]){
				failed = true;
				pixels[i*WIDTH + j] = ERROR_COLOR;
			}
		}
	}

	if(failed){
		if(!stbi_write_png(failed_filename, WIDTH, HEIGHT, 4, pixels, WIDTH*4)){
			std::cout << stderr << " Failed to generate image: " << failed_filename << std::endl;
			return_defer(false);
		}
		else{
			std::cout<<stderr<<" "<<actual_filename<<" : HINT : see difference in "<<failed_filename<<" for more info "<<" The pixels with color "<<display_hexcolor(ERROR_COLOR)<<" are the once that differ from the expected ones "<<std::endl;
			std::cout<<stderr<<" "<<actual_filename<<" HINT : if the changes is intentional consider to make the "<<actual_filename<<" by doing "<<programe_name<<" record "<<std::endl;
		}

		return_defer(false);
	}
		std::cout<<actual_filename<<" : PASSED"<<std::endl;
}

	defer:
	if(expected_pixels != NULL){
		stbi_image_free(expected_pixels);
	}
	return result;
}

typedef struct{
	void (*run)(void);
	/* void (*generate_actual_pixel)(void); */
	/* const char *expected_filename ; */
	const char *actual_filename ;
	const char *failed_filename ;
}test_case;

#define DEFINE_TEST_CASE(name)\
{\
	.run = name,\
	/* .generate_actual_pixel = name, */ \
	/* .expected_filename = #name "_expected.png",\ */ \
	.actual_filename = #name "_actual.png",\
	.failed_filename = #name "_failed.png",\
}

void test_fill_rect(void){
	vugl_fill_color(pixels,BACKGROUND_COLOR,HEIGHT,WIDTH);
	vugl_fill_rect(pixels,GREEN_COLOR,HEIGHT,WIDTH,WIDTH/2-WIDTH/8,HEIGHT/2-HEIGHT/8,HEIGHT/4,WIDTH/4);
}

void test_fill_circle(void){
	vugl_fill_color(pixels,BACKGROUND_COLOR,HEIGHT,WIDTH);
	vugl_fill_circle(pixels,RED_COLOR,HEIGHT,WIDTH,WIDTH/2,HEIGHT/2,50);
}

void test_fill_triangle(void){
	vugl_fill_color(pixels,BACKGROUND_COLOR,HEIGHT,WIDTH);
		/* vugl_fill_triangle(pixels,0xff2020ff,HEIGHT,WIDTH, WIDTH/2, WIDTH/2, WIDTH/3, HEIGHT/2, HEIGHT/4, HEIGHT/8); */
	int x1 = WIDTH/2;
	int y1 = HEIGHT/8;
	int x2 = WIDTH/8;
	int y2 = HEIGHT/2;
	int x3 = WIDTH*7/8;
	int y3 = HEIGHT*7/8;
	/* rotate(&x1,&y1); */
	/* rotate(&x2,&y2); */
	/* rotate(&x3,&y3); */
	vugl_fill_circle(pixels,0xff2020ff,HEIGHT,WIDTH,x1,y1,10);
	vugl_fill_circle(pixels,0xff2020ff,HEIGHT,WIDTH, x2, y2,10); 
	vugl_fill_circle(pixels,0xff2020ff,HEIGHT,WIDTH, x3, y3,10);
	/* vugl_fill_triangle(pixels,0xff2020ff,HEIGHT,WIDTH, WIDTH/2, WIDTH/4, WIDTH/3, HEIGHT/2, HEIGHT/4, HEIGHT/8); */
	
	vugl_fill_triangle(pixels,0xff2020ff,HEIGHT,WIDTH, x1 , x2 ,x3, y1, y2 , y3);

}

void test_draw_line(void){
	vugl_fill_color(pixels,BACKGROUND_COLOR,HEIGHT,WIDTH);
	vugl_fill_line(pixels , 0xff2020ff , HEIGHT , WIDTH , 0 , WIDTH-1 , 0 ,HEIGHT-1);
	vugl_fill_line(pixels , 0xff2020ff , HEIGHT , WIDTH , WIDTH , 0 , 0 ,HEIGHT-1);
	vugl_fill_line(pixels , 0xff2020ff , HEIGHT , WIDTH , 0 , WIDTH/2 , WIDTH/2 ,HEIGHT-1);
}

// typedef struct {
//   Red_color ;
//   Greeen_color ;
//   Blue_color ;
// }color_comps;

//c1+(c2-c1)*a/255 ;

// void unpack_color(uint32_t c1){
//   color_comps.Red_color = (c1>>16)&0xFF ;
//   color_comps.Greeen_color = (c1>>24)&0xFF ;
//   color_comps.Blue_color = (c1>>32)&0xFF ;
// }

void test_alpha_blending(void){
	vugl_fill_color(pixels,BACKGROUND_COLOR,HEIGHT,WIDTH);
	vugl_fill_rect(pixels,GREEN_COLOR,HEIGHT,WIDTH,0,0,HEIGHT*3/4,WIDTH*3/4);
	vugl_fill_rect(pixels,0xAA0000AA,HEIGHT,WIDTH,WIDTH*3/8,HEIGHT*3/8,HEIGHT*3/4,WIDTH*3/4);
  vugl_fill_triangle(pixels,0xff2020ff,HEIGHT,WIDTH, WIDTH/2, WIDTH/2, WIDTH/3, HEIGHT/2, HEIGHT/4, HEIGHT/8);
  vugl_fill_circle(pixels,0xccff0000,HEIGHT,WIDTH, WIDTH/3, HEIGHT/8,100); //blue
  }

test_case TEST_CASES[] = {
	DEFINE_TEST_CASE(test_fill_rect),
	DEFINE_TEST_CASE(test_fill_circle),
	DEFINE_TEST_CASE(test_fill_triangle),
	DEFINE_TEST_CASE(test_draw_line),
	DEFINE_TEST_CASE(test_alpha_blending)
};

#define TEST_CASE_COUNT (sizeof(TEST_CASES)/sizeof(TEST_CASES[0]))

int main(int argc , char **argv){
	assert(argc >=1);
    const char *programe_name = argv[0];
	bool record = (argc >=2 && strcmp(argv[1], "record") == 0);
	for(int i = 0;(uint32_t)i < TEST_CASE_COUNT; i++){
		test_case *test = &TEST_CASES[i];
		/* test->generate_actual_pixel(); */
		test->run();
		if(record){
			if(!check_test_case_again(test->actual_filename)){
				return 1;
			}
		}
		else{
			if(!check_test_case(programe_name,test->actual_filename,test->failed_filename)){
				return 1;
			}
		}
	}

	return 0;
}







