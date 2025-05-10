echo "Запуск ./bin/example1 на ядрах 0,1"
taskset -c 0,1 ./bin/example1

echo -e "\nЗапуск ./bin/example2 на ядрах 2,3"
taskset -c 2,3 ./bin/example2

echo -e "\nЗапуск ./bin/example3 на ядрах 4,5"
taskset -c 4,5 ./bin/example3 

echo -e "\nЗапуск ./bin/example4 на ядре 6"
taskset -c 6 ./bin/example4 
