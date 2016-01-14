echo "Semaphores and Memory removed during process, (memory removed on last detach due to ipcrm"

../start 5 &
sleep 1
../producer 1 5 & 
../consumer 1 &
sleep 4
ipcrm -M 0x54
ipcrm -S 0x56

../consumer 2 &
