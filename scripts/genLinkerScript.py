# genLinkerScript.py
# Generates a linker script based on a given symbol map and base address offset
import sys

symbolExceptions = [ "_init",
					 "_fini",
					 "__nnDetailNintendoSdkRuntimeObjectFileRefer",
					 "__nnDetailNintendoSdkRuntimeObjectFile",
					 "__nnDetailNintendoSdkNsoFileRefer" 
]
symbolPrefixes = [ 
					"Curl", # some curl stuff
					"curl", # moar curl
					# "_ZG",  # guards
					# "_ZN",  # regular variables
					# "_ZT",  # typeinfo / vtables
					# "_ZZ",
					"_Z",   # literally everything
					"pfnc_",
					"mem",
					"str"
					"alloc",
					"malloc",
					"free",
					"calloc",
					"realloc",
					"aligned_alloc",
					"malloc_usable_size"
]

if len(sys.argv) < 3:
	print("Syntax: genLinkerScript.py <map> <sizeFromMain>\n")
	sys.exit()

# open our map file
with open(sys.argv[1], "r") as f:
	lines = f.readlines()

# open our new generated linker
with open("syms.ld", "w") as linker:

	# we need to skip a few lines first
	curLine = 0
	for line in lines:
		# each line is structured as such:
		#  00000000:0000007100000160       _fini
		firstSplit = line.split(" ")
		if len(firstSplit) <= 1:
			continue
		
		addressSplit = firstSplit[1].split(":")
		if len(addressSplit) <= 1:
			continue

		address = addressSplit[1]
		
		symbolName = firstSplit[8]
		symbolName = symbolName.strip("\n\r")
		
		# the last few numbers are important, the higher ones are not
		address = address[9:]
		address = "0x" + address
	
		# we check to see if this symbol has a prefix that we need to keep
		if (any([symbolName.startswith(symbolPrefix)
				for symbolPrefix in symbolPrefixes])
				or symbolName in symbolExceptions):

			# skip the first 5 useless lines
			if curLine < 5:
				curLine += 1
				continue

			# sdk functions have a _0 at the end because they are duplicated
			# due to the originals being imported, so IDA adds a _0 at the
			# end... we need to strip this
			if symbolName.endswith("_0"):
				symbolName = symbolName[:-2]
			
			linker.write(
				"{} = {} - {};\n".format(symbolName, address, sys.argv[2]))
	
print("Linker script generated.")
