#include <string.h>
#include <stdbool.h>
#include "pd_helperfuncs.h"
#include "pd_api.h"
#include "Mazethingie.h"

LCDPattern kColorGrey = {
    // Bitmap
    0b10101010,
    0b01010101,
    0b10101010,
    0b01010101,
    0b10101010,
    0b01010101,
    0b10101010,
    0b01010101,

    // Mask
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
};

void drawTextColor(LCDFont* font, const char* text, size_t len, PDStringEncoding encoding, int x, int y, LCDColor color, bool inverted)
{
    int Lines = 1;
    size_t chars = 0;
    const char* p = text;
    while ((*p != '\0') && (chars < len))
    {
        if (*p == '\n')
            Lines++;
        p++;
        chars++;
    }

    int h = Lines * pd->graphics->getFontHeight(font);
    pd->graphics->setFont(font);
    int w = pd->graphics->getTextWidth(font, text, len, encoding, 0);
    //create new bitmap and fillrect with our color / pattern
    LCDBitmap* Bitmap = pd->graphics->newBitmap(w, h, kColorClear);
    if (inverted)
        pd->graphics->setDrawMode(kDrawModeInverted);
    pd->graphics->pushContext(Bitmap);
    pd->graphics->fillRect(0, 0, w, h, color);
    pd->graphics->popContext();

    //create mask with black background and draw text in white on the mask 
    LCDBitmap* bitmapmask = pd->graphics->newBitmap(w, h, kColorBlack);
    pd->graphics->pushContext(bitmapmask);
    pd->graphics->setDrawMode(kDrawModeFillWhite);
    pd->graphics->setFont(font);
    pd->graphics->drawText(text, len, encoding, 0, 0);
    pd->graphics->popContext();

    //set the mask to the bitmap with our pattern, this will make sure only the text
    //part (white in mask is drawn from the bitmap)
    pd->graphics->setBitmapMask(Bitmap, bitmapmask);

    //now draw the bitmap containing our text to the x & y position
    pd->graphics->drawBitmap(Bitmap, x, y, kBitmapUnflipped);
    pd->graphics->freeBitmap(Bitmap);
    pd->graphics->freeBitmap(bitmapmask);
}

