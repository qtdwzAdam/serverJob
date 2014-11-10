
#include "glo.h"


GloPalette::GloPalette()
{
    palette_base = new QPalette;
    palette_norm = new QPalette;
    palette_base->setBrush(QPalette::Base,QBrush(QColor(255,0,0,0)));
    palette_norm->setBrush(QPalette::Foreground, QBrush(QColor(255,0,0,0)));
}


