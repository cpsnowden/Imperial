echo "Consumer run with too many arguments, but one consumer correct"
../start 4 &
sleep 1
../producer 1 4 &
../consumer 1 4 &
../consumer 2 &

wait
sh CheckClean.sh
