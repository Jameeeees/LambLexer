#ifndef SYMSEG_H_
#define SYMSEG_H_

/*
 * This is actually the format of GDB symbol table data.
 * According to the limit of this lexer, not every data in this symbol is used.
 * The unused data has been all commentted.
 */
 
enum language {language_c};

struct symbol_root
{
	int format;			/* Data format version */
	int length;			/* # bytes in this symbol segment */
	//int ldsymoff;			/* Offset in ld symtab of this file's syms */
	//int textrel;			/* Relocation for text addresses */
	//int datarel;			/* Relocation for data addresses */
	//int bssrel;			/* Relocation for bss addresses */
	std::string filename;		/* Name of main source file compiled */
	std::string filedir;		/* Name of directory it was reached from */
	std::vector<block> blockvector; /* Vector of all symbol-naming blocks */
	std::vector<type> typevector; /* Vector of all data types */
	enum language language;	/* Code identifying the language used */
	std::string version;		/* Version info.  Not fully specified */
	std::string compilation;		/* Compilation info.  Not fully specified */
	//int databeg;			/* Address within the file of data start */
	//int bssbeg;			/* Address within the file of bss start */
	std::vector<source> sourcevector; /* Vector of line-number info */
};

/* All data types of symbols in the compiled program
 * are represented by `struct type' objects.
 * All of these objects are pointed to by the typevector.
 * The type vector may have empty slots that contain zero.  
 */

enum type_code
{
	TYPE_CODE_UNDEF,		/* Not used; catches errors */
	TYPE_CODE_PTR,		/* Pointer type */
	TYPE_CODE_ARRAY,		/* Array type, lower bound zero */
	TYPE_CODE_STRUCT,		/* C struct or Pascal record */
	TYPE_CODE_UNION,		/* C union or Pascal variant part */
	TYPE_CODE_ENUM,		/* Enumeration type */
	TYPE_CODE_FUNC,		/* Function type */
	TYPE_CODE_INT,		/* Integer type */
	TYPE_CODE_FLT,		/* Floating type */
	TYPE_CODE_VOID,		/* Void type (values zero length) */
	//TYPE_CODE_SET,		/* Pascal sets */
	TYPE_CODE_RANGE,		/* Range (integers within spec'd bounds) */
	//TYPE_CODE_PASCAL_ARRAY,	/* Array with explicit type of index */
};

typedef struct type type;

struct type
{
   /* 
	* Code for kind of type 
	*/
	enum type_code code;
   /* 
	* Name of this type, or zero if none.
	* This is used for printing only.
	*/
	std::string name;
   /* 
	* Length in bytes of storage for a value of this type 
	*/
	int length;
   /* 
	* For a pointer type, describes the type of object pointed to.
	* For an array type, describes the type of the elements.
	* For a function type, describes the type of the value.
	* Unused otherwise.  
	*/
	type *target_type;
   /* 
	* Type that is a pointer to this type.
	* Zero if no such pointer-to type is known yet.
	*/ 
	type *pointer_type;
   /* 
	* Type that is a function returning this type.
	* Zero if no such function type is known here.
	*/
	type *function_type;
   /* 
	* Flags about this type.  
	*/
	short flags;
   /* 
	* Number of fields described for this type 
	*/
	short nfields;
   /* 
	* For structure and union types, a description of each field.
	* For range types, there are two "fields",
	* the minimum and maximum values (both inclusive).
	* For enum types, each possible value is described by one "field".
	* For range types, there are two "fields", that record constant values
	* (inclusive) for the minimum and maximum.
	*
	* Using a pointer to a separate array of fields
	* allows all types to have the same size, which is useful
	* because we can allocate the space for a type before
	* we know what to put in it.  
	*/
	struct field
	{
   /* 
	* Position of this field, counting in bits from start of
	* containing structure.  For a function type, this is the
	* position in the argument list of this argument.
	* For a range bound or enum value, this is the value itself.  
	*/
		int bitpos;
   /*
	* Size of this field, in bits, or zero if not packed.
	* For an unpacked field, the field's type's length
	* says how many bytes the field occupies.  
	*/
		int bitsize;
   /* In a struct or enum type, type of this field.
	* In a function type, type of this argument.
	* In an array type, the domain-type of the array.  
	*/
		type *type;
   /* Name of field, value or argument.
    * Zero for range bounds and array domains.  
	*/
		char *name;
	} *fields;
};


#endif /* end of SYMSEG_H_ */