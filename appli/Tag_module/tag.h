/*
 * Tag.h
 *
 *  Created on: 24 mar. 2023
 *      Author: jjousse
 */

#include "macro_types.h"

#ifndef TAG_H_
#define TAG_H_

typedef struct tag_t Tag;

extern Tag* Tag_new(uint32_t mem_address);
extern void Tag_start(Tag *this);

extern void Tag_setSerial(Tag *this, uint32_t serial);
extern void Tag_printSerial(Tag* this);
extern void Tag_sleep(Tag *this);
extern void Tag_storeMem(Tag* this);
extern void Tag_loadMem(Tag* this);
extern void Tag_temp(Tag *this);

extern void Tag_stop(Tag *this);
extern void Tag_free(Tag *this);

#endif /* TAG_H_ */
