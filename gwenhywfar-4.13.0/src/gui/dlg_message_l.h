/***************************************************************************
 begin       : Wed Feb 17 2010
 copyright   : (C) 2010 by Martin Preuss
 email       : martin@libchipcard.de

 ***************************************************************************
 *          Please see toplevel file COPYING for license details           *
 ***************************************************************************/


#ifndef GWEN_GUI_DLG_MESSAGE_L_H
#define GWEN_GUI_DLG_MESSAGE_L_H


#include <gwenhywfar/dialog.h>



GWEN_DIALOG *GWEN_DlgMessage_new(uint32_t flags,
                                 const char *title,
                                 const char *text,
                                 const char *b1,
                                 const char *b2,
                                 const char *b3);


int GWEN_DlgMessage_GetResponse(const GWEN_DIALOG *dlg);


#endif



