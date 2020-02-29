#! /bin/bash
for i in "$@"
do
let "total = i + total"
done
echo "Количество параметров равно $#."
let "total = total / $#"
echo "Среднее арифметическое параметров равно $total."