# createActorTable.py
# Generates an .h file for defining an array of actors and their creation functions.

arr = []
names = []
classes = []
classes_al = []

with open("createActorFuncs.txt", "r") as f:
    lines = f.readlines()

for line in lines:
    sym = line.split("=")

    blah = sym[1].split("<")

    names.append(blah[1].strip("al::"))

    if "al::" in blah[1]:
        classes_al.append(blah[1].strip("al::"))
    else:
        classes.append(blah[1])

    # this line is awful
    arr.append("\t\t{ (char*)" + "\"" + blah[1].strip("al::\n") + "\"," + " (void*)al::createActorFunction<" + blah[1].strip("\n") + "> },\n")

with open("funcs.h", "w") as w:
    w.write("namespace al\n")
    w.write("{\n")

    for c in classes_al:
        c = c.strip("\n")
        w.write(f"\tclass {c};\n")

    w.write("};\n\n")

    for c in classes:
        c = c.strip("\n")
        w.write(f"class {c};\n")

    w.write("\n")

    w.write("ActorEntry entries[NUM_ACTORS] = {\n")

    for e in arr:
        w.write(e)

    w.write("};")