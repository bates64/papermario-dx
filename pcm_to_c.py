# pcm_to_c.py - Convert 16-bit raw PCM data to C u8 array
# you can export 16-bit PCM data from Audacity (Export Audio .. Other uncompressed files - Header: RAW (header-less))

import sys
import os
import struct

if len(sys.argv) < 2:
  print("usage: python pcm_to_c.py foo.raw")
  sys.exit(1)

filename = sys.argv[1]
basename = os.path.splitext(filename)[0]
c_filename = basename + ".c"

print("Converting %s to %s" % (filename, c_filename))

with open(filename, "rb") as f:
  data = f.read()

# print file size
print("File size: %d bytes" % len(data))

with open(c_filename, "w") as f:
  for i in range(0, len(data), 2):
    # fix endianness
    f.write("0x%02x, 0x%02x, " % (data[i+1], data[i]))
    #f.write("0x%02x, 0x%02x, " % (data[i], data[i+1]))
