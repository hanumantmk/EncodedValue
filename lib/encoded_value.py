class CLASS:
    def __init__(self, name, fields):
        self.name = name
        self.fields = fields

    def cpp(self):
        fields = self.fields
        out = []

        out.extend(["template <bool convertEndian = true>\n"])
        out.extend(["class ", self.name, " {\n"])
        out.extend(["public:\n\n"])

        sizeof = ["0"]
        for field in fields:
            sizeof.append(field.sizeof())

        out.extend(["    static const int _size = ", ' + '.join(sizeof), ";\n\n"])
        out.extend(["    typedef EncodedValue::Impl::Pointer<EncodedValue::Meta::EV<", self.name, "<convertEndian> > > Pointer;\n\n"])
        out.extend(["    class Value;\n\n"])
        out.extend(["    class Reference;\n\n"])

        offset = []

        for i in range(len(fields)):
            offset.append(["0"])

            for j in range(0, i):
                offset[i].append(fields[j].sizeof())

        self._cpp_helper(out, offset, sizeof, False);
        self._cpp_helper(out, offset, sizeof, True);

        out.extend(["};"])

        return ''.join(out)
    
    def _cpp_helper(self, out, offset, sizeof, intrusive):
        if (intrusive):
            name = "Value"
            storage = "char storage[_size]"
        else:
            name = "Reference"
            storage = "char * storage"

        fields = self.fields

        out.extend(["class ", name, " {\n"])
        out.extend(["public:\n"])

        out.extend(["    static const int _size = ", ' + '.join(sizeof), ";\n\n"])
        out.extend(["private:\n"])

        out.extend(["    ", storage, ";\n"])

        out.extend(["public:\n"])
        out.extend(["    void zero() {\n"])
        out.extend(["        std::memset(storage, 0, _size);\n"])
        out.extend(["    }\n\n"])

        out.extend(["    char * ptr() const {\n"])
        out.extend(["        return (char *)storage;\n"])
        out.extend(["    }\n\n"])

        out.extend(["    ", name, "& operator=(const Reference& p) {\n"])
        out.extend(["        std::memcpy(storage, p.ptr(), _size);\n"])
        out.extend(["        return *this;\n"])
        out.extend(["    }\n\n"])

        out.extend(["    ", name, "& operator=(const Value& p) {\n"])
        out.extend(["        std::memcpy(storage, p.ptr(), _size);\n"])
        out.extend(["        return *this;\n"])
        out.extend(["    }\n\n"])

        for i in range(len(fields)):
            out.extend(fields[i].cpp(' + '.join(offset[i])))

        if (intrusive):
            out.extend(["    ", name, "() {}\n\n"])
            out.extend(["    ", name, "(char * in) {\n"])
            out.extend(["        std::memcpy(storage, in, _size);\n"])
            out.extend(["    }\n\n"])

            out.extend(["    ", name, "(const Reference & p) {\n"])
            out.extend(["        std::memcpy(storage, p.ptr(), _size);\n"])
            out.extend(["    }\n\n"])

            out.extend(["    ", name, "(const Value& p) {\n"])
            out.extend(["        std::memcpy(storage, p.ptr(), _size);\n"])
            out.extend(["    }\n\n"])

            out.extend(["    Pointer operator &() {\n"])
            out.extend(["        return Pointer(storage);\n"])
            out.extend(["    }\n\n"])

        else:
            out.extend(["    ", name, "(char * in) {\n"])
            out.extend(["        storage = in;\n"])
            out.extend(["    }\n\n"])

            out.extend(["    ", name, "(const Value& p) {\n"])
            out.extend(["        storage = p.ptr();\n"])
            out.extend(["    }\n\n"])

            out.extend(["    Pointer operator &() {\n"])
            out.extend(["        return Pointer(storage);\n"])
            out.extend(["    }\n\n"])

        out.extend(["};\n\n"])

class FIELD:
    def __init__(self, t, name, array = None):
        self.type = t
        self.name = name
        self.array = array

    def sizeof(self):
        if self.array is None:
            return "sizeof(" + self.type + ")"
        else:
            return "(sizeof(" + self.type + ") * " + str(self.array) + ")"

    def cpp(self, offset_str):
        out = []
        if self.array is None:
            out.extend(["    typename EncodedValue::Reference<", self.type, ", convertEndian> ", self.name, "() {\n"])
            out.extend(["        return typename EncodedValue::Reference<", self.type, ", convertEndian>(storage +", offset_str, ");\n"])
            out.extend(["    }\n\n"])
        else:
            out.extend(["    typename EncodedValue::Pointer<", self.type, ", convertEndian> ", self.name, "() {\n"])
            out.extend(["        return typename EncodedValue::Pointer<", self.type, ", convertEndian>(storage +", offset_str, ");\n"])
            out.extend(["    }\n\n"])

        return out

class SKIP:
    def __init__(self, skip):
        self.skip = skip

    def sizeof(self):
        return str(self.skip)

    def cpp(self, offset_str):
        return []

class BITFIELD:
    def __init__(self, root, fields):
        self.fields = fields
        self.root = root

    def sizeof(self):
        return "sizeof(" + self.root + ")"

    def cpp(self, offset_str):
        out = []
        offset = 0

        for field in self.fields:
            if (isinstance(field, SKIP)):
                offset += field.skip
            else:
                bitfield_impl = field.type + ", " + self.root + ", " + str(offset) + ", " + str(field.array) + ", convertEndian"

                out.extend(["    typename EncodedValue::BitField::Reference<", bitfield_impl, "> ", field.name, "() {\n"])
                out.extend(["        return typename EncodedValue::BitField::Reference<", bitfield_impl, ">(storage +", offset_str, ");\n"])
                out.extend(["    }\n\n"])

                offset += field.array

        return out

class UNION:
    def __init__(self, fields):
        self.fields = fields

    def sizeof(self):
        out = []
        for i in range(len(self.fields) - 1):
            out.extend([ "EncodedValue::_max< ", self.fields[i].sizeof(), ", "])

        out.append( self.fields[len(self.fields) - 1].sizeof() )

        for i in range(len(self.fields) - 1):
            out.append( ">::result " )

        return ''.join(out)

    def cpp(self, offset_str):
        out = []

        for field in self.fields:
            out.extend(field.cpp(offset_str))

        return out

class STRUCT:
    def __init__(self, fields):
        self.fields = fields

    def sizeof(self):
        out = []
        for field in self.fields:
            out.append(field.sizeof())

        return ' + '.join(out)

    def cpp(self, offset_str):
        fields = self.fields

        out = []

        offset = []

        for i in range(len(fields)):
            offset.append([offset_str])

            for j in range(0, i):
                offset[i].append(fields[j].sizeof())

        for i in range(len(fields)):
            out.extend(fields[i].cpp(' + '.join(offset[i])))

        return out

class EVSTRUCT:
    def __init__(self, t, name, array = None):
        self.type = t
        self.name = name
        self.array = array

    def sizeof(self):
        if self.array is None:
            return self.type + "<convertEndian>::_size"
        else:
            return "(" + self.type + "<convertEndian>::_size * " + str(self.array) + ")"

    def cpp(self, offset_str):
        out = []

        if self.array is None:
            out.extend(["    typename ", self.type, "<convertEndian>::Reference ", self.name, "() {\n"])
            out.extend(["        return typename ", self.type, "<convertEndian>::Reference(storage +", offset_str, ");\n"])
            out.extend(["    }\n\n"])
        else:
            out.extend(["    typename ", self.type, "<convertEndian>::Pointer ", self.name, "() {\n"])
            out.extend(["        return typename ", self.type, "<convertEndian>::Pointer(storage +", offset_str, ");\n"])
            out.extend(["    }\n\n"])
        return out
