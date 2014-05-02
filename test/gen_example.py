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
    FIELD("unsigned char", "op"),
    EVSTRUCT("Type", "args", 2)
]).cpp())
