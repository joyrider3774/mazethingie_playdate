#ifndef PD_HELPERFUNCS_H
#define PD_HELPERFUNCS_H

#include <stdbool.h>
#include "pd_api.h"

extern LCDPattern kColorGrey;

void drawTextColor(LCDFont* font, const char* text, size_t len, PDStringEncoding encoding, int x, int y, LCDColor color, bool inverted);

#endif