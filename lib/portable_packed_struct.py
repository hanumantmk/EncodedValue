class CLASS:
    def __init__(self, name, fields):
        self.name = name
        self.fields = fields

    def cpp(self):
        name = self.name
        fields = self.fields
        out = []

        sizeof = ["0"]
        for field in fields:
            sizeof.append(field.sizeof())

        out.extend(["class ", name, " {\n"])

        out.extend(["    char * storage;\n\n"])

        out.extend(["public:\n"])

        out.extend(["    ", name, "(char * storage) : storage(storage) {}\n\n"])

        out.extend(["    int size() {\n"])
        out.extend(["        return ", ' + '.join(sizeof), ";\n"])
        out.extend(["    }\n\n"])

        out.extend(["    void zero() {\n"])
        out.extend(["        std::memset(storage, 0, size());\n"])
        out.extend(["    }\n\n"])

        out.extend(["    char * base() {\n"])
        out.extend(["        return storage;\n"])
        out.extend(["    }\n\n"])

        offset = []

        for i in xrange(len(fields)):
            offset.append(["0"])

            for j in xrange(0, i):
                offset[i].append(fields[j].sizeof())

        for i in xrange(len(fields)):
            out.extend(fields[i].cpp(' + '.join(offset[i])))

        out.extend(["};\n"])

        return ''.join(out)

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
        out.extend(["    char * ptr_to_", self.name, "() {\n"])
        out.extend(["        int off = ", offset_str, ";\n"])
        out.extend(["        return storage + off;\n"])
        out.extend(["    }\n\n"])
        out.extend(["    int size_of_", self.name, "() {\n"])
        out.extend(["        return ", self.sizeof(), ";\n"])
        out.extend(["    }\n\n"])

        if self.array is None:
            out.extend(["    ", self.type, " get_", self.name, "() {\n"])
            out.extend(["        ", self.type, " x;\n\n"])
            out.extend(["        std::memcpy(&x, ptr_to_", self.name, "(), sizeof(", self.type, "));\n"])
            out.extend(["        return x;\n"])
            out.extend(["    }\n\n"])
            out.extend(["    void set_", self.name, "(", self.type, " x) {\n"])
            out.extend(["        std::memcpy(ptr_to_", self.name, "(), &x, sizeof(", self.type, "));\n"])
            out.extend(["        return;\n"])
            out.extend(["    }\n\n"])
        else:
            out.extend(["    int number_of_", self.name, "() {\n"])
            out.extend(["        return ", str(self.array), ";\n"])
            out.extend(["    }\n\n"])
            out.extend(["    ", self.type, " get_", self.name, "(int idx) {\n"])
            out.extend(["        ", self.type, " x;\n\n"])
            out.extend(["        std::memcpy(&x, ptr_to_", self.name, "() + (sizeof(", self.type, ") * idx), sizeof(", self.type, "));\n"])
            out.extend(["        return x;\n"])
            out.extend(["    }\n\n"])
            out.extend(["    void set_", self.name, "(int idx, ", self.type, " x) {\n"])
            out.extend(["        std::memcpy(ptr_to_", self.name, "() + (sizeof(", self.type, ") * idx), &x, sizeof(", self.type, "));\n"])
            out.extend(["        return;\n"])
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
        out.extend(self.root.cpp(offset_str))

        offset = 0

        for field in self.fields:
            out.extend(["    ", field.type, " get_", field.name, "() {\n"])
            out.extend(["        ", self.root.type, " x = get_", self.root.name, "();\n\n"])
            out.extend(["        return ((x >> ", str(offset), ") & ((1 << ", str(field.bits), ") - 1));\n"])
            out.extend(["    }\n\n"])
            out.extend(["    void set_", field.name, "(", field.type, " x) {\n"])
            out.extend(["        ", self.root.type, " y = get_", self.root.name, "();\n\n"])
            out.extend(["        y &= ~(((1 << ", str(field.bits), ") - 1) << ", str(offset), ");\n"]);
            out.extend(["        y |= (x << ", str(offset), ");\n"]);
            out.extend(["        set_", self.root.name, "(y);\n"]);
            out.extend(["    }\n\n"])
            offset += field.bits

        return out

class BITFIELDFIELD:
    def __init__(self, t, name, bits):
        self.type = t
        self.name = name
        self.bits = bits

class UNION:
    def __init__(self, root, fields):
        self.root = root
        self.fields = fields

    def sizeof(self):
        return self.root.sizeof()

    def cpp(self, offset_str):
        out = []
        out.extend(self.root.cpp(offset_str))

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

        return ''.join(out)

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
