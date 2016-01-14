../cleaner


echo "=============Starting Tests============"

(sh Did_not_run_start.sh 2>&1) | tee testOutput.txt
echo " "
(sh Invalid_Character_On_All.sh  2>&1) | tee -a testOutput.txt
echo " "
(sh Invalid_Character_On_Consumer.sh  2>&1) | tee -a testOutput.txt
echo " "
(sh Invalid_Character_On_Producer.sh  2>&1) | tee -a testOutput.txt
echo " "
(sh Invalid_Character_On_Start.sh  2>&1) | tee -a testOutput.txt
echo " "
(sh ManyConsumers.sh  2>&1) | tee -a testOutput.txt
echo " "
(sh Long_Run.sh  2>&1) | tee -a testOutput.txt
echo " "
(sh No_Consumer_Mult_Producers.sh  2>&1) | tee -a testOutput.txt
echo " "
(sh No_Consumer_One_Producers.sh  2>&1) | tee -a testOutput.txt
echo " "
(sh No_Producer.sh  2>&1) | tee -a testOutput.txt
echo " "
(sh Queue_too_large.sh  2>&1) | tee -a testOutput.txt
echo " "
(sh Too_many_consumer_args.sh  2>&1) | tee -a testOutput.txt
echo " "
(sh Too_many_producer_args.sh 2>&1) | tee -a testOutput.txt
echo " "
(sh Too_many_start_args.sh  2>&1) | tee -a testOutput.txt
echo " "
(sh No_Prod_Cons.sh  2>&1) | tee -a testOutput.txt

echo "=============Finished Tests============"
