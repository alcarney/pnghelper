#!/bin/zsh


# Little function to move the header files 
move_headers(files) 
{
	for f in $1
	do 
		# Only move if they are valid files, otherwise fail silently
		if [[-f $f]]; then 
			echo "\tMoving $f" 
			cp $f ~/.myheaders/pnghelper/
		fi
	done
}

# Change into the src dir 
echo "Entering dir src/"
cd src

# Get a list of subdirs
sub_dirs=$(ls -d */)

#echo $sub_dirs

# Now lets move the headers in the src dir first
move_headers($(ls *.h))

# Now loop through each sub directory
for d in $sub_dirs
do
	echo "Entering dir $d"
	cd $d

	move_headers($(ls *.h))

	cd ..

done 

# Go back to where we started
cd ..
