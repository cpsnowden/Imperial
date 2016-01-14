echo "Start run with too many arguments"
../start 4 6 &
sleep 1
../producer 1 4 &
../consumer 1 &

wait
sh CheckClean.sh
