#!/bin/bash
type=png
find . -iname '*.webp' -maxdepth 1 -print0 | xargs -n1 -P8 -0I{} sh -c 'echo $(dirname "{}")/$(basename -s .webp "{}").($type)'
#find . -iname '*.webp' -maxdepth 1 -print0 | xargs -n1 -P8 -0I{} sh -c 'convert -quality 100 "{}" "$(dirname "{}")/$(basename -s .webp "{}").$type";'
#find . -iname '*.webp' -print0 | xargs -n1 -P8 -0I{} sh -c 'convert -quality 100 "{}" "$(dirname "{}")/$(basename -s .webp "{}").jpg";'

# test -f "/home/suraj/[Coding]/Apps/Webp converter/webp sample/" -t jpg -n
