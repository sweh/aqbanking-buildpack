/***************************************************************************
    begin       : Sun May 16 2010
    copyright   : (C) 2010 by Martin Preuss
    email       : martin@libchipcard.de

 ***************************************************************************
 *          Please see toplevel file COPYING for license details           *
 ***************************************************************************/

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif


#include "gtk2_gui_dialog_p.h"
#include <assert.h>

#include <gwenhywfar/inherit.h>
#include <gwenhywfar/debug.h>
#include <gwenhywfar/gui_be.h>
#include <gwenhywfar/i18n.h>

#include <gwenhywfar/text.h>
#include <gwenhywfar/mdigest.h>
#include <gwenhywfar/debug.h>
#include <gwenhywfar/directory.h>

#include <ctype.h>


#define I18N(msg) GWEN_I18N_Translate(PACKAGE, msg)


#define GTK2_DIALOG_WIDGET_REAL    0
#define GTK2_DIALOG_WIDGET_CONTENT 1
#define GTK2_DIALOG_WIDGET_DATA    2

#define GTK2_DIALOG_STRING_TITLE  0
#define GTK2_DIALOG_STRING_VALUE  1


#include "w_combobox.c"
#include "w_label.c"
#include "w_dialog.c"
#include "w_gridlayout.c"
#include "w_hlayout.c"
#include "w_hline.c"
#include "w_hspacer.c"
#include "w_vlayout.c"
#include "w_vline.c"
#include "w_vspacer.c"
#include "w_pushbutton.c"
#include "w_lineedit.c"
#include "w_textedit.c"
#include "w_textbrowser.c"
#include "w_stack.c"
#include "w_tabbook.c"
#include "w_groupbox.c"
#include "w_progressbar.c"
#include "w_listbox.c"
#include "w_checkbox.c"
#include "w_scrollarea.c"
#include "w_radiobutton.c"
#include "w_spinbox.c"



GWEN_INHERIT(GWEN_DIALOG, GTK2_GUI_DIALOG)




void Gtk2Gui_Dialog_Extend(GWEN_DIALOG *dlg) {
  GTK2_GUI_DIALOG *xdlg;

  GWEN_NEW_OBJECT(GTK2_GUI_DIALOG, xdlg);
  GWEN_INHERIT_SETDATA(GWEN_DIALOG, GTK2_GUI_DIALOG, dlg, xdlg, Gtk2Gui_Dialog_FreeData);

  /* set virtual functions */
  xdlg->setIntPropertyFn=GWEN_Dialog_SetSetIntPropertyFn(dlg, Gtk2Gui_Dialog_SetIntProperty);
  xdlg->getIntPropertyFn=GWEN_Dialog_SetGetIntPropertyFn(dlg, Gtk2Gui_Dialog_GetIntProperty);
  xdlg->setCharPropertyFn=GWEN_Dialog_SetSetCharPropertyFn(dlg, Gtk2Gui_Dialog_SetCharProperty);
  xdlg->getCharPropertyFn=GWEN_Dialog_SetGetCharPropertyFn(dlg, Gtk2Gui_Dialog_GetCharProperty);

}



void Gtk2Gui_Dialog_Unextend(GWEN_DIALOG *dlg) {
  GTK2_GUI_DIALOG *xdlg;

  assert(dlg);
  xdlg=GWEN_INHERIT_GETDATA(GWEN_DIALOG, GTK2_GUI_DIALOG, dlg);
  assert(xdlg);

  /* reset virtual functions */
  GWEN_Dialog_SetSetIntPropertyFn(dlg, xdlg->setIntPropertyFn);
  GWEN_Dialog_SetGetIntPropertyFn(dlg, xdlg->getIntPropertyFn);
  GWEN_Dialog_SetSetCharPropertyFn(dlg, xdlg->setCharPropertyFn);
  GWEN_Dialog_SetGetCharPropertyFn(dlg, xdlg->getCharPropertyFn);

  GWEN_INHERIT_UNLINK(GWEN_DIALOG, GTK2_GUI_DIALOG, dlg);
}



void GWENHYWFAR_CB Gtk2Gui_Dialog_FreeData(void *bp, void *p) {
  GTK2_GUI_DIALOG *xdlg;

  xdlg=(GTK2_GUI_DIALOG*) p;

  if (xdlg->mainWidget)
    gtk_widget_destroy(xdlg->mainWidget);

  GWEN_FREE_OBJECT(xdlg);
}



GtkWidget *Gtk2Gui_Dialog_GetMainWidget(const GWEN_DIALOG *dlg) {
  GTK2_GUI_DIALOG *xdlg;

  assert(dlg);
  xdlg=GWEN_INHERIT_GETDATA(GWEN_DIALOG, GTK2_GUI_DIALOG, dlg);
  assert(xdlg);

  return xdlg->mainWidget;
}



GWENHYWFAR_CB int Gtk2Gui_Dialog_SetIntProperty(GWEN_DIALOG *dlg,
    GWEN_WIDGET *w,
    GWEN_DIALOG_PROPERTY prop,
    int index,
    int value,
    int doSignal) {
  return GWEN_Widget_SetIntProperty(w, prop, index, value, doSignal);
}



GWENHYWFAR_CB int Gtk2Gui_Dialog_GetIntProperty(GWEN_DIALOG *dlg,
    GWEN_WIDGET *w,
    GWEN_DIALOG_PROPERTY prop,
    int index,
    int defaultValue) {
  return GWEN_Widget_GetIntProperty(w, prop, index, defaultValue);
}



GWENHYWFAR_CB int Gtk2Gui_Dialog_SetCharProperty(GWEN_DIALOG *dlg,
    GWEN_WIDGET *w,
    GWEN_DIALOG_PROPERTY prop,
    int index,
    const char *value,
    int doSignal) {
  return GWEN_Widget_SetCharProperty(w, prop, index, value, doSignal);
}



GWENHYWFAR_CB const char *Gtk2Gui_Dialog_GetCharProperty(GWEN_DIALOG *dlg,
    GWEN_WIDGET *w,
    GWEN_DIALOG_PROPERTY prop,
    int index,
    const char *defaultValue) {
  return GWEN_Widget_GetCharProperty(w, prop, index, defaultValue);
}



int Gtk2Gui_Dialog_Setup(GWEN_DIALOG *dlg, GtkWidget *parentWindow) {
  GTK2_GUI_DIALOG *xdlg;
  GWEN_WIDGET_TREE *wtree;
  GWEN_WIDGET *w;
  GtkWindow *gw;
  int rv;
  GList *tll;

  assert(dlg);
  xdlg=GWEN_INHERIT_GETDATA(GWEN_DIALOG, GTK2_GUI_DIALOG, dlg);
  assert(xdlg);

  wtree=GWEN_Dialog_GetWidgets(dlg);
  if (wtree==NULL) {
    DBG_ERROR(GWEN_LOGDOMAIN, "No widget tree in dialog");
    return GWEN_ERROR_NOT_FOUND;
  }
  w=GWEN_Widget_Tree_GetFirst(wtree);
  if (w==NULL) {
    DBG_ERROR(GWEN_LOGDOMAIN, "No widgets in dialog");
    return GWEN_ERROR_NOT_FOUND;
  }

  rv=Gtk2Gui_Dialog_SetupTree(w);
  if (rv<0) {
    DBG_INFO(GWEN_LOGDOMAIN, "here (%d)", rv);
    return rv;
  }

  gw=GTK_WINDOW(GWEN_Widget_GetImplData(w, GTK2_DIALOG_WIDGET_REAL));
  gtk_window_set_type_hint(GTK_WINDOW(gw), GDK_WINDOW_TYPE_HINT_DIALOG);
  gtk_window_set_position (GTK_WINDOW (gw), GTK_WIN_POS_CENTER_ON_PARENT);
  /*gtk_window_set_keep_above(GTK_WINDOW(gw), TRUE);*/
  xdlg->mainWidget=GTK_WIDGET(gw);

  tll=gtk_window_list_toplevels();
  if (tll) {
    GList* element;
    GtkWindow *topLevel=NULL;

    for (element = tll; element; element = g_list_next(element)) {
      GtkWindow* win = GTK_WINDOW(element->data);
      if (gtk_window_is_active(win)) {
        topLevel=win;
        break;
      }
    }
    g_list_free(tll);

    if (topLevel) {
      DBG_NOTICE(GWEN_LOGDOMAIN, "Found active window [%s]",
                 gtk_window_get_title(topLevel));
      gtk_window_set_transient_for(gw, topLevel);
    }
    else {
      DBG_ERROR(GWEN_LOGDOMAIN, "No active window found...");
    }
  }

  return 0;
}



void Gtk2Gui_Dialog_Leave(GWEN_DIALOG *dlg, int result) {
  GTK2_GUI_DIALOG *xdlg;
  GWEN_DIALOG *parent;

  /* get toplevel dialog, the one which actually is the GUI dialog */
  while( (parent=GWEN_Dialog_GetParentDialog(dlg)) )
    dlg=parent;

  assert(dlg);
  xdlg=GWEN_INHERIT_GETDATA(GWEN_DIALOG, GTK2_GUI_DIALOG, dlg);
  assert(xdlg);

  xdlg->response=result;
  if (g_main_loop_is_running(xdlg->loop))
    g_main_loop_quit(xdlg->loop);
}



static void
run_unmap_handler (GtkWindow *window, gpointer data) {
  GWEN_DIALOG *dlg;
  GTK2_GUI_DIALOG *xdlg;

  dlg=data;
  assert(dlg);
  xdlg=GWEN_INHERIT_GETDATA(GWEN_DIALOG, GTK2_GUI_DIALOG, dlg);
  assert(xdlg);

  Gtk2Gui_Dialog_Leave(dlg, 0);
}



static gint
run_delete_handler(GtkWindow *window,
                   GdkEventAny *event,
                   gpointer data) {
  GWEN_DIALOG *dlg;
  GTK2_GUI_DIALOG *xdlg;

  dlg=data;
  assert(dlg);
  xdlg=GWEN_INHERIT_GETDATA(GWEN_DIALOG, GTK2_GUI_DIALOG, dlg);
  assert(xdlg);

  Gtk2Gui_Dialog_Leave(dlg, 0);
  return TRUE; /* Do not destroy */
}



static void
run_destroy_handler(GtkWindow *window, gpointer data) {
  GWEN_DIALOG *dlg;
  GTK2_GUI_DIALOG *xdlg;

  dlg=data;
  assert(dlg);
  xdlg=GWEN_INHERIT_GETDATA(GWEN_DIALOG, GTK2_GUI_DIALOG, dlg);
  assert(xdlg);

  xdlg->destroyed=1;
}



int GTK2_Gui_Dialog_Run(GWEN_DIALOG *dlg, int untilEnd) {
  GTK2_GUI_DIALOG *xdlg;
  GtkWidget *g;

  assert(dlg);
  xdlg=GWEN_INHERIT_GETDATA(GWEN_DIALOG, GTK2_GUI_DIALOG, dlg);
  assert(xdlg);

  g=Gtk2Gui_Dialog_GetMainWidget(dlg);
  if (g==NULL) {
    DBG_ERROR(GWEN_LOGDOMAIN, "No main widget");
    Gtk2Gui_Dialog_Unextend(dlg);
    return GWEN_ERROR_INVALID;
  }

  xdlg->unmap_handler =
    g_signal_connect(g,
                     "unmap",
                     G_CALLBACK (run_unmap_handler),
                     dlg);

  xdlg->delete_handler =
    g_signal_connect(g,
                     "delete-event",
                     G_CALLBACK (run_delete_handler),
                     dlg);

  xdlg->destroy_handler =
    g_signal_connect(g,
                     "destroy",
                     G_CALLBACK (run_destroy_handler),
                     dlg);

  xdlg->loop=g_main_loop_new(NULL, FALSE);
  if (untilEnd)
    g_main_loop_run(xdlg->loop);
  else {
    GMainContext *ctx;

    ctx=g_main_loop_get_context(xdlg->loop);
    while(g_main_context_pending(ctx))
      g_main_context_iteration(ctx, FALSE);
  }
  g_main_loop_unref(xdlg->loop);

  if (!xdlg->destroyed) {
    g_signal_handler_disconnect(g, xdlg->unmap_handler);
    g_signal_handler_disconnect(g, xdlg->delete_handler);
    g_signal_handler_disconnect(g, xdlg->destroy_handler);
  }

  return xdlg->response;
}



int Gtk2Gui_Dialog_SetupTree(GWEN_WIDGET *w) {
  int rv;

  switch(GWEN_Widget_GetType(w)) {
  case GWEN_Widget_TypeDialog:
    rv=Gtk2Gui_WDialog_Setup(w);
    break;
  case GWEN_Widget_TypeLabel:
    rv=Gtk2Gui_WLabel_Setup(w);
    break;
  case GWEN_Widget_TypeGridLayout:
    rv=Gtk2Gui_WGridLayout_Setup(w);
    break;
  case GWEN_Widget_TypeVLayout:
    rv=Gtk2Gui_WVLayout_Setup(w);
    break;
  case GWEN_Widget_TypeHLayout:
    rv=Gtk2Gui_WHLayout_Setup(w);
    break;
  case GWEN_Widget_TypePushButton:
    rv=Gtk2Gui_WPushButton_Setup(w);
    break;
  case GWEN_Widget_TypeLineEdit:
    rv=Gtk2Gui_WLineEdit_Setup(w);
    break;
  case GWEN_Widget_TypeHLine:
    rv=Gtk2Gui_WHLine_Setup(w);
    break;
  case GWEN_Widget_TypeVLine:
    rv=Gtk2Gui_WVLine_Setup(w);
    break;
  case GWEN_Widget_TypeVSpacer:
    rv=Gtk2Gui_WVSpacer_Setup(w);
    break;
  case GWEN_Widget_TypeHSpacer:
    rv=Gtk2Gui_WHSpacer_Setup(w);
    break;
  case GWEN_Widget_TypeComboBox:
    rv=Gtk2Gui_WComboBox_Setup(w);
    break;
  case GWEN_Widget_TypeTextEdit:
    rv=Gtk2Gui_WTextEdit_Setup(w);
    break;
  case GWEN_Widget_TypeWidgetStack:
    rv=Gtk2Gui_WStack_Setup(w);
    break;
  case GWEN_Widget_TypeTabBook:
    rv=Gtk2Gui_WTabBook_Setup(w);
    break;
  case GWEN_Widget_TypeTabPage:
    /* just re-use vbox */
    GWEN_Widget_AddFlags(w, GWEN_WIDGET_FLAGS_FILLX | GWEN_WIDGET_FLAGS_FILLY);
    rv=Gtk2Gui_WVLayout_Setup(w);
    break;
  case GWEN_Widget_TypeGroupBox:
    rv=Gtk2Gui_WGroupBox_Setup(w);
    break;
  case GWEN_Widget_TypeTextBrowser:
    rv=Gtk2Gui_WTextBrowser_Setup(w);
    break;
  case GWEN_Widget_TypeProgressBar:
    rv=Gtk2Gui_WProgressBar_Setup(w);
    break;
  case GWEN_Widget_TypeSpinBox:
    rv=Gtk2Gui_WSpinBox_Setup(w);
    break;
  case GWEN_Widget_TypeListBox:
    rv=Gtk2Gui_WListBox_Setup(w);
    break;
  case GWEN_Widget_TypeCheckBox:
    rv=Gtk2Gui_WCheckBox_Setup(w);
    break;
  case GWEN_Widget_TypeScrollArea:
    rv=Gtk2Gui_WScrollArea_Setup(w);
    break;
  case GWEN_Widget_TypeRadioButton:
    rv=Gtk2Gui_WRadioButton_Setup(w);
    break;
  default:
    DBG_ERROR(GWEN_LOGDOMAIN, "Unhandled widget type %d", GWEN_Widget_GetType(w));
    rv=GWEN_ERROR_INVALID;
    break;
  }

  if (rv<0) {
    DBG_INFO(GWEN_LOGDOMAIN, "here (%d)", rv);
    return rv;
  }
  else {
    GWEN_WIDGET *wChild;

    /* handle children */
    wChild=GWEN_Widget_Tree_GetFirstChild(w);
    while(wChild) {
      /* recursion */
      rv=Gtk2Gui_Dialog_SetupTree(wChild);
      if (rv<0) {
        DBG_INFO(GWEN_LOGDOMAIN, "here (%d)", rv);
        return rv;
      }
      wChild=GWEN_Widget_Tree_GetNext(wChild);
    }
  }

  return 0;
}




int Gtk2Gui_GetRawText(const char *text, GWEN_BUFFER *tbuf) {
  const char *p=0;
  const char *p2=0;

  if (text==NULL)
    return 0;

  /* find begin of HTML area */
  p=text;
  while ((p=strchr(p, '<'))) {
    const char *t;

    t=p;
    t++;
    if (toupper(*t)=='H') {
      t++;
      if (toupper(*t)=='T') {
        t++;
        if (toupper(*t)=='M') {
          t++;
          if (toupper(*t)=='L') {
            t++;
            if (toupper(*t)=='>') {
              break;
            }
          }
        }
      }
    }
    p++;
  } /* while */

  /* find end of HTML area */
  if (p) {
    p2=p;
    p2+=6; /* skip "<html>" */
    while ((p2=strchr(p2, '<'))) {
      const char *t;

      t=p2;
      t++;
      if (toupper(*t)=='/') {
        t++;
        if (toupper(*t)=='H') {
          t++;
          if (toupper(*t)=='T') {
            t++;
            if (toupper(*t)=='M') {
              t++;
              if (toupper(*t)=='L') {
                t++;
                if (toupper(*t)=='>') {
                  break;
                }
              }
            }
          }
        }
      }
      p2++;
    } /* while */
  }

  if (p && p2) {
    int startPos;
    int endPos;

    p2+=7; /* skip "</html>" */

    startPos=(p-text);
    endPos=(p2-text);

    /* append stuff before startPos */
    if (startPos)
      GWEN_Buffer_AppendBytes(tbuf, text, startPos);
    if (*p2)
      GWEN_Buffer_AppendString(tbuf, p2);
    return 0;
  }
  else {
    GWEN_Buffer_AppendString(tbuf, text);
    return 0;
  }
}


