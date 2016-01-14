echo "Consumer started with invalid character"
../start 5 &
sleep 1
../producer 1 5 &
../producer 2 2 &
../consumer b &
../consumer 1 &
wait
sh CheckClean.sh
