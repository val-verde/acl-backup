#ifndef __LIBOBJ_H
#define __LIBOBJ_H

#include <stdlib.h>

/* Ugly pointer manipulation */

#ifdef LIBACL_DEBUG
#  define ext2int(T, ext_p) \
	((T##_obj *)__ext2int_and_check(ext_p, T##_MAGIC, #T))
#else
#  define ext2int(T, ext_p) \
	((T##_obj *)__ext2int_and_check(ext_p, T##_MAGIC))
#endif

#define int2ext(int_p) \
	((int_p) ? &(int_p)->i : NULL)
#define new_var_obj_p(T, sz) \
	((T##_obj *)__new_obj_p(T##_MAGIC, sizeof(T##_obj) + sz))
#define realloc_var_obj_p(T, p, sz) \
	((T##_obj *)realloc(p, sizeof(T##_obj) + sz))
#define new_obj_p(T) \
	new_var_obj_p(T, 0)
#define init_obj(T, o) \
	((o).o_prefix.p_magic = T##_MAGIC)
#define check_obj_p(T, obj_p) \
	((T##_obj *)__check_obj_p((obj_prefix *)(obj_p), T##_MAGIC))
#define free_obj_p(obj_p) \
	(__free_obj_p((obj_prefix *)(obj_p)))


/* prefix for all objects */
typedef struct {
	int			p_magic;
} obj_prefix;

#define pmagic i.p_magic

/* magic object values */
#define acl_MAGIC		(0x712C)
#define acl_entry_MAGIC		(0x9D6B)
#define acl_permset_MAGIC	(0x1ED5)
#define qualifier_MAGIC		(0x1C27)
#define string_MAGIC		(0xD5F2)
#define cap_MAGIC		(0x6CA8)

/* object types */
struct string_obj_tag;
typedef struct string_obj_tag string_obj;

/* string object */
struct __string_ext {
	char			s_str[0];
};
struct string_obj_tag {
	obj_prefix		o_prefix;
	struct __string_ext	i;
};

#define sstr i.s_str

/* object creation, destruction, conversion and validation */
void *__new_obj_p(int magic, size_t size);
void __free_obj_p(obj_prefix *obj_p);
obj_prefix *__check_obj_p(obj_prefix *obj_p, int magic);
#ifdef LIBACL_DEBUG
obj_prefix *__ext2int_and_check(void *ext_p, int magic, const char *typename);
#else
obj_prefix *__ext2int_and_check(void *ext_p, int magic);
#endif

#endif /* __LIBOBJ_H */