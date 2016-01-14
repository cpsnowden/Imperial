 echo "Many Consumers"

../start 5 &
sleep 1
../producer 1 15 &
../producer 2 15 &
../producer 3 15 &
../consumer 1 &
../consumer 2 &
../consumer 3 &
../consumer 4 &
../consumer 5 &
../consumer 6 &
../consumer 7 &
../consumer 8 &
../consumer 9 &
../consumer 10 &
../consumer 11 &
../consumer 12 &
../consumer 13 &
../consumer 14 &
../consumer 15 &
../consumer 16 &
../consumer 17 &
../consumer 18 &
../consumer 19 &

wait
sh CheckClean.sh
