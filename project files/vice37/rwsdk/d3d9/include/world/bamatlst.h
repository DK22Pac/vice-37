/***************************************************************************
 *                                                                         *
 * Module  : bamatlst.h                                                    *
 *                                                                         *
 * Purpose : Material list handling                                        *
 *                                                                         *
 **************************************************************************/

#ifndef RWMATLST_H
#define RWMATLST_H

/****************************************************************************
 Includes
 */

#include "../src/rwcore.h"
#include "bamateri.h"

/****************************************************************************
 Defines
 */

/* RWPUBLIC */
/****************************************************************************
 Global Types
 */

typedef struct RpMaterialList RpMaterialList;

#if (!defined(DOXYGEN))
struct RpMaterialList
{
    RpMaterial     **materials;
    RwInt32        numMaterials;
    RwInt32        space;
};
#endif /* (!defined(DOXYGEN)) */

/****************************************************************************
 Function prototypes
 */

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

#define rpMaterialListGetNumMaterials(mlist) ((mlist)->numMaterials)

/* Setting up and destroying material lists */
RWEXPORT RpMaterialList* RWAPI _rpMaterialListInitialize(RpMaterialList *matList);
RWEXPORT RpMaterialList* RWAPI _rpMaterialListDeinitialize(RpMaterialList *matList);

/* Accessing material lists */
RWEXPORT RpMaterial** RWAPI _rpMaterialListAlloc(RwUInt32 count);
RWEXPORT RpMaterial* RWAPI _rpMaterialListGetMaterial(const RpMaterialList *matList,
                                             RwInt32 matIndex);
RWEXPORT RpMaterialList* RWAPI _rpMaterialListSetSize(RpMaterialList * matList, 
                                               RwInt32 size);
RWEXPORT RpMaterialList* RWAPI _rpMaterialListCopy(RpMaterialList *matListOut,
                                          const RpMaterialList *matListIn);
RWEXPORT RwInt32 RWAPI _rpMaterialListAppendMaterial(RpMaterialList *matList,
                                            RpMaterial *material);
RWEXPORT RwInt32 RWAPI _rpMaterialListFindMaterialIndex(const RpMaterialList *matList,
                                               const RpMaterial *material);

/* Binary format */
RWEXPORT RwUInt32 RWAPI _rpMaterialListStreamGetSize(const RpMaterialList *matList);
RWEXPORT RpMaterialList* RWAPI _rpMaterialListStreamRead(RwStream *stream,
                                                RpMaterialList *matList);
RWEXPORT const RpMaterialList* RWAPI _rpMaterialListStreamWrite(const RpMaterialList *matList,
                                                       RwStream *stream);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#define rpMaterialListInitialize(_matList) \
    _rpMaterialListInitialize(_matList)

#define rpMaterialListDeinitialize(_matList) \
    _rpMaterialListDeinitialize(_matList)

#define rpMaterialListGetMaterial(_matList, _matIndex) \
    _rpMaterialListGetMaterial(_matList, _matIndex)

#define rpMaterialListCopy(_matListOut, _matListIn) \
    _rpMaterialListCopy(_matListOut, _matListIn)

#define rpMaterialListAppendMaterial(_matList, _material) \
    _rpMaterialListAppendMaterial(_matList, _material)

#define rpMaterialListStreamRead(_stream, _matList) \
    _rpMaterialListStreamRead(_stream, _matList)

#define rpMaterialListStreamWrite(_matList, _stream) \
    _rpMaterialListStreamWrite(_matList, _stream)

/* RWPUBLICEND */

#endif /* RWMATLST_H */


