/* TODO: get the right header and put it here */

#include "DitherImageSource.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int colorMap4[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55,0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};


inline int *  shiftErrorValues2(int x, int y, DitherStuckiStateType *ditherStuckiStatePtr)
{
    int * buf1;
    int * buf2;

    if ((y&1) == 0) {
        buf1 = ditherStuckiStatePtr->line1;
        buf2 = ditherStuckiStatePtr->line2;
    } else {
        buf1 = ditherStuckiStatePtr->line2;
        buf2 = ditherStuckiStatePtr->line1;
    }

    // handle edge cases
    if (x == 0) // left edge
    {
             // init north-north values
         if (y <= 1) { // first or second row
             ditherStuckiStatePtr->nnww = ditherStuckiStatePtr->nnw = ditherStuckiStatePtr->nn = ditherStuckiStatePtr->nne = ditherStuckiStatePtr->nnee = 0;
         } else {
             ditherStuckiStatePtr->nnww = ditherStuckiStatePtr->nnw = 0; 
             ditherStuckiStatePtr->nn = buf2[x]; 
             ditherStuckiStatePtr->nne = buf2[x+1]; 
             ditherStuckiStatePtr->nnee = buf2[x+2];
         }
         // init north values
         if (y == 0) { // first row
             ditherStuckiStatePtr->nww =  ditherStuckiStatePtr->nw =  ditherStuckiStatePtr->n =  ditherStuckiStatePtr->ne =  ditherStuckiStatePtr->nee = 0;
         } else {
             ditherStuckiStatePtr->nww =  ditherStuckiStatePtr->nw = 0;  
             ditherStuckiStatePtr->n = buf1[x];  
             ditherStuckiStatePtr->ne = buf1[x+1];  
             ditherStuckiStatePtr->nee = buf1[x+2];
         }

         // init west
         ditherStuckiStatePtr->ww = ditherStuckiStatePtr->w = 0;
     }
     else
     {
      // shift north-north values
         if (y > 1) { // not first or second row
             ditherStuckiStatePtr->nnww = ditherStuckiStatePtr->nnw; 
             ditherStuckiStatePtr->nnw = ditherStuckiStatePtr->nn; 
             ditherStuckiStatePtr->nn = ditherStuckiStatePtr->nne; 
             ditherStuckiStatePtr->nne = ditherStuckiStatePtr->nnee; 
             ditherStuckiStatePtr->nnee = buf2[x+2];
         }

         // shift north values
         if (y > 0) { // not first row
             ditherStuckiStatePtr->nww =  ditherStuckiStatePtr->nw;  
             ditherStuckiStatePtr->nw =  ditherStuckiStatePtr->n;  
             ditherStuckiStatePtr->n =  ditherStuckiStatePtr->ne;  
             ditherStuckiStatePtr->ne =  ditherStuckiStatePtr->nee;  
             ditherStuckiStatePtr->nee = buf1[x+2];
         }
     }
    return buf2;

}

int ditherStucki(int x, int y, int rgb, DitherStuckiStateType *ditherStuckiStatePtr){
    int r = (rgb >> 16) & 0xff;
    int g = (rgb >> 8) & 0xff;
    int b = rgb & 0xff;
    int gray;
    if (r == g && g == b)
        gray = r;
    else
        gray =  (77 * r + 150 * g + 29 * b) >> 8;
        
    int * buf2 = shiftErrorValues2(x, y, ditherStuckiStatePtr);
    // dither
    int lumD = gray +
    (ditherStuckiStatePtr->nnww + (ditherStuckiStatePtr->nnw<<1) + (ditherStuckiStatePtr->nn<<2) + (ditherStuckiStatePtr->nne<<1) + ditherStuckiStatePtr->nnee +
         (ditherStuckiStatePtr->nww<<1)  + (ditherStuckiStatePtr->nw<<2)  + (ditherStuckiStatePtr->n<<4)  + 
         (ditherStuckiStatePtr->ne<<2)  +    (ditherStuckiStatePtr->nee<<1)  +
         (ditherStuckiStatePtr->ww<<2)  + (ditherStuckiStatePtr->w<<4)) / 42;
		// quantize
     int lumQ;
#ifdef DITHER_CENTERED_GRAY
    if (lumD <= 8)
       lumQ =  0x00;
    else if (lumD >= 247)
       lumQ =  0xFF;
    else
    // quantize centered around the color values
    lumQ = colorMap4[(lumD+8) / 17];
#else
    // quantize equally divided color space

    if (lumD <= 15)
       lumQ =  0x00;
    else if (lumD >= 240)
       lumQ =  0xFF;
    else 
    	lumQ = colorMap4[lumD >> 4]; 
#endif
		// compute error
    int err = gray - lumQ;
		// save error in west value for next pixel
    ditherStuckiStatePtr->ww = ditherStuckiStatePtr->w; ditherStuckiStatePtr->w = err;
		// and in buf2 for the next n row (buf1)
    buf2[x] = err;
    gray =  lumQ;
    return ((rgb & STRIP_ALPHA) | gray << 16 | gray << 8 | gray);}

/* Floyd-Steinberg algorithm, which diffuses the pixel
 * error among the 4 pixels to the direct WEST, NORTH, NORTHEAST and NORTHWEST
 * by 7/16, 5/16, 3/16 and 1/16 of the error, respectively
 *
 * Note: the error buffer is allocated 1 byte wider that the image, so we don't
 * have to detect the right edge of the image
 *
 * Note: Masking the 2 LSBs (0x03) of the return value (lumQ) will produce a
 * 2-bit grayscale value
 */
inline int ditherGray8(int x, int y, int lum, DitherStateType *ditherState)
{
    int lumD,lumQ = 0,err;

    if (y == 0) { //first row
                // init north values
        ditherState->nw = ditherState->n = ditherState->ne = 0;
    } else if (x == 0) { // left edge
                // load north values
        ditherState->nw = 0; ditherState->n = ditherState->buf[x]; ditherState->ne = ditherState->buf[x+1];
    } else {
                // shift north values
        ditherState->nw = ditherState->n; ditherState->n = ditherState->ne; ditherState->nw = ditherState->buf[x+1];
    }

    if (x == 0) //left edge
        ditherState->w = 0; //init west

    lumD = lum + (1*ditherState->nw + 5*ditherState->n + 3*ditherState->ne + 7*ditherState->w)/16;
    //quantize
    if (lumD <= 15)
       lumQ =  0x00;
    else if (lumD >= 240)
       lumQ =  0xFF;
    else 
    	lumQ = colorMap4[lumD >> 4]; 

        //compute error
        err = lum - lumQ;

        // save error in west value for next pixel
        ditherState->w = err;
        // and in buf for next row
        ditherState->buf[x] = (char) err;

        return lumQ;
}

int ditherFS(int x, int y, int rgb, DitherStateType *ditherState)
{
   int luma = (77 * RED(rgb) + 150 * GREEN(rgb) + 29 * BLUE(rgb)) >>8;
   int luma1 = ditherGray8(x, y, luma, ditherState);
   return ((rgb & STRIP_ALPHA) >> 24 | luma1 << 16 | luma1 << 8 | luma1);

}


