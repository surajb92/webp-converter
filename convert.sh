#!/bin/bash
nesting=false
wdelete=false
export type=png
#while getopts f:t:n: flag
while getopts "ndf:t:": flag
do
    case ${flag} in
        f) filepath=$OPTARG;;
        t) type=$OPTARG;;
        n) nesting=true;;
        d) wdelete=true;;
    esac
done
#echo "Filepath: $filepath";
#echo "Type: $type";
#echo "Nesting: $nesting";
#echo $wdelete;
cd "$filepath"

if [ $nesting == true ] ; then
    find . -iname '*.webp' -print0 | xargs -n1 -P8 -0I{} sh -c 'convert -quality 100 "{}" "$(dirname "{}")/$(basename -s .webp "{}").$type";'
    if [ $wdelete == true ] ; then
        find . -name "*.webp" -type f -delete
    fi
else
    find . -maxdepth 1 -iname '*.webp' -print0 | xargs -n1 -P8 -0I{} sh -c 'convert -quality 100 "{}" "$(dirname "{}")/$(basename -s .webp "{}").$type";'
    if [ $wdelete == true ] ; then
        find . -maxdepth 1 -name "*.webp" -type f -delete
    fi
fi

#find . -iname '*.webp' -maxdepth 1 -print0 | xargs -n1 -P8 -0I{} sh -c 'convert -quality 100 "{}" "$(dirname "{}")/$(basename -s .webp "{}").$type";'
#find . -iname '*.webp' -print0 | xargs -n1 -P8 -0I{} sh -c 'convert -quality 100 "{}" "$(dirname "{}")/$(basename -s .webp "{}").$type";'
# test -f "/home/suraj/[Coding]/Apps/Webp converter/webp sample/" -t jpg -n -d
