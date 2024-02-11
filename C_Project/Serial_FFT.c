#include<stdio.h>
#include<png.h>
#include<stdlib.h>

#define MAX_LENGHT (1080)
#define MAX_HEIGHT (720)
#define MAX_GRAYLEVEL (256)

/*
 * 		IMAGE HANDLING
 * The program reads a portable gray map image PGM in order
 * to facilitate the handling of the picture
 * 
 * */
 
/*
 * The data structure below is responsible for hadling the image informations
 * */
  
struct image{
	int magic_number;	 //uised to identify the format by PGM it is originated from the combination of the first char and number of the file
	int width, height;	 // parameters of our image matrix
	int max_gray; 		 // max gray level of the image, migth be useful
	int *pixel_matrix; 	 // this pointer will contain the address of the pixel image matrix, it has to be initialized later due to its unknown size
	};
 
 /*
  * This function is responsible for populating the data structure associated to an image
  * */
  
void read_image(struct image *pgm, FILE *infile){
	/*
	 * offset is the value to sum to the buf char vector in order to discard some part of the buf in parsing 
	 * see the while loop explanation
	 * */
	int n;
	int i,j = 0;
	int offset;
	char buf[MAX_LENGHT];
	char *buf_pointer = buf;
	
	//extracting and saving the magic number
	fgets(buf,sizeof(buf),infile);
	sscanf(buf, "P%i", &pgm->magic_number);
	printf("Type of PGM image is: P%i\n", pgm->magic_number);
	
	//extracting and saving the image matrix dimension
	fgets(buf,sizeof(buf),infile);
	sscanf(buf, "%i %i", &pgm->width, &pgm->height);
	printf("Image size is %i width and %i height\n", pgm->width, pgm->height);
	//now i can initialize the matrix because i have the image size
	int pixel_matrix[pgm->width][pgm->height];
	
	//extracting max gray level
	fgets(buf,sizeof(buf),infile);
	sscanf(buf, "%i", &pgm->max_gray);
	printf("Max gray level %i\n", pgm->max_gray);
	
	//extracting the pixel matrix
	/*
	 * This loop is used to get the integers, in each iteration i start from
	 * the already parsed buf element by adding the offset
	 * to the. The while is there in order to check if the null value is parsed, 
	 * if that happens i end the loop
	 * */
	 
	for(i=0;i<pgm->height;i++){
		buf_pointer=fgets(buf,sizeof(buf),infile);
		printf("Debug i index is= %i\n",i);
			while(sscanf(buf_pointer,"%i%n", &n, &offset) == 1){
				printf("Debug j index is= %i\n",j);
				pixel_matrix[i][j] = n;
				j++;
				buf_pointer += offset;
			}
			j=0; 
		}
	return;
}
	
/*
 * This function is used to derive the string used in sscanf to interpret the line
 * in our case we want this to be dynamic because the number of pixel per image may changhe 
 * the result is of this type :"%i %i %i..." for the number of given line elements
 * */
	

int main(int argc, char *argv[]){
	int arg_pointer = 1;
	struct image pmg;	 //i define the image struct
	FILE *infile;	 	 //i initialize the infile variable as a pointer to a file
	
	printf("Main Serial_FFT is running...\n");
	//I check if the number of parameters passed to the program is correct
	if(argc != 2){
		printf("Wrong number of input parameters, program terminated");
		return 1;
		}
	//file opening
	if(!(infile = fopen(argv[arg_pointer],"r"))){
			printf("Error in openign %s\n",argv[arg_pointer]);
		} else {
			printf("Targhet file %s correcly opened\n",argv[arg_pointer]);
			}
	read_image(&pmg, infile);
	}
