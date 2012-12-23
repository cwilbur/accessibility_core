#include "ruby.h"
#import <Cocoa/Cocoa.h>

#ifdef NOT_MACRUBY

extern VALUE rb_mAccessibility;
extern VALUE rb_cElement;
extern VALUE rb_cCGPoint;
extern VALUE rb_cCGSize;
extern VALUE rb_cCGRect;
extern VALUE rb_mURI; // URI module
extern VALUE rb_cURI; // URI::Generic class

extern ID sel_x;
extern ID sel_y;
extern ID sel_width;
extern ID sel_height;
extern ID sel_origin;
extern ID sel_size;
extern ID sel_to_point;
extern ID sel_to_size;
extern ID sel_to_rect;
extern ID sel_to_s;
extern ID sel_parse;


#define WRAP_ARRAY(wrapper) do {				\
    CFIndex length = CFArrayGetCount(array);			\
    VALUE      ary = rb_ary_new2(length);			\
								\
    for (CFIndex idx = 0; idx < length; idx++)			\
      rb_ary_store(						\
		   ary,						\
		   idx,						\
		   wrapper(CFArrayGetValueAtIndex(array, idx))	\
		   );	                                        \
    return ary;							\
  } while (false);


VALUE wrap_unknown(CFTypeRef obj);
CFTypeRef unwrap_unknown(VALUE obj);

VALUE wrap_point(CGPoint point);
CGPoint unwrap_point(VALUE point);

VALUE wrap_size(CGSize size);
CGSize unwrap_size(VALUE size);

VALUE wrap_rect(CGRect rect);
CGRect unwrap_rect(VALUE rect);

VALUE convert_cf_range(CFRange range);
CFRange convert_rb_range(VALUE range);

VALUE wrap_value_point(AXValueRef value);
VALUE wrap_value_size(AXValueRef value);
VALUE wrap_value_rect(AXValueRef value);
VALUE wrap_value_range(AXValueRef value);
VALUE wrap_value_error(AXValueRef value);
VALUE wrap_value(AXValueRef value);
VALUE wrap_array_values(CFArrayRef array) { WRAP_ARRAY(wrap_value) }

AXValueRef unwrap_value_point(VALUE val);
AXValueRef unwrap_value_size(VALUE val);
AXValueRef unwrap_value_rect(VALUE val);
AXValueRef unwrap_value_range(VALUE val);
AXValueRef unwrap_value(VALUE value);

VALUE wrap_ref(AXUIElementRef ref);
VALUE wrap_array_refs(CFArrayRef array);
AXUIElementRef unwrap_ref(VALUE obj);

VALUE wrap_string(CFStringRef string);
VALUE wrap_nsstring(NSString* string);
VALUE wrap_array_strings(CFArrayRef array);
VALUE wrap_array_nsstrings(NSArray* ary);
CFStringRef unwrap_string(VALUE string);
NSString*   unwrap_nsstring(VALUE string);

VALUE wrap_long(CFNumberRef num);
VALUE wrap_long_long(CFNumberRef num);
VALUE wrap_float(CFNumberRef num);
VALUE wrap_number(CFNumberRef number);
VALUE wrap_array_numbers(CFArrayRef array);

CFNumberRef unwrap_long(VALUE num);
CFNumberRef unwrap_long_long(VALUE num);
CFNumberRef unwrap_float(VALUE num);
CFNumberRef unwrap_number(VALUE number);

VALUE wrap_url(CFURLRef url);
VALUE wrap_nsurl(NSURL* url);
CFURLRef unwrap_url(VALUE url);
VALUE wrap_array_urls(CFArrayRef array);

VALUE wrap_date(CFDateRef date);
VALUE wrap_nsdate(NSDate* date);
VALUE wrap_array_dates(CFArrayRef array);
CFDateRef unwrap_date(VALUE date);

VALUE wrap_boolean(CFBooleanRef bool_val);
VALUE wrap_array_booleans(CFArrayRef array);
CFBooleanRef unwrap_boolean(VALUE bool_val);

VALUE wrap_array(CFArrayRef array);

VALUE to_ruby(CFTypeRef obj);
CFTypeRef to_ax(VALUE obj);

#endif


// these functions are available on MacRuby as well as MRI
void spin(double seconds);
