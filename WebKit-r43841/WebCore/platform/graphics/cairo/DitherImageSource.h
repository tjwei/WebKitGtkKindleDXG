/* TODO Get the right header and put it here */
#ifndef DitherImageSource_h
#define DitherImageSource_h
/* <lab126> */
#define STRIP_ALPHA                 0xFF000000
#define STRIP_RED                   0x00FF0000
#define STRIP_GREEN                 0x0000FF00
#define STRIP_BLUE                  0x000000FF
#define RED(c)                      (((c) & STRIP_RED) >> 16)
#define GREEN(c)                    (((c) & STRIP_GREEN) >> 8)
#define BLUE(c)                     (((c) & STRIP_BLUE))



enum {
	    USE_NONE = 0,
        USE_STUCKI_ALGORITHM = 1,
        USE_FS_ALGORITHM =2,
        USE_SIMPLE_ALGORITHM =3
    };

typedef struct {
        int nw, n, ne, w; // north-west, north, north-east, west
        char buf[1];
} DitherStateType;

typedef struct {
    int *line1 ;
    int *line2;
    
    int lineWidth;	
    int nnww, nnw, nn, nne, nnee; // pixel direction
    int  nww,  nw,  n,  ne,  nee;
    int   ww,   w;
} DitherStuckiStateType;

/*  Floyd-Steinberg algorithm, which diffuses the pixel
 * error among the 4 pixels to the direct WEST, NORTH, NORTHEAST and NORTHWEST
 * by 7/16, 5/16, 3/16 and 1/16 of the error, respectively
 *
 * Note: the error buffer is allocated 1 byte wider that the image, so we don't
 * have to detect the right edge of the image
 *
 * Note: Masking the 2 LSBs (0x03) of the return value (lumQ) will produce a
 * 2-bit grayscale value
 */

int ditherFS(int x, int y, int rgb, DitherStateType *ditherState);

/*  Stucki algorithm, which diffuses the pixel
 * error among the 12 pixels to the direct WEST, NORTH, NORTHEAST and NORTHWEST, etc
 *
 */
int ditherStucki(int x, int y, int rgb, DitherStuckiStateType *ditherStuckiStatePtr);
/* </lab126> */
#endif // DitherImageSource_h
