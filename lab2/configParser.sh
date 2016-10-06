#!/bin/bash
file_location=$1
while read -r line
do
	if [[ $line != \#* ]]
	then
		var_parts=(${line//=/ })
		adjusted_var="${var_parts[0]^^}=${var_parts[1]}"
		export $adjusted_var
	fi
done < "$file_location"
