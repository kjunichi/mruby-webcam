/*
** mrb_webcam.c - Webcam class
**
** Copyright (c) Junichi Kajiwara 2015
**
** See Copyright Notice in LICENSE
*/

#include "mruby.h"
#include "mruby/data.h"
#include "mrb_webcam.h"

extern void webcam_start(void);

#define DONE mrb_gc_arena_restore(mrb, 0);

typedef struct {
  char *str;
  int len;
} mrb_webcam_data;

static const struct mrb_data_type mrb_webcam_data_type = {
    "mrb_webcam_data", mrb_free,
};

static mrb_value mrb_webcam_init(mrb_state *mrb, mrb_value self) {
  mrb_webcam_data *data;
  char *str;
  int len;

  data = (mrb_webcam_data *)DATA_PTR(self);
  if (data) {
    mrb_free(mrb, data);
  }
  DATA_TYPE(self) = &mrb_webcam_data_type;
  DATA_PTR(self) = NULL;

  mrb_get_args(mrb, "s", &str, &len);
  data = (mrb_webcam_data *)mrb_malloc(mrb, sizeof(mrb_webcam_data));
  data->str = str;
  data->len = len;
  DATA_PTR(self) = data;

  return self;
}

static mrb_value mrb_webcam_hello(mrb_state *mrb, mrb_value self) {
  mrb_webcam_data *data = DATA_PTR(self);

  return mrb_str_new(mrb, data->str, data->len);
}

static mrb_value mrb_webcam_hi(mrb_state *mrb, mrb_value self) {
  return mrb_str_new_cstr(mrb, "hi!!");
}

static mrb_value mrb_webcam_start(mrb_state *mrb, mrb_value self) {
  webcam_start();
  return mrb_str_new_cstr(mrb, "webcam start!!");
}

void mrb_mruby_webcam_gem_init(mrb_state *mrb) {
  struct RClass *webcam;
  webcam = mrb_define_class(mrb, "Webcam", mrb->object_class);
  mrb_define_method(mrb, webcam, "initialize", mrb_webcam_init,
                    MRB_ARGS_REQ(1));
  mrb_define_method(mrb, webcam, "hello", mrb_webcam_hello, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, webcam, "hi", mrb_webcam_hi, MRB_ARGS_NONE());
  mrb_define_method(mrb, webcam, "start", mrb_webcam_start, MRB_ARGS_NONE());
  DONE;
}

void mrb_mruby_webcam_gem_final(mrb_state *mrb) {}
