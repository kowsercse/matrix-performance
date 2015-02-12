rm -rf *.out

codes=( naive loop_interchange block register prefetch loop_unrolling )

output="size"
for code in ${codes[@]}
do
	# echo matmul_${code}.c
	output="$output, $code"
	gcc matmul_${code}.c -O0 -o $code.out
done
for code in ${codes[@]}
do
	# echo matmul_${code}.c
	output="$output, $code"
	gcc matmul_${code}.c -O3 -o ${code}3.out
done
echo $output

for size in 400 1200 1600 2000
do
	output=$size
	for code in ${codes[@]}
	do
		out=$(./$code.out $size $size $size)
		output="$output, $out"
	done
	for code in ${codes[@]}
	do
		out=$(./${code}3.out $size $size $size)
		output="$output, $out"
	done
	echo $output
done
