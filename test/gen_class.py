from portable_packed_struct import *

print("#include <cstring>\n\n")

print(CLASS("TestClass", [
    UNION(FIELD("long long", "i64", 2), [
        STRUCT([
            FIELD("char", "type"),
            BITFIELD(FIELD("unsigned char", "bm"), [
                BITFIELDFIELD("unsigned", "refCounter", 1),
                BITFIELDFIELD("unsigned", "pada", 4),
                BITFIELDFIELD("unsigned", "shortStr", 1),
                BITFIELDFIELD("unsigned", "padb", 2),
            ]),
            UNION(FIELD("char", "3_16", 14), [
                FIELD("char", "oid", 12),
                STRUCT([
                    FIELD("char", "shortStrSize"),
                    FIELD("char", "shortStrStorage", 12),
                    FIELD("char", "nulTerminator"),
                ]),
                STRUCT([
                    UNION(FIELD("char", "pad", 6), [
                        FIELD("unsigned char", "binSubType"),
                        FIELD("char", "stringCache", 6),
                    ]),
                    UNION(FIELD("long long", "longValue"), [
                        FIELD("void *", "genericRcPtr"),
                        FIELD("double", "doubleValue"),
                        FIELD("bool", "boolValue"),
                        FIELD("int", "intValue"),
                        FIELD("long long", "dateValue"),
                    ])
                ])
            ])
        ])
    ])
]).cpp())

print(CLASS("DoubleClass", [
    FIELD("double", "doubleValue"),
]).cpp())