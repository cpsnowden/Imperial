echo "No producer so should timeout and cleanup"
../start 5 &
sleep 1
../consumer 1 &

wait
sh CheckClean.sh
