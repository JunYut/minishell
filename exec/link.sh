#!/bin/bash

# Find all .c and .h files excluding main.c, sandbox, and gbc
srcs=$(find .. -type f | grep -E "\.c$|\.h$" | grep -Ev "main.c|sandbox")

# Create symbolic links in the exec directory
for src in $srcs; do
	target="$(basename $src)"

	# Check if the symbolic link already exists
	if [ -L "$target" ]; then
		# Check if the link is valid
		if [ ! -e "$target" ]; then
			echo "Removing broken link: $target"
			rm "$target"
		else
			echo "Link already exists and is valid: $target"
			continue
		fi
	fi

	# Create the symbolic link
	ln -s "$src" "$target"
	echo "Created link: $target -> $src"
done
