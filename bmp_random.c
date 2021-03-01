#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
typedef struct Pixel
{
  uint8_t red, green, blue;
} Pixel;
typedef struct Image
{
  uint16_t type;
  uint16_t size_1;
  uint16_t size_2;
  uint16_t reserved_1;
  uint16_t reserved_2;
  uint16_t offset_of_pixsels_bytes_1; //offset of pixels bytes
  uint16_t offset_of_pixsels_bytes_2;
  uint16_t structure_size_1; // (28 00 00 00 : structure size)
  uint16_t structure_size_2;
  uint16_t picture_width_1; //05 00 00 00 : picture width in pixels
  uint16_t picture_width_2;
  uint16_t picture_height_1;
  uint16_t picture_height_2;
  uint16_t num_planes;           // Number of color planes (01 00 : number of display plans)
  uint16_t bits_per_pixel;       // Bits per pixel (18 00 : number of bits per pixel)
  uint16_t type_of_compresion_1; //00 00 00 00 : type of compression
  uint16_t type_of_compresion_2;
  uint16_t number_of_bytes_in_picture_1; //50 00 00 00 : number of bytes in the picture
  uint16_t number_of_bytes_in_picture_2;
  uint16_t horizontal_resolution_1;
  uint16_t horizontal_resolution_2;
  uint16_t vertical_resolution_1;
  uint16_t vertical_resolution_2;
  uint16_t number_of_used_colors_1;
  uint16_t number_of_used_colors_2;
  uint16_t number_of_important_colors_1;
  uint16_t number_of_important_colors_2;
  Pixel img[1200][1200];
} Image;
//0x3876 129654 0x1FA76
int main(int argc, char const *argv[])
{
  time_t t;
  srand((unsigned)time(&t));
  Image img = {
      .type = 0x4d42,   //type identifyer for BMP
      .size_1 = 0x3ACE, // (!! 414 bytes)
      .size_2 = 0,      // ask teacher 0x0C
      .reserved_1 = 0,
      .reserved_2 = 0,
      .offset_of_pixsels_bytes_1 = 0x36, // (have to be:36 00 00 00 : offset of pixels bytes ) !!!54 bytes
      .offset_of_pixsels_bytes_2 = 0,
      .structure_size_1 = 0x28, // (28 00 00 00 : structure size)
      .structure_size_2 = 0,
      .picture_width_1 = 0x4B0, // , 20
      .picture_width_2 = 0,
      .picture_height_1 = 0x4B0,
      .picture_height_2 = 0,
      .num_planes = 1,
      .bits_per_pixel = 0x18,
      .type_of_compresion_1 = 0,
      .type_of_compresion_2 = 0,
      .number_of_bytes_in_picture_1 = 0x50,
      .number_of_bytes_in_picture_2 = 0,
      .horizontal_resolution_1 = 0xC40E,
      .horizontal_resolution_2 = 0,
      .vertical_resolution_1 = 0xC40E,
      .vertical_resolution_2 = 0,
      .number_of_used_colors_1 = 0,
      .number_of_used_colors_2 = 0,
      .number_of_important_colors_1 = 0,
      .number_of_important_colors_2 = 0,

  };

  FILE *in;
  FILE *out;
  for (int j = 0; j < 1; j++)
  {
    char filename[sizeof "Random100.png"];
    sprintf(filename, "Random%03d.png", j);
    out = fopen(filename, "wb"); // "wb" identifier says we want to write into file IN BINARY
    if (out == NULL)
    {
      printf("Error has occur!\n");
      return 1;
    }
    int color1 = 0;
    int color2 = 0;

    for (int i = 0; i < 1200; i++)
    {

      for (int j = 0; j < 1200; j++)
      {
        img.img[i][j].blue = 255;
        img.img[i][j].green = 255; //rand() % +255;
                                   //rand() % 235 + 20;
        img.img[i][j].red = 255;
      }
    }

    for (int i = 595; i < 605; i++)
    {

      for (int j = 0; j < 1200; j++)
      {
        img.img[i][j].blue = 0;
        img.img[i][j].green = 0; //rand() % +255;
                                 //rand() % 235 + 20;
        img.img[i][j].red = 0;
      }
    }

    for (int i = 0; i < 1200; i++)
    {

      for (int j = 595; j < 605; j++)
      {
        img.img[i][j].blue = 0;
        img.img[i][j].green = 0; //rand() % +255;
                                 //rand() % 235 + 20;
        img.img[i][j].red = 0;
      }
    }

    size_t elements_writen = fwrite(&img, sizeof(Image), 1, out);
    printf("ELEMENTS = %zu\n", elements_writen);
    printf("Size of char = %lu\n", sizeof(char));
    fclose(out);
    if (elements_writen == 0)
    {
      return 2;
    }
  }
  return 0;
}
