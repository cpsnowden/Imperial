echo "Memory deleted during process, but the memory won't be deleted until everyone detached"

../start 5 &
sleep 1
../producer 1 5 & 
../consumer 1 &
sleep 4
ipcrm -M 0x54
../consumer 2 &
