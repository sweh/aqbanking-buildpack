/***************************************************************************
    begin       : Sun Dec 05 2003
    copyright   : (C) 2003-2010 by Martin Preuss
    email       : martin@libchipcard.de

 ***************************************************************************
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Lesser General Public            *
 *   License as published by the Free Software Foundation; either          *
 *   version 2.1 of the License, or (at your option) any later version.    *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston,                 *
 *   MA  02111-1307  USA                                                   *
 *                                                                         *
 ***************************************************************************/


#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#define DISABLE_DEBUGLOG

#include "inherit_p.h"
#include <gwenhywfar/misc.h>
#include <gwenhywfar/debug.h>
#include <gwenhywfar/gwenhywfarapi.h>

#include <string.h>



GWEN_LIST_FUNCTIONS(GWEN_INHERITDATA, GWEN_InheritData)



GWEN_INHERITDATA *GWEN_InheritData_new(const char *t,
                                       uint32_t id,
                                       void *data,
                                       void *baseData,
                                       GWEN_INHERIT_FREEDATAFN freeDataFn) {
  GWEN_INHERITDATA *d;

  assert(t);
  GWEN_NEW_OBJECT(GWEN_INHERITDATA, d);
  GWEN_LIST_INIT(GWEN_INHERITDATA, d);
  d->typeName=strdup(t);
  d->id=id;
  d->data=data;
  d->baseData=baseData;
  d->freeDataFn=freeDataFn;

  DBG_VERBOUS(GWEN_LOGDOMAIN,
              "Created inheritance for type \"%s\" (%08x)", t, id);
  return d;
}



void GWEN_InheritData_free(GWEN_INHERITDATA *d) {
  if (d) {
    if (d->freeDataFn)
      d->freeDataFn(d->baseData, d->data);
    free(d->typeName);
    GWEN_LIST_FINI(GWEN_INHERITDATA, d);
    GWEN_FREE_OBJECT(d);
  }
}



void GWEN_InheritData_freeData(GWEN_INHERITDATA *d) {
  if (d) {
    DBG_VERBOUS(GWEN_LOGDOMAIN,
                "Freeing data for type \"%s\"",
                d->typeName);
    if (d->freeDataFn)
      d->freeDataFn(d->baseData, d->data);
    d->freeDataFn=NULL;
    d->data=NULL;
  }
}



void GWEN_InheritData_clear(GWEN_INHERITDATA *d) {
  assert(d);
  d->freeDataFn=0;
  d->data=0;
}



const char *GWEN_InheritData_GetTypeName(const GWEN_INHERITDATA *d) {
  assert(d);
  return d->typeName;
}



uint32_t GWEN_InheritData_GetId(const GWEN_INHERITDATA *d) {
  assert(d);
  return d->id;
}



void *GWEN_InheritData_GetData(const GWEN_INHERITDATA *d) {
  assert(d);
  return d->data;
}



GWEN_INHERIT_FREEDATAFN
GWEN_InheritData_GetFreeDataFn(const GWEN_INHERITDATA *d) {
  assert(d);
  return d->freeDataFn;
}





uint32_t GWEN_Inherit_MakeId(const char *typeName) {
  unsigned int i, j;
  uint32_t result;

  result=0;
  j=strlen(typeName);
  for (i=0; i<j; i++) {
    uint32_t tmpResult;
    unsigned char c;

    tmpResult=result<<8;
    c=((result>>24)&0xff);
    result=tmpResult|c;
    result^=(unsigned char)(typeName[i]);
  }

  DBG_VERBOUS(GWEN_LOGDOMAIN,
              "Id for type \"%s\" is \"%08x\"",
              typeName, result);
  return result;
}



void *GWEN_Inherit_FindData(GWEN_INHERITDATA_LIST *l,
                            uint32_t id,
                            int wantCreate) {
  GWEN_INHERITDATA *ih;

  assert(l);

  DBG_VERBOUS(GWEN_LOGDOMAIN,
              "Searching for inheritance id \"%08x\"", id);
  ih=GWEN_InheritData_List_First(l);
  while(ih) {
    DBG_VERBOUS(GWEN_LOGDOMAIN,
                "Checking type \"%s\" (%08x) against %08x",
                ih->typeName, ih->id, id);
    if (ih->id==id)
      return ih->data;
    ih=GWEN_InheritData_List_Next(ih);
  } /* while */
  if (!wantCreate) {
    DBG_WARN(GWEN_LOGDOMAIN,
             "Type \"%08x\" not derived from this base type", id);
  }
  return 0;
}



GWEN_INHERITDATA *GWEN_Inherit_FindEntry(GWEN_INHERITDATA_LIST *l,
    uint32_t id,
    int wantCreate) {
  GWEN_INHERITDATA *ih;

  assert(l);

  DBG_VERBOUS(GWEN_LOGDOMAIN, "Searching for inheritance id \"%08x\"", id);
  ih=GWEN_InheritData_List_First(l);
  while(ih) {
    DBG_VERBOUS(GWEN_LOGDOMAIN, "Checking type \"%s\" (%08x) against %08x",
                ih->typeName, ih->id, id);
    if (ih->id==id)
      return ih;
    ih=GWEN_InheritData_List_Next(ih);
  } /* while */
  if (!wantCreate) {
    DBG_WARN(GWEN_LOGDOMAIN,
             "Type \"%08x\" not derived from this base type", id);
  }
  return 0;
}





