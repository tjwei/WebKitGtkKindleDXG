#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

	 

#include <directfb.h>

	 

static IDirectFB *dfb = NULL;
static IDirectFBSurface *primary = NULL;
static IDirectFBSurface *foot = NULL;
static IDirectFBInputDevice *keyboard = NULL;
static int screen_width  = 0;
static int screen_height = 0;
#define DFBCHECK(x...)                                         \
  {                                                            \
    DFBResult err = x;                                         \
                                                               \
    if (err != DFB_OK)                                         \
      {                                                        \
        fprintf( stderr, "%s <%d>:\n\t", __FILE__, __LINE__ ); \
        DirectFBErrorFatal( #x, err );                         \
      }                                                        \
  }


static IDirectFBEventBuffer *buffer = NULL;


int main (int argc, char **argv)
{

	 

  DFBSurfaceDescription   dsc;
  IDirectFBImageProvider *provider;


  int quit = 0;
  int i=10,j=10;


  DFBCHECK (DirectFBInit (&argc, &argv));
  DFBCHECK (DirectFBCreate (&dfb));
  DFBCHECK (dfb->SetCooperativeLevel (dfb, DFSCL_FULLSCREEN));
  dsc.flags = DSDESC_CAPS;
  dsc.caps  = DSCAPS_PRIMARY;
  DFBCHECK (dfb->CreateSurface( dfb, &dsc, &primary ));
  DFBCHECK (primary->GetSize (primary, &screen_width, &screen_height));


  DFBCHECK (primary->FillRectangle (primary, 
                                    0, 0, screen_width, screen_height));


  DFBCHECK (dfb->GetInputDevice (dfb, DIDID_KEYBOARD, &keyboard));


  DFBCHECK (keyboard->CreateEventBuffer (keyboard, &buffer));


  DFBCHECK (dfb->CreateImageProvider (dfb, DATADIR"/foot.png", &provider));
  DFBCHECK (provider->GetSurfaceDescription (provider, &dsc));
  DFBCHECK (dfb->CreateSurface (dfb, &dsc, &foot));
  DFBCHECK (provider->RenderTo (provider, foot, NULL));
  provider->Release (provider);


  DFBCHECK (primary->SetBlittingFlags (primary, DSBLIT_BLEND_ALPHACHANNEL));


  while (!quit)
    {


      DFBInputEvent event;


      DFBCHECK (buffer->WaitForEvent (buffer));


      while (buffer->GetEvent (buffer, DFB_EVENT(&event)) == DFB_OK)
        {


  /*        if (event.type == DIET_KEYRELEASE)
            DFBCHECK (primary->FillRectangle (primary,
                                              0, 0, 
                                              screen_width, screen_height));*/


          if (event.type == DIET_KEYPRESS)
            {
              if ( (event.key_id == DIKI_ESCAPE ) || ( event.key_id == DIKI_PAGE_DOWN) )
                quit = 1;
              else
                DFBCHECK (primary->Blit (primary, foot, NULL,i++,j++));
            }
        }


    }


  buffer->Release (buffer);


  keyboard->Release (keyboard);
  foot->Release (foot);
  primary->Release (primary);
  dfb->Release (dfb);


  return 23;
}

	 
