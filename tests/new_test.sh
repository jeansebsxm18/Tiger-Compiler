#!/bin/sh

DIR="all_tests/*"

echo "Creating a new test..."
echo "What directory ?"

for d in $DIR
do
	dir="${d#*/}"
	echo -n "$dir"
	echo -n "  "
done
echo
read -p "Select: " input_dir

#check nb test in input_dir
i=0

FILES="all_tests/$input_dir/*"
for f in $FILES
do
	i=$((i + 1))
done	


#Error message
echo "Error message:"
read -p ">" input_error

#Code
echo "Write your code:"
echo "Press 'q' to exit"
touch code
while : ; do
	read -p "" input_code
	case "$input_code" in
		"q")
			break
			;;
	esac
	echo $input_code >> code
done

#Creating test file
touch $input_file.tig
echo "/* error : $input_error */" >> $input_file
echo "" >> $input_file
cat code >> $input_file

rm code
mv $input_file all_tests/$input_dir/

input_file="test$i.tig"
FILE=all_tests/$input_dir/$input_file
if test -f "$FILE"
then
    echo "$FILE exists."
else
	echo "Error"
	exit 1
fi

echo "A new test has been created !"
