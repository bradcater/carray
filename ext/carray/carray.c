#include <glib.h>
#include <math.h>
#include <ruby.h>

void iterator(gpointer key, gpointer value, gpointer user_data) {
  rb_ary_push((VALUE)user_data, (VALUE)value);
}

static VALUE c_dot_product(VALUE self, VALUE v2) {
  long n = RARRAY_LEN(self);
  double sum = 0.0;

  VALUE *x_a = RARRAY_PTR(self);
  VALUE *y_a = RARRAY_PTR(v2);

  long i;
  for (i=0; i<n; i++) {
    if (TYPE(x_a[i]) != T_FIXNUM) {
      rb_raise(rb_eTypeError, "input was not all integers");
    }
    if (TYPE(y_a[i]) != T_FIXNUM) {
      rb_raise(rb_eTypeError, "input was not all integers");
    }
    sum += NUM2DBL(x_a[i]) * NUM2DBL(y_a[i]);
  }
  return DBL2NUM(sum);
}

static VALUE c_euclidean_distance(VALUE self, VALUE v2) {
  long n = RARRAY_LEN(self);
  double sum = 0.0;

  VALUE *x_a = RARRAY_PTR(self);
  VALUE *y_a = RARRAY_PTR(v2);

  long i;
  for (i=0; i<n; i++) {
    if (TYPE(x_a[i]) != T_FIXNUM) {
      rb_raise(rb_eTypeError, "input was not all integers");
    }
    if (TYPE(y_a[i]) != T_FIXNUM) {
      rb_raise(rb_eTypeError, "input was not all integers");
    }
    sum += pow((NUM2DBL(x_a[i]) - NUM2DBL(y_a[i])), 2);
  }
  return DBL2NUM(sqrt(sum));
}

static VALUE c_int_include(VALUE self, VALUE v) {
  VALUE *x = RARRAY_PTR(self);
  long n = RARRAY_LEN(self);
  long vv = NUM2LONG(v);
  long i;
  for (i=0; i<n; i++) {
    if (TYPE(x[i]) != T_FIXNUM) {
      rb_raise(rb_eTypeError, "input was not all integers");
    }
    if (NUM2LONG(x[i]) == vv) {
      return Qtrue;
    }
  }
  return Qfalse;
}

static VALUE c_int_uniq(VALUE self) {
  GHashTable* hash;
  long i;
  VALUE new_ary;

  VALUE *x_a = RARRAY_PTR(self);
  long ary_len = RARRAY_LEN(self);

  if (ary_len <= 1) {
    return rb_ary_dup(self);
  }

  hash = g_hash_table_new(g_direct_hash, g_direct_equal);

  for (i=0; i<ary_len; i++) {
    if (TYPE(x_a[i]) != T_FIXNUM) {
      rb_raise(rb_eTypeError, "input was not all integers");
    }
    if (!g_hash_table_contains(hash, (gconstpointer *)x_a[i])) {
      g_hash_table_insert(hash, (gconstpointer *)x_a[i], (gconstpointer *)x_a[i]);
    }
  }

  new_ary = rb_ary_new2(g_hash_table_size(hash));

  g_hash_table_foreach(hash, (GHFunc)iterator, (gpointer *)new_ary);

  g_hash_table_destroy(hash);
  return new_ary;
}

static VALUE c_magnitude(VALUE self) {
  long n = RARRAY_LEN(self);
  double sum = 0.0;

  VALUE *x_a = RARRAY_PTR(self);

  long i;
  for (i=0; i<n; i++) {
    if (TYPE(x_a[i]) != T_FIXNUM) {
      rb_raise(rb_eTypeError, "input was not all integers");
    }
    sum += pow(NUM2DBL(x_a[i]), 2);
  }
  return DBL2NUM(sqrt(sum));
}

static VALUE c_mean(VALUE self) {
  long n = RARRAY_LEN(self);
  double sum = 0.0;

  VALUE *x_a = RARRAY_PTR(self);

  long i;
  for (i=0; i<n; i++) {
    if (TYPE(x_a[i]) != T_FIXNUM) {
      rb_raise(rb_eTypeError, "input was not all integers");
    }
    sum += NUM2DBL(x_a[i]);
  }
  return DBL2NUM(sum / n);
}

static VALUE c_pearson_correlation(VALUE self, VALUE v2) {
  long n = RARRAY_LEN(self);
  double sum1 = 0.0;
  double sum2 = 0.0;
  double sum1Sq = 0.0;
  double sum2Sq = 0.0;
  double pSum = 0.0;
  double num;
  double den;

  VALUE *x_a = RARRAY_PTR(self);
  VALUE *y_a = RARRAY_PTR(v2);

  long i;
  double this_x;
  double this_y;
  for (i=0; i<n; i++) {
    if (TYPE(x_a[i]) != T_FIXNUM) {
      rb_raise(rb_eTypeError, "input was not all integers");
    }
    if (TYPE(y_a[i]) != T_FIXNUM) {
      rb_raise(rb_eTypeError, "input was not all integers");
    }
    this_x = NUM2DBL(x_a[i]);
    this_y = NUM2DBL(y_a[i]);
    sum1 += this_x;
    sum2 += this_y;
    sum1Sq += pow(this_x, 2);
    sum2Sq += pow(this_y, 2);
    pSum += this_y * this_x;
  }
  num = pSum - ( ( sum1 * sum2 ) / n );
  den = sqrt( ( sum1Sq - ( pow(sum1, 2) ) / n ) * ( sum2Sq - ( pow(sum2, 2) ) / n ) );
  if (den == 0) {
    return DBL2NUM(0.0);
  } else {
    return DBL2NUM(num / den);
  }
}

static VALUE c_variance(VALUE self) {
  long n = RARRAY_LEN(self);
  double mean_sum = 0.0;
  double mean;
  double accum_sum = 0.0;

  VALUE *x_a = RARRAY_PTR(self);

  long i;
  for (i=0; i<n; i++) {
    if (TYPE(x_a[i]) != T_FIXNUM) {
      rb_raise(rb_eTypeError, "input was not all integers");
    }
    mean_sum += NUM2DBL(x_a[i]);
  }
  mean = mean_sum / n;
  for (i=0; i<n; i++) {
    accum_sum += pow((NUM2DBL(x_a[i]) - mean), 2);
  }
  return DBL2NUM(accum_sum / n);
}

void Init_carray() {
  rb_define_method(rb_cArray, "c_dot_product", c_dot_product, 1);
  rb_define_method(rb_cArray, "c_euclidean_distance", c_euclidean_distance, 1);
  rb_define_method(rb_cArray, "c_int_include", c_int_include, 1);
  rb_define_method(rb_cArray, "c_int_uniq", c_int_uniq, 0);
  rb_define_method(rb_cArray, "c_magnitude", c_magnitude, 0);
  rb_define_method(rb_cArray, "c_mean", c_mean, 0);
  rb_define_method(rb_cArray, "c_pearson_correlation", c_pearson_correlation, 1);
  rb_define_method(rb_cArray, "c_variance", c_variance, 0);
  printf("Welcome to carray!\n");
}
