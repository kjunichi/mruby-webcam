/*
** mrb_webcam.h - Webcam class
**
** See Copyright Notice in LICENSE
*/

#ifndef MRB_WEBCAM_H
#define MRB_WEBCAM_H
#include "mruby.h"

typedef struct {
  int num;
  char *str;
} mrb_webcam_data;

void
mrb_mruby_webcam_gem_init(mrb_state *mrb);

#endif
