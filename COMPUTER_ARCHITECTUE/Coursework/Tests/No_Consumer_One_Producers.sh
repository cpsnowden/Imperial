echo "No consume only one producer so producer so should cleanup:"
../start 5 &
sleep 1
../producer 1 4 &

wait
sh CheckClean.sh
