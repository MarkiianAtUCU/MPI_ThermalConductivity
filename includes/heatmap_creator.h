//
// Created by mmatsi on 10/16/19.
//

#ifndef MPI_HEATMAP_CREATOR_H
#define MPI_HEATMAP_CREATOR_H

#include <string>
#include <map>

#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>

struct RGB {
    int red;
    int green;
    int blue;

    RGB(int red=0, int green=0, int blue=0) {
        this->red = red;
        this->green = green;
        this->blue = blue;
    }
};

class heatmap {
private:
    int imageCounter = 0;
    int width;
    int height;
    int minValue;
    int maxValue;

    RGB HSVTORGB(double H, double S, double V) {
        RGB rgb = RGB();

        double C = S * V;
        double X = C * (1 - abs(fmod(H / 60.0, 2) - 1));
        double m = V - C;
        double Rs, Gs, Bs;

        if(H >= 0 && H < 60) {
            Rs = C;
            Gs = X;
            Bs = 0;
        }
        else if(H >= 60 && H < 120) {
            Rs = X;
            Gs = C;
            Bs = 0;
        }
        else if(H >= 120 && H < 180) {
            Rs = 0;
            Gs = C;
            Bs = X;
        }
        else if(H >= 180 && H < 240) {
            Rs = 0;
            Gs = X;
            Bs = C;
        }
        else if(H >= 240 && H < 300) {
            Rs = X;
            Gs = 0;
            Bs = C;
        }
        else {
            Rs = C;
            Gs = 0;
            Bs = X;
        }

        rgb.red = (Rs + m) * 255;
        rgb.green = (Gs + m) * 255;
        rgb.blue = (Bs + m) * 255;

        std::cout << "-------" <<std::endl;
        std::cout << rgb.red << std::endl;
        std::cout << rgb.green << std::endl;
        std::cout << rgb.blue << std::endl;
        std::cout << "-------" <<std::endl;

        return rgb;
    }

    double convertRange(double value, double fromOld, double toOld, double fromNew, double toNew) {
        return (((value - fromOld) * (toNew - fromNew)) / (toOld - fromOld)) + fromNew;
    }

    RGB temperatureToColor(double value) {
        double range = this->maxValue - this->minValue;
        double h = convertRange(value / range, 0, 1, 0, 360);

        std::cout << h << std::endl;

        RGB rgb = HSVTORGB(h, 1.0, 1.0);
        return rgb;
    }
public:
    heatmap(int minValue, int maxValue, int width, int height) {
        this->minValue = minValue;
        this->maxValue = maxValue;
        this->width = width;
        this->height = height;
    }
    void saveImage(std::vector<double> &table) {
        FILE *f;
        unsigned char *img = NULL;
        int filesize = 54 + 3*this->width*this->height;

        img = (unsigned char *)malloc(3*this->width*this->height);
        memset(img,0,3*this->width*this->height);

        for(int i=0; i<this->width; i++)
        {
            for(int j=0; j<this->height; j++)
            {
                int x=i;
                int y=(this->height-1)-j;

                RGB color = temperatureToColor(table[j*width + i]);

                if (color.red > 255) color.red=255;
                if (color.green > 255) color.green=255;
                if (color.blue > 255) color.blue=255;
                img[(x+y*this->width)*3+2] = (unsigned char)(color.red);
                img[(x+y*this->width)*3+1] = (unsigned char)(color.green);
                img[(x+y*this->width)*3+0] = (unsigned char)(color.blue);
            }
        }

        unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
        unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
        unsigned char bmppad[3] = {0,0,0};

        bmpfileheader[ 2] = (unsigned char)(filesize    );
        bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
        bmpfileheader[ 4] = (unsigned char)(filesize>>16);
        bmpfileheader[ 5] = (unsigned char)(filesize>>24);

        bmpinfoheader[ 4] = (unsigned char)(       this->width     );
        bmpinfoheader[ 5] = (unsigned char)(       this->width >> 8);
        bmpinfoheader[ 6] = (unsigned char)(       this->width >>16);
        bmpinfoheader[ 7] = (unsigned char)(       this->width >>24);
        bmpinfoheader[ 8] = (unsigned char)(       this->height     );
        bmpinfoheader[ 9] = (unsigned char)(       this->height >> 8);
        bmpinfoheader[10] = (unsigned char)(       this->height >>16);
        bmpinfoheader[11] = (unsigned char)(       this->height >>24);

        f = fopen("img.bmp","wb");
        fwrite(bmpfileheader,1,14,f);
        fwrite(bmpinfoheader,1,40,f);
        for(int i=0; i<this->height; i++)
        {
            fwrite(img+(this->width*(this->height-i-1)*3),3,this->width,f);
            fwrite(bmppad,1,(4-(this->width*3)%4)%4,f);
        }

        free(img);
        fclose(f);
    }
};

#endif //MPI_HEATMAP_CREATOR_H
