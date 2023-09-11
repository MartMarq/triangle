#ifndef WATCHY_triangle_H
#define WATCHY_triangle_H

#ifdef WATCHY_SIM
    #include "..\..\Watchy.h"
#else // WATCHY_SIM
    #include <Watchy.h>
#endif // WATCHY_SIM

#include "icons.h"
#include "FreeMonoBold16pt7b.h"

class Watchytriangle : public Watchy{
    using Watchy::Watchy;
    public:
        void drawWatchFace();
        void drawTime();
 };

#endif