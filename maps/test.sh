#!/bin/bash
# Runs ./cub3D on every map in maps/good and maps/bad and prints the result.
#   good: the window opens and stays open (it is closed after 2 seconds)
#   bad : the program exits with status 1 and prints "Error" on the first line
# usage: make && bash maps/test.sh

cd "$(dirname "$0")/.." || exit 1
if [ ! -x ./cub3D ]; then
	echo "./cub3D not found: run make first" >&2
	exit 1
fi

pass=0
fail=0
err=$(mktemp)

# Runs ./cub3D for at most 2 seconds. The subshell keeps bash's "Alarm clock" notice out of the output.
run_map() {
	(perl -e 'alarm 2; exec @ARGV' ./cub3D "$1" >/dev/null 2>"$err"; exit $?) 2>/dev/null
}

result() {
	if [ "$1" = ok ]; then
		pass=$((pass + 1))
		printf '  OK    %s\n' "$2"
	else
		fail=$((fail + 1))
		printf '  FAIL  %s  (%s)\n' "$2" "$3"
	fi
}

echo "maps/good"
for map in maps/good/*.cub; do
	run_map "$map"
	status=$?
	if [ $status = 142 ]; then
		result ok "$map"
	else
		result ng "$map" "exit $status: $(head -2 "$err" | tr '\n' ' ')"
	fi
done

echo "maps/bad"
for map in maps/bad/*.cub; do
	run_map "$map"
	status=$?
	if [ $status = 1 ] && [ "$(head -1 "$err")" = "Error" ]; then
		result ok "$map"
	elif [ $status = 142 ]; then
		result ng "$map" "the window opened"
	else
		result ng "$map" "exit $status: $(head -2 "$err" | tr '\n' ' ')"
	fi
done

rm -f "$err"
echo
echo "OK: $pass  FAIL: $fail"
[ $fail = 0 ]
