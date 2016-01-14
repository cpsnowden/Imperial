echo "Start run with invalid character"
../start a &
sleep 1
../consumer 1 &

wait
sh CheckClean.sh
