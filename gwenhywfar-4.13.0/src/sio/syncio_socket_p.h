/***************************************************************************
 begin       : Tue Apr 27 2010
 copyright   : (C) 2010 by Martin Preuss
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


#ifndef GWENHYWFAR_SYNCIO_SOCKET_P_H
#define GWENHYWFAR_SYNCIO_SOCKET_P_H

#include <gwenhywfar/syncio_socket.h>



typedef struct GWEN_SYNCIO_SOCKET GWEN_SYNCIO_SOCKET;
struct GWEN_SYNCIO_SOCKET {
  GWEN_SOCKETTYPE socketType;
  GWEN_AddressFamily addressFamily;

  char *address;
  int port;

  GWEN_SOCKET *socket;
};


static void GWENHYWFAR_CB GWEN_SyncIo_Socket_FreeData(void *bp, void *p);


int GWENHYWFAR_CB GWEN_SyncIo_Socket_Connect(GWEN_SYNCIO *sio);
int GWENHYWFAR_CB GWEN_SyncIo_Socket_Disconnect(GWEN_SYNCIO *sio);


int GWENHYWFAR_CB GWEN_SyncIo_Socket_Read(GWEN_SYNCIO *sio,
    uint8_t *buffer,
    uint32_t size);



int GWENHYWFAR_CB GWEN_SyncIo_Socket_Write(GWEN_SYNCIO *sio,
    const uint8_t *buffer,
    uint32_t size);



#endif


