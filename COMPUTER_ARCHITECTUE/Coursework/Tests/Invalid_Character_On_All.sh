echo "Start, producer and consumer run with invalid character"
../start a &
sleep 1
../producer 1 g &
../consumer b &

wait
sh CheckClean.sh
