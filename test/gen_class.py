from encoded_value import *

print("#include \"EncodedValue.h\"\n\n")

print(CLASS("TestEmbed", [
    FIELD("int", "intValue"),
    SKIP(2),
    FIELD("short", "shortValue"),
]).cpp())

print(CLASS("TestClass", [
    UNION([
        STRUCT([
            FIELD("char", "type"),
            BITFIELD("unsigned char", [
                FIELD("unsigned", "refCounter", 1),
                SKIP(4),
                FIELD("unsigned", "shortStr", 1),
                FIELD("unsigned", "padb", 2),
            ]),
            UNION([
                FIELD("char", "oid", 12),
                STRUCT([
                    FIELD("char", "shortStrSize"),
                    FIELD("char", "shortStrStorage", 12),
                    FIELD("char", "nulTerminator"),
                ]),
                STRUCT([
                    UNION([
                        FIELD("char", "pad", 6),
                        FIELD("unsigned char", "binSubType"),
                        FIELD("char", "stringCache", 6),
                    ]),
                    UNION([
                        FIELD("long long", "longValue"),
                        FIELD("void *", "genericRcPtr"),
                        FIELD("double", "doubleValue"),
                        FIELD("bool", "boolValue"),
                        FIELD("int", "intValue"),
                        FIELD("long long", "dateValue"),
                    ])
                ])
            ])
        ]),
        EVSTRUCT("TestEmbed", "te"),
        EVSTRUCT("TestEmbed", "te_array", 2),
        FIELD("long long", "i64", 2),
    ])
]).cpp())

print(CLASS("DoubleClass", [
    FIELD("double", "doubleValue"),
]).cpp())
