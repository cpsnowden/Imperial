echo "./start not run so no memory setup::"
../producer 1 3 &
../producer 2 3 &
../consumer 1 &

wait
sh CheckClean.sh
