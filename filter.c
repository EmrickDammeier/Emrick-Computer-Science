#include "helpers.h"
#include <math.h>
// worked with Jack Yuan

// Convert image to grayscale
// for loop to go through each pixel
// put RGB values equal to each other by making them equal gray
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gray =
                round((float) (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0); // equation to find gray
            image[i][j].rgbtRed = gray;
            image[i][j].rgbtBlue = gray;
            image[i][j].rgbtGreen = gray;
        }
    }
}

// Convert image to sepia
// for loop to go through each pixel
// one for height and one for width
// Use formula that is given from the Harvard page
// check to make sure that the values are capped at 255
//
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int Red = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int Green = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int Blue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen +
                             .131 * image[i][j].rgbtBlue); // equation that is given on harvard page

            if (Red > 255) // checks if it goes over 255
                Red = 255;

            if (Green > 255)
                Green = 255;

            if (Blue > 255)
                Blue = 255;

            image[i][j].rgbtRed = Red;
            image[i][j].rgbtGreen = Green;
            image[i][j].rgbtBlue = Blue;
        }
    }
}

// Reflect image horizontally
// for loop to go through each pixel
// must use temp to switch around to create reflection
// mirror width is used to flip horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++) // divide by 2 to get half
        {
            temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
}

// Blur image
// using box blur
// for loop to go through each pixel
// give new value, which would be value after averaging color values of pixels around it
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    // Create a copy of the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    // Go through each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int totalRed = 0, totalGreen = 0, totalBlue = 0;
            int count = 0;

            // Go through the neighbors of the current pixel
            for (int r = -1; r <= 1; r++)
            {
                for (int b = -1; b <= 1; b++)
                {
                    int origI = i + r;
                    int origJ = j + b;

                    // Check if the neighbor is within bounds
                    if (origI >= 0 && origI < height && origJ >= 0 && origJ < width)
                    {
                        totalRed += temp[origI][origJ].rgbtRed;
                        totalGreen += temp[origI][origJ].rgbtGreen;
                        totalBlue += temp[origI][origJ].rgbtBlue;
                        count++;
                    }
                }
            }

            // Calculate the average color values
            image[i][j].rgbtRed = round((float) totalRed / count);
            image[i][j].rgbtGreen = round((float) totalGreen / count);
            image[i][j].rgbtBlue = round((float) totalBlue / count);
        }
    }
}
