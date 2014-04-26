class CLASS:
    def __init__(self, name, fields):
        self.name = name
        self.fields = fields

    def cpp(self):
        fields = self.fields
        out = []

        out.extend(["namespace ", self.name, " {\n"])

        sizeof = ["0"]
        for field in fields:
            sizeof.append(field.sizeof())

        out.extend(["    using namespace PortablePackedStruct;\n\n"])
        out.extend(["    static const int _size = ", ' + '.join(sizeof), ";\n\n"])

        out.extend(["template <typename T>\n"])
        out.extend(["class Base {\n"])
        out.extend(["protected:\n"])
        out.extend(["    T storage;\n"])

        out.extend(["public:\n"])

        out.extend(["    static const int _size = ", self.name, "::_size;\n\n"])

        out.extend(["    void zero() {\n"])
        out.extend(["        std::memset(storage, 0, _size);\n"])
        out.extend(["    }\n\n"])

        out.extend(["    char * ptr() {\n"])
        out.extend(["        return storage;\n"])
        out.extend(["    }\n\n"])

        offset = []

        for i in xrange(len(fields)):
            offset.append(["0"])

            for j in xrange(0, i):
                offset[i].append(fields[j].sizeof())

        for i in xrange(len(fields)):
            out.extend(fields[i].cpp(' + '.join(offset[i])))

        out.extend(["};\n\n"])
        self._cpp_helper(out, False);
        self._cpp_helper(out, True);

        out.extend(["}"])

        return ''.join(out)
    
    def _cpp_helper(self, out, intrusive):
        if (intrusive):
            name = "Data"
            storage = "char[" + self.name + "::_size]"
        else:
            name = "Ptr"
            storage = "char *"

        fields = self.fields

        out.extend(["class ", name, " : public Base<", storage, "> {\n"])

        out.extend(["public:\n"])

        out.extend(["    ", name, "() {}\n\n"])

        out.extend(["    char * ptr() {\n"])
        out.extend(["        return storage;\n"])
        out.extend(["    }\n\n"])

        if (intrusive):
            out.extend(["    ", name, "(char * in) {\n"])
            out.extend(["        std::memcpy(storage, in, _size);\n"])
            out.extend(["    }\n\n"])
            out.extend(["    ", name, "(Ptr p) {\n"])
            out.extend(["        std::memcpy(storage, p.ptr(), _size);\n"])
            out.extend(["    }\n\n"])
        else:
            out.extend(["    ", name, "(char * in) {\n"])
            out.extend(["        storage = in;\n"])
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
            out.extend(["    Pointer<Impl::Memcpy<", self.type, "> >::Reference ", self.name, "() {\n"])
            out.extend(["        return *Pointer<Impl::Memcpy<", self.type, "> >(storage +", offset_str, ");\n"])
            out.extend(["    }\n\n"])
        else:
            out.extend(["    Pointer<Impl::Memcpy<", self.type, "> > ", self.name, "() {\n"])
            out.extend(["        return Pointer<Impl::Memcpy<", self.type, "> >(storage +", offset_str, ");\n"])
            out.extend(["    }\n\n"])

        return out

class BITFIELD:
    def __init__(self, root, fields):
        self.fields = fields
        self.root = root

    def sizeof(self):
        return self.root.sizeof()

    def cpp(self, offset_str):
        out = []
        offset = 0

        for field in self.fields:
            bitfield_impl = "Impl::BitField< " + field.type + ", " + self.root.type + ", " + str(offset) + ", " + str(field.bits) + ">"

            out.extend(["    Pointer<", bitfield_impl, " >::Reference ", field.name, "() {\n"])
            out.extend(["        return *Pointer<", bitfield_impl, " >(storage +", offset_str, ");\n"])
            out.extend(["    }\n\n"])

            offset += field.bits

        return out

class BITFIELDFIELD:
    def __init__(self, t, name, bits):
        self.type = t
        self.name = name
        self.bits = bits

class UNION:
    def __init__(self, fields):
        self.fields = fields

    def sizeof(self):
        out = []
        for i in xrange(len(self.fields) - 1):
            out.extend([ "_max< ", self.fields[i].sizeof(), ", "])

        out.append( self.fields[len(self.fields) - 1].sizeof() )

        for i in xrange(len(self.fields) - 1):
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

        for i in xrange(len(fields)):
            offset.append([offset_str])

            for j in xrange(0, i):
                offset[i].append(fields[j].sizeof())

        for i in xrange(len(fields)):
            out.extend(fields[i].cpp(' + '.join(offset[i])))

        return out

class PPSTRUCT:
    def __init__(self, t, name, array = None):
        self.type = t
        self.name = name
        self.array = array

    def sizeof(self):
        if self.array is None:
            return self.type + "::_size"
        else:
            return "(" + self.type + "::_size * " + str(self.array) + ")"

    def cpp(self, offset_str):
        out = []

        if self.array is None:
            out.extend(["    Pointer<Impl::PPS<", self.type, "> >::Reference ", self.name, "() {\n"])
            out.extend(["        return *Pointer<Impl::PPS<", self.type, "> >(storage +", offset_str, ");\n"])
            out.extend(["    }\n\n"])
        else:
            out.extend(["    Pointer<Impl::PPS<", self.type, "> > ", self.name, "() {\n"])
            out.extend(["        return Pointer<Impl::PPS<", self.type, "> >(storage +", offset_str, ");\n"])
            out.extend(["    }\n\n"])
        return out
