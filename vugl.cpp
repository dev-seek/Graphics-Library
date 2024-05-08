#ifndef VUGL_H
#define VUGL_H

#include <stdint.h>

typedef int Errno;

template <typename T>
void vugl_swap(T *a , T *b){
	T temp = *b ;
	*b = *a ;
	*a = temp ;
}

typedef enum  {
  Red_color = 0 ,
  Greeen_color ,
  Blue_color ,
  Alpha ,
  Count_comps ,
}color_comp ;

void unpack_color(uint32_t c , uint32_t comp[Count_comps]){
  for (int i = 0; i < Count_comps; i++){
    comp[i] = c&0xFF;
    c >>= 8 ;
  }
}

uint32_t pack_color(uint32_t comp[Count_comps]){
   uint32_t c = 0 ;
  for (int i = 0; i < Count_comps; i++) {
    c |= comp[i]<<(8*i);
  }
  return c ;
}

uint32_t mix_comp(uint32_t c1 , uint32_t c2 , uint32_t a){
   return c1+(c2-c1)*a/255;
}

uint32_t mix_color(uint32_t c1 , uint32_t c2 ){
  uint32_t comp1[Count_comps];
  unpack_color(c1 , comp1);
  uint32_t comp2[Count_comps];
  unpack_color(c2 , comp2);
  for (int i = 0; i < Alpha; i++) {
    comp1[i] = mix_comp(comp1[i] , comp2[i],comp2[Alpha]);
  } 
   return pack_color(comp1);
}

void vugl_fill_triangle(uint32_t *pixels , uint32_t color , int height , int width , int x1, int x2 , int x3 , int y1 , int y2 , int y3 )
{
	
	// i want to sort a point on the basis of y axis so that i can get the top point and bottom point
	
	if(y1>y2){
		vugl_swap<int>(&x1,&x2);
		vugl_swap<int>(&y1,&y2);
	}
	if(y1>y3){
		vugl_swap<int>(&x1,&x3);
		vugl_swap<int>(&y1,&y3);
	}
	if(y2>y3){
		vugl_swap<int>(&x2,&x3);
		vugl_swap<int>(&y2,&y3);
	}

	int c12 , c13 , c23 ;

	for(int y = y1 ; y<=y2 ; y++){
		if(y>=0 and y<=height){
			if(x1!=x2){
				 c12 = y1 - ((y2-y1)*x1)/(x2-x1);
				/* int x12 = ((y-c12)*(x2-x1))/(y2-y1); */
			}
			if(x3!=x1){
				 c13 = y1 - ((y3-y1)*x1)/(x3-x1);
				/* int x13 = ((y-c13)*(x3-x1))/(y3-y1); */
			}
			int x12 = (x1!=x2) ? ((y-c12)*(x2-x1))/(y2-y1) : x1;
			int x13 = (x3!=x1) ? ((y-c13)*(x3-x1))/(y3-y1) : x1;
			if(x12>x13){
				vugl_swap<int>(&x12,&x13);
			}
			for(int x = x12 ; x<=x13 ; x++){
				if(x>=0 and x<=width){
					pixels[y*width + x] = mix_color(pixels[y*width + x],color);				
        }
			}
		}
	}
	for(int y = y2 ; y<=y3 ; y++){
		if(y>=0 and y<=height){
			if(x2!=x3){
				 c23 = y2 - ((y3-y2)*x2)/(x3-x2);
				/* int x23 = ((y-c23)*(x3-x2))/(y3-y2); */
			}
			if(x1!=x3){
				 c13 = y1 - ((y3-y1)*x1)/(x3-x1);
				/* int x12 = ((y-c12)*(x2-x1))/(y2-y1); */
			}
			int x23 = (x2!=x3) ? ((y-c23)*(x3-x2))/(y3-y2) : x2;
			int x13 = (x1!=x3) ? ((y-c13)*(x3-x1))/(y3-y1) : x1;
			if(x13>x23){
				vugl_swap<int>(&x13,&x23);
			}
			for(int x = x13 ; x<=x23 ; x++){
				if(x>=0 and x<=width){
					pixels[y*width + x] = mix_color(pixels[y*width + x],color);			
        }
			}
		}
	}
}

void vugl_fill_line(uint32_t *pixels , uint32_t color , int height , int width , int x1 , int x2 , int y1 , int y2)
{
	int dy = y2-y1 ;
	int dx = x2-x1 ;
	// y = k*x+c ;
	
	if(dx!=0){
		int c = y1 - dy*x1/dx ;
		if(x1>x2) vugl_swap<int>(&x1 , &x2) ;
		for(int x = x1 ; x<=x2 ; x++){
			if(x>=0 and x<=width){
				if(y1>y2) vugl_swap<int>(&y1 , &y2) ;
				int y = dy*x/dx+c ;
				if(y>=0 and y<=height){
					pixels[y*width+x] = mix_color(pixels[y*width + x],color);
				}
			}
		}
	}

	else
	{

	// vertical line 
	if(x1>=0 and x1<=width){
		for(int y = y1 ; y<=y2 ; y++){
			if(y>=0 and y<=height){
				pixels[y*width+x1] = mix_color(pixels[y*width + x1],color);
			}
		}
	}


}
}

void vugl_fill_circle(uint32_t *pixels , uint32_t color , int pixel_height , int pixel_width , int cx , int cy , int r ){

	int x1 = cx-r ;
	int x2 = cx+r ;
	int y1 = cy-r ;
	int y2 = cy+r ;
	for(int i = x1 ; i<=x2 ; i++){
		if(i>=0 and i<=pixel_width){
			for(int j = y1 ; j<=y2 ; j++){

				if(j>=0 and j<=pixel_height){
					int dx = cx-i;
					int dy = cy-j;
					if(dx * dx + dy * dy <= r*r){
						pixels[j*pixel_width+i] = mix_color(pixels[j*pixel_width + i],color);
					}

				}

			}
		}

}
}

// RGBA 0xrrggbbaa how we read
// ABGR 0xaabbggrr how computer process 
// 0xRRGGBB 



void vugl_fill_rect(uint32_t *pixels,uint32_t color,int pixel_height,int pixel_width,int x0, int y0 , int rect_height , int rect_width){
	
	for(int i=0; i<rect_height; i++){
		int y = y0 + (int)i;
		if(0<=y and (int)y<pixel_height){
			for(int j=0; j<rect_width; j++){
				int x = x0 + (int)j;
				if(0<=x and (int)x<=pixel_width){
					pixels[y*pixel_width + x] = mix_color(pixels[y*pixel_width + x],color);
				}
			}
		}

}
}

void vugl_fill_color(uint32_t *pixels, uint32_t color, int height, int width){
	
	for(int i=0; i<height*width; i++){
		pixels[i] = color;
	}
}

#endif // VUGL_H
