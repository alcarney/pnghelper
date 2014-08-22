#!/bin/zsh


# Little function to move the header files 
move_headers() 
{
	for f in $(ls)
	do 
		#echo $f

		# Only move if they are valid files ending in .h, otherwise fail silently
		if [[ -f $f && $f == *.h ]]; then 
			echo "\tMoving $f" 
			cp $f ~/.myheaders/pnghelper/
		fi
	done
}

# Change into the src dir 
echo "Entering dir src/"
cd src

# Now lets move the headers in the src dir first
move_headers

# Now loop through each sub directory and do the same
for d in $(ls -d */)
do
	echo "Entering dir $d"
	cd $d
	move_headers
	cd ..
done 

# Go back to where we started
cd ..
