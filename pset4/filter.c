#include <math.h>
#include "helpers.h"
#include <stdio.h>

int cap255(double n);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int gray;

    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            gray = round((image[x][y].rgbtBlue + image[x][y].rgbtGreen + image[x][y].rgbtRed) / 3.0);

            image[x][y].rgbtBlue = gray;
            image[x][y].rgbtGreen = gray;
            image[x][y].rgbtRed = gray;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp;
    int halfWidth;

    for (int x = 0; x < height; x++)
    {
        halfWidth = round(width / 2.0);

        for (int y = 0; y < halfWidth; y++)
        {
            tmp = image[x][y];
            int substract = y + 1;

            image[x][y] = image[x][width - substract];
            image[x][width - substract] = tmp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blurredImage[height][width];
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            blurredImage[x][y] = image[x][y];
        }
    }


    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            int red = 0;
            int green = 0;
            int blue = 0;
            int pixelsCount = 0;
            int newXlimit = x + 1;

            if (newXlimit >= height)
            {
                newXlimit = height - 1;
            }

            for (int newX = x - 1; newX <= newXlimit; newX++)
            {
                if (newX < 0)
                {
                    continue;
                }

                int newYlimit = y + 1;

                if (newYlimit == width)
                {
                    newYlimit = width - 1;
                }

                for (int newY = y - 1; newY <= newYlimit; newY++)
                {
                    if (newY < 0)
                    {
                        continue;
                    }

                    red += blurredImage[newX][newY].rgbtRed;
                    green += blurredImage[newX][newY].rgbtGreen;
                    blue += blurredImage[newX][newY].rgbtBlue;

                    pixelsCount++;
                }
            }


            image[x][y].rgbtRed = (int) round((float) red / pixelsCount);
            image[x][y].rgbtGreen = (int) round((float) green / pixelsCount);
            image[x][y].rgbtBlue = (int) round((float) blue / pixelsCount);
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE newImage[height][width];
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            newImage[x][y] = image[x][y];
        }
    }


    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            long gxRed = 0, gyRed = 0, gxGreen = 0, gyGreen = 0, gxBlue = 0, gyBlue = 0;
            int newXlimit = x + 1;
            int gx, gy;

            if (newXlimit >= height)
            {
                newXlimit = height - 1;
            }

            for (int newX = x - 1, i = 0; newX <= newXlimit; newX++, i++)
            {
                if (newX < 0)
                {
                    continue;
                }

                int newYlimit = y + 1;

                if (newYlimit == width)
                {
                    newYlimit = width - 1;
                }

                for (int newY = y - 1, j = 0; newY <= newYlimit; newY++, j++)
                {
                    if (newY < 0)
                    {
                        continue;
                    }

                    if (i == 0)
                    {
                        if (j == 0)
                        {
                            gx = -1;
                            gy = -1;
                        }
                        else if (j == 1)
                        {
                            gx = 0;
                            gy = -2;
                        }
                        else if (j == 2)
                        {
                            gx = 1;
                            gy = -1;
                        }
                    }
                    else if (i == 1)
                    {
                        if (j == 0)
                        {
                            gx = -2;
                            gy = 0;
                        }
                        else if (j == 1)
                        {
                            gx = 0;
                            gy = 0;
                        }
                        else if (j == 2)
                        {
                            gx = 2;
                            gy = 0;
                        }
                    }
                    else if (i == 2)
                    {
                        if (j == 0)
                        {
                            gx = -1;
                            gy = 1;
                        }
                        else if (j == 1)
                        {
                            gx = 0;
                            gy = 2;
                        }
                        else if (j == 2)
                        {
                            gx = 1;
                            gy = 1;
                        }
                    }

                    // printf("gx: %i\n", gx);

                    gxRed += gx * newImage[newX][newY].rgbtRed;
                    gxGreen += gx * newImage[newX][newY].rgbtGreen;
                    gxBlue += gx * newImage[newX][newY].rgbtBlue;

                    gyRed += gy * newImage[newX][newY].rgbtRed;
                    gyGreen += gy * newImage[newX][newY].rgbtGreen;
                    gyBlue += gy * newImage[newX][newY].rgbtBlue;
                }
            }

            image[x][y].rgbtRed = cap255(round(sqrt((double) gxRed * gxRed + (double) gyRed * gyRed)));
            image[x][y].rgbtGreen = cap255(round(sqrt((double) gxGreen * gxGreen + (double) gyGreen * gyGreen)));
            image[x][y].rgbtBlue = cap255(round(sqrt((double) gxBlue * gxBlue + (double) gyBlue * gyBlue)));
        }
    }

    return;
}

int cap255(double n)
{
    int result = 0;

    if (n >= 255)
    {
        result = 255;
    }
    else if (n < 0)
    {
        result = 0;
    }
    else
    {
        result = (int) round(n);
    }
    return (result);
}