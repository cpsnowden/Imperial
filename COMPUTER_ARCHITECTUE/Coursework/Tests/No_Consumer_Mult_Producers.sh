echo "No consumer so producers should timeout:"
../start 5 &
sleep 1
../producer 1 4 &
../producer 2 3 &

wait
sh CheckClean.sh
