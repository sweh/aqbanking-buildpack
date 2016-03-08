/***************************************************************************
 begin       : Mon Feb 22 2010
 copyright   : (C) 2010 by Martin Preuss
 email       : martin@libchipcard.de

 ***************************************************************************
 *          Please see toplevel file COPYING for license details           *
 ***************************************************************************/


#ifndef HTML_G_TABLEROW_L_H
#define HTML_G_TABLEROW_L_H


#include "htmlgroup_l.h"


HTML_GROUP *HtmlGroup_TableRow_new(const char *groupName,
                                   HTML_GROUP *parent,
                                   GWEN_XML_CONTEXT *ctx);

int HtmlGroup_TableRow_GetColumns(const HTML_GROUP *g);
void HtmlGroup_TableRow_SetRow(HTML_GROUP *g, int row);

#endif

