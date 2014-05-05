from encoded_value import *

print("#include \"EncodedValue.h\"\n\n")

print(CLASS("Complex", [
    FIELD("double", "real"),
    FIELD("double", "imag")
]).cpp());

print(CLASS("Type", [
    FIELD("unsigned char", "type"),
    UNION([
        FIELD("int", "i"),
        FIELD("double", "d"),
        EVSTRUCT("Complex", "c")
    ])
]).cpp())

print(CLASS("Expression", [
    BITFIELD("unsigned char", [
        FIELD("unsigned", "op", 4),
        FIELD("unsigned", "precedence", 3),
        FIELD("unsigned", "is_infix", 1)
    ]),
    EVSTRUCT("Type", "args", 2)
]).cpp())
