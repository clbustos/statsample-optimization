#include <ruby.h>
#include "as116.h"
/**
* :stopdoc:
*/

void Init_statsamplert();
VALUE statsample_frequencies(VALUE self, VALUE data);
VALUE statsample_set_valid_data_intern(VALUE self, VALUE vector);
VALUE statsample_case_as_hash(VALUE self, VALUE ds, VALUE index);
VALUE statsample_case_as_array(VALUE self, VALUE ds, VALUE index);
VALUE statsample_tetrachoric(VALUE self, VALUE a, VALUE b, VALUE c, VALUE d);

void Init_statsamplert()
{
	VALUE mStatsample;
    VALUE mSTATSAMPLE__;
	ID id_statsample;
	ID id_STATSAMPLE__;
    id_statsample   = rb_intern("Statsample");
    id_STATSAMPLE__ = rb_intern("STATSAMPLE__");

    if(rb_const_defined(rb_cObject, id_statsample)) {
		mStatsample = rb_const_get(rb_cObject, id_statsample);
	 } else {
		mStatsample = rb_define_module("Statsample"); 
	 }
    if(rb_const_defined(mStatsample, id_STATSAMPLE__)) {
		mSTATSAMPLE__ = rb_const_get(mStatsample, id_STATSAMPLE__);
	 } else {
		mSTATSAMPLE__ = rb_define_module_under(mStatsample, "STATSAMPLE__"); 
	 }
     
     rb_define_const(mStatsample, "OPTIMIZED",Qtrue);
    rb_define_module_function(mSTATSAMPLE__,"frequencies",statsample_frequencies,1);
    rb_define_module_function(mSTATSAMPLE__,"set_valid_data_intern", statsample_set_valid_data_intern, 1);
    rb_define_module_function(mSTATSAMPLE__,"case_as_hash",statsample_case_as_hash,2);
    rb_define_module_function(mSTATSAMPLE__,"case_as_array",statsample_case_as_array,2);
    rb_define_module_function(mSTATSAMPLE__,"tetrachoric",statsample_tetrachoric,4);

}

VALUE statsample_set_valid_data_intern(VALUE self, VALUE vector) {
/** Emulate

@data.each do |n|
				if is_valid? n
                    @valid_data.push(n)
                    @data_with_nils.push(n)
				else
                    @data_with_nils.push(nil)
                    @missing_data.push(n)
				end
			end
            @has_missing_data=@missing_data.size>0
            */
    VALUE data=rb_iv_get(vector,"@data");
    VALUE valid_data=rb_iv_get(vector,"@valid_data");
    VALUE data_with_nils=rb_iv_get(vector,"@data_with_nils");
    VALUE missing_data=rb_iv_get(vector,"@missing_data");
    VALUE missing_values=rb_iv_get(vector,"@missing_values");
//    VALUE has_missing_data=rb_iv_get(vector,"@has_missing_data");
    long len=RARRAY_LEN(data);
    long i;
    VALUE val;
    for(i=0;i<len;i++) {
        val=rb_ary_entry(data,i);
        if(val==Qnil || rb_ary_includes(missing_values,val)) {
            rb_ary_push(missing_data,val);
            rb_ary_push(data_with_nils,Qnil);
        } else {
            rb_ary_push(valid_data,val);
            rb_ary_push(data_with_nils,val);
        }
    }
    rb_iv_set(vector,"@has_missing_data",(RARRAY_LEN(missing_data)>0) ? Qtrue : Qfalse);
    return Qnil;
}
/**
* Retuns frequencies for an array as a hash, with 
* keys as items and values as number of items
*/
VALUE statsample_frequencies(VALUE self, VALUE data) {
    VALUE h;
    VALUE val;
    long len;
    long i;

	Check_Type(data,T_ARRAY);
     h=rb_hash_new();

	len=RARRAY_LEN(data);
    for(i=0;i<len;i++) {
        val=rb_ary_entry(data,i);
        if(rb_hash_aref(h,val)==Qnil) {
            rb_hash_aset(h,val,INT2FIX(1));
        } else {
            long antiguo=FIX2LONG(rb_hash_aref(h,val));
            rb_hash_aset(h,val,LONG2FIX(antiguo+1));
        }
    }
    return h;
}

VALUE statsample_case_as_hash(VALUE self, VALUE ds,VALUE index) {
    VALUE vector,data,key;
    VALUE fields=rb_iv_get(ds,"@fields");
    VALUE vectors=rb_iv_get(ds,"@vectors");
    VALUE h=rb_hash_new();
    long len=RARRAY_LEN(fields);
    long i;
    for(i=0;i<len;i++) {
        key=rb_ary_entry(fields,i);
        vector=rb_hash_aref(vectors,key);
        data=rb_iv_get(vector,"@data");
        rb_hash_aset(h,key,rb_ary_entry(data,NUM2LONG(index)));
    }
    return h;
}
VALUE statsample_case_as_array(VALUE self, VALUE ds, VALUE index) {
    VALUE vector,data,key;
    VALUE fields=rb_iv_get(ds,"@fields");
    VALUE vectors=rb_iv_get(ds,"@vectors");
    VALUE ar=rb_ary_new();
    long len=RARRAY_LEN(fields);
    long i;
    for(i=0;i<len;i++) {
        key=rb_ary_entry(fields,i);
        vector=rb_hash_aref(vectors,key);
        data=rb_iv_get(vector,"@data");
        rb_ary_push(ar,rb_ary_entry(data,NUM2LONG(index)));
    }
    return ar;
}



VALUE statsample_tetrachoric(VALUE self, VALUE a, VALUE b, VALUE c, VALUE d) {
    VALUE h=rb_hash_new();
    double pa;
    double pb;
    double pc;
    double pd;
    double r;
	double sdr; 
    double sdzero;
	double t_x; 
    double t_y;
    
    int itype;
    int ifault;
    int result;
    pa=NUM2DBL(a);
    pb=NUM2DBL(b);
    pc=NUM2DBL(c);
    pd=NUM2DBL(d);
    
    result= tetra(&pa,&pb, &pc, &pd, &r,
	 &sdr, &sdzero, &t_x,&t_y, &itype, &ifault);
    rb_hash_aset(h, rb_str_new_cstr("r"), DBL2NUM(r));
    rb_hash_aset(h, rb_str_new_cstr("sdr"), DBL2NUM(sdr));
    rb_hash_aset(h, rb_str_new_cstr("sdzero"), DBL2NUM(sdzero));
    rb_hash_aset(h, rb_str_new_cstr("threshold_x"), DBL2NUM(t_x));
    rb_hash_aset(h, rb_str_new_cstr("threshold_y"), DBL2NUM(t_y));
    rb_hash_aset(h, rb_str_new_cstr("itype"), INT2NUM(itype));
    rb_hash_aset(h, rb_str_new_cstr("ifault"), INT2NUM(ifault));
    
    return h;
    
}
