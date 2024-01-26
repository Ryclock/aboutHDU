mq_ids=$(ipcs -q | awk 'NR > 3 && NF {print $2}')

if [ -n "${mq_ids}" ]; then
  echo "${mq_ids}" | xargs -n 1 ipcrm -q
fi
