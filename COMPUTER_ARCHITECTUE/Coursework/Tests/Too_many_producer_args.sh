echo "Producer run with too many arguments, one run correctly"
../start 5 &
sleep 1
../producer 1 4 &
../producer 2 5 7 &
../consumer 1 &

wait
sh CheckClean.sh
