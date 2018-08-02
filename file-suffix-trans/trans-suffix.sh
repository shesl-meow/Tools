
if [$# -le 1]; then
	echo "missing operate, script requires at least one parameter."
	exit 1
elif [ ! -f *.$1 ]; then
	echo "source file doesn't exist"
	exit 1
fi


for f in *$1; do
	mv "$f" "$(basename "$f" "$1")$2"
done
