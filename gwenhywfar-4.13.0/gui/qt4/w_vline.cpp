/***************************************************************************
    begin       : Mon Feb 15 2010
    copyright   : (C) 2010 by Martin Preuss
    email       : martin@libchipcard.de

 ***************************************************************************
 *          Please see toplevel file COPYING for license details           *
 ***************************************************************************/


#include <gwen-gui-cpp/cppwidget.hpp>


class Qt4_W_VLine: public Qt4_W_Widget {
public:
  Qt4_W_VLine(GWEN_WIDGET *w):Qt4_W_Widget(w) {
  }



  ~Qt4_W_VLine() {
  }



  virtual int setup() {
    QFrame *qw;
    uint32_t flags;
    GWEN_WIDGET *wParent;
    QSizePolicy::Policy hpolicy=QSizePolicy::Minimum;
    QSizePolicy::Policy vpolicy=QSizePolicy::Minimum;
    const char *s;
    QString text;

    flags=GWEN_Widget_GetFlags(_widget);
    wParent=GWEN_Widget_Tree_GetParent(_widget);
    s=GWEN_Widget_GetText(_widget, 0);
    if (s)
      text=QString::fromUtf8(s);

    qw=new QFrame();
    qw->setFrameShape(QFrame::VLine);
    qw->setFrameShadow(QFrame::Sunken);

    /* handle flags */
    if (flags & GWEN_WIDGET_FLAGS_FILLX)
      hpolicy=QSizePolicy::Expanding;
    if (flags & GWEN_WIDGET_FLAGS_FILLY)
      vpolicy=QSizePolicy::Expanding;
    qw->setSizePolicy(hpolicy, vpolicy);

    GWEN_Widget_SetImplData(_widget, QT4_DIALOG_WIDGET_REAL, (void*) qw);

    if (wParent)
      GWEN_Widget_AddChildGuiWidget(wParent, _widget);
    return 0;
  }

};







