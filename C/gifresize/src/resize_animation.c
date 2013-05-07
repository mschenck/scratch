
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <wand/MagickWand.h>
#define MAX_IMAGE_SIZE 20971520  /* 20 MB */
#define MAGICK_BLUR   0.5 

const int TARGET_WIDTH  = 400;
const int TARGET_HEIGHT = 258;

int
main (void)
{
  int                   orig_fd, new_fd;
  ssize_t               gif_size;
  void                  *gif_data;
  FILE                  *new_file;
  MagickWand            *magick_wand;
  ColorspaceType        colorspace;
  int                   colors;

  // Read source image into memory space
  orig_fd  = open( "./1_500.gif", O_RDONLY );
  gif_data = malloc( MAX_IMAGE_SIZE );
  gif_size = read( orig_fd, gif_data, MAX_IMAGE_SIZE );
  close(orig_fd);


  // Initialize this Wand
  MagickWandGenesis();
  magick_wand = NewMagickWand();

  if ( MagickReadImageBlob(magick_wand, gif_data, gif_size) == MagickFalse ) {
    printf( "ERROR: failed to read image blob\n");
    return 1;
  }


  colorspace = MagickGetImageColorspace( magick_wand );

  // For supporting animated gifs
  //MagickClampImage( magick_wand );

  // Resize all frames
  MagickSetFirstIterator( magick_wand );
  do {

    MagickCoalesceImages( magick_wand );

    colors = MagickGetImageColors( magick_wand );
    printf( "Colors: %d\t", colors );

    // Resize current 'image' (frame)
    MagickResizeImage( magick_wand, TARGET_WIDTH, TARGET_HEIGHT, MitchellFilter, MAGICK_BLUR );
    //MagickAdaptiveResizeImage( magick_wand, TARGET_WIDTH, TARGET_HEIGHT );


    //MagickUnsharpMaskImage( magick_wand, 0.5, 0.5, 1.0, 0.1 );
    //MagickTransformImageColorspace( magick_wand, colorspace );

    colors = MagickGetImageColors( magick_wand );
    printf( "Colors: %d\n", colors );

  } while ( MagickNextImage(magick_wand) != MagickFalse );


  MagickStripImage( magick_wand );
  MagickEqualizeImage( magick_wand );

  // Fix the optimizations we broke in coalesce
  MagickOptimizeImageLayers( magick_wand );


  // Write new file
  printf( "Writing new image\n");
  new_fd   = open( "./1_400.gif", O_WRONLY|O_TRUNC );
  new_file = fdopen( new_fd, "w" );
  MagickWriteImagesFile( magick_wand, new_file );

  
  // Clean-up
  printf( "New image written, clean-up time\n");
  close(new_fd);
  magick_wand = DestroyMagickWand( magick_wand );
  MagickWandTerminus();

  return 0;
}
