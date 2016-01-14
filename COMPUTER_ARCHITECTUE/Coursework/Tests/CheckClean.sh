ipcs | grep "0x00000054"
if [ $? -eq 0 ]; then
    echo "Test Failed - Mem" 1>&2
else
    echo "Test Passed - Mem" 1>&2
fi
ipcs | grep "0x00000056"
if [ $? -eq 0 ]; then
    echo "Test Failed - Sem" 1>&2
else
    echo "Test Passed - Sem" 1>&2
fi
