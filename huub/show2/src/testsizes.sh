
dt=$(date '+%Y%m%dT%H%M')
logfile="testrun${dt}.log"
echo "# testrun at ${dt}" > ${logfile}
for rawsize in $(<sizes.txt)
do
	size=$(($rawsize))
	echo "# time $(date '+%Y/%m/%d %H:%M:%S') size ${size}" >> "${logfile}"
	respt1 $size  >> "${logfile}"
done
