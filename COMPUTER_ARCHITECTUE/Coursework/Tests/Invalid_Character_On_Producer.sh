echo "Producer started with invalid character"
../start 5 &
sleep 1
../producer a 5 &
../producer 1 2 &
../consumer 1 &
wait
sh CheckClean.sh
