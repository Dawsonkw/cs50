#include "helpers.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through the images rows and columns to find pixel values
    // Average the values of the pixels
    // Set each color value to average and return new modified image
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            float avg = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;
            float average = round(avg);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through each pixel 
    // Calculate the new color value according to sepia formula
    // Resulting value must be b/t 0 and 255, if greater than 255 set value = 255
    
    for (int i = 0; i <= height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float red = image[i][j].rgbtRed;
            float green = image[i][j].rgbtGreen;
            float blue = image[i][j].rgbtBlue;
            
            float sepRed = round((0.393 * red + 0.769 * green + 0.189 * blue));
            float sepGreen = round((0.349 * red + 0.686 * green + 0.168 * blue));
            float sepBlue = round((0.272 * red + 0.534 * green + 0.131 * blue));
            
            if (sepRed > 255)
            {
                sepRed = 255;
            }
            if (sepGreen > 255)
            {
                sepGreen = 255;
            }
            if (sepBlue > 255)
            {
                sepBlue = 255;
            }
            
            image[i][j].rgbtRed = sepRed;
            image[i][j].rgbtGreen = sepGreen;
            image[i][j].rgbtBlue = sepBlue;
        }
    }
    
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through each pixel
    // swap pixels of each ROW to horizontally opposite sides
    
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width / 2.0 ; j++)
        {
            // Use a dummy variable to store one pixel while swapping the other pixel into the correct position
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // loop through the pixels in the image
    // average surrounding pixels each w/in 1 row or 1 column from original 
    // set each pixel to average and return new averaged 'blurred' photo
    RGBTRIPLE originalImage[height][width];
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            originalImage[i][j] = image[i][j];
        }
    }
    
    for(int i = 0, red, green, blue, counter; i < height; i ++)
    {
        for(int j = 0; j < width; j++)
        {
            red = green = blue = counter = 0;
            
            if(i >= 0 && j >=0)
            {
                red += originalImage[i][j].rgbtRed;
                green += originalImage[i][j].rgbtGreen;
                blue += originalImage[i][j].rgbtBlue;
                counter++;
            }
            if(i >= 0 && j -1 >= 0)
            {
                red += originalImage[i][j - 1].rgbtRed;
                green += originalImage[i][j - 1].rgbtGreen;
                blue += originalImage[i][j - 1].rgbtBlue;
                counter++;
            }
            if((i >= 0 && j + 1 >= 0) && (i >= 0 && j + 1 < width))
            {
                red += originalImage[i][j + 1].rgbtRed;
                green += originalImage[i][j + 1].rgbtGreen;
                blue += originalImage[i][j + 1].rgbtBlue;
                counter++;
            }
            if(i - 1 >= 0 && j >=0)
            {
                red += originalImage[i - 1][j].rgbtRed;
                green += originalImage[i - 1][j].rgbtGreen;
                blue += originalImage[i - 1][j].rgbtBlue;
                counter++;
            }
            if(i - 1 >= 0 && j - 1 >= 0)
            {
                red += originalImage[i - 1][j - 1].rgbtRed;
                green += originalImage[i - 1][j - 1].rgbtGreen;
                blue += originalImage[i - 1][j - 1].rgbtBlue;
                counter++;
            }
            if((i - 1 >= 0 && j + 1 >= 0) && (i - 1 >= 0 && j + 1 < width))
            {
                red += originalImage[i - 1][j + 1].rgbtRed;
                green += originalImage[i - 1][j + 1].rgbtGreen;
                blue += originalImage[i - 1][j + 1].rgbtBlue;
                counter++;
            }
            if((i + 1 >= 0 && j >= 0) && (i + 1 < height && j >= 0))
            {
                red += originalImage[i + 1][j].rgbtRed;
                green += originalImage[i + 1][j].rgbtGreen;
                blue += originalImage[i + 1][j].rgbtBlue;
                counter++;
            }
            if((i + 1 >= 0 && j - 1 >= 0) && (i + 1 < height && j - 1 >= 0))
            {
                red += originalImage[i + 1][j - 1].rgbtRed;
                green += originalImage[i + 1][j - 1].rgbtGreen;
                blue += originalImage[i + 1][j - 1].rgbtBlue;
                counter++;
            }
            if((i + 1 >= 0 && j + 1 >= 0) && (i + 1 < height && j + 1 < width))
            {
                red += originalImage[i + 1][j + 1].rgbtRed;
                green += originalImage[i + 1][j + 1].rgbtGreen;
                blue += originalImage[i + 1][j + 1].rgbtBlue;
                counter++;
            }
            
            image[i][j].rgbtRed = round(red / (counter * 1.0));
            image[i][j].rgbtGreen = round(green / (counter * 1.0));
            image[i][j].rgbtBlue = round(blue / (counter * 1.0));
        }
    }
    
    return;
}