#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "./headers/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./headers/stb_image_write.h"

unsigned char *uc_arrayNew_1d(int _size){
    return (unsigned char *)calloc(_size, sizeof(unsigned char));
}

unsigned char *merge_image(unsigned char *b, unsigned char *f, int width, int height, int channel)
{   
    unsigned char *temp = uc_arrayNew_1d(width * height * channel);
    for(int i=0; i < width * height * channel; i+=3){
        if(f[i] <= 180 && f[i] >= 50 && f[i+1] <= 255 && f[i+1] >= 138 && f[i+2] <= 101 && f[i+2] >= 0){ 
            temp[i]=b[i];
            temp[i+1]=b[i+1];
            temp[i+2]=b[i+2];
        }
        else{
            temp[i]=f[i];
            temp[i+1]=f[i+1];
            temp[i+2]=f[i+2];
            };
    }
    return temp; 
}

int main(){
    //declare vars
    int width, height, channelf, channelw;
    char path_foreground[] = "./images/foreground.png";
    char path_weather[] = "./images/weather.jpg";

    char save_path[] = "./images/new.png";

    //read foreground
    unsigned char *foreground = stbi_load(path_foreground, &width, &height, &channelf, 0);
    if (foreground == NULL) {
        printf("\nError in loading the image\n");
        exit(1);
    }

    //read weather
    unsigned char *weather = stbi_load(path_weather, &width, &height, &channelw, 0);
    unsigned char *new = stbi_load(path_weather, &width, &height, &channelw, 0);
    if (weather == NULL) {
        printf("\nError in loading the image\n");
        exit(1);
    }

    //merge
    new = merge_image(weather, foreground, width, height, channelw);

    //save image
    stbi_write_png(save_path, width, height, channelw, new, width * channelw);
    printf("New image save to %s\n", save_path);
}