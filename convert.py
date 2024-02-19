from PIL import Image
import getopt,sys

import glob, os
nesting=False
wdelete=False
filetype="png"
#os.chdir("/home/suraj/[Coding]/Apps/Webp converter/webp sample/")
#current_dir = "/home/suraj/[Coding]/Apps/Webp converter/webp sample/"
current_dir=""

try:
    opts, args = getopt.getopt(sys.argv[1:], "ndf:t:")
except getopt.GetoptError as err:
    # print help information and exit:
    print("Improper arguments.")  # will print something like "option -a not recognized"
    usage()
    sys.exit(2)

for o, a in opts:
    if o == "-n":
        nesting = True
    elif o == "-d":
        wdelete = True
    elif o == "-f":
        current_dir = a
    elif o == "-t":
        filetype = a
    else:
        assert False, "Improper arguments"

for root, dirs, files in os.walk(current_dir):
    for file in files:
        if file.endswith(".webp"):
             print(os.path.join(root, file))
             im = Image.open(os.path.join(root, file)).convert("RGB")
             im.save(os.path.join(root, file)[:-4]+filetype)
             #im.save(os.path.join(root, file)[:-4]+"jpg")
             if (wdelete == True): os.remove(os.path.join(root, file))
    if nesting == False: break

#for file in glob.glob("**/*.webp"):
#    print(file)
