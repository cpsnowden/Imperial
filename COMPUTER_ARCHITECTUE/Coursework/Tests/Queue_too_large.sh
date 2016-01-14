echo "Start run with queue = 502"
../start 502 &
sleep 1
../producer 1 4 &
../consumer 1 &

wait
sh CheckClean.sh
