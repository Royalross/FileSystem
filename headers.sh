#! /bin/sh

# this code is by Kyle Rosenberg augmenting code by
# Neil Kirby


# name that will be inserted at the top of each header file
# YOU MUST CHANGE THIS TO YOUR NAME BEFORE USING THIS FILE
# TURNING IN CODE WITH ANOTHER STUDENTS NAME IN IT IS A COAM OFFENSE
# - Professor Kirby
readonly AUTHOR_NAME="Royalross"

# do the mystery that professor Kirby did for us
echo "Creating header files..."
echo "new visible sysmbols..."
ctags -x --c-kinds=f --file-scope=no *.c | awk -f headers.awk
echo "updating changed visible symbols"
for f in *.nvs ; do
    [ -f "$f" ] || break
    # get the .vs filename from the .nvs filename
    filename="$(basename $f .nvs).vs"
    # echo "...checking $filename"
    diff $filename $f >/dev/null 2>&1
    #what did diff return?
    error=$?
    if [ $error -eq 0 ]
    then
    	# echo "    no change to $filename"
	rm $f
    else
    	echo "   need to update $filename"
    fi
done

echo "creating headers from changed visible sysmbols"
# create the header files from the visible symbols professor Kirby did for us
for nf in *.nvs; do
    [ -f "$nf" ] || break

    # get the name of the file with the .h and .vs extension
    filename="$(basename $nf .nvs).h"
    f="$(basename $nf .nvs).vs"

    # echo "    Moving $nf to $f"
    mv $nf $f

    # notify the user we are crafting them a delicous header file
    echo -e "\tcreating $filename from $f"

    # clear the file and write the aution comment string
    echo -e "/* $AUTHOR_NAME */\n" > $filename
    
    # append everything in the visible symbol files
    cat $f >> $filename
done

date > headers
echo "Done creating headers."
