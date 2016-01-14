echo "No producer or consumer so will timeout after 200s "
../start 5 &
sleep 1

wait
sh CheckClean.sh
