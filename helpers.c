#include "helpers.h"
// check through each pixel using for loops
// if pixel is black, change the color using if statement
void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (image[i][j].rgbtRed == 0 && image[i][j].rgbtBlue == 0 && image[i][j].rgbtGreen == 0)
            {
                image[i][j].rgbtRed = 235;
                image[i][j].rgbtBlue = 185;
                image[i][j].rgbtGreen = 79;
            }
        }
    }
}
