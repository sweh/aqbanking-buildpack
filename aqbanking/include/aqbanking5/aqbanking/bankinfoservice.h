/* This file is auto-generated from "bankinfoservice.xml" by the typemaker
   tool of Gwenhywfar. 
   Do not edit this file -- all changes will be lost! */
#ifndef BANKINFOSERVICE_H
#define BANKINFOSERVICE_H

/** @page P_AB_BANKINFO_SERVICE_PUBLIC AB_BankInfoService (public)
This page describes the properties of AB_BANKINFO_SERVICE
@anchor AB_BANKINFO_SERVICE_Type
<h3>Type</h3>
<p>
The following types have been registered with AqBanking:
<ul><li><b>HBCI</b>- German homebanking protocol</li><li><b>EBICS</b>- German and French homebanking protocol</li><li><b>OFX</b>- OFX direct connect protocol</li></ul></p>
<p>
Set this property with @ref AB_BankInfoService_SetType, 
get it with @ref AB_BankInfoService_GetType
</p>

@anchor AB_BANKINFO_SERVICE_Address
<h3>Address</h3>
<p>
For most services this is the URL or hostname of the server.</p>
<p>
Set this property with @ref AB_BankInfoService_SetAddress, 
get it with @ref AB_BankInfoService_GetAddress
</p>

@anchor AB_BANKINFO_SERVICE_Suffix
<h3>Suffix</h3>
<p>
For IP based services this is the port to be used (if omitted a default value suitable for the service is chosen).</p>
<p>
Set this property with @ref AB_BankInfoService_SetSuffix, 
get it with @ref AB_BankInfoService_GetSuffix
</p>

@anchor AB_BANKINFO_SERVICE_Pversion
<h3>Pversion</h3>
<p>
The content of this field depends on the service type. For
<b>HBCI</b>
this is the protocol version to be used:
<ul><li>2.01</li><li>2.10</li><li>2.20</li></ul>
For
<b>EBICS</b>
this is also the protocol version:
<ul><li>H002</li><li>H003</li></ul></p>
<p>
Set this property with @ref AB_BankInfoService_SetPversion, 
get it with @ref AB_BankInfoService_GetPversion
</p>

@anchor AB_BANKINFO_SERVICE_Mode
<h3>Mode</h3>
<p>
The content of this field depends on the service type. For
<b>HBCI</b>
the following values are used:
<ul><li>DDV</li><li>RDH1</li><li>RDH2</li><li>RDH3</li><li>RDH4</li><li>RDH5</li><li>RDH6</li><li>RDH7</li><li>RDH8</li><li>RDH9</li><li>RDH10</li><li>PINTAN</li></ul></p>
<p>
Set this property with @ref AB_BankInfoService_SetMode, 
get it with @ref AB_BankInfoService_GetMode
</p>

@anchor AB_BANKINFO_SERVICE_UserFlags
<h3>UserFlags</h3>
<p>
This field contains some service-dependent user flags. For HBCI these are the flags of AH_USER (e.g. forceSslv3 etc).</p>
<p>
Set this property with @ref AB_BankInfoService_SetUserFlags, 
get it with @ref AB_BankInfoService_GetUserFlags
</p>

@anchor AB_BANKINFO_SERVICE_Hversion
<h3>Hversion</h3>
<p>
For HTTP-based protocols this is the HTTP version to be used:
<ul><li>1.0</li><li>1.1</li></ul></p>
<p>
Set this property with @ref AB_BankInfoService_SetHversion, 
get it with @ref AB_BankInfoService_GetHversion
</p>

@anchor AB_BANKINFO_SERVICE_Aux1
<h3>Aux1</h3>
<p>
This is a multi purpose field to be used by a bankinfo plugin as it sees fit. OFX uses this to store the FID from the bankinfo file. EBICS stores the HOSTID here.</p>
<p>
Set this property with @ref AB_BankInfoService_SetAux1, 
get it with @ref AB_BankInfoService_GetAux1
</p>

@anchor AB_BANKINFO_SERVICE_Aux2
<h3>Aux2</h3>
<p>
This is a multi purpose field to be used by a bankinfo plugin as it sees fit. OFX uses this to store the ORG field from the bankinfo file.</p>
<p>
Set this property with @ref AB_BankInfoService_SetAux2, 
get it with @ref AB_BankInfoService_GetAux2
</p>

@anchor AB_BANKINFO_SERVICE_Aux3
<h3>Aux3</h3>
<p>
This is a multi purpose field to be used by a bankinfo plugin as it sees fit. OFX uses this to store the APPID field from the bankinfo file.</p>
<p>
Set this property with @ref AB_BankInfoService_SetAux3, 
get it with @ref AB_BankInfoService_GetAux3
</p>

@anchor AB_BANKINFO_SERVICE_Aux4
<h3>Aux4</h3>
<p>
This is a multi purpose field to be used by a bankinfo plugin as it sees fit. OFX uses this to store the APPVER field from the bankinfo file.</p>
<p>
Set this property with @ref AB_BankInfoService_SetAux4, 
get it with @ref AB_BankInfoService_GetAux4
</p>

*/
#ifdef __cplusplus
extern "C" {
#endif

typedef struct AB_BANKINFO_SERVICE AB_BANKINFO_SERVICE;

#ifdef __cplusplus
} /* __cplusplus */
#endif

#include <gwenhywfar/db.h>
#include <gwenhywfar/misc.h>
#include <gwenhywfar/list2.h>
/* headers */
#include <gwenhywfar/types.h>
#include <aqbanking/error.h>

#ifdef __cplusplus
extern "C" {
#endif


GWEN_LIST_FUNCTION_LIB_DEFS(AB_BANKINFO_SERVICE, AB_BankInfoService, AQBANKING_API)
AQBANKING_API AB_BANKINFO_SERVICE_LIST *AB_BankInfoService_List_dup(const AB_BANKINFO_SERVICE_LIST *stl);

GWEN_LIST2_FUNCTION_LIB_DEFS(AB_BANKINFO_SERVICE, AB_BankInfoService, AQBANKING_API)

/** Destroys all objects stored in the given LIST2 and the list itself
*/
AQBANKING_API void AB_BankInfoService_List2_freeAll(AB_BANKINFO_SERVICE_LIST2 *stl);

/** Creates a new object.
*/
AQBANKING_API AB_BANKINFO_SERVICE *AB_BankInfoService_new(void);
/** Creates an object from the data in the given GWEN_DB_NODE
*/
AQBANKING_API AB_BANKINFO_SERVICE *AB_BankInfoService_fromDb(GWEN_DB_NODE *db);
/** Creates and returns a deep copy of thegiven object.
*/
AQBANKING_API AB_BANKINFO_SERVICE *AB_BankInfoService_dup(const AB_BANKINFO_SERVICE*st);
/** Destroys the given object.
*/
AQBANKING_API void AB_BankInfoService_free(AB_BANKINFO_SERVICE *st);
/** Increments the usage counter of the given object, so an additional free() is needed to destroy the object.
*/
AQBANKING_API void AB_BankInfoService_Attach(AB_BANKINFO_SERVICE *st);
/** Reads data from a GWEN_DB.
*/
AQBANKING_API int AB_BankInfoService_ReadDb(AB_BANKINFO_SERVICE *st, GWEN_DB_NODE *db);
/** Stores an object in the given GWEN_DB_NODE
*/
AQBANKING_API int AB_BankInfoService_toDb(const AB_BANKINFO_SERVICE*st, GWEN_DB_NODE *db);
/** Returns 0 if this object has not been modified, !=0 otherwise
*/
AQBANKING_API int AB_BankInfoService_IsModified(const AB_BANKINFO_SERVICE *st);
/** Sets the modified state of the given object
*/
AQBANKING_API void AB_BankInfoService_SetModified(AB_BANKINFO_SERVICE *st, int i);

/**
* Returns the property @ref AB_BANKINFO_SERVICE_Type
*/
AQBANKING_API const char *AB_BankInfoService_GetType(const AB_BANKINFO_SERVICE *el);
/**
* Set the property @ref AB_BANKINFO_SERVICE_Type
*/
AQBANKING_API void AB_BankInfoService_SetType(AB_BANKINFO_SERVICE *el, const char *d);

/**
* Returns the property @ref AB_BANKINFO_SERVICE_Address
*/
AQBANKING_API const char *AB_BankInfoService_GetAddress(const AB_BANKINFO_SERVICE *el);
/**
* Set the property @ref AB_BANKINFO_SERVICE_Address
*/
AQBANKING_API void AB_BankInfoService_SetAddress(AB_BANKINFO_SERVICE *el, const char *d);

/**
* Returns the property @ref AB_BANKINFO_SERVICE_Suffix
*/
AQBANKING_API const char *AB_BankInfoService_GetSuffix(const AB_BANKINFO_SERVICE *el);
/**
* Set the property @ref AB_BANKINFO_SERVICE_Suffix
*/
AQBANKING_API void AB_BankInfoService_SetSuffix(AB_BANKINFO_SERVICE *el, const char *d);

/**
* Returns the property @ref AB_BANKINFO_SERVICE_Pversion
*/
AQBANKING_API const char *AB_BankInfoService_GetPversion(const AB_BANKINFO_SERVICE *el);
/**
* Set the property @ref AB_BANKINFO_SERVICE_Pversion
*/
AQBANKING_API void AB_BankInfoService_SetPversion(AB_BANKINFO_SERVICE *el, const char *d);

/**
* Returns the property @ref AB_BANKINFO_SERVICE_Mode
*/
AQBANKING_API const char *AB_BankInfoService_GetMode(const AB_BANKINFO_SERVICE *el);
/**
* Set the property @ref AB_BANKINFO_SERVICE_Mode
*/
AQBANKING_API void AB_BankInfoService_SetMode(AB_BANKINFO_SERVICE *el, const char *d);

/**
* Returns the property @ref AB_BANKINFO_SERVICE_UserFlags
*/
AQBANKING_API uint32_t AB_BankInfoService_GetUserFlags(const AB_BANKINFO_SERVICE *el);
/**
* Set the property @ref AB_BANKINFO_SERVICE_UserFlags
*/
AQBANKING_API void AB_BankInfoService_SetUserFlags(AB_BANKINFO_SERVICE *el, uint32_t d);

/**
* Returns the property @ref AB_BANKINFO_SERVICE_Hversion
*/
AQBANKING_API const char *AB_BankInfoService_GetHversion(const AB_BANKINFO_SERVICE *el);
/**
* Set the property @ref AB_BANKINFO_SERVICE_Hversion
*/
AQBANKING_API void AB_BankInfoService_SetHversion(AB_BANKINFO_SERVICE *el, const char *d);

/**
* Returns the property @ref AB_BANKINFO_SERVICE_Aux1
*/
AQBANKING_API const char *AB_BankInfoService_GetAux1(const AB_BANKINFO_SERVICE *el);
/**
* Set the property @ref AB_BANKINFO_SERVICE_Aux1
*/
AQBANKING_API void AB_BankInfoService_SetAux1(AB_BANKINFO_SERVICE *el, const char *d);

/**
* Returns the property @ref AB_BANKINFO_SERVICE_Aux2
*/
AQBANKING_API const char *AB_BankInfoService_GetAux2(const AB_BANKINFO_SERVICE *el);
/**
* Set the property @ref AB_BANKINFO_SERVICE_Aux2
*/
AQBANKING_API void AB_BankInfoService_SetAux2(AB_BANKINFO_SERVICE *el, const char *d);

/**
* Returns the property @ref AB_BANKINFO_SERVICE_Aux3
*/
AQBANKING_API const char *AB_BankInfoService_GetAux3(const AB_BANKINFO_SERVICE *el);
/**
* Set the property @ref AB_BANKINFO_SERVICE_Aux3
*/
AQBANKING_API void AB_BankInfoService_SetAux3(AB_BANKINFO_SERVICE *el, const char *d);

/**
* Returns the property @ref AB_BANKINFO_SERVICE_Aux4
*/
AQBANKING_API const char *AB_BankInfoService_GetAux4(const AB_BANKINFO_SERVICE *el);
/**
* Set the property @ref AB_BANKINFO_SERVICE_Aux4
*/
AQBANKING_API void AB_BankInfoService_SetAux4(AB_BANKINFO_SERVICE *el, const char *d);


#ifdef __cplusplus
} /* __cplusplus */
#endif


#endif /* BANKINFOSERVICE_H */
