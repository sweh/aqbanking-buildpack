/***************************************************************************
 $RCSfile$
                             -------------------
    cvs         : $Id: idlist.c 705 2005-02-23 02:16:57Z aquamaniac $
    begin       : Mon Mar 01 2004
    copyright   : (C) 2004 by Martin Preuss
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


#include "idmap_p.h"

#include <gwenhywfar/misc.h>
#include <gwenhywfar/debug.h>


#include <stdlib.h>
#include <assert.h>
#include <string.h>



GWEN_IDMAP *GWEN_IdMap_new(GWEN_IDMAP_ALGO algo) {
  GWEN_IDMAP *map;

  GWEN_NEW_OBJECT(GWEN_IDMAP, map);
  map->algo=algo;
  switch(algo) {
  case GWEN_IdMapAlgo_Hex4:
    GWEN_IdMapHex4_Extend(map);
    break;
  case GWEN_IdMapAlgo_Unknown:
  default:
    DBG_ERROR(GWEN_LOGDOMAIN, "Unknown algo %d", algo);
    GWEN_IdMap_free(map);
    return 0;
  }

  return map;
}



void GWEN_IdMap_free(GWEN_IDMAP *map) {
  assert(map);
  if (map->freeDataFn)
    map->freeDataFn(map);
  GWEN_FREE_OBJECT(map);
}



GWEN_IDMAP_RESULT GWEN_IdMap_Insert(GWEN_IDMAP *map,
                                    uint32_t id,
                                    void *ptr) {
  assert(map);
  assert(ptr);
  assert(map->setPairFn);
  return map->setPairFn(map, id, ptr);
}



GWEN_IDMAP_RESULT GWEN_IdMap_Remove(GWEN_IDMAP *map,
                                    uint32_t id) {
  assert(map);
  assert(map->setPairFn);
  return map->setPairFn(map, id, 0);
}



void *GWEN_IdMap_Find(GWEN_IDMAP *map, uint32_t id) {
  assert(map);
  assert(map->getPairFn);
  return map->getPairFn(map, id);
}



GWEN_IDMAP_RESULT GWEN_IdMap_GetFirst(const GWEN_IDMAP *map,
                                      uint32_t *pid) {
  assert(map);
  assert(map->findFirstFn);
  return map->findFirstFn(map, pid);
}



GWEN_IDMAP_RESULT GWEN_IdMap_GetNext(const GWEN_IDMAP *map,
                                     uint32_t *pid) {
  assert(map);
  assert(map->findNextFn);
  return map->findNextFn(map, pid);
}



uint32_t GWEN_IdMap_GetSize(const GWEN_IDMAP *map) {
  assert(map);
  return map->count;
}



void GWEN_IdMap_Clear(GWEN_IDMAP *map) {
  assert(map);
  if (map->freeDataFn)
    map->freeDataFn(map);
  map->algoData=0;

  switch(map->algo) {
  case GWEN_IdMapAlgo_Hex4:
    GWEN_IdMapHex4_Extend(map);
    break;
  case GWEN_IdMapAlgo_Unknown:
  default:
    DBG_ERROR(GWEN_LOGDOMAIN, "Unknown algo %d", map->algo);
  }
}



void GWEN_IdMap_Dump(GWEN_IDMAP *map, FILE *f, int indent) {
  assert(map);
  if (map->dumpFn)
    map->dumpFn(map, f, indent);
  else {
    DBG_ERROR(GWEN_LOGDOMAIN, "No dump fn");
  }
}





/* _________________________________________________________________________
 * AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
 *                             Algo: HEX4
 * YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY
 */


void GWEN_IdMapHex4_Extend(GWEN_IDMAP *map) {
  GWEN_IDMAP_HEX4 *xmap;

  GWEN_NEW_OBJECT(GWEN_IDMAP_HEX4, xmap);
  xmap->table=GWEN_IdMapHex4Map_new(0, 0);
  map->algoData=(void*)xmap;
  map->setPairFn=GWEN_IdMapHex4_Insert;
  map->getPairFn=GWEN_IdMapHex4_Find;
  map->findFirstFn=GWEN_IdMapHex4_FindFirst;
  map->findNextFn=GWEN_IdMapHex4_FindNext;
  map->freeDataFn=GWEN_IdMapHex4_free;
  map->dumpFn=GWEN_IdMapHex4_Dump;
}



void GWEN_IdMapHex4_free(GWEN_IDMAP *map) {
  GWEN_IDMAP_HEX4 *xmap;

  xmap=(GWEN_IDMAP_HEX4*)map->algoData;
  GWEN_IdMapHex4Map_free(xmap->table);
  GWEN_FREE_OBJECT(xmap);
}



GWEN_IDMAP_HEX4_TABLE *GWEN_IdMapHex4Map_new(GWEN_IDMAP_HEX4_TABLE *p,
    int isPtrTable) {
  GWEN_IDMAP_HEX4_TABLE *t;

  GWEN_NEW_OBJECT(GWEN_IDMAP_HEX4_TABLE, t);
  t->parent=p;
  t->isPtrTable=isPtrTable;
  return t;
}



void GWEN_IdMapHex4Map_free(GWEN_IDMAP_HEX4_TABLE *t) {
  if (t) {
    if (!(t->isPtrTable)) {
      int i;

      for(i=0; i<16; i++) {
        if (t->ptrs[i])
          GWEN_IdMapHex4Map_free(t->ptrs[i]);
      }
    }
    GWEN_FREE_OBJECT(t);
  }
}



GWEN_IDMAP_RESULT GWEN_IdMapHex4_Insert(GWEN_IDMAP *map,
                                        uint32_t id,
                                        void *ptr) {
  GWEN_IDMAP_HEX4 *xmap;
  void **p;
  GWEN_IDMAP_HEX4_TABLE *t;

  xmap=(GWEN_IDMAP_HEX4*)map->algoData;

  t=xmap->table;
  p=&(t->ptrs[(id>>28) & 0xf]);
  if (!*p) {
    if (ptr==0)
      return GWEN_IdMapResult_NotFound;
    *p=(void*)GWEN_IdMapHex4Map_new(t, 0);
  }
  t=(GWEN_IDMAP_HEX4_TABLE*) *p;

  p=&(t->ptrs[(id>>24) & 0xf]);
  if (!*p) {
    if (ptr==0)
      return GWEN_IdMapResult_NotFound;
    *p=(void*)GWEN_IdMapHex4Map_new(t, 0);
  }
  t=(GWEN_IDMAP_HEX4_TABLE*) *p;

  p=&(t->ptrs[(id>>20) & 0xf]);
  if (!*p) {
    if (ptr==0)
      return GWEN_IdMapResult_NotFound;
    *p=(void*)GWEN_IdMapHex4Map_new(t, 0);
  }
  t=(GWEN_IDMAP_HEX4_TABLE*) *p;

  p=&(t->ptrs[(id>>16) & 0xf]);
  if (!*p) {
    if (ptr==0)
      return GWEN_IdMapResult_NotFound;
    *p=(void*)GWEN_IdMapHex4Map_new(t, 0);
  }
  t=(GWEN_IDMAP_HEX4_TABLE*) *p;

  p=&(t->ptrs[(id>>12) & 0xf]);
  if (!*p) {
    if (ptr==0)
      return GWEN_IdMapResult_NotFound;
    *p=(void*)GWEN_IdMapHex4Map_new(t, 0);
  }
  t=(GWEN_IDMAP_HEX4_TABLE*) *p;

  p=&(t->ptrs[(id>>8) & 0xf]);
  if (!*p) {
    if (ptr==0)
      return GWEN_IdMapResult_NotFound;
    *p=(void*)GWEN_IdMapHex4Map_new(t, 0);
  }
  t=(GWEN_IDMAP_HEX4_TABLE*) *p;

  p=&(t->ptrs[(id>>4) & 0xf]);
  if (!*p) {
    if (ptr==0)
      return GWEN_IdMapResult_NotFound;
    *p=(void*)GWEN_IdMapHex4Map_new(t, 1);
  }
  t=(GWEN_IDMAP_HEX4_TABLE*) *p;

  p=&(t->ptrs[id & 0xf]);
  *p=ptr;

  if (ptr==0) {
    assert(map->count);
    map->count--;
    /* do some cleanup */
    for (;;) {
      GWEN_IDMAP_HEX4_TABLE *parent;
      int i;

      parent=t->parent;
      id>>=4;
      if (parent==0)
        break;
      for (i=0; i<16; i++) {
        if (t->ptrs[i]!=0)
          break;
      }
      if (i<16)
        break;
      /* DBG_ERROR(0, "Deleting table %x", id); */
      GWEN_IdMapHex4Map_free(t);
      parent->ptrs[id & 0xf]=0;
      t=parent;
    }
  }
  else
    map->count++;

  return GWEN_IdMapResult_Ok;
}



void *GWEN_IdMapHex4_Find(GWEN_IDMAP *map, uint32_t id) {
  GWEN_IDMAP_HEX4 *xmap;
  GWEN_IDMAP_HEX4_TABLE *t;

  xmap=(GWEN_IDMAP_HEX4*)map->algoData;

  t=xmap->table;
  if (!t)
    return 0;
  t=(GWEN_IDMAP_HEX4_TABLE*)(t->ptrs[(id>>28)&0xf]);
  if (!t)
    return 0;
  t=(GWEN_IDMAP_HEX4_TABLE*)(t->ptrs[(id>>24)&0xf]);
  if (!t)
    return 0;
  t=(GWEN_IDMAP_HEX4_TABLE*)(t->ptrs[(id>>20)&0xf]);
  if (!t)
    return 0;
  t=(GWEN_IDMAP_HEX4_TABLE*)(t->ptrs[(id>>16)&0xf]);
  if (!t)
    return 0;
  t=(GWEN_IDMAP_HEX4_TABLE*)(t->ptrs[(id>>12)&0xf]);
  if (!t)
    return 0;
  t=(GWEN_IDMAP_HEX4_TABLE*)(t->ptrs[(id>>8)&0xf]);
  if (!t)
    return 0;
  t=(GWEN_IDMAP_HEX4_TABLE*)(t->ptrs[(id>>4)&0xf]);
  if (!t)
    return 0;

  return (t->ptrs[id & 0xf]);
}



GWEN_IDMAP_HEX4_TABLE *GWEN_IdMapHex4__GetTable(GWEN_IDMAP_HEX4_TABLE *t,
    uint32_t id) {
  void **p;

  p=&(t->ptrs[(id>>28) & 0xf]);
  if (!*p)
    return 0;
  t=(GWEN_IDMAP_HEX4_TABLE*) *p;

  p=&(t->ptrs[(id>>24) & 0xf]);
  if (!*p)
    return 0;
  t=(GWEN_IDMAP_HEX4_TABLE*) *p;

  p=&(t->ptrs[(id>>20) & 0xf]);
  if (!*p)
    return 0;
  t=(GWEN_IDMAP_HEX4_TABLE*) *p;

  p=&(t->ptrs[(id>>16) & 0xf]);
  if (!*p)
    return 0;
  t=(GWEN_IDMAP_HEX4_TABLE*) *p;

  p=&(t->ptrs[(id>>12) & 0xf]);
  if (!*p)
    return 0;
  t=(GWEN_IDMAP_HEX4_TABLE*) *p;

  p=&(t->ptrs[(id>>8) & 0xf]);
  if (!*p)
    return 0;
  t=(GWEN_IDMAP_HEX4_TABLE*) *p;

  p=&(t->ptrs[(id>>4) & 0xf]);
  if (!*p)
    return 0;
  t=(GWEN_IDMAP_HEX4_TABLE*) *p;

  return t;
}



GWEN_IDMAP_HEX4_TABLE *GWEN_IdMapHex4__GetFirstTable(GWEN_IDMAP_HEX4_TABLE *t,
    uint32_t *pid) {
  uint32_t id;
  int i;

  /* id=*pid; */
  id=0;
  for (i=0; i<16; i++) {
    if (t->ptrs[i]) {
      uint32_t lid;

      lid=(id<<4) | i;
      if (t->isPtrTable) {
        *pid=lid;
        return t;
      }
      else {
        GWEN_IDMAP_HEX4_TABLE *dt;

        dt=GWEN_IdMapHex4__GetFirstTable((GWEN_IDMAP_HEX4_TABLE*)(t->ptrs[i]),
                                         &lid);
        if (dt) {
          *pid=lid;
          return dt;
        }
      }
    }
  }
  return 0;
}



GWEN_IDMAP_HEX4_TABLE *GWEN_IdMapHex4__GetNextTable(GWEN_IDMAP_HEX4_TABLE *t,
    uint32_t *pid,
    int incr) {
  uint32_t id;

  id=*pid;
  while (t) {
    int i;

    if (incr) {
      while (t && (id & 0xf)==0xf) {
        t=t->parent;
        id>>=4;
      }
      if (!t)
        return 0;
      id++;
    }

    for (i=id & 0xf; i<16; i++) {
      if (t->ptrs[i]) {
        uint32_t lid;

        lid=((id & 0xfffffff0) | i);
        if (t->isPtrTable) {
          *pid=lid;
          return t;
        }
        else {
          GWEN_IDMAP_HEX4_TABLE *dt;

          lid=lid<<4;
          dt=GWEN_IdMapHex4__GetNextTable((GWEN_IDMAP_HEX4_TABLE*)(t->ptrs[i]),
                                          &lid, 0);
          if (dt) {
            *pid=lid;
            return dt;
          }
        }
      }
    }

    id>>=4;
    t=t->parent;
  }
  return 0;
}



GWEN_IDMAP_RESULT GWEN_IdMapHex4_FindFirst(const GWEN_IDMAP *map,
    uint32_t *pid) {

  GWEN_IDMAP_HEX4_TABLE *t;
  GWEN_IDMAP_HEX4 *xmap;
  uint32_t id;

  xmap=(GWEN_IDMAP_HEX4*)map->algoData;

  t=GWEN_IdMapHex4__GetFirstTable(xmap->table, &id);
  if (t) {
    *pid=id;
    return GWEN_IdMapResult_Ok;
  }

  return GWEN_IdMapResult_NotFound;
}



GWEN_IDMAP_RESULT GWEN_IdMapHex4_FindNext(const GWEN_IDMAP *map,
    uint32_t *pid) {
  GWEN_IDMAP_HEX4_TABLE *t;
  GWEN_IDMAP_HEX4 *xmap;
  uint32_t id;

  xmap=(GWEN_IDMAP_HEX4*)map->algoData;

  id=*pid;

  t=GWEN_IdMapHex4__GetTable(xmap->table, id);
  assert(t);

  t=GWEN_IdMapHex4__GetNextTable(t, &id, 1);
  if (t) {
    *pid=id;
    return GWEN_IdMapResult_Ok;
  }

  return GWEN_IdMapResult_NotFound;
}



void GWEN_IdMapHex4__Dump(GWEN_IDMAP_HEX4_TABLE *tbl, FILE *f, int indent) {
  int i;

  for (i=0; i<16; i++) {
    int j;

    if (tbl->ptrs[i]) {
      for (j=0; j<indent; j++)
        fprintf(f, " ");
      fprintf(f, "Id: %01x Ptr: %p\n",
              i, tbl->ptrs[i]);
      if (!(tbl->isPtrTable))
        GWEN_IdMapHex4__Dump(tbl->ptrs[i], f, indent+2);
    }
  }
}



void GWEN_IdMapHex4_Dump(GWEN_IDMAP *map, FILE *f, int indent) {
  GWEN_IDMAP_HEX4 *xmap;

  xmap=(GWEN_IDMAP_HEX4*)map->algoData;
  GWEN_IdMapHex4__Dump(xmap->table, f, indent);
}






