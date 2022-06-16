import sys, os

subsdk0Offset = {
    "310" : 0x48DF000
}

DEFAULT_VERS = "310"
SOURCE_DIR = "source"
HOOK_MAGIC = "// hook_from "

def calcJump(from_addr_str, dest_func, vers=DEFAULT_VERS):
    from_addr = int(from_addr_str, 16)
    dest_func = dest_func + "("

    mapFilePath = "build" + vers + "/starlight" + vers + ".map"
    with open(mapFilePath, 'r') as f:
        mapFile = f.read()

    foundPos = mapFile.find(dest_func) - 34
    foundLine = mapFile[foundPos:mapFile.find("\n", foundPos)]

    print("Found:")
    print(foundLine)

    func_addr = int(foundLine[:foundLine.find(" ")], 0)
    jump_offset = subsdk0Offset[vers] + func_addr - from_addr
    print("Jump needed: " + hex(jump_offset))

if len(sys.argv) > 3:
    calcJump(sys.argv[1], sys.argv[2], sys.argv[3])
elif len(sys.argv) > 2:
    calcJump(sys.argv[1], sys.argv[2])
else:
    hasOutput = False
    for root, subdirs, files in os.walk(SOURCE_DIR):
        for file in files:
            with open(root+"/"+file, 'r') as f:
                file_iter = iter(f.readlines())
            for line in file_iter:
                if HOOK_MAGIC in line:
                    hook_addr = line[len(HOOK_MAGIC):-1]
                    line = next(file_iter)
                    hook_func = line[:line.find('(')]
                    hook_func = hook_func[hook_func.rfind(' ') + 1:]
                    calcJump(hook_addr, hook_func)
                    hasOutput = True
            
    if not hasOutput:
        print("Usage: %s [from addr] [to func name] (s2 vers, like '310')" % sys.argv[0])
