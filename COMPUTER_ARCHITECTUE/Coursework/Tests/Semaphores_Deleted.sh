
echo "Semaphores deleted during process"

../start 5 &
sleep 1
../producer 1 5 & 
../consumer 1 &
sleep 4

ipcrm -S 0x56

../consumer 2 &
